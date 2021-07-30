// IDEDOS_SystemPartition.cpp: implementation of the CIDEDOS_SystemPartition class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3eExplorer.h"
#include "IDEDOS_SystemPartition.h"
#include "3eExplorerDoc.h"
#include "IDEDOS_Plus3DOSPartition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIDEDOS_SystemPartition::CIDEDOS_SystemPartition(CMy3eExplorerDoc * _p3eDoc, char * block, unsigned int _tt)
: CIDEDOSPartitionDefinition(_p3eDoc, PARTITION_PLUSIDEDOS, block)
, m_start_track(_tt)
{
	// copy the additional part of the definition
	::CopyMemory(&m_system_partition, &block[0x20], sizeof(m_system_partition));
}

CIDEDOS_SystemPartition::~CIDEDOS_SystemPartition()
{

}

std::string CIDEDOS_SystemPartition::GetInformation()
{
	std::ostringstream ostr;
	ostr << "PLUSIDEDOS System Partition" << "\r\n";
	ostr << CIDEDOSPartitionDefinition::GetInformation() << "\r\n";
	ostr << "CHT : " << m_system_partition.g_cylinders() << "/" << m_system_partition.g_heads() << "/" << m_system_partition.g_tracks() << "\r\n";
	ostr << "      " << m_system_partition.g_sectors_per_cylinder() << " sectors per cylinder\r\n";
	ostr << "max : " << m_system_partition.g_partitions_allowed() << " partitions";
	return(ostr.str());
}

void CIDEDOS_SystemPartition::ParseForChildren()
{
	// here we want to parse the system partition to find any _real_ partitions.

	if (NULL != m_p3eDoc && !m_bParsedForChildren)
	{
		m_bParsedForChildren = TRUE;

		try
		{
			char * ss_buff;
			unsigned int curr_sect = 0;
			const unsigned int max_sect = m_p3eDoc->GetRoot()->getSectors();
			unsigned int sect_offset = m_partition_entry_size;
			const unsigned int max_offset = m_p3eDoc->GetRoot()->getSectorSize();

			// *** to do - system partition taking more than one track ***

			// for the moment we're only supporting type 0x03 (+3dos)
			// for other partitions we'll create a childless CTreeObject
			m_p3eDoc->ReadSector(CCHS(0, m_start_track, curr_sect), &ss_buff);

			while (curr_sect < max_sect)
			{
				char * block = &ss_buff[sect_offset];
				switch ((unsigned char)block[0x10])
				{
				case CIDEDOSPartitionDefinition::PLUS3DOS:
					{
						// it's a +3dos partition
						CIDEDOS_Plus3DOSPartition *cplus3dos = new CIDEDOS_Plus3DOSPartition(m_p3eDoc, block);
						m_vChildren.push_back(cplus3dos);
					}
					break;
				case CIDEDOSPartitionDefinition::UNUSED:
				case CIDEDOSPartitionDefinition::BAD_SPACE:
				case CIDEDOSPartitionDefinition::FREE_SPACE:
					// we can ignore these
					break;
				default:
					{
						// it's an unsupported partition
						CIDEDOSPartitionDefinition *partition = new CIDEDOSPartitionDefinition(m_p3eDoc, CTreeObject::INVALID, block);
						m_vChildren.push_back(partition);
					}
					break;
				}

				sect_offset += m_partition_entry_size;
				if (sect_offset >= max_offset)
				{
					// reached the end of this sector, so see if we read in the next...
					sect_offset = 0x00;
					++curr_sect;
					if (curr_sect < max_sect)
					{
						m_p3eDoc->ReadSector(CCHS(0, m_start_track, curr_sect), &ss_buff);
					}
				}
			}
		}
		catch (CFileException *e)
		{
			m_p3eDoc->ReportSaveLoadException(m_p3eDoc->Filename().c_str(), e, FALSE, IDS_FILE_ACCESS_ERROR);
		}
	}
}
