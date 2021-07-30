// IDEDOS_SystemPartition.h: interface for the CIDEDOS_SystemPartition class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDEDOS_SYSTEMPARTITION_H__DEB9F53D_4E27_4718_9C4F_2127FD1B7BA1__INCLUDED_)
#define AFX_IDEDOS_SYSTEMPARTITION_H__DEB9F53D_4E27_4718_9C4F_2127FD1B7BA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDEDOSPartitionDefinition.h"

class CIDEDOS_SystemPartition : public CIDEDOSPartitionDefinition  
{
public:
	CIDEDOS_SystemPartition(CMy3eExplorerDoc * _p3eDoc, char * block, unsigned int _tt);
	virtual ~CIDEDOS_SystemPartition();

#pragma pack(push, 1)
	typedef struct {
		WORD cylinders;
		BYTE heads;
		BYTE tracks;
		WORD sectors_per_cylinder;
		WORD partitions_allowed;
		int g_cylinders() const {return (int)cylinders;};
		int g_heads() const {return (int)heads;};
		int g_tracks() const {return (int)tracks;};
		int g_sectors_per_cylinder() const {return (int)sectors_per_cylinder;};
		int g_partitions_allowed() const {return (int)partitions_allowed;};
	} T_IDEDOS_SYSTEM_PARTITION;
#pragma pack(pop)

protected:
	unsigned int m_start_track;
	T_IDEDOS_SYSTEM_PARTITION m_system_partition;
public:
	virtual void ParseForChildren();
	virtual std::string GetInformation();
};

#endif // !defined(AFX_IDEDOS_SYSTEMPARTITION_H__DEB9F53D_4E27_4718_9C4F_2127FD1B7BA1__INCLUDED_)
