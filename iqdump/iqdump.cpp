#include <stdio.h>
#include <math.h>
#include<string.h>
#include "rdats.h"
//#include <io.h>
#include <fstream>
#include <ostream>	

#include "tspack.h"
#include "iqfunc.h"


#define  PI 3.1415926 
//#pragma comment(lib, "ipps.lib")

const char *OP_IF="if";
const char *OP_AIQ="AIQ";
void help()
{

#define DUMP_OP(a,desp) printf( "\t --%s desp \n",a);
	DUMP_OP(OP_IF ,"input base data file");
//	DUMP_OP(OP__AIQ ,"output product max range in km,default as input basedata");
	exit(0);
}

using namespace std;
//void pp_Process(float *I,float *Q);
//void FFT_Process(float *I,float *Q);
//void fftshift(int M,float *InData, float *OutData);
Iqcmpl gIQbuf[4096*2];
int main (int argc,char *argv[])
{
	
	SweepHeaderList  shl;
//	const char *fname="/home/rda/IQ/Z9220_20120203_010600_01_CS.IQ";
	const char *fname="/home/rda/IQ/NJU_20140224_014916_01_RPH.IQ";
	TSHeader tsh;
	scanIQFile(fname,&tsh,shl);
	printf("sitename: %s\n",tsh.sitename);
	printf("freq: %f\n",tsh.freq);
	printf("noise: %f\n",tsh.noise);
	printf("wavelength: %.2f\n",tsh.wavelength);
	SweepHeaderList::iterator it;
	for(it=shl.begin();it!=shl.end();it++)
	{
		TSSweepHeader *swphdr=*it;
		printf("sweep seq %d\t",swphdr->seqnum);
		printf("AZ: %.2f\t",DecodeAnteAngleDeg(tsh.version,swphdr->az));
		printf("El: %.2f\t",DecodeAnteAngleDeg(tsh.version,swphdr->el));
		printf("prf: %d\n",swphdr->prf);
		Iqcmpl *pIQ=getIQData(swphdr);
		if(tsh.version<5)
		{
			memcpy(gIQbuf,pIQ,getSweepLength(swphdr)-sizeof(*swphdr));
		}
		else
		{
			
			depackIQ((unsigned short*)pIQ,(float*)gIQbuf,(getSweepLength(swphdr)-sizeof(*swphdr))/2);	
		}	
		int binnum=3;//swphdr->binnum;
		int swpindex;
		swpindex=swphdr->swpidx;
		//ippsCartToPolar_32fc((Ipp32fc*)pIQ,amp,phase,swphdr->binnum);
#define dump_bins(offset) \
		for (int i=0;i<binnum;i++)  \
		{ printf("(%f %f) ",gIQbuf[i+offset][0],gIQbuf[i+offset][1]); }\
		 printf("\n");
		if(swphdr->chan<=1)
		{
			dump_bins(0);
		}
		else
		{
			printf("----hori---\n");
			dump_bins(0);
			printf("----vert---\n");
			dump_bins(swphdr->binnum);
		}
	}
	
}
 



