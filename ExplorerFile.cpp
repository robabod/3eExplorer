// ExplorerFile.cpp: implementation of the CExplorerFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3eExplorer.h"
#include "ExplorerFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExplorerFile::CExplorerFile(std::string _filename, char * _data, int _size, TFILETYPE _type, WORD _param1, WORD _param2)
: m_strFilename(_filename)
, m_param1(_param1)
, m_param2(_param2)
, m_type(_type)
, m_vData(_size)
, m_tapfile(NULL)
{
	if (NULL != _data)
	{
		// copy this data into the vector...
		::CopyMemory(&m_vData[0], _data, _size);
	}
}

CExplorerFile::~CExplorerFile()
{
	if (NULL != m_tapfile)
	{
		delete [] m_tapfile;
	}
}

void CExplorerFile::AddData(char *_data, int _datasize)
{
	if (NULL != _data && 0 < _datasize)
	{
		int curr_size = m_vData.size();
		m_vData.resize(curr_size + _datasize);
		::CopyMemory(&m_vData[curr_size], _data, _datasize);
	}
}

int CExplorerFile::GenerateTapfile(char ** _buff, bool headerless)
{
	// here we'll allocate some memory for a tapfile, and return the pointer.
	if (NULL != m_tapfile)
	{
		delete [] m_tapfile;
		m_tapfile = NULL;
	}

	unsigned int data_size = m_vData.size();

	if (data_size > 0xffff)
	{
		throw EExplorerFile("File is too large to export to a .tap");
	}

	// how much memory do we need?
	unsigned int total_mem = data_size;
	total_mem += 4;

	if (!headerless)
		total_mem += 21;

	m_tapfile = new char [total_mem];

	unsigned int current_pointer = 0;

	if (!headerless)
	{
		// set up the header with the information we have...
		T_TAPFILE_HEADER *header = reinterpret_cast<T_TAPFILE_HEADER*>(m_tapfile);
		header->base.blocksize = sizeof(T_TAPFILE_HEADER) - 2;
		header->base.flag = 0x00;
		header->type = m_type;
		std::string fn = m_strFilename;
		fn.resize(10, ' ');
		strncpy(header->filename, fn.c_str(), 10);
		header->filesize = data_size;
		header->param1 = m_param1;
		header->param2 = m_param2;

		// set checksum...
		BYTE chk = 0;
		for (int ii = 2; ii < 20; ++ii)
		{
			chk ^= m_tapfile[ii];
		}
		header->checksum = chk;
		current_pointer += 21;
	}


	int chk_ptr = current_pointer;

	// now add in the actual data...
	T_TAPFILE_BASE *tape = reinterpret_cast<T_TAPFILE_BASE*>(&m_tapfile[current_pointer]);
	tape->blocksize = data_size + 2;
	tape->flag = 0xff;
	current_pointer += sizeof(T_TAPFILE_BASE);

	if (data_size)
	{
		::CopyMemory(&m_tapfile[current_pointer], &m_vData[0], data_size);
	}

	current_pointer += data_size;

	// now work out the checksum
	BYTE chk = 0;
	chk_ptr += 2;
	while (chk_ptr < current_pointer)
	{
		chk ^= m_tapfile[chk_ptr++];
	}
	m_tapfile[chk_ptr] = chk;

	*_buff = m_tapfile;
	return total_mem;
}

int CExplorerFile::GenerateBinfile(char ** _buff)
{
	// for the moment just return a pointer to the first element
	*_buff = m_vData.size() ? &m_vData[0] : NULL;
	return m_vData.size();
}
