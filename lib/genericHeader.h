// **********************************************************************
//
// Copyright (c) 1996-2014 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#ifndef RPG_GENERIC_DATA_HEADER
#define RPG_GENERIC_DATA_HEADER
int const GDT_BASEDATA=1;
int const GDT_PRODUCT=2;
int const GDT_TASK_CONFIG=3;
int const GDT_MAGIC=0x4D545352;//MTSR
int const MAJOR_VER=1;
int const MINOR_VER=1;
struct geneHeader{
	int magic;//same with GDT_MAGIC
	short majorVer;
	short minorVer;
	int msgType;
	int prodType;// only valid  when msgtype is GDT_PRODUCT
	int spared[4];
};


#define MAX_TILTS_NUM 14
#define RADAR_NOECHO -1280
#define RADAR_FOLDED -1281
#define RADAR_NODATA -32768

void geneHeaderInit(geneHeader &hdr,int type);
#endif
