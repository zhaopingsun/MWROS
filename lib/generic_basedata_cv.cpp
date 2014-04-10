// **********************************************************************
//
// Copyright (c) 1996-2014 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#include "generic_basedata_cv.h"
#include "generic_common_cv.h"
#include "radar_dt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
int HDR_SIZE1=sizeof(geneHeader)+sizeof(geneSiteConfig)+sizeof(geneTaskConfig);
//sizeof(ubytes)*MAX_BIN_NUM*MAX_DATA_TYPE_IN_BASE_DAT //
unsigned char gRadBuffer[2*4096*10]={0};
int const GENE_RAD_HEADER_LEN=sizeof(geneRadialHeader);
int loadCommonHeader(FILE *fp,int type,commonImage*cmn)
{
	if(1!=fread(&(cmn->uniHeader),HDR_SIZE1,1,fp))
	{
		return -2;
	}
	if(cmn->uniHeader.magic!=GDT_MAGIC||cmn->uniHeader.msgType!=type)
	{
		return -3;
	}
	int cutn=cmn->taskConf.cutNum;
	cmn->cuts.resize(cutn);
	if(cutn!=fread(&cmn->cuts[0],sizeof(geneCutConfig),cutn,fp))
	{
		return -5;
	}
	return 1;
}
//copy 8 or 16 byte data to 16bit dest
void uniCopyToShort(unsigned short *dest,unsigned char *src,size_t binnum,size_t binSize)
{
	size_t cpylen=binnum*binSize;
	if(binSize==2)
		memcpy(dest,src,cpylen);
	else
		for(int i=0;i<binnum;i++)
		{
			dest[i]=src[i];
		}
}
//copy 8 or 16byte data from short 
void uniCopyFromShort(unsigned char *dest,unsigned short *src,size_t binnum,size_t binSize)
{
	size_t cpylen=binnum*binSize;
	if(binSize==2)
		memcpy(dest,src,cpylen);
	else
	{
		for(int i=0;i<binnum;i++)
		{
			dest[i]=src[i];
		}
	}
}
int loadBasedataImage(const char *fpath,struct basedataImage &gdi)
{
	FILE *fp=fopen(fpath ,"rb");
	if(fp==NULL) 
		return -1;
	int ret=loadCommonHeader(fp,GDT_BASEDATA,&gdi);
	if(1!=ret)
	{
		return ret;
	}
	while(1)
	{
		cv_geneRadial grad;	
		geneRadialHeader *pgrad=(geneRadialHeader*)&grad;
		int ret=fread(pgrad,1,GENE_RAD_HEADER_LEN,fp);
//                printf("radial header: az %.2f el %.2f radInx %d\n", pgrad->az, pgrad->el, pgrad->radIdx);
		if(ret==0)
		{
			fclose(fp);
			//printf("end of file\n");
			break;
		}
		if(ret!=GENE_RAD_HEADER_LEN)
		{
			printf("read radial header failed\n");
			//exit(-1);
		}
//                printf("az %.2f el %.2f radInx %d length %d\n",grad.az,grad.el, grad.radIdx, grad.length);
		ret=fread(gRadBuffer,grad.length,1,fp);
		int pos=0;
		for(int i=0;i<grad.momNum;i++)
		{
			cv_geneMom gm;
			geneMomHeader *pmh=&gm.udt;
			memcpy(pmh,&gRadBuffer[pos],sizeof(*pmh));
			pos+=sizeof(*pmh);
			int len=gm.udt.length;
			int binsize=gm.udt.binSize;
			int binnum=len/binsize;	
			gm.data.resize(binnum);
			/*
			if(binsize==2)
				memcpy(&gm.data[0],&gRadBuffer[pos],len);
			else
			{
				for(int j=0;j<binnum;j++)
				{
					gm.data[j]=gRadBuffer[pos+j];
				}
			}
			*/
			uniCopyToShort(&gm.data[0],&gRadBuffer[pos],binnum,binsize);
			grad.mom.push_back(gm);
			pos+=len;
		}
		gdi.radials.push_back(grad);
	}
	return 1;
}
int writeCommHeader(FILE *fp ,commonImage*cmn)
{
	if(1!=fwrite(&cmn->uniHeader,HDR_SIZE1,1,fp))
	{
		return -2;
	}
	int cutn=cmn->taskConf.cutNum;
	//gdi.cuts.resize(cutn);
	if(cutn!=fwrite(&cmn->cuts[0],sizeof(geneCutConfig),cutn,fp))
	{
		return -5;
	}
	return 1;
}
int writeBasedataImage(const char*fpath,struct basedataImage &gdi)
{
	FILE *fp=fopen(fpath,"wb+");
	if(fp==NULL) 
		return -1;
	int ret=writeCommHeader(fp,&gdi);
	if(ret!=1)
		return ret;
	cvRadial::iterator it;
	for(it=gdi.radials.begin();it!=gdi.radials.end();it++)
	{
		geneRadialHeader *pgrad=(geneRadialHeader*)&(*it);
		int ret=fwrite(pgrad,1,GENE_RAD_HEADER_LEN,fp);
		if(ret!=GENE_RAD_HEADER_LEN)
		{
			printf("write radial failed\n");
			exit(-1);
		}
		cvGeneMom::iterator iit;
		for(iit=it->mom.begin();iit!=it->mom.end();iit++)
		{
			geneMomHeader *pmh=&((iit)->udt);
			int const GENE_MOM_HEADER_LEN=sizeof(geneMomHeader);
			ret=fwrite(pmh,1,GENE_MOM_HEADER_LEN,fp);
			if(ret!=GENE_MOM_HEADER_LEN)
			{
				printf("write mom header failed\n");
				exit(-1);
			}
			int len=pmh->length;
			int binsize=pmh->binSize;
			int binnum=len/binsize;
			uniCopyFromShort(gRadBuffer,&iit->data[0],binnum,binsize);
			ret=fwrite(gRadBuffer,1,len,fp);
			if(ret!=len)
			{
				printf("write mom data failed\n");
				exit(-1);
			}
		}
	}
	return 1;
}
typedef  vector<short> shortSeq;
long long  getMomsInWaveFrom(int wf)
{
	shortSeq rtds;
	if(wf==WF_CS)
	{
		rtds.push_back(RDT_DBZ);
	}
	else if(wf==WF_CD||wf==WF_DPRF)
	{
		rtds.push_back(RDT_VEL);
		rtds.push_back(RDT_WID);
	}
	else if(wf==WF_CDX||wf==WF_BATCH)
	{
		rtds.push_back(RDT_DBZ);
		rtds.push_back(RDT_VEL);
		rtds.push_back(RDT_WID);
	}
	return getMomMask(rtds);
}
void fakeSiteInfo(const char *name,geneSiteConfig &sc)
{
	strcpy(sc.name,name);
	strcpy(sc.code,name);
	sc.lat=30;
	sc.lon=30;
	sc.freq=3000;
	sc.height=100;
	sc.beamwidth=.97;
	sc.ground=100;
}
bool fakeVcpTaskConfig(int vcp,geneTaskConfig &tc,cvCutConfig &cuts)
{
	char buff[32];
	
	memset(&tc, 0, sizeof(geneTaskConfig));
	sprintf(buff, "VCP%d",vcp);
	strcpy(tc.name , buff);
	sprintf(tc.desp, "WSR88D task %s", buff);

	geneQcThresh defthresh;
	defthresh.sig=10;
	defthresh.csr=18;
	defthresh.log=2;
	defthresh.sqi=0.4;

	//task information
	tc.pol = 1;
	tc.startTime = 0; //need to be updated
	tc.horNoise = -80.;
	tc.verNoise = -80;
	tc.horCalib = 18; //need to be updated
	tc.verCalib = 0.;
	tc.horNoiseTemp = 0;
	tc.verNoiseTemp = 0;
	tc.zdrCal = 0.;
	tc.phaseCal = 0.;
	tc.ldrCal = 0.;
	//for vcp 12/22, same parameter was used except elevation angles
	int def_pm=PM_PPP;
	if(vcp==11||vcp==12)
	{
		tc.pulseWidth=int(1.57*1000);
		tc.scanType=SP_VOL;

		int cutNum=16;
		int vcp11_wf[]={WF_CS,WF_CD,WF_CS,WF_CD,WF_BATCH,WF_BATCH,WF_BATCH,WF_BATCH,WF_BATCH,
			       WF_CDX,WF_CDX,WF_CDX,WF_CDX,WF_CDX,WF_CDX,WF_CDX};
		float vcp11_el[]={0.5,0.5,1.5,1.5,2.4,3.4,4.3,5.3,6.2,7.5,8.7,10.0,12.0,14.0,16.7,19.5};
		
		float vcp11_prf_low[]={PRF1,PRF5,PRF1,PRF5,PRF1,PRF2,PRF2,PRF3,PRF3,PRF6,PRF7,PRF7,PRF7,PRF7,PRF7,PRF7};
		float vcp11_prf_high[]={NOPRF,NOPRF,NOPRF,NOPRF,PRF5,PRF5,PRF5,PRF5,PRF5,NOPRF,NOPRF,NOPRF,NOPRF,NOPRF,NOPRF,NOPRF};
	
		int vcp11_samp_low[]={17,52,16,52, 6, 6, 6,10,10,43,46,46,46,46,46,46};
		int vcp11_samp_high[]={ 0, 0, 0,0,41,41,41,41,41, 0, 0, 0, 0, 0, 0, 0};		
		float vcp11_maxRange[]={460,230,460,230,330,330,330,230,127,127,127,90,90,90,90,90};
		
		float cutspeed11[] = {18.675,19.224,19.844,19.225,16.116,17.893,17.898,
								17.459,17.466,25.168,25.398,25.421,25.464,25.515,25.596,25.696};
		cuts.resize(cutNum);

		for(int i=0;i<cutNum;i++)
		{
			cuts[i].processMode=def_pm;
			
			cuts[i].az=-1;
			cuts[i].el=vcp11_el[i];
			cuts[i].angleReso=1.0;
			cuts[i].scanSpeed = cutspeed11[i];
			cuts[i].startAngle=cuts[i].endAngle=-1.;
									
			cuts[i].waveForm=vcp11_wf[i];
			cuts[i].momMask=getMomsInWaveFrom(vcp11_wf[i]);
			
			cuts[i].logReso=1000; 
			cuts[i].dopReso=250;
			cuts[i].startRange=0;			
			cuts[i].maxRange=(int)vcp11_maxRange[i]*1000;
									
			cuts[i].prf=vcp11_prf_low[i];
			cuts[i].prf2=vcp11_prf_high[i];
			cuts[i].unfoldMode=0;
			cuts[i].samples=vcp11_samp_low[i];
			cuts[i].samples2=vcp11_samp_high[i];			
			cuts[i].phaseMode=0;
			cuts[i].atmos = 0.;
			cuts[i].nyquist = 27.0;
			
			cuts[i].qcThresh=defthresh;
			cuts[i].scanSync=0;
		}	
	}
	else if(vcp==21||vcp==22)
	{
		tc.pulseWidth=int(1.57*1000);
		tc.scanType=SP_VOL;

		int cutNum=11;
		int vcp21_wf[]={WF_CS,WF_CD,WF_CS,WF_CD, WF_BATCH,WF_BATCH,WF_BATCH,WF_BATCH, WF_CDX,WF_CDX,WF_CDX};
		float vcp21_el[]={.5,.5,1.5,1.5,2.4,3.4,4.3,6.0,9.9,14.6,19.5};
		
		float vcp21_prf_low[]={PRF1,PRF5,PRF1,PRF5,PRF2,PRF2,PRF2,PRF3,PRF7,PRF7,PRF7};
		float vcp21_prf_high[]={NOPRF,NOPRF,NOPRF,NOPRF,PRF5,PRF5,PRF5,PRF5,NOPRF,NOPRF,NOPRF};
		
		int vcp21_samp_low[]={28,88,28,88,8,8,8,12,82,82,82};
		int vcp21_samp_high[]={0, 0,0 ,0 ,70,70,70,70,0,0,0};		
		float vcp21_maxRange[]={460,230,460,230,330,330,330,230,127,127,127};
		float cutspeed21[] = {11.339,11.360,11.339,11.360,11.180,11.182,11.185,11.189,14.260,14.332,14.415};
										
		cuts.resize(cutNum);

		for(int i=0;i<cutNum;i++)
		{
			cuts[i].processMode=def_pm;		
			
			cuts[i].az=-1;
			cuts[i].el=vcp21_el[i];
			cuts[i].angleReso=1.0;
			cuts[i].scanSpeed = cutspeed21[i];
			cuts[i].startAngle=cuts[i].endAngle=-1.;
												
			cuts[i].waveForm=vcp21_wf[i];
			cuts[i].momMask=getMomsInWaveFrom(vcp21_wf[i]);
			
			cuts[i].logReso=1000; 
			cuts[i].dopReso=250;
			cuts[i].startRange=0;			
			cuts[i].maxRange=(int)vcp21_maxRange[i]*1000;
									
			cuts[i].prf=vcp21_prf_low[i];
			cuts[i].prf2=vcp21_prf_high[i];
			cuts[i].unfoldMode=0;
			cuts[i].samples=vcp21_samp_low[i];
			cuts[i].samples2=vcp21_samp_high[i];			
			cuts[i].phaseMode=0;
			cuts[i].atmos = 0.;
			cuts[i].nyquist = 27.0;
			
			cuts[i].qcThresh=defthresh;
			cuts[i].scanSync=0;		
		}
	}
	else if (vcp==31)
	{
		tc.pulseWidth=int(4.51*1000);
		tc.scanType=SP_VOL;

		int cutNum=8;
		int vcp31_wf[]={WF_CS,WF_CD,WF_CS,WF_CD,WF_CS,WF_CD,WF_CDX,WF_CDX};
		float vcp31_el[]={0.5,0.5,1.5,1.5,2.5,2.5,3.5,4.5};
		
		float vcp31_prf_low[]={PRF1,PRF2,PRF1,PRF2,PRF1,PRF2,PRF2,PRF2};
		float vcp31_prf_high[]={NOPRF,NOPRF,NOPRF,NOPRF,NOPRF,NOPRF,NOPRF,NOPRF};
		
		int vcp31_samp_low[]={64,88,64,88,64,88,88,88};
		int vcp31_samp_high[]={0,0,0,0,0,0,0,0};		
		float vcp31_maxRange[]={460,230,460,230,330,330,330,230};
		float cutspeed31[] = {5.039,5.061,5.040,5.062,5.041,5.062,5.063,5.065};
										
		cuts.resize(cutNum);

		for(int i=0;i<cutNum;i++)
		{
			cuts[i].processMode=def_pm;		
			
			cuts[i].az=-1;
			cuts[i].el=vcp31_el[i];
			cuts[i].angleReso=1.0;
			cuts[i].scanSpeed = cutspeed31[i];
			cuts[i].startAngle=cuts[i].endAngle=-1.;
												
			cuts[i].waveForm=vcp31_wf[i];
			cuts[i].momMask=getMomsInWaveFrom(vcp31_wf[i]);
			
			cuts[i].logReso=1000; 
			cuts[i].dopReso=250;
			cuts[i].startRange=0;			
			cuts[i].maxRange=(int)vcp31_maxRange[i]*1000;
									
			cuts[i].prf=vcp31_prf_low[i];
			cuts[i].prf2=vcp31_prf_high[i];
			cuts[i].unfoldMode=0;
			cuts[i].samples=vcp31_samp_low[i];
			cuts[i].samples2=vcp31_samp_high[i];			
			cuts[i].phaseMode=0;
			cuts[i].atmos = 0.;
			cuts[i].nyquist = 27.0;
			
			cuts[i].qcThresh=defthresh;
			cuts[i].scanSync=0;		
		}
	}	
	else if (vcp==32)
	{
		tc.pulseWidth=int(1.57*1000);
		tc.scanType=SP_VOL;

		int cutNum=7;
		int vcp31_wf[]={WF_CS,WF_CD,WF_CS,WF_CD,WF_BATCH,WF_BATCH,WF_BATCH};
		float vcp31_el[]={0.5,0.5,1.5,1.5,2.5,3.5,4.5};
		
		float vcp31_prf_low[]={PRF1,PRF5,PRF1,PRF5,PRF2,PRF2,PRF2};
		float vcp31_prf_high[]={NOPRF,NOPRF,NOPRF,NOPRF,PRF5,PRF5,PRF5};
		
		int vcp31_samp_low[]={64,220,64,220,11,11,11};
		int vcp31_samp_high[]={0, 0,0 ,0 ,220,220,220};
		float vcp31_maxRange[]={460,230,460,230,330,330,330};
		float cutspeed31[] = {4.961,4.544,4.961,4.544,4.060,4.061,4.063};
										
		cuts.resize(cutNum);

		for(int i=0;i<cutNum;i++)
		{
			cuts[i].processMode=def_pm;		
			
			cuts[i].az=-1;
			cuts[i].el=vcp31_el[i];
			cuts[i].angleReso=1.0;
			cuts[i].scanSpeed = cutspeed31[i];
			cuts[i].startAngle=cuts[i].endAngle=-1.;
												
			cuts[i].waveForm=vcp31_wf[i];
			cuts[i].momMask=getMomsInWaveFrom(vcp31_wf[i]);
			
			cuts[i].logReso=1000; 
			cuts[i].dopReso=250;
			cuts[i].startRange=0;			
			cuts[i].maxRange=(int)vcp31_maxRange[i]*1000;
									
			cuts[i].prf=vcp31_prf_low[i];
			cuts[i].prf2=vcp31_prf_high[i];
			cuts[i].unfoldMode=0;
			cuts[i].samples=vcp31_samp_low[i];
			cuts[i].samples2=vcp31_samp_high[i];			
			cuts[i].phaseMode=0;
			cuts[i].atmos = 0.;
			cuts[i].nyquist = 27.0;
			
			cuts[i].qcThresh=defthresh;
			cuts[i].scanSync=0;		
		}
	}	
	else if (vcp==41) //PPI
	{
		sprintf(buff, "PPI%d",vcp);
		strcpy(tc.name , buff);		
		tc.pulseWidth=int(1.57*1000);
		tc.scanType=SP_PPI;

		int cutNum=1;

		cuts.resize(cutNum);
		for(int i=0;i<cutNum;i++)
		{
			cuts[i].qcThresh=defthresh;
			cuts[i].maxRange=(int)230*1000; 
			cuts[i].az=-1;

			cuts[i].el=0.5;
			cuts[i].scanSpeed = 12.0;
			cuts[i].waveForm=WF_CDX;
			cuts[i].momMask=getMomsInWaveFrom(WF_CDX);

			cuts[i].angleReso=1.0;
			cuts[i].logReso=1000;
			cuts[i].dopReso=250;
			cuts[i].prf=1014;
			cuts[i].prf2=1014;

			cuts[i].unfoldMode=0;
			cuts[i].startRange=0;
			cuts[i].samples=82;
			cuts[i].phaseMode=0;
			cuts[i].startAngle=cuts[i].endAngle=-1;
			cuts[i].processMode=def_pm;
		}
	}
	else if (vcp==61) //RHI
	{
		sprintf(buff, "RHI%d",vcp);
		strcpy(tc.name , buff);
	
		tc.pulseWidth=int(1.57*1000);
		tc.scanType=SP_RHI;

		int cutNum=1;

		cuts.resize(cutNum);
		for(int i=0;i<cutNum;i++)
		{
			cuts[i].qcThresh=defthresh;
			cuts[i].maxRange=(int)230*1000; 
			cuts[i].az=0.0;

			cuts[i].el=-1;
			cuts[i].waveForm=WF_CDX;
			cuts[i].momMask=getMomsInWaveFrom(WF_CDX);

			cuts[i].angleReso=1.0;
			cuts[i].logReso=1000;
			cuts[i].dopReso=250;
			cuts[i].prf=1014;
			cuts[i].prf2=1014;

			cuts[i].unfoldMode=0;
			cuts[i].startRange=0;
			cuts[i].samples=82;
			cuts[i].phaseMode=0;
			cuts[i].startAngle=cuts[i].endAngle=-1;
			cuts[i].processMode=def_pm;
		}
	}
	return true;
}
int loadTaskConfig(const char *fpath,commonImage &ci,char *erstr)
{
	FILE *fp=fopen(fpath,"r");
	int ret=0;
	if(fp==NULL)
	{
		if(erstr!=NULL)
			sprintf(erstr,"open file %s failed,due to %s",fpath,strerror(errno));
		return -1;
	}
	if(1!=fread(&(ci.uniHeader),sizeof(ci.uniHeader),1,fp))
	{
		if(erstr!=NULL)
		sprintf(erstr,"read  taskconfig file %s failed,due to %s",fpath,strerror(errno));
		ret= -2;
		goto er;
	}
	//check header 
	if(!(ci.uniHeader.magic==GDT_MAGIC&&ci.uniHeader.msgType==GDT_TASK_CONFIG))
	{
		if(erstr!=NULL)
			sprintf(erstr,"file %s is not task config file",fpath);
		ret= -3;	
		goto er;
	}
	if(1!=fread(&(ci.taskConf),sizeof(geneTaskConfig),1,fp))
	{
		if(erstr!=NULL)
			sprintf(erstr,"read  taskconfig file %s failed,due to %s",fpath,strerror(errno));
		ret= -4;
		goto er;

	}
	ci.cuts.resize(ci.taskConf.cutNum);
	for(int i=0;i<ci.taskConf.cutNum;i++)
	{
		if(!fread(&(ci.cuts[i]),sizeof(geneCutConfig),1,fp))
		{
			if(erstr!=NULL)
				sprintf(erstr,"read  cutconfig file %s failed,due to %s",fpath,strerror(errno));
			ret=-5;
			goto er;
		}

	}
er:	fclose(fp);
	return ret;
}
void searchCuts(struct basedataImage &bdi,cvCutMark &cutMarks)
{
	cvRadial::iterator it;
	cv_cutmark mark;
	mark.begin=mark.end=bdi.radials.end();
	int radNum=0;
	for(it=bdi.radials.begin();it!=bdi.radials.end();it++)
	{
		//cv_geneRadial *prad=it;
		if(it->state==VOL_START||it->state==CUT_START)
		{
			mark.begin=it;
			radNum=0;
		}
		if(it->state==VOL_END||it->state==CUT_END)
		{
			mark.end=it;
			mark.radNum=radNum;
			if(mark.begin!=bdi.radials.end())
				cutMarks.push_back(mark);
			else
			{
				fprintf(stderr,"not cut begin\n");
			}
			mark.begin=mark.end=bdi.radials.end();
		}
		radNum++;
	}
}
