// IDEDOSPartitionDefinition.h: interface for the CIDEDOSPartitionDefinition class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDEDOSPARTITIONDEFINITION_H__99998564_1B63_4B07_B30C_23B9C03BEECD__INCLUDED_)
#define AFX_IDEDOSPARTITIONDEFINITION_H__99998564_1B63_4B07_B30C_23B9C03BEECD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TreeObject.h"

class CIDEDOSPartitionDefinition : public CTreeObject  
{
public:
	CIDEDOSPartitionDefinition(CMy3eExplorerDoc * _p3eDoc, TreeObjectType _type, char * block);
	virtual ~CIDEDOSPartitionDefinition();

#pragma pack(push, 1)
	typedef struct {
		BYTE name[16];
		BYTE type;
		WORD cylinder_start;
		BYTE head_start;
		WORD cylinder_end;
		BYTE head_end;
		DWORD largest_logical_sector;
		// type-specific?

		int g_cylinder_start() const {return (int)cylinder_start;};
		int g_cylinder_end() const {return (int)cylinder_end;};
		int g_head_start() const {return (int)head_start;};
		int g_head_end() const {return (int)head_end;};
		int g_largest_logical_sector() const {return (int)largest_logical_sector;};
		int g_type() const {return (int)type;};
	} T_IDEDOS_PARTITION_BASE;
#pragma pack(pop)

	typedef enum
	{
		UNUSED		= 0x00,
		SYSTEM		= 0x01,
		SWAP		= 0x02,
		PLUS3DOS	= 0x03,
		CPM			= 0x04,
		BOOT		= 0x05,
		MOVIE		= 0x0f,
		FAT16		= 0x10,
		UZIX		= 0x20,
		TRDOS		= 0x30,
		SAMDOS		= 0x31,
		MB02		= 0x32,
		BAD_SPACE	= 0xfe,
		FREE_SPACE	= 0xff
	} T_PARTITION_TYPES;

public:
	virtual std::string GetInformation();

protected:
	std::string GetPartitionName();

protected:
	unsigned int m_partition_entry_size;
	T_IDEDOS_PARTITION_BASE m_idedos_partition;
};

#endif // !defined(AFX_IDEDOSPARTITIONDEFINITION_H__99998564_1B63_4B07_B30C_23B9C03BEECD__INCLUDED_)
