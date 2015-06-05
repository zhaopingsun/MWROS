// **********************************************************************
//
// Copyright (c) 1996-2014 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#ifndef RADAR_GENERIC_BASEDATA_H
#define RADAR_GENERIC_BASEDATA_H
#include "genericHeader.h"
#include "genericTask.h"
#ifdef __linux__
#include <sys/time.h>
#endif
#pragma pack(push,1)
// uni data flag
#define UDTF_POL 0// data polarization  hori/vert
#define HORI 0
#define VERT 2
/**
  format of basedata

  	geneHeader  
	geneSiteConfig 
	geneTaskConfig
	N*{geneCutConfig,N is the cutNum in geneTaskConfig
	}
	geneTaskSpec 
	K*{radials of cut 1,k is number of radails in this cut
			
	}
	...
	...
	K*(radials of cut n}

format of radials
	geneRadialHeader
	N*{ geneMomHeader+ real_ data_stream  ,N is the momNum in taskconfig} 
  */
struct geneUniDataType{
	int type;
	int scale;
	int offset;
	short binSize; //length of bytes for each bin
    	short flag;
};
struct geneMomHeader :public geneUniDataType
{
	int length;//length of data in bytes,this header is not included.
	int spared[3];
//add for pup windows vss compiler
#ifdef __linux__
	unsigned char data[0];
#endif
};
float decodeMomData(const geneMomHeader *pmh,unsigned short data);
int copyMomData(const geneMomHeader *pmh,unsigned short *pdata);
int decodeMomData(const geneMomHeader *pmh,float *pdata);

/**
  status of the cut,it is used to mark sweep and radial.
  \todo rename it to CutState.
  it should match with the radial state with basedata file.
  */
#if 0
    const short CUT_START=0;
    const short CUT_MID=0;    
    const short CUT_END=2;
    const short VOL_START=3;
    const short VOL_END=4;
    const short RHI_START=5;
    const short RHI_END=6;    
#endif

/* header block length in bytes */
const int BD_HEADER_LEN=128;  

/* radial status */
enum  RadailState{CUT_START,CUT_MID,CUT_END,VOL_START,VOL_END,
	RHI_START, RHI_END, CUT_INIT,FORCE_END};
enum  BaseDataTyp{BDFMT_GENERIC=0,BDFMT_CINRAD=1,BDFMT_IRIS=2,BDFMT_ORPG=3};
struct geneRadialHeader
{
	int state;
	int spotblank;
	int seqNum;
	int radIdx; //radial number in each cut, from 1 
	int elIdx; //elevation/cut number, from 1
	float az;
	float el;
	int timeSec;
	int timeUsec;
	int length;// length of data in this radial, this header is not included.
	int momNum;//moments available in this radials.
	int spared[5];
};

struct geneCutSpec
{
		int startTime;
		int endTime;
		short index;//index in the task config, start from 0
		short dataType;
		short reso;	
};

struct geneBaseBuffKey
{
    char siteCode[SITE_CODE_LENGTH];
    char taskName[TASK_NAME_LENGTH];
	int volStartTime; //start of volume
	int ingestTime; //ingest time
	short fixedAngle;// *10 it' el for ppi ,az for rhi
	short dataType;//z,v,w,t,zdr...
};
// add struct basedata
#pragma pack(pop)
#endif
