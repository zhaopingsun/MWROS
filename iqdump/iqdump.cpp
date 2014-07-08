#include <stdio.h>
#include <math.h>
#include<string.h>
#include "rdats.h"
//#include <io.h>
#include <fstream>
#include <ostream>	

#include "ipps.h"
#include "ipp.h"


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
int main (int argc,char *argv[])
{
	
	SweepHeaderList  shl;
	const char *fname="/home/rda/IQ/Z9220_20120203_010600_01_CS.IQ";
	TSHeader IQFileHead;
	scanIQFile(fname,&IQFileHead,shl);
	printf("sitename: %s\n",IQFileHead.sitename);
	printf("freq: %f\n",IQFileHead.freq);
	printf("noise: %f\n",IQFileHead.noise);
	printf("wavelength: %.2f\n",IQFileHead.wavelength);

	SweepHeaderList::iterator it;
	for(it=shl.begin();it!=shl.end();it++)
	{
		TSSweepHeader *swphdr=*it;
		printf("sweep seq %d\t",swphdr->seqnum);
		printf("AZ: %f\t",(swphdr->az)*360/pow(2.0,13));
		printf("El: %d\t",swphdr->el);
		printf("prf: %d\n",swphdr->prf);
		Iqcmpl *pIQ=getIQData(swphdr);
		float *amp =new float[swphdr->binnum];
		memset(amp,0,sizeof(float)*swphdr->binnum);
		float *phase=new float[swphdr->binnum];
		memset(phase,0,sizeof(float)*swphdr->binnum);
		int binnum=3;//swphdr->binnum;
		int swpindex;
		swpindex=swphdr->swpidx;
		//ippsCartToPolar_32fc((Ipp32fc*)pIQ,amp,phase,swphdr->binnum);
		for (int i=0;i<binnum;i++)
		{
			
			if (i%3 == 0)
			{
				printf("\nbinnum is %d\n",i);
			}	
			printf("\n(%f %f) ",pIQ[i][0],pIQ[i][1]);

			
/*
			amp[i]=10*log10(pIQ[i][0]*pIQ[i][0]+pIQ[i][1]*pIQ[i][1]);
			phase[i]=atan2(pIQ[i][1],pIQ[i][0])*360/(2*PI);	
			amp[i]=20*log10(amp[i]);
			phase[i]=phase[i]*180/PI;
			printf("(%f %f) ",amp[i],phase[i]);
*/
		}
		delete []amp;
		delete []phase;
	}
	
}
 



