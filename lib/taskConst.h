// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#ifndef TASK_CONFIG_CONST_H
#define TASK_CONFIG_CONST_H

//not speed of light in vacuum,refractrive index of air is included.
const float SPEED_OF_LIGHT=(float)299735000.0;//m/s

enum {
	SCAN_SYNC_AUTO=0,
	SCAN_SYNC_MANU=1
};
enum{
	WF_CS=0,//cs mode
	WF_CD=1,//doppler mode
	WF_CDX=2,//cdx mode
	WF_RX_TEST=3, 
	WF_BATCH=4,//batch mode
	WF_DPRF=5, //dual prf
	WF_RPHASE=6,//random phase
	WF_SZ=7,//sz 8/64 code
	WF_SPRT=8 //staggered prt	
};
enum {
	SP_VOL=0, //mulit ppi is included,marked as VOL_START,CUT_END,CUT_START,CUT_END....VOL_END 
	SP_PPI=1, // single ppi, marked as VOL_START,VOL_END
	SP_RHI=2,//  single rhi, marked as VOL_START,VOL_END
	SP_SECTOR=3,// single ppi sector  ,marked as VOL_START,VOL_END
	SP_VOL_SECT=4, //mulit sector scan is included ,marked same as volume scan
	SP_VOL_RHI=5,//mulit rhi scan is included ,marked same as volume scan
	SP_MAN=6 //mannual scan,or fixed scan,marked as PPI,radial num is 360/angluar_reso 
};
bool isPPIFull(int sc);
bool isPPISector(int sc);
bool isRHI(int sc);
bool isVolScan(int sc);
bool isPPI(int sc);

enum {
	 PRF_SINGLE=1,
	 PRF_2V3=2,
	 PRF_3V4=3,
	 PRF_4V5=4
};

//process mode
enum {
	 PM_PPP=1,
	 PM_FFT=2,
	 PM_RP=3
};

enum {
	 POL_HORI=0,// horizontal only
	 POL_VERT=1,//vertical only
	 POL_ALT=2,
	 POL_SIMU=3// simu star mode
};
#define  MAX_POL_TYPE_NUM 4 

#define  MAX_TSC_NUM 16
#define  TASK_NAME_LENGTH 32
#define  TASK_DESP_LENGTH 128
#define  MAX_MOM_NUM 64  //maxinum moment data number in raw product
#define  MAX_CUT_NUM 32 //maximum cut number for one task
#define  MAX_RAD_NUM 1000 //maximum radial number for one cut
#define  MAX_BIN_NUM 4000 //maximum bin number for one radial
enum {
	 QC_LOG=1,//LOG THRESH CONTROL BIT
	 QC_SQI=2,//SQI THRESH CONTROL BIT
	 QC_CCR=4,//CCR THRESH CONTROL BIT
	 QC_SIG=8,//SIG THRESH CONTROL BIT
	 QC_PMI=16,
	 QC_DPLOG=32,
	
};
#define QC_MAX (QC_DPLOG+1)
#define QC_MASK_NUM 6
#define QC_MASK_CONJ "&"
//description of antenna rotation direction
enum {
	 ROT_CW = 1, //clockwise
	 ROT_CCW = 2 //counter-clockwise
};
//ground clutter classfier
enum {
	GCC_AP=1,//all pass,treat all bins as weather signal,filter no bins then
	GCC_NP=2,//none pass, treat all bins as ground clutter, filter all bins then
	GCC_RT=3,//use real time ground clutter classfier CMD algorithm
	GCC_PRE=4 // use predefined by pass map
};
//ground clutter filter
enum {
	GCF_NONE=0,//no filter,comp
	GCF_ADAPTIVE=1,//fft adaptive
	GCF_FIXED=2,// fft fixed
	GCF_VARI=3,//fft varied
	GCF_VARSQ=4,
	GCF_IIR=5// IIR filter
};
enum {
	WINDOW_NONE= -1,
	WINDOW_RECT=0,//rectangle window
	WINDOW_HAMMING=1,//hamming window
	WINDOW_BLACKMAN=2,//blackman window
	WINDOW_ADAPTIVE=3,//adaptive window
	WINDOW_CHEB80=4,//DOLPH-CHEBYSHEV window
 	WINDOW_FUNC_NUM=5// number of window function
};
//phase code type
enum {
	PC_FIXED=0,//fix phase
	PC_RANDOM=1,//random phase 
	PC_SZ64=2,//sz 8/64 code 
	PC_TEST=3, // test code ,download phasecode 0,1,2,3....127
	PC_POLY=4
};
#endif
