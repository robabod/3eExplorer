// HdfHeader.h: interface for the CHdfHeader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HDFHEADER_H__74BF451F_C49E_41A3_A5E9_65D15205AD2F__INCLUDED_)
#define AFX_HDFHEADER_H__74BF451F_C49E_41A3_A5E9_65D15205AD2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TreeObject.h"

class CCHS;

class CHdfHeader : public CTreeObject
{
public:
	CHdfHeader(CMy3eExplorerDoc * _p3eDoc, char * block, const int blocksize, const char * _name);
	virtual ~CHdfHeader();

#pragma pack(push, 1)
	typedef struct {
		WORD general_config;
		WORD cylinders;
		WORD _reserved_1;
		WORD heads;
		WORD _obsolete_1;
		WORD _obsolete_2;
		WORD sectors;
		WORD _vender_1;
		WORD _vender_2;
		WORD _vender_3;
		WORD serial[10];
		WORD _obsolete_3;
		WORD _obsolete_4;
		WORD bytes_on_rw_long_cmds;
		CHAR firmware[8];
		CHAR model[40];
		WORD _vendor_4;
		WORD _reserved_2;
		WORD capabilities;
	} T_ATA_Device_ID;
#pragma pack(pop)

	void getCHS(CCHS &_chs) const;
	unsigned int getOffset() const;
	unsigned int getCylinders() const;
	unsigned int getHeads() const;
	unsigned int getSectors() const;
	unsigned int getSectorSize();
	BOOL UsingHalfWord() const {return bHalfWordUsed;};
	virtual void ParseForChildren();

protected:
	static std::string HDF_Signature;
	BYTE revision;
	BOOL bHalvedSectorData;
	BOOL bHalfWordUsed;
	BOOL bATAPIDevice;
	unsigned int image_offset;
	BOOL bOffset_valid;
	BYTE _reserved[11];
	T_ATA_Device_ID ata_device_id;

public:
	// define an exception that could occur
	class EHdfInvalid : public std::runtime_error {public: EHdfInvalid(const std::string &what_arg) : std::runtime_error(what_arg) {};};
	class EHdfUnsupported : public std::runtime_error {public: EHdfUnsupported(const std::string &what_arg) : std::runtime_error(what_arg) {};};
	virtual std::string GetInformation();
};

#endif // !defined(AFX_HDFHEADER_H__74BF451F_C49E_41A3_A5E9_65D15205AD2F__INCLUDED_)
