// IDEDOSPartitionDefinition.cpp: implementation of the CIDEDOSPartitionDefinition class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3eExplorer.h"
#include "IDEDOSPartitionDefinition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIDEDOSPartitionDefinition::CIDEDOSPartitionDefinition(CMy3eExplorerDoc * _p3eDoc, TreeObjectType _type, char * block)
: CTreeObject(_p3eDoc, _type)
, m_partition_entry_size(0x40)
{
	// for now simply copy the block onto the definition
	::CopyMemory(&m_idedos_partition, block, sizeof(m_idedos_partition));

	// set the name
	m_strName = GetPartitionName();
}

CIDEDOSPartitionDefinition::~CIDEDOSPartitionDefinition()
{

}

std::string CIDEDOSPartitionDefinition::GetPartitionName()
{
	std::string str;
	str.append(reinterpret_cast<char*>(m_idedos_partition.name), 16);
	return str;
}

std::string CIDEDOSPartitionDefinition::GetInformation()
{
	std::ostringstream ostr;
	ostr << "from: " << m_idedos_partition.g_cylinder_start() << "/" << m_idedos_partition.g_head_start() << "\r\n";
	ostr << "to  : " << m_idedos_partition.g_cylinder_end() << "/" << m_idedos_partition.g_head_end() << "\r\n";
	ostr << "      " << m_idedos_partition.g_largest_logical_sector() << " is largest logical sector";
	return (ostr.str());
}
