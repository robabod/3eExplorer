// IDEDOS_Plus3DOSPartition.cpp: implementation of the CIDEDOS_Plus3DOSPartition class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3eExplorer.h"
#include "IDEDOS_Plus3DOSPartition.h"
#include "3eExplorerDoc.h"
#include "Plus3DOS_UserArea.h"
#include "Plus3DOS_DirectoryEntry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIDEDOS_Plus3DOSPartition::CIDEDOS_Plus3DOSPartition(CMy3eExplorerDoc * _p3eDoc, char * block)
: CIDEDOSPartitionDefinition(_p3eDoc, PARTITION_PLUS3DOS, block)
, m_block_size(0)
{
	::CopyMemory(&m_plus3dos_partition, &block[0x20], sizeof(m_plus3dos_partition));
	m_block_size = 0x80 << (m_plus3dos_partition.bsh);
}

CIDEDOS_Plus3DOSPartition::~CIDEDOS_Plus3DOSPartition()
{

}

void CIDEDOS_Plus3DOSPartition::ParseForChildren()
{
	//CTreeObject::ParseForChildren(p3eDoc);

	// here we want to go through the directory entries checking for
	// files in various user areas (0-f and e5).

	// first work out what the values are to pass into user-area constructors...
	// this is: area_id, partition_name, start cyl/track/sector, and max_dir_entries
	unsigned int start_cyl = m_idedos_partition.g_cylinder_start();
	unsigned int start_trk = m_idedos_partition.g_head_start() + m_plus3dos_partition.g_off();
	unsigned int start_sec = 0;
	unsigned int max_dir_entries = m_plus3dos_partition.g_drm() + 1;
	const unsigned int max_heads_per_cylinder = m_p3eDoc->GetRoot()->getHeads();

	// we should also check the allocation mask to see how many blocks (128 << bsh) the directory takes up.
	// for now we'll assume the mask will be all in the top bits.
	// this may not be the case, but we can fix that later.
	//WORD directory_mask = AllocationMask();
	//int block_count = 0;
	//while (directory_mask & 0x8000)
	//{
	//	block_count++;
	//	directory_mask <<= 1;
	//}

	// now work out how many sectors that would be...
	//const int sectors_of_directory = ((block_count * BlockSize()) / m_p3eDoc->GetRoot()->getSectorSize());

	// ensure start cylinder and track is valid
	start_cyl += (start_trk / max_heads_per_cylinder);
	start_trk %= max_heads_per_cylinder;

	// now we want to go through the whole directory area, searching for files in the various user areas.
	// as soon as we find a file, we stop searching, create that user area, and search for the next.
	const unsigned int dir_entry_size = sizeof(CPlus3DOS_DirectoryEntry::T_IDEDOS_PLUS3DOS_DIRECTORY_ENTRY);


	for (BYTE user_id = 0x00; user_id <= 0xe5; user_id++)
	{
		// a bit hacky, but...
		if ((0x00 <= user_id && 0x0f >= user_id) || 0xe5 == user_id)
		{
			// go through the directory entries and find an entry of this user id
			char * ss_buff = NULL;
			unsigned int dir_pointer = 0;
			unsigned int sector_size = m_p3eDoc->ReadSector(CCHS(start_cyl, start_trk, start_sec), &ss_buff);

			bool found = false;
			unsigned int cur_dir_entry = 0;

			do
			{
				// map the current directory entry
				CPlus3DOS_DirectoryEntry::T_IDEDOS_PLUS3DOS_DIRECTORY_ENTRY *dir_entry;
				dir_entry = reinterpret_cast<CPlus3DOS_DirectoryEntry::T_IDEDOS_PLUS3DOS_DIRECTORY_ENTRY*>(&ss_buff[dir_pointer]);

				// check the type
				if (dir_entry->user_number == user_id)
				{
					// we may have an entry... if it's 0xe5 it could simply be blank, so check the remaining bytes...
					if (0xe5 == user_id)
					{
						// for now, just check the first byte of the filename...
						if (0xe5 != dir_entry->filename[0])
						{
							found = true;
						}
					}
					else
					{
						found = true;
					}

					if (found)
					{
						// create a new user-area and add it here.
						// note, we're passing in this partition, so we can get xdpb information
						CPlus3DOS_UserArea *user_area = new CPlus3DOS_UserArea(m_p3eDoc, user_id, GetName(), start_cyl, start_trk, start_sec, max_dir_entries, this);
						m_vChildren.push_back(user_area);
					}
				}

				// done...
				if (!found)
				{
					// select next directory entry
					cur_dir_entry++;
					if (cur_dir_entry < max_dir_entries)
					{
						dir_pointer += dir_entry_size;
						if (dir_pointer >= sector_size)
						{
							dir_pointer = 0;
							// read the next sector
							sector_size = m_p3eDoc->ReadNextSector(&ss_buff);
						}
					}
				}
			} while (!found && cur_dir_entry < max_dir_entries);
		}
		// else it's not a valid user area code so ignore
	}

	CTreeObject::ParseForChildren();
}

std::string CIDEDOS_Plus3DOSPartition::GetInformation()
{
	std::ostringstream ostr;
	ostr << "+3DOS: " << GetName() << "\r\n";
	ostr << CIDEDOSPartitionDefinition::GetInformation() << "\r\n\r\n";

	ostr << "XDPB Structure:\r\n";
	ostr << "spt   : " << m_plus3dos_partition.g_spt() << "\r\n";
	ostr << "bsh   : " << m_plus3dos_partition.g_bsh() << "\r\n";
	ostr << "blm   : " << m_plus3dos_partition.g_blm() << "\r\n";
	ostr << "exm   : " << m_plus3dos_partition.g_exm() << "\r\n";
	ostr << "dsm   : " << m_plus3dos_partition.g_dsm() << "\r\n";
	ostr << "drm   : " << m_plus3dos_partition.g_drm() << "\r\n";
	ostr << "al0   : " << m_plus3dos_partition.g_al0() << "\r\n";
	ostr << "al1   : " << m_plus3dos_partition.g_al1() << "\r\n";
	ostr << "cks   : " << m_plus3dos_partition.g_cks() << "\r\n";
	ostr << "off   : " << m_plus3dos_partition.g_off() << "\r\n";
	ostr << "psh   : " << m_plus3dos_partition.g_psh() << "\r\n";
	ostr << "phm   : " << m_plus3dos_partition.g_phm() << "\r\n";
	ostr << "sidedness                    : " << m_plus3dos_partition.g_sidedness() << "\r\n";
	ostr << "tracks_per_side              : " << m_plus3dos_partition.g_tracks_per_side() << "\r\n";
	ostr << "sectors_per_track            : " << m_plus3dos_partition.g_sectors_per_track() << "\r\n";
	ostr << "first_physical_sector_number : " << m_plus3dos_partition.g_first_physical_sector_number() << "\r\n";
	ostr << "sector_size                  : " << m_plus3dos_partition.g_sector_size() << "\r\n";
	ostr << "upd765a_rw_gap               : " << m_plus3dos_partition.g_upd765a_rw_gap() << "\r\n";
	ostr << "upd765a_format_gap           : " << m_plus3dos_partition.g_upd765a_format_gap() << "\r\n";
	ostr << "multitrack_flags             : " << m_plus3dos_partition.g_multitrack_flags() << "\r\n";
	ostr << "freeze_flag                  : " << m_plus3dos_partition.g_freeze_flag();

	return(ostr.str());
}


bool CIDEDOS_Plus3DOSPartition::BlockToCHS(WORD _block, CCHS &_chs) const
{
	// this method translates a block to a chs.
	// the return value is true if the value is safe to use, false if it lies outside this partition

	// first get the sector number...
	unsigned int full_sector = _block * (BlockSize() / m_p3eDoc->GetRoot()->getSectorSize());

	// now apply the offsets due to the position of this partition
	unsigned int start_cyl = m_idedos_partition.g_cylinder_start();
	unsigned int start_trk = m_idedos_partition.g_head_start();

	full_sector += (start_trk * m_p3eDoc->GetRoot()->getSectors());
	full_sector += (start_cyl * (m_p3eDoc->GetRoot()->getSectors() * m_p3eDoc->GetRoot()->getHeads()));

	// now full_sector is the sector number...
	// we want to convert this to a CHS...
	_chs.c = full_sector / (m_p3eDoc->GetRoot()->getSectors() * m_p3eDoc->GetRoot()->getHeads());
	full_sector -= _chs.c * (m_p3eDoc->GetRoot()->getSectors() * m_p3eDoc->GetRoot()->getHeads());

	_chs.h = full_sector / m_p3eDoc->GetRoot()->getSectors();
	full_sector -= _chs.h * m_p3eDoc->GetRoot()->getSectors();

	_chs.s = full_sector;

	return true;
}
