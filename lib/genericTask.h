// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#ifndef RADAR_GENERIC_TASK_H
#define RADAR_GENERIC_TASK_H
#pragma pack(push,1)
#include <vector>
using namespace std;
#include"taskConst.h"
struct geneQcThresh{
	float sqi;//signal quality index
	float sig;//weather signal thresh
	float csr;//cluter signal ratio
	float log;//singal noise ratio
	float cpa;//const phase aligment
	float pmi;//polarimetric meteo index
	float dplog;
	float spare[1];
};

struct geneQcMask{
	int dbt;
	int dbz;
	int vel;
        int wid;	
	int dpvar;//thresh apply to dual pol variable
	int spare[3];
};
struct geneFilterMask{
	unsigned int interFilter:1;
	unsigned int censorFilter:1;
	unsigned int spekFilter1DLog:1;
	unsigned int spekFilter1DDop:1;
	unsigned int spekFilter2DLog:1;
	unsigned int spekFilter2DDop:1;
	unsigned int nebor:1;//1 for enable noise estimation
	unsigned int gccal:1;//1 for enable ground clutter calibration 
	unsigned int spared:24;
};

int WaveformIndex(const char *swf);
const char* WaveformDesp(int wf);
int ScanTypeIndex(const char *st);
const char* ScanTypeDesp(int st);
const char *ProcessModeDesp(int pm);
const char *unfoldModeDesp(int um);
const char *PolDesp(int pol);
int PolType(const char *pol);
const char *QcMaskDesp(int qm);
int QcMaskType(const char* desp);
int parseQCMask(const char *str);
void formatQcMask(int mask ,char *str);
const char*RadStateDesp(int s);
int RadStateType(const char* desp);

const char *scanSyncDesp(int);
struct geneCutConfig{
	/** although pol scantype and pulsewidth should not changed within a VCP,we still put it
	  in cut configuration ,make controlword easy.
	*/
	int processMode;
	int waveForm;
	//for cut have one prf, prf2 and  maxrange2 should be ignored or same as prf and maxrange
	// for cut have two prfs prf <-> maxrange  ,prf2 <->maxrange2	
	// prf2 is used in dprf and batch mode, prf2 is the low prf (cs prf in batch mode)
	float prf;// in hz
	float prf2;//in hz
	int unfoldMode;
	float az;
	float el;
	float startAngle;
	float endAngle;
	float angleReso;
	float scanSpeed;// use sign as cw/rcw
	int logReso;
	int dopReso;
	int maxRange;
	//maxrange2 will be enabled for CD mode with random phase code or SZ phase code,
	//which means the max unfold range,2 times for RP and 3 times for SZ 
	int maxRange2;
	int startRange;
	int samples;
	int samples2;//for batch modes'sur samples
	int phaseMode;
	float atmos;
	float nyquist;
	long long momMask;//moments available in this cut, bit
	long long momSizeMask;//mask for moment data size 1 for 16bit 0 for 8bit
	geneFilterMask filterMask;
	geneQcThresh qcThresh;
	geneQcMask qcMask;
	int scanSync;
	int direction; //antenna rotate direction, CW or CCW
	//all for ground clutter filter
	short gcCf;
	short gcFilter;
	short gcNw;
	short gcWin;
	char twins;
	//ground clutter filter related options
	unsigned char gcfMinWidth;
	unsigned char gcfEdgePoints;
	unsigned char gcfSlopePoints;
	int spare[17];
};
typedef vector<unsigned short> shortVec;
short getMomNum(long long momMask);
short getMomList(long long momMask,shortVec &seq);
long long getMomMask(shortVec seq);
/**  get moment mask from predefined waveform*/
long long getMomMaskFromWF(int wf);
bool isDataAvail(long long momMask,short dt);
void clrMomMask(short dt,long long &momMask);
void setMomMask(short dt,long long &momMask);
void getMomSizeList(long long msm,shortVec &seq);
int getMomDataSize(long long msm,int rdt);
int GCFilterIndex(const char *desp);
const char *GCFilterDesp(int gcf);
int GCWinIndex(const char*desp);
const char *GCWinDesp(int win);
void formatMomMask(long long mom,long long msize,char *desp);
void finalUpdateCut(geneCutConfig *pcc);
int compAmbRange(int prf);
struct geneTaskConfig{
	char name[TASK_NAME_LENGTH];
	char desp[TASK_DESP_LENGTH];
	int pol;
	int scanType;
	int pulseWidth;
	int startTime;
	int cutNum;
	float horNoise;
	float verNoise;
	float horCalib;
	float verCalib;
	float horNoiseTemp;
	float verNoiseTemp;
	float zdrCal;
	float phaseCal;
	float ldrCal;
	int spare[10];
};
struct geneTscConfig{
	char taskname[TASK_NAME_LENGTH];
	int startTime;  //seconds of task start time in one day
	int stopTime;   //seconds of task stop time in one day 
	int period; // seconds of task schedule period 
	char spared[20];
};
struct geneTaskSchedule{
	char name[TASK_NAME_LENGTH];
	char desp[TASK_DESP_LENGTH];
	int num;
//	geneTscConfig tscConfig[MAX_TSC_NUM];
	char spared[12];
};
#define SITE_CODE_LENGTH 8
#define SITE_NAME_LENGTH 32

//ALL CINRAD RADAR MODEL 
//S BAND
#define MODEL_SA 1
#define MODEL_SB 2
#define MODEL_SC 3
//C BAND
#define MODEL_CA 33
#define MODEL_CB 34
#define MODEL_CC 35
#define MODEL_CCJ 36
#define MODEL_CD 37
//X BAND
#define MODEL_XA 65 
struct geneSiteConfig{
	char code[SITE_CODE_LENGTH];
	char name[SITE_NAME_LENGTH];
	float lat;
	float lon;
	int height;
	int ground;
	float freq;
	float beamwidth;
	float beamwidthVert;
	int rdaVersion;//rdasc source code svn version
	short model;// refer to MODEL_xx
	char spared[2];
	int spare[13];
};
void getWaveformExplain(char*buf);
void getPolAvailMoms(int pol,int chan,shortVec &dt);
const char *PCDesp(int pc);
int PCIndex(const char *desp);
const char *GCCDesp(int gcc);
int GCCIndex(const char *desp);
#pragma pack(pop)
#endif
