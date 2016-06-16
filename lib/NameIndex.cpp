// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#include "NameIndex.h"
#include "radar_dt.h"
#include "prodtype.h"
#include "NameIndexUtil.h"
#include "string.h"

bool CreateRdtNameMap(NameIndexMap &m)
{
    m[RDT_DBT]="dBT";
    m[RDT_DBZ]="dBZ";
    m[RDT_VEL]="V";
    m[RDT_WID]="W";
    m[RDT_SQI]="SQI";
    m[RDT_RR]="RR";
    m[RDT_ZDR]="ZDR";
    m[RDT_LDR]="LDR";
    m[RDT_PDP]="PhiDP";
    m[RDT_KDP]="KDP";
    m[RDT_HCL]="HCL";
    m[RDT_HGT]="HGT";
    m[RDT_VIL]="VIL";
    m[RDT_SHR]="SHEAR";
    m[RDT_RAIN]="RAIN";
    m[RDT_CC]="CC";
    m[RDT_CPA]="CPA";
    m[RDT_CP]="CP";
    m[RDT_CF]="CF";
    m[RDT_RMS]="RMS";
    m[RDT_CTR]="CONTOUR";
    m[RDT_SNR]="SNRH";
    m[RDT_SNRV]="SNRV";
    m[RDT_SWIS]="SWIS";
    m[RDT_RDD]="RDD";
    m[RDT_RDN]="RDN";
    m[RDT_ML] = "ML";
    m[RDT_OCR] = "OCR";
    m[RDT_TURB]="TURB";

    m[RDT_DBZC]="Zc";
    m[RDT_VELC]="Vc";
    m[RDT_WIDC]="Wc";
    m[RDT_ZDRC]="ZDRc";
    m[RDT_PDPC]="PDPc";
    m[RDT_KDPC]="KDPc";
    m[RDT_CCC] ="CCc";
    m[RDT_LDRC]="LDRc";
    m[RDT_POTS]="POTS";
    m[RDT_COP]="COP";
    m[RDT_N]="N";
    return true;
}
bool CreateRdtShortNameMap(NameIndexMap &m)
{
    m[RDT_DBT]="T";
    m[RDT_DBZ]="Z";
    m[RDT_VEL]="V";
    m[RDT_WID]="W";
    m[RDT_SQI]="SQI";
    m[RDT_RR]="R";
    m[RDT_ZDR]="ZDR";
    m[RDT_LDR]="LDR";
    m[RDT_PDP]="PhiDP";
    m[RDT_KDP]="KDP";
    m[RDT_HCL]="HCL";
    m[RDT_HGT]="HGT";
    m[RDT_VIL]="VIL";
    m[RDT_SHR]="SHEAR";
    m[RDT_RAIN]="RAIN";
    m[RDT_DSD]="DSD";
    m[RDT_CC]="CC";
    m[RDT_CPA]="CPA";
    m[RDT_CP]="CP";
    m[RDT_CF]="CF";
    m[RDT_RMS]="RMS";
    m[RDT_CTR]="CTR";
    m[RDT_SNR]="SNRH";
    m[RDT_SNRV]="SNRV";
    m[RDT_SWIS]="SWIS";    
    m[RDT_RDD]="RDD";
    m[RDT_RDN]="RDN";
    m[RDT_ML] = "ML";
    m[RDT_OCR] = "OCR";
    m[RDT_TURB]="TURB";

    m[RDT_POTS]="POTS";
    m[RDT_COP]="COP";
    m[RDT_N]="N";
    m[RDT_DBZC]="Zc";
    m[RDT_VELC]="Vc";
    m[RDT_WIDC]="Wc";
    m[RDT_ZDRC]="ZDRc";
    m[RDT_PDPC]="PDPc";
    m[RDT_KDPC]="KDPc";
    m[RDT_CCC] ="CCc";
    m[RDT_LDRC]="LDRc";
    return true;
}
bool CreateRdtUnitMap(NameIndexMap &m)
{
    m[RDT_DBT]="dBZ";
    m[RDT_DBZ]="dBZ";
    m[RDT_VEL]="m/s";
    m[RDT_WID]="m/s";
    m[RDT_SQI]="";
    m[RDT_RR]="mm/hr";
    m[RDT_ZDR]="dB";
    m[RDT_LDR]="dB";
    m[RDT_PDP]="deg";
    m[RDT_KDP]="deg/km";
    m[RDT_HCL]="";
    m[RDT_HGT]="km";
    m[RDT_VIL]="kg/m**2";
    m[RDT_SHR]="E-4/s";
    m[RDT_RAIN]="mm";
    m[RDT_CC]="";
    m[RDT_CPA]="";
    m[RDT_CP]="";
    m[RDT_RMS]="m/s";
    m[RDT_CTR]="";
    m[RDT_SNR]="dB";
    m[RDT_SNRV]="dB";
    m[RDT_SWIS]="";    
    m[RDT_RDD]="mm";
    m[RDT_RDN]="1/m**3";
    m[RDT_RDN]= "";
    m[RDT_OCR]="%";
    m[RDT_POTS]="deg";
    m[RDT_COP]="deg";
    m[RDT_N]="";

    m[RDT_DBZC]="dBZ";
    m[RDT_VELC]="m/s";
    m[RDT_WIDC]="m/s";
    m[RDT_ZDRC]="dB";
    m[RDT_PDPC]="deg";
    m[RDT_KDPC]="deg/km";
    m[RDT_CCC] ="";
    m[RDT_LDRC]="dB";
    m[RDT_TURB]="CM E/2/3S";
    return true;
}
bool CreateRdtUnitNameMap(NameIndexMap &m)
{
    m[RDT_DBT]="Total Reflectivity";
    m[RDT_DBZ]="Reflectivity";
    m[RDT_VEL]="Velocity";
    m[RDT_WID]="Spectrum Width";
    m[RDT_SQI]="Signal Quantity Index";
    m[RDT_RR]="Rain Rate";
    m[RDT_ZDR]="Differential Reflectivity";
    m[RDT_LDR]="Linear Differential Reflectivity";
    m[RDT_PDP]="Differential Phase";
    m[RDT_KDP]="Specific Differential Phase";
    m[RDT_HCL]="Hydro Classification";
    m[RDT_HGT]="Height";
    m[RDT_VIL]="Vertical Integrated Liquid Water";
    m[RDT_SHR]="Shear";
    m[RDT_RAIN]="Rainfall Accumulation";
    m[RDT_CC]="Correlation Coefficient";
    m[RDT_CPA]="Clutter Phase Alignment";
    m[RDT_CP]="Clutter Possibility";
    m[RDT_CF]="Clutter Flag";
    m[RDT_RMS]="Root Mean Square";
    m[RDT_CTR]="Contour";
    m[RDT_SNR]="Signal Noise Ratio";
    m[RDT_SNRV]="Total Signal Noise Ratio";
    m[RDT_SWIS]="SWIS";
    m[RDT_RDD]="Drop Diameter";
    m[RDT_RDN]="Drop Density";
    m[RDT_ML]= "Melting Layer";
    m[RDT_OCR]= "Occulation Rate";
    m[RDT_POTS]="Phase Of Time Serise ";
    m[RDT_COP]="Change Of POTS to Ref";
    m[RDT_N]="Refractivity";
    m[RDT_DBZC]="Reflectivity Corrected";
    m[RDT_VELC]="Velocity Corrected";
    m[RDT_WIDC]="Spectrum Width Corrected";
    m[RDT_ZDRC]="Differential Reflectivity Corrected";
    m[RDT_PDPC]="Differential Phase Corrected";
    m[RDT_KDPC]="Specific Differential Phase Corrected";
    m[RDT_CCC] ="Correlation Coefficient Corrected";
    m[RDT_LDRC]="Linear Differential Reflectivity Corrected";
    m[RDT_TURB]="Turbulence";
    return true;
}
bool CreateProdTypeNameMap(NameIndexMap &m)
{
    m[PT_PPI]="PPI";
    m[PT_PPI_T]="PPI_T";
    m[PT_CAPPI]="CAPPI";
    m[PT_MAX]="MAX";
    m[PT_ET]="TOPS";
    m[PT_BEAM]="BEAM";
    m[PT_EB]="BASE";
    m[PT_VIL]="VIL";
    m[PT_HMAX]="HMAX";
    m[PT_HSR]="HSR";
    m[PT_SRI]="SRI";
    m[PT_RI_VOL]="RVOL";
    m[PT_RI_VOLC]="RVOLC";
    m[PT_VCS]="VCS";
    m[PT_LRM]="LRM";
    m[PT_LRA]="LRA";
    m[PT_LTA]="LTA";
    m[PT_CM]="CM";
    m[PT_WER]="WER";
    m[PT_SRM]="SRM";
    m[PT_SRR]="SRR";
    m[PT_SWA]="SWA"; //old swa product save as swa_t
    m[PT_SWA4]="SWA";
    m[PT_SWP]="SWP";
    m[PT_SHEAR] ="SHEAR";
    m[PT_STI]="STI";
    m[PT_M]="M";
    m[PT_TVS]="TVS";
    m[PT_HI]="HI";
    m[PT_SS]="SS";
    m[PT_WIND]="WIND";
    m[PT_WIND_T]="WIND_T";
    m[PT_STP]="STP";
    m[PT_SPD]="SPD";
    m[PT_USP]="USP";
    m[PT_OHP]="OHP";
    m[PT_OHP_T]="OHP_T";
    m[PT_THP]="THP";
    m[PT_GAGE]="GAGE";
    m[PT_CATCH]="CATCH";
    m[PT_VAD]="VAD";
    m[PT_VWP]="VWP";
    m[PT_UAM]="UAM";
    m[PT_CTR]="CONTOUR";
    m[PT_FTM]="FTM";
    m[PT_RAW]="RAW";
    m[PT_RHI]="RHI";
    m[PT_PDA]="PDA";
    m[PT_PDA_T]="PDA_T";
    m[PT_HCL]="HCL";
    m[PT_MBD]="MB";
    m[PT_ML]="ML";
    m[PT_ML_T]="ML_T";
    m[PT_IGST]="IGST";
    m[PT_USER] = "USER";
    m[PT_COMP] = "COMP";
    m[PT_NGRID] = "NGRID";
    m[PT_SWIS]="SWIS";
    m[PT_DSD]="DSD";
    m[PT_QPE]="QPE";
    m[PT_QPE_T]="QPE_T";
    m[PT_HCL_T]="HCL_T";
    m[PT_GF_T]="GFT";
    m[PT_GFD]="GF";
    m[PT_HVVP]="HVVP";
    m[PT_SLINE]="SLINE";
    m[PT_NDOP] = "NDOP";
    m[PT_CM] = "CM";
    m[PT_NUAM] = "NUAM";
    m[PT_NCATCH] = "NCATCH";
    m[PT_NSCAN] = "NSCAN";

    /* for legacy products */
    m[PT_R]   = "R";
    m[PT_V]   = "V";
    m[PT_SW]  = "SW";
    m[PT_CR]  = "CR";
    m[PT_CRC] = "CRC";
    m[PT_ETC] = "ETC";
    m[PT_CS]  = "CS";
    m[PT_CSC] = "CSC";
    m[PT_SWR] = "SWR";
    m[PT_SWV] = "SWV";
    m[PT_SWW] = "SWW";
    m[PT_SWS] = "SWS";
    m[PT_RCS] = "RCS";
    m[PT_ET2] = "ET";
    m[PT_SCS] = "SCS";
    m[PT_CAR] = "CAR";
    m[PT_CAV] = "CAV";
    m[PT_CAS] = "CAS";
    m[PT_PPR] = "PPR";
    m[PT_PPV] = "PPV";
    m[PT_PPS] = "PPS";
    m[PT_RHR] = "RHR";
    m[PT_RHV] = "RHV";
    m[PT_RHS] = "RHS";
    return true;
}

/* product type vs task type table, task type is defined in taskConst.h
	SP_VOL=0, //mulit ppi is included,marked as VOL_START,CUT_END,CUT_START,CUT_END....VOL_END 
	SP_PPI=1, // single ppi, marked as VOL_START,VOL_END
	SP_RHI=2,//  single rhi, marked as VOL_START,VOL_END
	SP_SECTOR=3,// single ppi sector  ,marked as VOL_START,VOL_END
	SP_VOL_SECT=4, //mulit sector scan is included ,marked same as volume scan
	SP_VOL_RHI=5,//mulit rhi scan is included ,marked same as volume scan
	SP_MAN=6, 
*/
bool CreateProdTypeTaskMap(TypeMaskMap &m)
{
    m[PT_PPI]=0x1B;
    m[PT_PPI_T]=0x1B;
    m[PT_CAPPI]=0x11;
    m[PT_MAX]=0x11;
    m[PT_ET]=0x11;
    m[PT_BEAM]=0x7F;
    m[PT_EB]=0x11;
    m[PT_VIL]=0x11;
    m[PT_HMAX]=0x11;
    m[PT_HSR]=0x11;
    m[PT_SRI]=0x11;
    m[PT_VCS]=0x11;
    m[PT_LRM]=0x11;
    m[PT_LRA]=0x11;
    m[PT_LTA]=0x11;
    m[PT_CM]=0x11;
    m[PT_WER]=0x11;
    m[PT_SRM]=0x1B;
    m[PT_SRR]=0x1B;
    m[PT_SWA]=0x1B;
    m[PT_SWA4]=0x1B;
    m[PT_SWP]=0x11;
    m[PT_SHEAR]=0x1B;
    m[PT_STI]=0x11;
    m[PT_M]=0x11;
    m[PT_MBD]=0x11;
    m[PT_TVS]=0x11;
    m[PT_HI]=0x11;
    m[PT_SS]=0x11;
    m[PT_WIND]=0x11;
    m[PT_WIND_T]=0x11;
    m[PT_STP]=0x11;
    m[PT_SPD]=0x11;
    m[PT_USP]=0x11;
    m[PT_OHP]=0x11;
    m[PT_OHP_T]=0x11;
    m[PT_THP]=0x11;
    m[PT_GAGE]=0x11;
    m[PT_VAD]=0x11;
    m[PT_VWP]=0x11;
    m[PT_UAM]=0x1B;
    m[PT_CTR]=0x1B;
    m[PT_FTM]=0x7B;
    m[PT_RAW]=0x1B;
    m[PT_RHI]=0x24;
    m[PT_PDA]=0x11;
    m[PT_PDA_T]=0x11;
    m[PT_ML]=0x11;
    m[PT_ML_T]=0x11;
    m[PT_IGST]=0x11;
    m[PT_USER]=0x11;
    m[PT_HCL]=0x1B;
    m[PT_ML]=0x13;
    m[PT_SWIS]=0x11;
    m[PT_DSD]=0x1B;
    m[PT_QPE]=0x11;
    m[PT_QPE_T]=0x11;
    m[PT_HCL_T]=0x1B;
    m[PT_GF_T]=0x11;
    m[PT_GFD]=0x11;
    m[PT_HVVP]=0x11;
    m[PT_SLINE]=0x11;
    m[PT_COMP]=0x1B;
    m[PT_NGRID]=0x1B;
    m[PT_NDOP]=0x1B;
    m[PT_CM]=0x11;
    m[PT_NUAM]=0x1B;
    m[PT_CATCH]=0x1B;
    m[PT_NCATCH]=0x1B;
    m[PT_NSCAN]=0x1B;
    return true;
}

static NameIndexMap RdtNameMap;
static NameIndexMap RdtShortNameMap;
static NameIndexMap RdtUnitMap;
static NameIndexMap ProdTypeNameMap;
static TypeMaskMap ProdTypeTaskMap; //product type vs task types
static NameIndexMap RdtUnitNameMap;
// trick to init RdtNameMap and ProdTypeNameMap;
static bool _dump1=CreateRdtNameMap(RdtNameMap);
static bool _dump11=CreateRdtShortNameMap(RdtShortNameMap);
static bool _dump2=CreateProdTypeNameMap(ProdTypeNameMap);
static bool _dump21=CreateProdTypeTaskMap(ProdTypeTaskMap);
static bool _dump3=CreateRdtUnitMap(RdtUnitMap);
static bool _dump4=CreateRdtUnitNameMap(RdtUnitNameMap);

int NameToIndex(NameIndexMap &m,const char *rdtstr)
{
    NameIndexMap::iterator it;
    for(it=m.begin();it!=m.end();it++)
    {
        if(strcmp(it->second,rdtstr)==0)
            return it->first;
    }
    return -1;
}
const char *IndexToName(NameIndexMap &m,const int rdti)
{
    NameIndexMap::iterator it;
    it=m.find(rdti);
    if(it!=m.end())
    {
        return it->second;
    }

    //zhangchian, chang from NULL to ?, for PUP product configuration - DSP data, NULL leads to exepction
    return "?";
}
int RdtToIndex(const char *rdtstr)
{
    return NameToIndex(RdtNameMap,rdtstr);
}
int RdtToIndex(const string &rdtstr)
{
    return RdtToIndex(rdtstr.c_str());
}
const char * RdtToStr(const int rdti)
{
    return IndexToName(RdtNameMap,rdti);
}
const char * RdtToShortStr(const int rdti)
{
    return IndexToName(RdtShortNameMap,rdti);
}

int ProdTypeToIndex(const char *prodstr)
{
    return NameToIndex(ProdTypeNameMap,prodstr);
}
const char * ProdTypeToStr(const int prodi)
{
    return IndexToName(ProdTypeNameMap,prodi);
}
int ProdTypeToIndex(const string &prodstr)
{
    return ProdTypeToIndex(prodstr.c_str());
}
int GetProdTaskMask(int prodtype)
{
    TypeMaskMap::iterator it;
    it=ProdTypeTaskMap.find(prodtype);
    if(it!=ProdTypeTaskMap.end())
    {
        return it->second;
    }

    return 0;
}
const char *RdtUnit(int rdt)
{
    return RdtUnitMap[rdt];
}
const char * RdtUnitName(const int prodi)
{
    return RdtUnitNameMap[prodi];
}

int getCorrectedRdt(int type)
{
    if (type==RDT_ZDR)
        return RDT_ZDRC;
    else if (type==RDT_CC)
        return RDT_CCC;
    else if (type==RDT_PDP)
        return RDT_PDPC;
    else if (type==RDT_KDP)
        return RDT_KDPC;
    else if (type==RDT_DBZ)
        return RDT_DBZC;
    else if (type==RDT_VEL)
        return RDT_VELC;
    else if (type==RDT_WID)
        return RDT_WIDC;
    else if (type==RDT_LDR)
        return RDT_LDRC;
    else return 0;
}


int getBasedRdt(int type)
{
    if (type==RDT_ZDRC)
        return RDT_ZDR;
    else if (type==RDT_CCC)
        return RDT_CC;
    else if (type==RDT_PDPC)
        return RDT_PDP;
    else if (type==RDT_KDPC)
        return RDT_KDP;
    else if (type==RDT_DBZC)
        return RDT_DBZ;
    else if (type==RDT_VELC)
        return RDT_VEL;
    else if (type==RDT_WIDC)
        return RDT_WID;
    else if (type==RDT_LDRC)
        return RDT_LDR;
    else return type;
}
