#include <stdio.h>
#include <math.h>
#include<string.h>
#include "../lib/rdats.h"
#include <io.h>
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
	const char *fname="H:\\SCI\\src\\vists\\Z9220_20110508_141200_01_CS.IQ";
	TSHeader IQFileHead;
	scanIQFile(fname,&IQFileHead,shl);
	printf("sitename: %s\n",IQFileHead.sitename);
	printf("freq: %f\n",IQFileHead.freq);
	printf("noise: %f\n",IQFileHead.noise);
	printf("wavelength: %.2f\n",IQFileHead.wavelength);

	SweepHeaderList::iterator it;
	int swpnum=0;
	for(it=shl.begin();it!=shl.end()&&swpnum<1;it++)
	{
		swpnum++;
		TSSweepHeader *swphdr=*it;
		printf("sweep seq %d\n",swphdr->seqnum);
		printf("AZ: %f\n",(swphdr->az)*360/pow(2.0,13));
		printf("El: %d\n",swphdr->el);
		printf("prf: %d\n",swphdr->prf);
		Iqcmpl *pIQ=getIQData(swphdr);
		float *amp =new float[swphdr->binnum];
		memset(amp,0,sizeof(float)*swphdr->binnum);
		float *phase=new float[swphdr->binnum];
		memset(phase,0,sizeof(float)*swphdr->binnum);
		int binnum=10;//swphdr->binnum;
		int swpindex;
		swpindex=swphdr->swpidx;
		ippsCartToPolar_32fc((Ipp32fc*)pIQ,amp,phase,swphdr->binnum);
		for (int i=0;i<binnum;i++)
		{
			
			if (i%3 == 0)
			{
				printf("\nbinnum is %d\n",i);
			}	
			printf("\n(%f %f) ",pIQ[i][0],pIQ[i][1]);

			
			//amp[i]=10*log10(pIQ[i][0]*pIQ[i][0]+pIQ[i][1]*pIQ[i][1]);
			//phase[i]=atan2(pIQ[i][1],pIQ[i][0])*360/(2*PI);	
			amp[i]=20*log10(amp[i]);
			phase[i]=phase[i]*180/PI;
			printf("(%f %f) ",amp[i],phase[i]);
		}
		delete []amp;
		delete []phase;
	}
	
}
 
	//	int data_len;
	//	data_len=filelength(fileno(m_fp));

	//	int data_num=data_len/sizeof(float);

	//	float *Data_buffer=new float[data_num]; //���ٴ洢һ��SWEEP�����е�IQ���ݻ���
	//	memset(Data_buffer,0,sizeof(float)*data_num);

	//	float *I=new float[data_num];      //���ٴ洢����I���ݵĻ���
	//	memset(I,0,sizeof(float)*data_num);
	//	float *Q=new float[data_num];	  //���ٴ洢����Q���ݵĻ���
	//	memset(Q,0,sizeof(float)*data_num);

	//	short *CurAz=new short[data_num];
	//	memset(CurAz,0,sizeof(short)*data_num);

	//	short *Curprf=new short[data_num];
	//	memset(Curprf,0,sizeof(short)*data_num);

	//	

	//	fread(&IQFileHead,sizeof(IQFileHead),1,m_fp); //��ȡ�ļ�ͷ
	//	version =IQFileHead.version;
	//	
	//	fread(&SWFileHead,sizeof(SWFileHead),1,m_fp); //��ȡ��һ��sweepͷ�ļ�
	//	m_binnum=SWFileHead.binnum;
	//	Az_start=SWFileHead.az*360/(short)pow(2.0,13);
	//	El_start=SWFileHead.el*360/(short)pow(2.0,13);
	//	IQ_LEN=sizeof(SWFileHead)+m_binnum*2*sizeof(float);

	//	while(!feof(m_fp))
	//	{	
	//		Ssweep++;
	//		sweepsnum=SWFileHead.samples; 
	//		binnum=SWFileHead.binnum;
	//		CurAz[Ssweep]=SWFileHead.az*360/(short)pow(2.0,13);
	//		Curprf[Ssweep]=SWFileHead.prf;
	//		IQ_LEN=IQ_LEN+binnum*8; 

	//		fread(Data_buffer,sizeof(float)*binnum*2,1,m_fp); //��ȡһ��sweep�ڵ�����IQ����

	//		for(int i=0;i<binnum;i++)  //���ļ��е�����I��Q���ݷֱ�����������
	//		{
	//			I[(Ssweep-1)*binnum+i]=Data_buffer[2*i];
	//			Q[(Ssweep-1)*binnum+i]=Data_buffer[2*i+1];
	//		}

	//		if (SWFileHead.swpidx>=sweepsnum-1)
	//		{		
	//			radialnum++;
	//		}
	//		fread(&SWFileHead,sizeof(SWFileHead),1,m_fp); //��ȡ��һ��sweepͷ�ļ�
	//	}
	//	delete Data_buffer;Data_buffer=NULL;
	//	fclose(m_fp);

	////	pp_Process(I,Q); //�����ݰ�����ĸ�ʽ�洢�������д���
	////	FFT_Process(I,Q);

	//	delete I;I=NULL;
	//	delete Q;Q=NULL;
	//}
	//return(1);	

//void pp_Process(float *I,float *Q)
//{
//	float *pI=new float[m_binnum];     //���ٴ洢ͬһ������һ��sweep�����о�����I���ݵĻ���
//	memset(pI,0,sizeof(float)*m_binnum);
//	float *pQ=new float[m_binnum];	  //���ٴ洢ͬһ������һ��sweep�����о�����Q���ݵĻ���
//	memset(pQ,0,sizeof(float)*m_binnum);
//
//	for (int i=0;i<radialnum;i++) //����
//	{
//		for(int j=0;j<sweepsnum;j++)//sweep
//		{
//			for (int k=0;k<m_binnum;k++)//�����
//			{
//				pI[k]=I[(i*sweepsnum+j)*m_binnum+k]; //��������Է�������
//				pQ[k]=Q[(i*sweepsnum+j)*m_binnum+k];
//			}
//		}
//	}
//}
//
//void FFT_Process(float *I,float *Q)
//{
//	Ipp32fc *fIQ=new Ipp32fc[sweepsnum];     //���ٴ洢ͬһ������ͬһ�����������sweep��I���ݵĻ���
//	memset(fIQ,0,sizeof(Ipp32fc)*sweepsnum);
//
//	for (int i=0;i<radialnum;i++) //����
//	{
//		for(int j=0;j<m_binnum;j++)//sweep
//		{
//			for (int k=0;k<sweepsnum;k++)//�����
//			{
//				fIQ[k].re=I[(i*m_binnum+j)*sweepsnum+k]; //����FFT��������
//				fIQ[k].im=Q[(i*m_binnum+j)*sweepsnum+k];
//			}
//
//			//���ź���FFT,�õ��źŵ�Ƶ��	
//
//			int M = 128;
//			
//			for(int i=0;i<M;i++)
//			{
//				if (i<sweepsnum)
//				{
//					fIQ[i].re=fIQ[i].re; 
//					fIQ[i].im=fIQ[i].im;
//				}
//				else   //����
//				{
//					fIQ[i].re=0; 
//					fIQ[i].im=0;
//				}
//			}
//
//			Ipp32fc *FFT_OUT = new Ipp32fc[M];
//			memset(FFT_OUT,0,sizeof(Ipp32fc)*M);
//			
//			IppsFFTSpec_C_32fc *Specfc=new  IppsFFTSpec_C_32fc[M]; //���ٴ洢һ�������Ĺ����׻���
//			memset(Specfc,0,sizeof( IppsFFTSpec_C_32fc)*M);
//			
//
//			float *Specfc_amp=new float[M];        //���ٴ洢һ�������Ĺ����׷�ֵ
//			memset(Specfc_amp,0,sizeof(float)*M);
//
//			float *Specfc_phase=new float[M];     //���ٴ洢һ�������Ĺ�������λ
//			memset(Specfc_phase,0,sizeof(float)*M);
//
//			float *Specfc_shift=new float[M];     //���ٴ洢һ�������Ĺ����׻���
//			memset(Specfc_shift,0,sizeof(float)*M);
//			
//		
//			//fft����
//			ippsFFTFwd_CToC_32fc( fIQ,FFT_OUT,Specfc,NULL);//����IPP fft�㷨����FFT
//			for(int i=0;i<M;i++)
//			{
//				//��ز��źŵĹ�����
//				Specfc_amp[i]=(FFT_OUT[i].re*FFT_OUT[i].re+FFT_OUT[i].im*FFT_OUT[i].im)/M; //����
//				Specfc_phase[i]=atan(FFT_OUT[i].im/FFT_OUT[i].re);//��λ
//			}
//
//			fftshift(M,Specfc_amp, Specfc_shift);
//		}
//	}
//}
//
//
//void fftshift(int M,float *InData, float *OutData)
//{
//	int i=0;
//	for(i=0;i<M;i++)
//	{
//		if(i+M/2<M)
//		{
//			OutData[i]=InData[i+M/2];
//		}
//		else
//		{
//			OutData[i]=InData[i-M/2];
//		}
//	}
//}



