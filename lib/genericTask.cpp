// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#include "genericTask.h"
#include "NameIndexUtil.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "genericBasedata.h"
#include <map>
#include "NameIndex.h"
#include "radar_dt.h"
static NameIndexMap scanSyncMap;
static NameIndexMap WaveFormMap;
static NameIndexMap ProcModeMap;
static NameIndexMap UnfoldModeMap;
static NameIndexMap ScanTypeMap;
static NameIndexMap PolMap;
static NameIndexMap QcMaskMap;
static NameIndexMap RadStateMaskMap;
static NameIndexMap GCFilterMaskMap;
static NameIndexMap GCWinMaskMap;
static NameIndexMap GCClassfierMap;
static NameIndexMap PhaseCodeMap;

bool CreateDefaultNameMap()
{
	scanSyncMap[0]="Auto";
	scanSyncMap[1]="Manual";
	
	WaveFormMap[WF_CS]="CS";
	WaveFormMap[WF_CD]="CD";
	WaveFormMap[WF_CDX]="CDX";
	WaveFormMap[WF_BATCH]="BATCH";
	WaveFormMap[WF_DPRF]="DPRF";
	WaveFormMap[WF_RPHASE]="RPH";
	const char *SZ_DESP="SZ 8/64";
	WaveFormMap[WF_SZ]=SZ_DESP;
	WaveFormMap[WF_SPRT]="SPRT";

	ProcModeMap[PM_PPP]="PPP";//pulse pair process
	ProcModeMap[PM_FFT]="FFT";//requency process
	ProcModeMap[PM_RP]="RPP";//random phase process 

	UnfoldModeMap[PRF_SINGLE]="NONE";
	UnfoldModeMap[PRF_2V3]="3:2";
	UnfoldModeMap[PRF_3V4]="4:3";
	UnfoldModeMap[PRF_4V5]="5:4";

	ScanTypeMap[SP_VOL]="VCP";
	ScanTypeMap[SP_PPI]="PPI";
	ScanTypeMap[SP_RHI]="RHI";
	ScanTypeMap[SP_SECTOR]="PPI Sector";
	ScanTypeMap[SP_VOL_SECT]="Sector VCP";
	ScanTypeMap[SP_VOL_RHI]="RHI VCP";
	ScanTypeMap[SP_MAN]="Fixed";

	PolMap[POL_HORI]="Hori";
	PolMap[POL_VERT]="Vert";
	PolMap[POL_ALT]="Alt";
	PolMap[POL_SIMU]="Simu";

	QcMaskMap[QC_LOG]="LOG";
	QcMaskMap[QC_CCR]="CSR";
	QcMaskMap[QC_SQI]="SQI";
	QcMaskMap[QC_SIG]="SIG";
	QcMaskMap[QC_PMI]="PMI";
	QcMaskMap[QC_DPLOG]="DPLOG";

#define INIT_RADST_MAP(a) \
	RadStateMaskMap[a]=#a
	INIT_RADST_MAP(CUT_END);
	INIT_RADST_MAP(CUT_START);
	INIT_RADST_MAP(CUT_MID);
	INIT_RADST_MAP(VOL_START);
	INIT_RADST_MAP(VOL_END);

	GCFilterMaskMap[GCF_ADAPTIVE]="Adaptive";
	GCFilterMaskMap[GCF_NONE]="None";
	GCFilterMaskMap[GCF_FIXED]="Fixed";
	GCFilterMaskMap[GCF_VARSQ]="VarLSQ";
	GCFilterMaskMap[GCF_VARI]="Vari";
	GCFilterMaskMap[GCF_IIR]="IIR";

	GCWinMaskMap[WINDOW_NONE]="NONE";
	GCWinMaskMap[WINDOW_RECT]="RECT";
	GCWinMaskMap[WINDOW_HAMMING]="HAMMING";
	GCWinMaskMap[WINDOW_BLACKMAN]="BLACKMAN";

	PhaseCodeMap[PC_FIXED]="FIXED";	
	PhaseCodeMap[PC_RANDOM]="RANDOM";	
	PhaseCodeMap[PC_SZ64]=SZ_DESP;	
	PhaseCodeMap[PC_TEST]="TEST";	
	PhaseCodeMap[PC_POLY]="POLY";	

	GCClassfierMap[GCC_AP]="All Pass";
	GCClassfierMap[GCC_NP]="None Pass";
	GCClassfierMap[GCC_RT]="CMD";
	GCClassfierMap[GCC_PRE]="Map";
	return true;
}
static bool _dump1=CreateDefaultNameMap();
const char*RadStateDesp(int s)
{
	return IndexToName(RadStateMaskMap,s);
}
int RadStateType(const char* desp)
{
	return NameToIndex(RadStateMaskMap,desp);
}
//refine the following code when boost >1.35 is supported by devel env"
const char *scanSyncDesp(int ss)
{
	return IndexToName(scanSyncMap,ss);
}
int WaveformIndex(const char *swf)
{
	return NameToIndex(WaveFormMap,swf);
}
/**
  return description the waveform
  */
const char * WaveformDesp(int wf)
{
	return IndexToName(WaveFormMap,wf);
}
const char *ProcessModeDesp(int pm)
{
	return IndexToName(ProcModeMap,pm);
}
const char *unfoldModeDesp(int um)
{
	return IndexToName(UnfoldModeMap,um);
}
int ScanTypeIndex(const char *st)
{
	return NameToIndex(ScanTypeMap,st);
}
const char* ScanTypeDesp(int st)
{
	return IndexToName(ScanTypeMap,st);
}
int PolType(const char *pol)
{
	return NameToIndex(PolMap,pol);
}
const char *PolDesp(int pol)
{
	return IndexToName(PolMap ,pol);
}
const char *QcMaskDesp(int qm)
{
	return IndexToName(QcMaskMap ,qm);
}
int QcMaskType(const char* desp)
{
	return NameToIndex(QcMaskMap,desp);
}
short getMomList(long long momMask,shortVec &seq)
{
	seq.resize(0);
	unsigned int *pData = (unsigned int *)&momMask;

	unsigned int bit,index;
	for (int i=0;i<MAX_MOM_NUM;i++)
	{
		bit = 1<<(i%32);
		index = i/32;
		if (pData[index]&bit)
			seq.push_back(i);
	}

	return seq.size();
}

void getMomSizeList(long long msm,shortVec &seq)
{
	seq.resize(MAX_MOM_NUM);
	unsigned int *pData = (unsigned int *)&msm;

	unsigned int bit,index;
	for(int i=0;i<MAX_MOM_NUM;i++)
	{
		bit = 1<<(i%32);
		index = i/32;
		if(pData[index]&bit)
			seq[i]=2;
		else
			seq[i]=1;
	}
}

int getMomDataSize(long long msm,int rdt)
{
	if (rdt<0||rdt>MAX_MOM_NUM) return 1;

	unsigned int *pData = (unsigned int *)&msm;
	unsigned int bit,index;
	bit = 1<<(rdt%32);
	index = rdt/32;

	if (pData[index]&bit) return 2;
	else return 1;
}

short getMomNum(long long momMask)
{
	short count = 0;
	unsigned int *pData = (unsigned int *)&momMask;
	unsigned int bit,index;

	for(int i=0;i<MAX_MOM_NUM;i++)
	{
		bit = 1<<(i%32);
		index = i/32;
		if(pData[index]&bit) count++;
	}
	return count;
}

long long getMomMask(shortVec seq)
{
	unsigned long long mask = 0;
	unsigned int *pData = (unsigned int *)&mask;
	unsigned int bit,index;
	
	for(unsigned int i=0;i<seq.size();i++)
	{
		if (seq[i]<0||seq[i]>MAX_MOM_NUM)  continue;
		bit = 1<<(seq[i]%32);
		index = seq[i]/32;

		pData[index] |= bit;
	}

	return mask;
}

void formatMomMask(long long mom,long long msize,char *desp)
{
	shortVec momSeq,sSeq;
	getMomList(mom,momSeq);
	getMomSizeList(msize,sSeq);
	char buf[32]={0};
	for(unsigned int i=0;i<momSeq.size();i++)
	{
		int dt=momSeq[i];
		int ds=sSeq[dt];
		sprintf(buf,"%s%d ",RdtToStr(dt),ds);
		strcat(desp,buf);
	}
}

void setMomMask(short dt,long long &momMask) 
{
	if (dt<0||dt>MAX_MOM_NUM) return;
	unsigned int *pData = (unsigned int *)&momMask;
	unsigned int bit,index;
	bit = 1<<(dt%32);
	index = dt/32;
	pData[index] |= 1<<dt;
}

void clrMomMask(short dt,long long &momMask)
{
	if (dt<0||dt>MAX_MOM_NUM) return;
	unsigned int *pData = (unsigned int *)&momMask;
	unsigned int bit,index;
	bit = 1<<(dt%32);
	index = dt/32;

	pData[index] &= ~bit;
}

bool isDataAvail(long long momMask,short dt)
{
	if(dt<0||dt>MAX_MOM_NUM) return false;

        //for corrected data type
        dt = getBasedRdt(dt);

	unsigned int *pData = (unsigned int *)&momMask;
	unsigned int bit,index;
	bit = 1<<(dt%32);
	index = dt/32;

	if (pData[index]&bit) return true;
	else return false;
}

int parseQCMask(const char *str)
{
	int mask=0;
	if(str==NULL) return mask;

	char qc[256]={0};
	
	int i=0,j=0;
	int len = strlen(str);
	while(i<len)
	{
		if (str[i]==QC_MASK_CONJ[0])
		{
			qc[j] = 0;
			if (strlen(qc))
			{
				int bit = QcMaskType(qc);
				if(bit>0) mask+=bit;
			}
			
			j = 0;
		}
		else
		{
			qc[j++] = str[i];
		}
		i++;
	}
	
	//process last one
	qc[j] = 0;
	if (strlen(qc))
	{
		int bit = QcMaskType(qc);
		if(bit>0) mask+=bit;
	}	
		
//	printf("mask %x\n",mask);
	return mask;
}
void formatQcMask(int mask ,char *str)
{
	for(int i=0;i<QC_MASK_NUM;i++)
	{
		int bit=1<<i;
		if(bit&mask)
		{
			const char *desp=QcMaskDesp(bit);
			if(desp!=NULL)
			{
				strcat(str,desp);
				strcat(str,QC_MASK_CONJ);
			}
		}
	}
	if(strlen(str)>1)
		str[strlen(str)-1]=0;
//	printf("qc mask %s\n",str);
}
const char *GCFilterDesp(int gcf)
{
	return IndexToName(GCFilterMaskMap,gcf);
}
int GCFilterIndex(const char *desp)
{
	return NameToIndex(GCFilterMaskMap,desp);
}
const char *GCWinDesp(int win)
{
	return IndexToName(GCWinMaskMap,win);
}
int GCWinIndex(const char *desp)
{
	return NameToIndex(GCWinMaskMap,desp);
}
void geneHeaderInit(geneHeader &hdr,int type)
{
	memset(&hdr, 0, sizeof(geneHeader));
	hdr.msgType=type;
	hdr.magic=GDT_MAGIC;
	hdr.majorVer=MAJOR_VER;
	hdr.minorVer=MINOR_VER;
}
bool isPPIFull(int sc)
{
	return sc==SP_VOL||sc==SP_PPI;
}
bool isPPISector(int sc)
{
	return sc==SP_SECTOR||sc==SP_VOL_SECT;
}
bool isRHI(int sc)
{
	return sc==SP_RHI||sc==SP_VOL_RHI;
}
bool isVolScan(int sc)
{
	return sc==SP_VOL||sc==SP_VOL_RHI||sc==SP_VOL_SECT;
}
bool isPPI(int sc)
{
	return isPPISector(sc)||isPPIFull(sc);
}
void getWaveformExplain(char*buf)
{
	//WaveFormMap
	NameIndexMap::iterator it;
	int pos=0;
	for(it=WaveFormMap.begin();it!=WaveFormMap.end();it++)
	{
		size_t len=sprintf(&buf[pos],"%s=%d ",it->second,it->first);	
		pos+=len;
	}
}
void getPolAvailMoms(int pol,int chan,shortVec &dt)
{
	// data types available for all mode
	short COMMON_MOMS[]={RDT_DBT,RDT_DBZ,RDT_VEL,RDT_WID,RDT_SQI,RDT_SNR,RDT_CF,-1};	
	//data types dual pol simu mode 
	short DUAL_POL_MOMS[]={RDT_ZDR,RDT_KDP,RDT_CC,RDT_PDP,RDT_SNRV,-1};
	//data types for single pol while have two channels
	short SGL_POL_2CHAN_MOMS[]={RDT_LDR,RDT_CC,RDT_PDP,-1};
	int i=0;
	while(COMMON_MOMS[i]>0)
		dt.push_back(COMMON_MOMS[i++]);
	i=0;
	if(pol==POL_SIMU&&chan==2)
	{
		while(DUAL_POL_MOMS[i]>0)
			dt.push_back(DUAL_POL_MOMS[i++]);
	}
	else if(pol==POL_HORI&&chan==2)
	{
		i=0;
		while(SGL_POL_2CHAN_MOMS[i]>0)
			dt.push_back(SGL_POL_2CHAN_MOMS[i++]);
	}
}
const char *PCDesp(int pc)
{
	return IndexToName(PhaseCodeMap,pc);
}
int PCIndex(const char *desp)
{
	return NameToIndex(PhaseCodeMap,desp);
}
const char *GCCDesp(int gcc)
{
	return IndexToName(GCClassfierMap,gcc);
}
int GCCIndex(const char *desp)
{
	return NameToIndex(GCClassfierMap,desp);
}
//update cut config after signal process and before send basedata to RPG 
void finalUpdateCut(geneCutConfig *pcc)
{
	pcc->startRange=0;
	if(pcc->waveForm==WF_CD)
        {       
                pcc->maxRange=pcc->maxRange2;
        }   
}
//compute ambugous range  from PRF
// range in meter
int compAmbRange(int prf)
{
	return SPEED_OF_LIGHT/2/prf;
}
