// **********************************************************************
//
// Copyright (c) 1996-2014 Beijing Metstar Radar, Inc. All rights reserved.
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
	unsigned int spared:26;
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
typedef vector<short> shortVec;
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
#define SITE_CODE_LENGTH 8
#define SITE_NAME_LENGTH 32
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
	int spare[15];
};
void getWaveformExplain(char*buf);
void getPolAvailMoms(int pol,int chan,shortVec &dt);
const char *PCDesp(int pc);
int PCIndex(const char *desp);
const char *GCCDesp(int gcc);
int GCCIndex(const char *desp);
#pragma pack(pop)
#endif
