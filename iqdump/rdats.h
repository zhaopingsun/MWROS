
#ifndef RDA_TS_HEADER
#define RDA_TS_HEADER
#ifndef __unix__
#include "WinSock2.h"
#endif
#include <stdlib.h>
#include <list>
using namespace std;
#pragma pack(1)
enum  RadailState{CUT_START,CUT_MID,CUT_END,VOL_START,VOL_END,
	RHI_START, RHI_END, CUT_INIT,FORCE_END};
int const SITE_NAME_LEN=16;
int const TS_HEADER_SIZE=128;
struct TSHeader{
	char version;//version number
	char sitename[SITE_NAME_LEN];
	float wavelength;// wave length of radar  in meter;
	char vcp;//vcp number of current sweep
	char pol;// h ,v ,hv
	float pulsewidth;// pulse width in microseconds.
	float calibration;// calibration reflectivity (dbz at 1km)
	float noise; //noise level of the system in dbm
	float freq;// tx freq in MHz
	short firstbin;// first bin range in meter
	char pad[87];
};
int const TS_SWP_HEADER_SIZE=128;
struct TSSweepHeader{
	size_t IQLength();
	struct timeval time;// time of data,
	unsigned int clock ;// clock tagged by Card
	unsigned int seqnum;// squence number  of this sweep
	int latitude;//latitude of the radar . presion 1/1000 deg
	int longitude;//longtitude of the radar .as above
	int height;// height of the radar in meter 
	short az;//azimuth
	short el;//elevation
	short prf;//pulse repeat freq in hz
	short samples;// samples number in current radial
	short binnum;// range bin number in this radial
	short reso;// range bin resolution
	char mode;//surv/dopper. used only by batch mode
	RadailState state;
	char spotblank;//true if the radial is blankspot
	short nextprf;//prf of next sweep;
	float burstmag;//magnitude of burst
	float burstang;//angle of burst
	short swpidx;// index of this sweep in the radial
	short anglereso;//angle (azimuth for ppi ) resolution
	char chan;//channnel number in this pulse 1 for h and v ,2 for hv
	char pad[67];

	// must keep it at the end of the structure
//	float iq[0][2];
};
typedef list<TSSweepHeader*> SweepHeaderList;
typedef float Iqcmpl[2]; 
Iqcmpl *getIQData(TSSweepHeader *swphdr);
TSSweepHeader *getNextSwpHeader(TSSweepHeader *swphdr);
size_t getSweepLength(TSSweepHeader *swphdr);
int scanIQFile(const char*fname,TSHeader *tsh,SweepHeaderList &swplist);

struct SortedSwp
{
	TSSweepHeader *swphdr;
};
typedef list<SortedSwp> SortedSwpList;

#pragma pack()
#endif
