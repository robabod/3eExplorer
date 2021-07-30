// TreeObject.cpp: implementation of the CTreeObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3eExplorer.h"
#include "TreeObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTreeObject::CTreeObject(CMy3eExplorerDoc * _p3eDoc, CTreeObject::TreeObjectType _type, const char * _name, bool _expand, bool _extract)
: m_tType(_type)
, m_strName(_name)
, m_bParsedForChildren(FALSE)
, m_bExpandable(_expand)
, m_bExtractable(_extract)
, m_p3eDoc(_p3eDoc)
{
	ASSERT (NULL != _p3eDoc);
}

CTreeObject::~CTreeObject()
{
	// iterate through the children and delete them
	std::vector<CTreeObject *>::iterator it = GetChildren();
	while (it != GetChildrenEnd())
	{
		delete (*it);
		it++;
	}
	m_vChildren.clear();
}

void CTreeObject::ParseForChildren()
{
	// a default object has no children
	m_bParsedForChildren = TRUE;
}

std::string CTreeObject::GetInformation()
{
	std::ostringstream ostr;
	ostr << "INVALID: " << GetName();
	return (ostr.str());
}

void CTreeObject::ExtractObject(CExplorerFile::TEXTRACTABLE_FORMATS _format, bool _include_header)
{
	// default to doing nothing
}
