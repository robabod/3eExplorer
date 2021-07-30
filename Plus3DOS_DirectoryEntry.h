// Plus3DOS_DirectoryEntry.h: interface for the CPlus3DOS_DirectoryEntry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLUS3DOS_DIRECTORYENTRY_H__8A127574_D8EA_4E50_B57C_9A0DA2F65AF3__INCLUDED_)
#define AFX_PLUS3DOS_DIRECTORYENTRY_H__8A127574_D8EA_4E50_B57C_9A0DA2F65AF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TreeObject.h"
#include "IDEDOS_Plus3DOSPartition.h"
#include "ExplorerFile.h"

class CPlus3DOS_DirectoryEntry : public CTreeObject  
{
public:
	CPlus3DOS_DirectoryEntry(CMy3eExplorerDoc * _p3eDoc, TreeObjectType _type, char * block, const CIDEDOS_Plus3DOSPartition *_partition);
	virtual ~CPlus3DOS_DirectoryEntry();

	virtual void ExtractObject(CExplorerFile::TEXTRACTABLE_FORMATS _format, bool _include_header = false);

	// this type allows us to map an extent to a vector of blocks
	typedef std::map<int,WORD> TExtentMap;
	typedef std::map<int,WORD>::iterator TExtentMapIterator;

#pragma pack(push, 1)
	typedef struct {
		CHAR magic[8];
		CHAR soft_eof;
		CHAR issue;
		CHAR version;
		DWORD length;	// usually it's the filesize + 128
		BYTE type;
		WORD filesize;
		WORD param1;
		WORD param2;
		BYTE _reserved1;
		CHAR _reserved2[104];
		BYTE checksum;
	} T_PLUS3DOS_HEADER;


	typedef struct {
		BYTE user_number;
		BYTE filename[8];
		union ext_t
		{
			struct {
				BYTE read_only;
				BYTE system_file;
				BYTE archived;
			} flags;
			BYTE extension[3];
		} ext;
		BYTE extent_low;
		BYTE s1_reserved;
		BYTE extent_high;
		BYTE records_used;
		union alloc_t
		{
			struct {
				WORD al[8];
			} al_16;
			struct {
				BYTE al[16];
			} al_8;
		} alloc;

		int g_extent(BYTE _exm) const {return (((int)extent_low + (32 * (int)extent_high)) / (_exm + 1));};
		bool g_readonly() const {return ((ext.flags.read_only & 0x80) == 0x80);};
		bool g_systemfile() const {return ((ext.flags.system_file & 0x80) == 0x80);};
		bool g_archived() const {return ((ext.flags.archived & 0x80) == 0x80);};
	} T_IDEDOS_PLUS3DOS_DIRECTORY_ENTRY;
#pragma pack(pop)


public:
	void ReadFile(CExplorerFile *_file, unsigned int _skip = 0);
	void ExamineHeader();
	void AddExtent(char * block);
	virtual std::string GetInformation();

protected:
	//T_IDEDOS_PLUS3DOS_DIRECTORY_ENTRY m_directory_entry;
	const CIDEDOS_Plus3DOSPartition *m_pPartition;
	TExtentMap extent_map;
	static std::string PLUS3DOS_Signature;

protected:
	bool m_bHeaderless;
	CExplorerFile::TFILETYPE m_filetype;
	WORD m_param1;
	WORD m_param2;
	DWORD m_disk_file_length;	// usually filesize + 128
	WORD m_filesize;
	CHAR m_issue;
	CHAR m_version;

private:
	bool m_bHeaderExamined;
};

#endif // !defined(AFX_PLUS3DOS_DIRECTORYENTRY_H__8A127574_D8EA_4E50_B57C_9A0DA2F65AF3__INCLUDED_)
