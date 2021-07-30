// Plus3DOS_UserArea.h: interface for the CPlus3DOS_UserArea class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLUS3DOS_USERAREA_H__6B31F7E1_171E_41C0_9942_A381C50586D2__INCLUDED_)
#define AFX_PLUS3DOS_USERAREA_H__6B31F7E1_171E_41C0_9942_A381C50586D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TreeObject.h"
#include "IDEDOS_Plus3DOSPartition.h"

class CPlus3DOS_UserArea : public CTreeObject  
{
public:
	class EUserAreaInvalid : public std::runtime_error {public: EUserAreaInvalid(const std::string &what_arg) : std::runtime_error(what_arg) {};};
		virtual void ExtractObject(CExplorerFile::TEXTRACTABLE_FORMATS _format, bool _include_header = false);
	virtual void ParseForChildren();
	virtual std::string GetInformation();
	CPlus3DOS_UserArea(CMy3eExplorerDoc * _p3eDoc, BYTE _id, std::string _partition_name, unsigned int _cc, unsigned int _tt, unsigned int _ss, unsigned int _max_dir_entries, const CIDEDOS_Plus3DOSPartition *_partition);
	virtual ~CPlus3DOS_UserArea();

protected:
	unsigned int m_start_cc;	// start cylinder of directory records
	unsigned int m_start_tt;	// start track of directory records
	unsigned int m_start_ss;	// start sector of directory records (probably 0)
	unsigned int m_max_dir_entries;	// maximum number of directory entries. each entry is 32b
	BYTE m_user_id;

	const CIDEDOS_Plus3DOSPartition *m_partition;

private:
	static std::map<BYTE, std::string> user_area_id;
};

#endif // !defined(AFX_PLUS3DOS_USERAREA_H__6B31F7E1_171E_41C0_9942_A381C50586D2__INCLUDED_)
