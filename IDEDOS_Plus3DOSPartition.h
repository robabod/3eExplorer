// IDEDOS_Plus3DOSPartition.h: interface for the CIDEDOS_Plus3DOSPartition class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDEDOS_PLUS3DOSPARTITION_H__9F47A008_2139_4F90_9BC0_77D7D4B5F4CE__INCLUDED_)
#define AFX_IDEDOS_PLUS3DOSPARTITION_H__9F47A008_2139_4F90_9BC0_77D7D4B5F4CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDEDOSPartitionDefinition.h"
#include "3eExplorerDoc.h"	// Added by ClassView

class CIDEDOS_Plus3DOSPartition : public CIDEDOSPartitionDefinition  
{
public:
	CIDEDOS_Plus3DOSPartition(CMy3eExplorerDoc * _p3eDoc, char * block);
	virtual ~CIDEDOS_Plus3DOSPartition();

#pragma pack(push, 1)
	typedef struct {
		WORD spt; // records_per_track_128
		BYTE bsh; // block_shift
		BYTE blm; // block_mask
		BYTE exm; // extent_mask
		WORD dsm; // blocks_on_disk
		WORD drm; // directory_entries
		BYTE al0; // directory allocation bitmap first byte
		BYTE al1; // directory allocation bitmap second byte
		WORD cks; // checksum vector size
		WORD off; // offset, number of reserved tracks
		BYTE psh; // physical sector shift (0 = 128b, 1 = 256b, 2 = 512b, ...)
		BYTE phm; // physical sector mask  (0 = 128b, 1 = 256b, 3 = 512b, ...)

		// now come the amstrad extensions...
		BYTE sidedness;
		BYTE tracks_per_side;
		BYTE sectors_per_track;
		BYTE first_physical_sector_number;
		WORD sector_size;
		BYTE upd765a_rw_gap;
		BYTE upd765a_format_gap;
		BYTE multitrack_flags;
		BYTE freeze_flag;


		inline int g_spt() const {return (int)spt;};
		inline int g_bsh() const {return (int)bsh;};
		inline int g_blm() const {return (int)blm;};
		inline int g_exm() const {return (int)exm;};
		inline int g_dsm() const {return (int)dsm;};
		inline int g_drm() const {return (int)drm;};
		inline int g_al0() const {return (int)al0;};
		inline int g_al1() const {return (int)al1;};
		inline int g_cks() const {return (int)cks;};
		inline int g_off() const {return (int)off;};
		inline int g_psh() const {return (int)psh;};
		inline int g_phm() const {return (int)phm;};
		inline int g_sidedness() const {return (int)sidedness;};
		inline int g_tracks_per_side() const {return (int)tracks_per_side;};
		inline int g_sectors_per_track() const {return (int)sectors_per_track;};
		inline int g_first_physical_sector_number() const {return (int)first_physical_sector_number;};
		inline int g_sector_size() const {return (int)sector_size;};
		inline int g_upd765a_rw_gap() const {return (int)upd765a_rw_gap;};
		inline int g_upd765a_format_gap() const {return (int)upd765a_format_gap;};
		inline int g_multitrack_flags() const {return (int)multitrack_flags;};
		inline int g_freeze_flag() const {return (int)freeze_flag;};
	} T_IDEDOS_PLUS3DOS_PARTITION;
#pragma pack(pop)

public:
	bool BlockToCHS(WORD _block, CCHS &_chs) const;
	virtual void ParseForChildren();
	virtual std::string GetInformation();

	BYTE ExtentMask() const {return m_plus3dos_partition.exm;};
	WORD AllocationMask() const {return (WORD)(m_plus3dos_partition.al1 + (m_plus3dos_partition.al0 * 256));};
	int BlockSize() const {return (128 << (m_plus3dos_partition.g_bsh()));};
	int SectorsInABlock() const {return (BlockSize() / m_p3eDoc->GetRoot()->getSectorSize());};
	bool ALRecordsAre16bit() const {return (m_plus3dos_partition.g_dsm() > 255);};

protected:
	T_IDEDOS_PLUS3DOS_PARTITION m_plus3dos_partition;
	unsigned int m_block_size;

};

#endif // !defined(AFX_IDEDOS_PLUS3DOSPARTITION_H__9F47A008_2139_4F90_9BC0_77D7D4B5F4CE__INCLUDED_)
