#ifndef RDA_TS_HEADER
#define RDA_TS_HEADER
#include <sys/time.h>
#include <list>
//#include "ctrlword.h"
#include "genericBasedata.h"
int const SITE_NAME_LEN=16;
using namespace std;
#pragma pack(1)
/**
   Time Series Data(IQ) format 

   IQ data start with a TSHeader ,which include all task parameter,
   followed by a control word,
   then every radial with TSRadialHeader,followed by real IQ data
    during IQ recording ,either a new sweep or system parameter change will cause
   a new TSHeader will be recorded.
   for single pol I,Q,I,Q,I,Q..
   for dual pol  I(h),Q(h),.....,I(v),Q(v),....
  */
/**
  format of ts archive data.
  TS Header 
  (cut/cut sector/rhi)...

  format of cut/cutsecotr/rhi:
  Ctrlword
  (TS Sweep)...
  TS Sweep End(binnum is zero)
  */
/**
  IQ data header 128bytes.
  */
int const TS_HEADER_SIZE=128;
struct TSHeader{
	char version;//version number
	char sitename[SITE_NAME_LEN];
	float spared;// wave length of radar  in meter;
	char spared2;//
	char pol;// h ,v ,hv
	float pulsewidth;// pulse width in microseconds.
	float calibration;//system  syscal 
	float noise; //noise level of the system in dbm
	float freq;// tx freq in MHz
	short firstbin;// first bin range in meter
	char phasecode;//phase code type of IQ
        float vnoise;//noise level of v channel
	float vcalib;//dbz0 for vertical channel
	char unfoldmode;
	float slat;//site latitude N>0,S<0
	float slon;//site longitude E>0,W<0
	float sheight;//site height about sea level 	
	char pad[65];
};
/**
  iq data sweep header ,128bytes
  */
int const TS_BURST_BIN_NUM=512;
int const TS_SWP_HEADER_SIZE=128;
int const TS_SWP_HEADER_SIZE_INT=TS_SWP_HEADER_SIZE/4;
struct TSSweepHeader{
	size_t IQLength();
	struct timeval time;// time of data,
	unsigned int clock ;// clock tagged by Card
	unsigned int seqnum;// squence number  of this sweep
	int spared[3];// height of the radar in meter 
	unsigned short az;//azimuth
	unsigned short  el;//elevation
	short prf;//pulse repeat freq in hz
	short samples;// samples number in current radial
	short binnum;// range bin number in this radial
	short reso;// range bin resolution
	char mode;//surv/dopper. used only by batch mode
	RadailState state;
	char spotblank;//true if the radial is blankspot
	short prevprf;//prf of next sweep;
	float burstmag;//magnitude of burst
	float burstang;//angle of burst
	short swpidx;// index of this sweep in the radial
	short anglereso;//angle (azimuth for ppi ) resolution
	char chan;//channnel number in this pulse 1 for h and v ,2 for hv
	unsigned short length;//just for rawiq(16bit short),internal use.
	short  burstbinnum;//bin number of burst signal 0 for no burst
	char pad[63];
	// must keep it at the end of the structure
	float iq[0][2];
};

TSSweepHeader *getNextSwpHeader(TSSweepHeader *swphdr);
TSSweepHeader *getAfterSwpHeader(TSSweepHeader *swphdr,int n);
void TSSwpHdrComp(short ver,TSSweepHeader *swphdr);
short getChanNum(TSSweepHeader *swphdr);
size_t getSweepLength(TSSweepHeader *swphdr);
size_t getSweepsLength(TSSweepHeader *swphdr,size_t n);
//playback
int const RAD_ANG_RESO=1;//one radial covert 1 deg
int const RAD_NUM_PER_CUT=360/RAD_ANG_RESO;
//int const  MAX_CUT_NUM=20;
typedef list<TSSweepHeader*>SwpHdrList;
typedef float Iqcmpl[2];
int scanIQFile(const char*fname,TSHeader *tsh,SwpHdrList &swplist);
Iqcmpl *getIQData(TSSweepHeader *swphdr);
/** \todo use SwpHdrList*/
struct SortedSwp
{
	TSSweepHeader *swphdr;
};
typedef list<SortedSwp> SortedSwpList;
struct Cut
{
	int swpcnt;//radial count;
	short el;
	float saz;
	float eaz;
	TSSweepHeader *startswp;
	//control_word ctrlword;
};
int SearchCuts(char  *tsData,size_t len, Cut *cuts);
void PowerAvg(TSSweepHeader *swphdr,int swpnum,float *outbuf);
void CreateSwpHdrList(char *tsData,size_t len,SortedSwpList &ssl); 
int Sum(char *dat,int len);
float PowerIQ(float iq[2]);
bool CheckVipDS();
int const TS_VER_DP=3;//version for dual pol support
int const TS_VER_BURST=4;//version for burst singal 
int const TS_VER_IQ16=5;//version for burst singal 
//void InitTSHeader(TSHeader &tsh,const control_word &cw);
//encode angle 0-360 
const short  TS_ANGLE_SCALE=100;
unsigned short TSEncodeAngle(float a);
float TSDecodeAngle(unsigned short a);
#pragma pack()
#endif
