// HdfHeader.cpp: implementation of the CHdfHeader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3eExplorer.h"
#include "HdfHeader.h"

#include "3eExplorerDoc.h"

#include "IDEDOS_SystemPartition.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

std::string CHdfHeader::HDF_Signature("RS-IDE");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHdfHeader::CHdfHeader(CMy3eExplorerDoc * _p3eDoc, char * block, const int blocksize, const char * _name)
: CTreeObject(_p3eDoc, HDF, _name, true)
, bHalvedSectorData(FALSE)
, bHalfWordUsed(FALSE)
{
	if (0x80 > blocksize)
	{
		// we should throw an exception here
		throw EHdfInvalid("File is invalid");
	}
	else
	{
		// check that it's the right filetype from the first few bytes
		std::string header;
		header.append(block, 6);
		if (!HDF_Signature.compare(header) && 0x1a == block[0x06])
		{
			// check the revision
			revision = block[0x07];
			if (0x10 != revision && 0x11 != revision)
			{
				// it's not an acceptable revision of the HDF format
				std::ostringstream except;
				int major = (revision >> 4);
				int minor = (revision & 0x0f);
				except << "Revision " << major << "." << minor << " of HDF format not supported";
				throw EHdfUnsupported(except.str());
			}
			else
			{
				// we're ok so get more values...
				bHalvedSectorData = block[0x08] & 0x01;
				bATAPIDevice = block[0x08] & 0x02;

				// for the moment ATAPI is not supported - sorry
				if (0x11 == revision && bATAPIDevice)
				{
					throw EHdfUnsupported("ATAPI Devices are not currently supported, sorry.");
				}

				image_offset = *(reinterpret_cast<WORD*>(&block[0x09]));
				bOffset_valid = FALSE;

				// verify this offset, tho' it doesn't actually matter
				if ((0x10 == revision && 0x0080 == image_offset) ||
					(0x11 == revision && 0x0216 == image_offset))
				{
					bOffset_valid = TRUE;
				}

				// now copy (some of) the rest of the block into the ATA Device ID output
				::CopyMemory(&ata_device_id, &block[0x16], sizeof(T_ATA_Device_ID));
			}
		}
		else
		{
			// throw an exception
			throw EHdfInvalid("Not an HDF image - incorrect magic");
		}
	}
}

CHdfHeader::~CHdfHeader()
{

}

void CHdfHeader::getCHS(CCHS &_chs) const
{
	_chs.c = getCylinders();
	_chs.h = getHeads();
	_chs.s = getSectors();
}

unsigned int CHdfHeader::getOffset() const
{
	return image_offset;
}

unsigned int CHdfHeader::getCylinders() const
{
	return ata_device_id.cylinders;
}

unsigned int CHdfHeader::getHeads() const
{
	return ata_device_id.heads;
}

unsigned int CHdfHeader::getSectors() const
{
	return ata_device_id.sectors;
}

unsigned int CHdfHeader::getSectorSize()
{
	// need to parse this now, or the sector size could be wrong
	ParseForChildren();
	return bHalvedSectorData || bHalfWordUsed ? 256 : 512;
}

void CHdfHeader::ParseForChildren()
{
	if (NULL != m_p3eDoc && !m_bParsedForChildren)
	{
		m_bParsedForChildren = TRUE;
		// this is an HDF, so parse the first sector...
		// the first item _must_ be a PLUSIDEDOS partition.
		// or... it could be on the second track :]
		// so we'll validate it...
		try
		{
			CCHS chs(0,0,0);
			char * ss_buff;
			std::string header = "PLUSIDEDOS      ";
			std::string block;

			m_p3eDoc->ReadSector(chs, &ss_buff);
			block.append(ss_buff, 0x10);
			if (header.compare(block) || CIDEDOSPartitionDefinition::SYSTEM != ss_buff[0x10])
			{
				// try the next track
				++chs.h;
				m_p3eDoc->ReadSector(chs, &ss_buff);
				block = "";
				block.append(ss_buff, 0x10);
				if (header.compare(block) || CIDEDOSPartitionDefinition::SYSTEM != ss_buff[0x10])
				{
					// ok, it's still not valid.
					// we'll try the same thing but with half-word data...
					m_p3eDoc->FlushCache();
					bHalfWordUsed = TRUE;
					--chs.h;
					m_p3eDoc->ReadSector(chs, &ss_buff);
					block = "";
					block.append(ss_buff, 0x10);
					if (header.compare(block) || CIDEDOSPartitionDefinition::SYSTEM != ss_buff[0x10])
					{
						++chs.h;
						m_p3eDoc->ReadSector(chs, &ss_buff);
						block = "";
						block.append(ss_buff, 0x10);
					}
				}
			}

			if (!header.compare(block) && CIDEDOSPartitionDefinition::SYSTEM == ss_buff[0x10])
			{
				// it's a valid PLUSIDEDOS image
				// create a new object (system partition) and add it as a child
				CIDEDOS_SystemPartition *cide_sys = new CIDEDOS_SystemPartition(m_p3eDoc, ss_buff, chs.h);
				m_vChildren.push_back(cide_sys);
			}
			else
			{
				throw EHdfInvalid("Not a PLUSIDEDOS image");
			}
		}
		catch (CFileException *e)
		{
			m_p3eDoc->ReportSaveLoadException(m_p3eDoc->Filename().c_str(), e, FALSE, IDS_FILE_ACCESS_ERROR);
		}
		catch (EHdfInvalid &e)
		{
			::AfxMessageBox(e.what(), MB_ICONEXCLAMATION | MB_OK);
		}
	}
}

std::string CHdfHeader::GetInformation()
{
	std::ostringstream ostr;
	ostr << "HDF: " << GetName() << "\r\n";
	ostr << "CHS: " << getCylinders() << "/" << getHeads() << "/" << getSectors() << "\r\n";
	ostr << "Sec: " << getSectorSize() << " bytes";
	if (bHalfWordUsed)
		ostr << " : half-word mode";
	return(ostr.str());
}
