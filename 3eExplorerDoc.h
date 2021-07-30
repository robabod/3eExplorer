// 3eExplorerDoc.h : interface of the CMy3eExplorerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_3EEXPLORERDOC_H__1D2D4AB6_9635_483C_AAA3_F36ADAC7439F__INCLUDED_)
#define AFX_3EEXPLORERDOC_H__1D2D4AB6_9635_483C_AAA3_F36ADAC7439F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HdfHeader.h"


class CCHS
{
public:
	CCHS(unsigned int _c = 0, unsigned int _h = 0, unsigned int _s = 0);
	unsigned int c;
	unsigned int h;
	unsigned int s;
};

class CMy3eExplorerDoc : public CDocument
{
public:
	typedef std::map<unsigned long int, char*> TCache;
	typedef std::map<unsigned long int, char*>::iterator TCacheIterator;

protected: // create from serialization only
	CMy3eExplorerDoc();
	DECLARE_DYNCREATE(CMy3eExplorerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3eExplorerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
protected:
	unsigned int ReadSector(const unsigned int _zz, char ** _buff);
public:
	unsigned int ReadSector(CCHS _chs, char ** _buff);
public:
	virtual ~CMy3eExplorerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	class EInvalidSector : public std::runtime_error {public: EInvalidSector(const std::string &what_arg) : std::runtime_error(what_arg) {};};

public:
	void FlushCache();
	unsigned int ReadNextSector(char ** _buff);
	const std::string Filename() const {return m_sFileName;};
	CHdfHeader * GetRoot() {return m_pHdfHeader;};

	unsigned long int GetCacheSize() {return m_sector_cache.size();};

// Generated message map functions
protected:
	std::string m_sFileName;
	CHdfHeader * m_pHdfHeader;
	// This is the cache used to read in the sectors of the .hdf file
	TCache m_sector_cache;
	CFile * m_pFile;

	CCHS m_cur_chs;

	//{{AFX_MSG(CMy3eExplorerDoc)
	afx_msg void OnFileFilestatus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3EEXPLORERDOC_H__1D2D4AB6_9635_483C_AAA3_F36ADAC7439F__INCLUDED_)
