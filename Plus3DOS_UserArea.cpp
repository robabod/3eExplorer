// Plus3DOS_UserArea.cpp: implementation of the CPlus3DOS_UserArea class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3eExplorer.h"
#include "Plus3DOS_UserArea.h"
#include "Plus3DOS_DirectoryEntry.h"
#include "3eExplorerDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

std::map<BYTE, std::string> CPlus3DOS_UserArea::user_area_id;

CPlus3DOS_UserArea::CPlus3DOS_UserArea(CMy3eExplorerDoc * _p3eDoc, BYTE _id, std::string _partition_name, unsigned int _cc, unsigned int _tt, unsigned int _ss, unsigned int _max_dir_entries, const CIDEDOS_Plus3DOSPartition *_partition)
: CTreeObject(_p3eDoc)
, m_start_cc(_cc)
, m_start_tt(_tt)
, m_start_ss(_ss)
, m_max_dir_entries(_max_dir_entries)
, m_user_id(_id)
, m_partition(_partition)
{
	if (0 == user_area_id.size())
	{
		// initialised the static map
		user_area_id[0x00] = "0:";
		user_area_id[0x01] = "1:";
		user_area_id[0x02] = "2:";
		user_area_id[0x03] = "3:";
		user_area_id[0x04] = "4:";
		user_area_id[0x05] = "5:";
		user_area_id[0x06] = "6:";
		user_area_id[0x07] = "7:";
		user_area_id[0x08] = "8:";
		user_area_id[0x09] = "9:";
		user_area_id[0x0a] = "a:";
		user_area_id[0x0b] = "b:";
		user_area_id[0x0c] = "c:";
		user_area_id[0x0d] = "d:";
		user_area_id[0x0e] = "e:";
		user_area_id[0x0f] = "f:";
		user_area_id[0xe5] = "x:";
	}

	// first a little bit of "protection"
	// check that the user-area if valid. 0x00..0x0f, or 0xe5
	// if _id isn't one of those, throw an exception.

	std::map<BYTE, std::string>::iterator it = user_area_id.find(_id);

	if (it != user_area_id.end())
	{
		// we're ok
		if ((BYTE)0xe5 == _id)
		{
			m_tType = CTreeObject::PLUS3DOS_USER_DIRECTORY_ERASED;
		}
		else
		{
			m_tType = CTreeObject::PLUS3DOS_USER_DIRECTORY;
		}

		m_strName = (*it).second;
		m_strName += _partition_name;
	}
	else
	{
		// not a valid user area, so throw an exception
		std::ostringstream except;
		except << std::ios::hex << _id << " is not a valid user area";
		throw EUserAreaInvalid(except.str());
	}

	// allow extraction of the contents of this user area...
	//m_bExtractable = TRUE;
}

CPlus3DOS_UserArea::~CPlus3DOS_UserArea()
{

}

std::string CPlus3DOS_UserArea::GetInformation()
{
	std::ostringstream ostr;
	ostr << "User Partition: " << (int)m_user_id << "\r\n";
	ostr << "You can call me " << GetName();
	return (ostr.str());
}

void CPlus3DOS_UserArea::ParseForChildren()
{
	// here we want to go through the directory entries finding any from our user-area
	// and adding them.
	// note that if our user-area of 0xe5 it means we are "deleted files".

	// mostly this is very similar to the code in CIDEDOS_Plus3DOSPartition::ParseForChildren
	// however, we need to remember that a single file can take up several directory entries.
	// so... we'll temporarily store new CPlus3DOS_DirectoryEntry objects in a map based on name.

	// go through the directory entries and find an entry of this user id
	char * ss_buff = NULL;
	unsigned int dir_pointer = 0;
	unsigned int sector_size = m_p3eDoc->ReadSector(CCHS(m_start_cc, m_start_tt, m_start_ss), &ss_buff);

	unsigned int cur_dir_entry = 0;

	const unsigned int dir_entry_size = sizeof(CPlus3DOS_DirectoryEntry::T_IDEDOS_PLUS3DOS_DIRECTORY_ENTRY);

	std::map<std::string, CPlus3DOS_DirectoryEntry*> files;

	CTreeObject::TreeObjectType file_type = CTreeObject::PLUS3DOS_FILE;
	if (0xe5 == m_user_id)
	{
		file_type = CTreeObject::PLUS3DOS_FILE_ERASED;
	}

	do
	{
		// map the current directory entry
		CPlus3DOS_DirectoryEntry::T_IDEDOS_PLUS3DOS_DIRECTORY_ENTRY *dir_entry;
		dir_entry = reinterpret_cast<CPlus3DOS_DirectoryEntry::T_IDEDOS_PLUS3DOS_DIRECTORY_ENTRY*>(&ss_buff[dir_pointer]);

		bool valid = false;

		// check the type
		if (dir_entry->user_number == m_user_id)
		{
			// we may have an entry... if it's 0xe5 it could simply be blank, so check the remaining bytes...
			if (0xe5 == m_user_id)
			{
				// for now, just check the first byte of the filename...
				if (0xe5 != dir_entry->filename[0])
				{
					valid = true;
				}
			}
			else
			{
				valid = true;
			}

			if (valid)
			{
				// ok. first up, check to see if this filename already exists...
				std::string filename;
				filename.append(reinterpret_cast<char*>(dir_entry->filename), 8);
				filename.append(reinterpret_cast<char*>(dir_entry->ext.extension), 3);

				std::map<std::string, CPlus3DOS_DirectoryEntry*>::iterator it = files.find(filename);

				if (it == files.end())
				{
					// it's a new entry so create it
					// note, we're passing in the parent partition, so we can get xdpb information
					CPlus3DOS_DirectoryEntry *obj = new CPlus3DOS_DirectoryEntry(m_p3eDoc, file_type, &ss_buff[dir_pointer], m_partition);
					files[filename] = obj;
				}
				else
				{
					// it's most likely a continuation, so we need to add it to an existing object
					(*it).second->AddExtent(&ss_buff[dir_pointer]);
				}

				// create a new directory entry and add it here.
				//CPlus3DOS_DirectoryEntry *directory = new CPlus3DOS_UserArea(user_id, GetName(), start_cyl, start_trk, start_sec, max_dir_entries);
				//m_vChildren.push_back(user_area);
			}
		}

		// select next directory entry
		cur_dir_entry++;
		if (cur_dir_entry < m_max_dir_entries)
		{
			dir_pointer += dir_entry_size;
			if (dir_pointer >= sector_size)
			{
				dir_pointer = 0;
				// read the next sector
				sector_size = m_p3eDoc->ReadNextSector(&ss_buff);
			}
		}
	} while (cur_dir_entry < m_max_dir_entries);


	// now we've done that, we want to step through the map we made and push them into m_vChildren
	std::map<std::string, CPlus3DOS_DirectoryEntry*>::iterator it = files.begin();

	while (it != files.end())
	{
		// should we pre-read the file info?
		if (theApp.PreReadFileInfo())
		{
			(*it).second->ExamineHeader();
		}
		m_vChildren.push_back((*it).second);
		++it;
	}

	// phew, now we can ensure this doesn't happen again...
	CTreeObject::ParseForChildren();
}

void CPlus3DOS_UserArea::ExtractObject(CExplorerFile::TEXTRACTABLE_FORMATS _format, bool _include_header)
{
	// here we should create a new directory and set that as our "current" dir.
}
