// 3eExplorerDoc.cpp : implementation of the CMy3eExplorerDoc class
//

#include "stdafx.h"
#include "3eExplorer.h"

#include "3eExplorerDoc.h"
#include "DocumentStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CCHS::CCHS(unsigned int _c, unsigned int _h, unsigned int _s)
: c(_c), h(_h), s(_s)
{
}



/////////////////////////////////////////////////////////////////////////////
// CMy3eExplorerDoc

IMPLEMENT_DYNCREATE(CMy3eExplorerDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy3eExplorerDoc, CDocument)
	//{{AFX_MSG_MAP(CMy3eExplorerDoc)
	ON_COMMAND(ID_FILE_FILESTATUS, OnFileFilestatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3eExplorerDoc construction/destruction

CMy3eExplorerDoc::CMy3eExplorerDoc()
: m_pFile(NULL)
, m_pHdfHeader(NULL)
{
	// TODO: add one-time construction code here

}

CMy3eExplorerDoc::~CMy3eExplorerDoc()
{
}

BOOL CMy3eExplorerDoc::OnNewDocument()
{
	//if (!CDocument::OnNewDocument())
	//	return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CMy3eExplorerDoc serialization

void CMy3eExplorerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMy3eExplorerDoc diagnostics

#ifdef _DEBUG
void CMy3eExplorerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy3eExplorerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy3eExplorerDoc commands

BOOL CMy3eExplorerDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	// we want to override the default stuff, as we want to keep the file open and cache it as we go

	// so we'll do pretty much the default handling
	if (IsModified())
		TRACE0("Warning: OnOpenDocument replaces an unsaved document.\n");

	CFileException fe;
	CFile* pFile = GetFile(lpszPathName,
		CFile::modeRead|CFile::shareDenyWrite|CFile::typeBinary, &fe);
	if (pFile == NULL)
	{
		ReportSaveLoadException(lpszPathName, &fe,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		return FALSE;
	}

	DeleteContents();
	SetModifiedFlag();  // dirty during de-serialize

	// store the filename
	std::string filename = lpszPathName;
	std::string::size_type pos = filename.find_last_of("\\/");
	if (std::string::npos == pos)
		pos = 0;
	else
		pos++;

	m_sFileName = filename.substr(pos);

	// store the file pointer
	m_pFile = pFile;

	ASSERT (m_pHdfHeader == NULL);
	// read in a block of the image and verify it

	try
	{
		char first_block[0x216];
		UINT read = pFile->Read(first_block, 0x216);
		m_pHdfHeader = new CHdfHeader(this, first_block, read, m_sFileName.c_str());
	}
	catch (CHdfHeader::EHdfInvalid &e)
	{
		::AfxMessageBox(e.what(), MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}
	catch (CHdfHeader::EHdfUnsupported &e)
	{
		::AfxMessageBox(e.what(), MB_ICONINFORMATION | MB_OK);
		return FALSE;
	}
	catch (CFileException *e)
	{
		ReportSaveLoadException(lpszPathName, e, FALSE, IDS_FILE_ACCESS_ERROR);
		return FALSE;
	}

	SetModifiedFlag(FALSE);     // start off with unmodified

	return TRUE;
}

void CMy3eExplorerDoc::DeleteContents() 
{
	// Here we need to release the file and delete any allocated memory
	if (NULL != m_pFile)
	{
		m_pFile->Close();
		ReleaseFile(m_pFile, TRUE);
		m_pFile = NULL;
	}
	
	// step through the cache and free up memory
	for (TCacheIterator it = m_sector_cache.begin(); it != m_sector_cache.end(); it++)
	{
		delete [] (*it).second;
	}

	m_sector_cache.clear();

	// now delete the object tree we have created.
	if (NULL != m_pHdfHeader)
	{
		delete m_pHdfHeader;
		m_pHdfHeader = NULL;
	}

	CDocument::DeleteContents();
}

BOOL CMy3eExplorerDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//return CDocument::OnSaveDocument(lpszPathName);

	// DON'T SAVE!
	return 0;
}

unsigned int CMy3eExplorerDoc::ReadSector(const unsigned int _zz, char ** _buff)
{
	ASSERT (m_pFile != NULL);
	ASSERT (m_pHdfHeader != NULL);

	unsigned int sector_size = m_pHdfHeader->getSectorSize();

	// first see if this sector is in our cache...
	TCacheIterator it = m_sector_cache.find(_zz);

	if (it == m_sector_cache.end())
	{
		// we could be reading a word and using a byte, you know...
		unsigned int read_size = sector_size;
		if (m_pHdfHeader->UsingHalfWord())
			read_size *= 2;

		// need to allocate another sector in memory
		char * temp_buffer = new char[read_size];

		// read from the file into the buffer
		LONG byte_offset = m_pHdfHeader->getOffset() + (_zz * read_size);

		try
		{
			m_pFile->Seek(byte_offset, CFile::begin);
			if (read_size != m_pFile->Read(temp_buffer, read_size))
			{
				// couldn't read everything - throw an exception
				std::ostringstream except;
				except << "Error reading sector " << _zz << ". File may be truncated";
				throw EInvalidSector(except.str());
			}
		}
		catch (CFileException *e)
		{
			// for now just rethrow
			throw e;
		}

		if (m_pHdfHeader->UsingHalfWord())
		{
			char * copy_sector = new char[sector_size];
			// now copy every other byte
			for (int ccount = 0; ccount < sector_size; ccount++)
			{
				copy_sector[ccount] = temp_buffer[2 * ccount];
			}
			m_sector_cache[_zz] = copy_sector;
			delete [] temp_buffer;
		}
		else
		{
			m_sector_cache[_zz] = temp_buffer;
		}
		it = m_sector_cache.find(_zz);

		ASSERT (it != m_sector_cache.end());
	}

	// just for fun, see what happens if we try to set the status...

	*_buff = (*it).second;

	return sector_size;
}

unsigned int CMy3eExplorerDoc::ReadSector(CCHS _chs, char ** _buff)
{
	// work out the sector number and call the other method
	ASSERT (m_pHdfHeader != NULL);

	unsigned int cc = m_pHdfHeader->getCylinders();
	unsigned int hh = m_pHdfHeader->getHeads();
	unsigned int ss = m_pHdfHeader->getSectors();

	if (_chs.c > m_pHdfHeader->getCylinders())
	{
		std::ostringstream except;
		except << "Cylinder count error : " << _chs.c << " > " << m_pHdfHeader->getCylinders();
		throw EInvalidSector(except.str());
	}
	if (_chs.h > m_pHdfHeader->getHeads())
	{
		std::ostringstream except;
		except << "Head count error : " << _chs.h << " > " << m_pHdfHeader->getHeads();
		throw EInvalidSector(except.str());
	}
	if (_chs.s > m_pHdfHeader->getSectors())
	{
		std::ostringstream except;
		except << "Sector count error : " << _chs.s << " > " << m_pHdfHeader->getSectors();
		throw EInvalidSector(except.str());
	}

	// see if we're doing a cache of a head a time...
	if (theApp.HeadCache())
	{
		// do a precache of all the sectors in this head
		unsigned int presec = (_chs.h * ss) + (_chs.c * hh);
		unsigned int presec_max = (presec + ss);
		for (; presec < presec_max; presec++)
		{
			ReadSector(presec, _buff);
		}
	}

	unsigned int sector = (_chs.s) + (_chs.h * ss) + (_chs.c * (hh * ss));

	m_cur_chs = _chs;

	return ReadSector(sector, _buff);
}

unsigned int CMy3eExplorerDoc::ReadNextSector(char ** _buff)
{
	if (++m_cur_chs.s >= m_pHdfHeader->getSectors())
	{
		m_cur_chs.s = 0;
		if (++m_cur_chs.h >= m_pHdfHeader->getHeads())
		{
			m_cur_chs.h = 0;
			if (++m_cur_chs.c >= m_pHdfHeader->getCylinders())
			{
				m_cur_chs.c = 0;
			}
		}
	}

	return ReadSector(m_cur_chs, _buff);
}

void CMy3eExplorerDoc::OnFileFilestatus() 
{
	// here we want to open the dialog that gives us some status information about this document
	CDocumentStatus docStatus;
	docStatus.SetExplorerDoc(this);
	docStatus.DoModal();
}

void CMy3eExplorerDoc::FlushCache()
{
	// step through the cache and free up memory
	for (TCacheIterator it = m_sector_cache.begin(); it != m_sector_cache.end(); it++)
	{
		delete [] (*it).second;
	}

	m_sector_cache.clear();
}
