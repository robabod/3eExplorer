// Plus3DOS_DirectoryEntry.cpp: implementation of the CPlus3DOS_DirectoryEntry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3eExplorer.h"
#include "3eExplorerDoc.h"
#include "Plus3DOS_DirectoryEntry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

std::string CPlus3DOS_DirectoryEntry::PLUS3DOS_Signature("PLUS3DOS");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlus3DOS_DirectoryEntry::CPlus3DOS_DirectoryEntry(CMy3eExplorerDoc * _p3eDoc, TreeObjectType _type, char * block, const CIDEDOS_Plus3DOSPartition *_partition)
:CTreeObject(_p3eDoc, _type, _T(""), false, true)
, m_pPartition(_partition)
, m_bHeaderExamined(false)
, m_bHeaderless(true)	// assume headerless until we know otherwise
, m_filetype(CExplorerFile::CODE)
, m_param1(0x0000)
, m_param2(0x8000)
, m_disk_file_length(0x00000080)
, m_filesize(0x0000)
, m_issue(0x00)
, m_version(0x00)
{
	const T_IDEDOS_PLUS3DOS_DIRECTORY_ENTRY *directory_entry = reinterpret_cast<T_IDEDOS_PLUS3DOS_DIRECTORY_ENTRY*>(block);

	// sort out the filename...
	int fn_count = 8;
	while (0x20 == directory_entry->filename[fn_count - 1] && fn_count)
		--fn_count;

	m_strName.append(reinterpret_cast<const char*>(directory_entry->filename), fn_count);

	fn_count = 0;
	std::string extension;
	// note that the extension is the top 7 bits
	while (0x20 != (0x7f & directory_entry->ext.extension[fn_count]) && fn_count < 3)
	{
		char ext_c = 0x7f & directory_entry->ext.extension[fn_count];
		extension.append(&ext_c, 1);
		fn_count++;
	}
	if (extension.size())
	{
		m_strName += ".";
		m_strName += extension;
	}

	// create this extent (it may not be the first, you know)
	AddExtent(block);
}

CPlus3DOS_DirectoryEntry::~CPlus3DOS_DirectoryEntry()
{

}

void CPlus3DOS_DirectoryEntry::AddExtent(char *block)
{
	// this method allows us to add an extent, should there be one, to this directory entry
	// an extent is an additional directory entry which lists additional blocks for this file.

	const T_IDEDOS_PLUS3DOS_DIRECTORY_ENTRY *directory_entry = reinterpret_cast<T_IDEDOS_PLUS3DOS_DIRECTORY_ENTRY*>(block);

	// get the sequence number
	const int extent_sequence = directory_entry->g_extent(m_pPartition->ExtentMask());

	// are we using 8-bit or 16-bit allocation records?

	int max_al_records = 16;
	if (m_pPartition->ALRecordsAre16bit())
	{
		max_al_records = 8;
	}


	// now add each of the allocation things to this extent...
	int records_in_this_extent = ((directory_entry->extent_low & m_pPartition->ExtentMask()) * 128) + directory_entry->records_used;

	int blocks_in_this_extent  = (128 * records_in_this_extent) / m_pPartition->BlockSize();
	if ((128 * records_in_this_extent) % m_pPartition->BlockSize())
		blocks_in_this_extent++;

	int this_allocator = 0;
	// now, blocks_in_this_extent is the number of AL records in use here.
	while ((this_allocator < blocks_in_this_extent) && (this_allocator < max_al_records))
	{
		WORD this_alloc;
		if (m_pPartition->ALRecordsAre16bit())
		{
			this_alloc = directory_entry->alloc.al_16.al[this_allocator];
		}
		else
		{
			this_alloc = directory_entry->alloc.al_8.al[this_allocator];
		}
		extent_map[(extent_sequence * max_al_records) + this_allocator] = this_alloc;
		++ this_allocator;
	}
}

std::string CPlus3DOS_DirectoryEntry::GetInformation()
{
	ExamineHeader();

	int block_count = extent_map.size();

	std::ostringstream ostr;
	if (m_bHeaderless)
	{
		ostr << "Headerless File: " << GetName() << "\r\n";
	}
	else
	{
		switch (m_filetype)
		{
		case CExplorerFile::PROGRAM:
			{
				ostr << "Program: " << GetName() << "\r\n";
				ostr << "Line: " << m_param1 << "\t ";
				ostr << "Vars: +" << m_param2 << "\r\n";
			}
			break;
		case CExplorerFile::NUMBER_ARRAY:
			{
				ostr << "Number Array: " << GetName() << "\r\n";
				char var = (HIBYTE(m_param1) & 0x1f) | 0x40;
				ostr << "Var:  " << var << "\r\n";
			}
			break;
		case CExplorerFile::CHARACTER_ARRAY:
			{
				ostr << "Character Array: " << GetName() << "\r\n";
				char var = (HIBYTE(m_param1) & 0x1f) | 0x40;
				ostr << "Var:  " << var << "$\r\n";
			}
			break;
		case CExplorerFile::CODE:
			{
				ostr << "Bytes: " << GetName() << "\r\n";
				ostr << "Addr: " << m_param1 << "\r\n";
			}
			break;
		}

		ostr << "Size: " << m_filesize << "\r\n";
	}

	ostr << "Disk: " << m_disk_file_length << "\r\n";
	ostr << "BlkC: " << block_count << "\r\n";

	ostr << "Using Blocks:";

	// we'll verify that we have all extents by just counting the map entries
	bool missing_entries = false;
	unsigned int map_counter = 0;

	TExtentMapIterator map_it = extent_map.begin();
	int line_count = 0;
	while (map_it != extent_map.end())
	{
		if (map_counter != (*map_it).first)
		{
			missing_entries = true;
		}
		map_counter++;

		line_count++;
		if (16 == line_count)
		{
			ostr << "\r\n" << (*map_it).second;
			line_count = 0;
		}
		else
		{
			ostr << "," << (*map_it).second;
		}
		++map_it;
	}

	if (missing_entries)
		ostr << "\r\n\r\nWARNING - MAY BE MISSING DIRECTORY ENTRIES!";

	return (ostr.str());
}

void CPlus3DOS_DirectoryEntry::ExtractObject(CExplorerFile::TEXTRACTABLE_FORMATS _format, bool _include_header)
{
	// here we want to read in the blocks of the file
	// and add them to a new CExplorerFile object.

	ExamineHeader();

	if (extent_map.size())
	{
		int sector_offset = (m_bHeaderless || _include_header) ? 0 : sizeof(T_PLUS3DOS_HEADER);

		// now create a new file and fill it with data...
		CExplorerFile the_file(m_strName, NULL, 0, m_filetype, m_param1, m_param2);

		ReadFile(&the_file, sector_offset);

		// right, we've done that...
		// now we want to write it out to a file...

		try
		{
			std::string filename = m_strName;
			int result = 0;
			char * the_data;

			switch(_format)
			{
			case CExplorerFile::TAPFILE:
				filename += ".tap";
				result = the_file.GenerateTapfile(&the_data, false);
				break;
			case CExplorerFile::TAPFILE_HEADERLESS:
				filename += ".tap";
				result = the_file.GenerateTapfile(&the_data, true);
				break;
			case CExplorerFile::BINFILE:
				filename += ".bin";
				result = the_file.GenerateBinfile(&the_data);
				break;
			default:
				break;
			}

			if (result)
			{
				HANDLE xxx = CreateFile(filename.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
				DWORD written;
				WriteFile(xxx, the_data, result, &written, NULL);
				CloseHandle(xxx);
			}
		}
		catch (CExplorerFile::EExplorerFile &e)
		{
			::AfxMessageBox(e.what(), 0, 0);
		}
	}
}

void CPlus3DOS_DirectoryEntry::ExamineHeader()
{
	// this method looks at the first sector of the file to see if it's got a header.
	// if it has, it rips the information out.
	// if it hasn't... it makes it up :)

	// only do this if we've not done it already, and the file has any data
	if (extent_map.size() && !m_bHeaderExamined)
	{
		CCHS chs;

		// before we do anything else, work out if we're headerless...
		WORD first_block = (*extent_map.begin()).second;
		m_pPartition->BlockToCHS(first_block, chs);

		char * one_sector;
		unsigned int sec_size = m_p3eDoc->ReadSector(chs, &one_sector);

		T_PLUS3DOS_HEADER *plus3dos_header = reinterpret_cast<T_PLUS3DOS_HEADER *>(one_sector);

		std::string header_magic;
		header_magic.append(plus3dos_header->magic, 8);
		if (!PLUS3DOS_Signature.compare(header_magic) && 0x1a == plus3dos_header->soft_eof)
		{
			// looks good so far... work out the checksum...
			unsigned int chk = 0;
			for (int chk_count = 0; chk_count < sizeof(T_PLUS3DOS_HEADER) - 1; chk_count++)
			{
				chk += one_sector[chk_count];
			}

			chk %= 0x100;

			if (chk == plus3dos_header->checksum)
			{
				m_bHeaderless = false;
			}
		}

		if (m_bHeaderless)
		{
			// it's a headerless file so fill in the gaps
			m_disk_file_length = extent_map.size() * m_pPartition->BlockSize();
			m_filesize = m_disk_file_length > 0xffff ? 0xffff : m_disk_file_length;

			if (CTreeObject::PLUS3DOS_FILE_ERASED != m_tType)
			{
				m_tType = CTreeObject::PLUS3DOS_FILE_HEADERLESS;
			}
		}
		else
		{
			// take the data we want out of the header
			m_filetype = static_cast<CExplorerFile::TFILETYPE>(plus3dos_header->type);
			m_param1 = plus3dos_header->param1;
			m_param2 = plus3dos_header->param2;
			m_disk_file_length = plus3dos_header->length;
			m_filesize = plus3dos_header->filesize;
			m_issue = plus3dos_header->issue;
			m_version = plus3dos_header->version;

			if (CTreeObject::PLUS3DOS_FILE_ERASED != m_tType)
			{
				// alter the file type
				switch (m_filetype)
				{
				case CExplorerFile::PROGRAM:
					m_tType = CTreeObject::PLUS3DOS_FILE_PROGRAM;
					break;
				case CExplorerFile::NUMBER_ARRAY:
					m_tType = CTreeObject::PLUS3DOS_FILE_NUMARRAY;
					break;
				case CExplorerFile::CHARACTER_ARRAY:
					m_tType = CTreeObject::PLUS3DOS_FILE_CHARARRAY;
					break;
				case CExplorerFile::CODE:
					m_tType = CTreeObject::PLUS3DOS_FILE_CODE;
					break;
				}
			}
		}
	}

	m_bHeaderExamined = true;
}

void CPlus3DOS_DirectoryEntry::ReadFile(CExplorerFile *_file, unsigned int _skip)
{
	TExtentMapIterator map_it = extent_map.begin();

	unsigned int filesize_left = m_disk_file_length - _skip;

	// now loop through the blocks and add them.
	bool carry_on = true;
	while (0 < filesize_left && carry_on)
	{
		if (map_it != extent_map.end())
		{
			// ok, get the block id...
			WORD block = (*map_it).second;
			CCHS chs;
			m_pPartition->BlockToCHS(block, chs);

			int sectors_in_block = m_pPartition->SectorsInABlock() - 1;

			// read in this sector...
			char * sector;
			int sec_size = m_p3eDoc->ReadSector(chs, &sector);

			do
			{
				// handle this sector
				sec_size -= _skip;
				if (sec_size > filesize_left)
					sec_size = filesize_left;

				_file->AddData(&sector[_skip], sec_size);

				filesize_left -= sec_size;

				if (filesize_left)
				{
					sec_size = m_p3eDoc->ReadNextSector(&sector);
				}

				// it's only the first block we want to skip the start of...
				_skip = 0;
			} while (sectors_in_block-- && 0 < filesize_left);

			map_it++;
		}
		else
		{
			carry_on = false;
		}
	}
}
