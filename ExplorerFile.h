// ExplorerFile.h: interface for the CExplorerFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPLORERFILE_H__EFA8EFCE_76FE_4767_95EB_D107D5FC14B4__INCLUDED_)
#define AFX_EXPLORERFILE_H__EFA8EFCE_76FE_4767_95EB_D107D5FC14B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CExplorerFile  
{
public:
	int GenerateTapfile(char ** _buff, bool headerless = false);
	int GenerateBinfile(char ** _buff);

	typedef enum
	{
		TAPFILE,
		TAPFILE_HEADERLESS,
		BINFILE
	} TEXTRACTABLE_FORMATS;

	typedef enum
	{
		PROGRAM = 0,
		NUMBER_ARRAY = 1,
		CHARACTER_ARRAY = 2,
		CODE = 3
	} TFILETYPE;

#pragma pack(push, 1)
	typedef struct {
		WORD blocksize;
		BYTE flag;
	} T_TAPFILE_BASE;

	typedef struct {
		T_TAPFILE_BASE base;
		BYTE type;
		char filename[10];
		WORD filesize;
		WORD param1;
		WORD param2;
		BYTE checksum;
	} T_TAPFILE_HEADER;
#pragma pack(pop)


	void AddData(char * _data, int _datasize);
	CExplorerFile(std::string _filename, char * _data = NULL, int _size = 0, TFILETYPE _type = CODE, WORD _param1 = 0, WORD _param2 = 0);
	virtual ~CExplorerFile();

	void SetType(TFILETYPE _type) {m_type = _type;};
	void SetParam1(TFILETYPE _p1) {m_param1 = _p1;};
	void SetParam2(TFILETYPE _p2) {m_param2 = _p2;};
	void SetFilename(std::string _fn) {m_strFilename = _fn;};

	class EExplorerFile : public std::runtime_error {public: EExplorerFile(const std::string &what_arg) : std::runtime_error(what_arg) {};};

protected:
	std::string m_strFilename;
	std::vector<char> m_vData;
	TFILETYPE m_type;
	WORD m_param1;
	WORD m_param2;
	char * m_tapfile;
};

#endif // !defined(AFX_EXPLORERFILE_H__EFA8EFCE_76FE_4767_95EB_D107D5FC14B4__INCLUDED_)
