// TreeObject.h: interface for the CTreeObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREEOBJECT_H__3FAB6305_33FD_42EE_80C1_1FA3A5598C3A__INCLUDED_)
#define AFX_TREEOBJECT_H__3FAB6305_33FD_42EE_80C1_1FA3A5598C3A__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMy3eExplorerDoc;
#include "ExplorerFile.h"

class CTreeObject : public CObject
{
public:
	// _format			: what format are we outputting to?
	// _include_header	: do we include the, for example, +3dos header in the output?
	virtual void ExtractObject(CExplorerFile::TEXTRACTABLE_FORMATS _format, bool _include_header = false);
	typedef enum
	{
		INVALID = 0,
		HDF = 1,
		PARTITION_PLUSIDEDOS = 2,
		PARTITION_PLUS3DOS = 3,
		PLUS3DOS_USER_DIRECTORY = 0x100 + 0x00,
		PLUS3DOS_FILE = 0x100 + 0x01,
		PLUS3DOS_FILE_PROGRAM = 0x100 + 0x02,
		PLUS3DOS_FILE_NUMARRAY = 0x100 + 0x03,
		PLUS3DOS_FILE_CHARARRAY = 0x100 + 0x04,
		PLUS3DOS_FILE_CODE = 0x100 + 0x05,
		PLUS3DOS_FILE_HEADERLESS = 0x100 + 0x06,
		PLUS3DOS_USER_DIRECTORY_ERASED = 0x100 + 0x10,
		PLUS3DOS_FILE_ERASED = 0x100 + 0x11,
		RESERVED = 65535
	} TreeObjectType;

	typedef std::vector<CTreeObject*> TTree;
	typedef std::vector<CTreeObject*>::iterator TTreeIterator;

	CTreeObject(CMy3eExplorerDoc * _p3eDoc, TreeObjectType _type = INVALID, const char * _name = _T(""), bool _expand = true, bool _extract = false);
	virtual ~CTreeObject();
	const TreeObjectType Type() const {return m_tType;};

	std::vector<CTreeObject *>::iterator GetChildren() {return m_vChildren.begin();};
	std::vector<CTreeObject *>::iterator GetChildrenEnd() {return m_vChildren.end();};
	virtual void ParseForChildren();

	std::string GetName() const {return m_strName;};
	BOOL IsExpandable() const {return m_bExpandable;};
	BOOL IsExtractable() const {return m_bExtractable;};

	virtual std::string GetInformation();

protected:
	TreeObjectType m_tType;
	BOOL m_bParsedForChildren;
	std::vector<CTreeObject *> m_vChildren;
	std::string m_strName;
	BOOL m_bExpandable;
	BOOL m_bExtractable;
	CMy3eExplorerDoc *m_p3eDoc;

};

#endif // !defined(AFX_TREEOBJECT_H__3FAB6305_33FD_42EE_80C1_1FA3A5598C3A__INCLUDED_)
