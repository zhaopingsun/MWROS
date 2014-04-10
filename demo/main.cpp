// **********************************************************************
//
// Copyright (c) 1996-2014 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "generic_basedata_cv.h"
#include "generic_product_cv.h"
#include "prodtype.h"
#include "proj_type.h"
#include "radar_dt.h"
#include "geneCodeData.h"
#include <iostream>
#include <list>
#include <time.h>
using namespace std;

struct AppOptions{
	char infile[256];//full file path
	char outfile[256];//full file path
	char prodname[PROD_NAME_LENGTH];
	int reso;
	int range;
};
void createPPIProduct(struct basedataImage &gdi,struct PPIProdImage & pdi,int reso,int range,char *prodName)
{
	 int proddt=RDT_DBZ;
#define CP_MEM(a) pdi.a=gdi.a
	CP_MEM(uniHeader);
	pdi.uniHeader.majorVer=MAJOR_VER;
	pdi.uniHeader.minorVer=MINOR_VER;
	pdi.uniHeader.msgType=GDT_PRODUCT;
	CP_MEM(siteInfo);
	CP_MEM(taskConf);
	CP_MEM(cuts);
	//make pch
	geneProdCommHeader pch;
	strcpy(pch.prodName,prodName);
	pch.prodType=pdi.uniHeader.prodType=PT_PPI;
	time_t tim;
	time(&tim);
	pch.prodGenTime=tim;
	pch.volStartTime=gdi.taskConf.startTime;
	pch.dataStartTime=pch.volStartTime;
	int radnum;
	cv_geneRadial lastradial=gdi.radials.back();
	cv_geneRadial firstradial=gdi.radials.front();
	{
	//	cvRadial::iterator it=gdi.radials.begin();

		//search for end of first cut
	//	lastradial.
		/*for(it=gdi.radials.begin();it!=gdi.radials.end();it++)
		{
			radnum++;
			if(it->state==CUT_END)
			{
				break;
			}
		}*/
	}
	 pch.dataEndTime=lastradial.timeSec;
	 pch.projType =PROJ_NONE;
	
	 pch.momType1=proddt;
	 pdi.header=pch;
   
	
	 geneProdPpiSpec spec;
	 spec.elevation=firstradial.el;
	 pdi.spec.ppi=spec;
//
	 //search for dbz data
	 const  cv_geneMom *pMom=NULL; //gMom->
	 cvGeneMom::iterator mit;
	 for(mit=firstradial.mom.begin();mit!=firstradial.mom.end();mit++)
	 {
		 if( mit->udt.type==proddt)
		 {
			 pMom=&*mit;
		 }
	 }
	 if(pMom==NULL)
	 {
		 printf("can not found dt %d\n",proddt);
		 return;
	 }
	 //search cuts
	 cvCutMark cm;
	 searchCuts(gdi,cm);
	 geneRadialProdHeader grph;
	 grph.dataType.binSize=pMom->udt.binSize;
	 grph.dataType.offset=pMom->udt.offset ;
	 grph.dataType.scale=pMom->udt.scale;
	 grph.dataType.type=pMom->udt.type;
	 grph.max=grph.min=0;
	 grph.radNum=gdi.radials.size();
	 grph.reso=reso;
	 grph.startRange=gdi.cuts[0].startRange;
	 grph.maxRange=gdi.cuts[0].maxRange;
	 grph.reso=gdi.cuts[0].logReso;
	 grph.radNum=cm.front().radNum;
	// grph.
	// firstradial.
	 //grph.
	// grph.maxRange=firstradial.
	 pdi.radialHeader=grph;
	 

	 //create radials
	 cvRadial::iterator rit;
	 //only first cut is used
	 int max=-1000;
	 for(rit=cm.front().begin;rit!=cm.front().end;rit++)
	 {
	 	for(mit=rit->mom.begin();mit!=rit->mom.end();mit++)
		{
		 	if( mit->udt.type==proddt)
			{
				cv_prodRadial prodRad;
				prodRad.data=mit->data;
				prodRad.header.angStart=rit->az;
				prodRad.header.angReso=gdi.cuts[0].angleReso;
				prodRad.header.binNum=mit->data.size();
				pdi.radials.push_back(prodRad);
				//search max 
				for(int i=0;i<mit->data.size();i++)
				{
					int code=mit->data[i];
					if(!isSpecCode(code))
					{
						if(code>max)
							max=code;
					}
				}
			}
		}
	 }
	 pdi.radialHeader.max=max;

}
const char *OP_IF="if";
const char *OP_OF="of";
const char *OP_RESO="reso";
const char *OP_RANGE="range";
const char *OP_PRODNAME="prodname";
void help()
{
	printf("Cinrad new basedata read/write demo program\n");
#define DUMP_OP(a,desp) printf( "\t --%s desp \n",a);
			//printf("\t --%s input base data file\n",OP_IF);
			DUMP_OP(OP_IF ,"input base data file");
			DUMP_OP(OP_OF ,"output base data file, default is test.ar2");
			DUMP_OP(OP_PRODNAME ,"output product name");
			DUMP_OP(OP_RESO ,"output product reso in meter,default as input basedata");
			DUMP_OP(OP_RANGE ,"output product max range in km,default as input basedata");
			exit(0);
}

int main(int argc,char *argv[])
{
	//first process program options
	struct AppOptions options;
	memset(&options,0,sizeof(options));
	
	strcpy(options.outfile,"test.ar2");
	for(int i=1;i<argc;i++)
	{
		if(strcmp(argv[i],"help")==0)
		{
			help();
		}
		else if(strcmp(argv[i],OP_IF)==0)
		{
			i++;
			strcpy(options.infile,argv[i]);
		}
		else if(strcmp(argv[i],OP_OF)==0)
		{
			i++;
			strcpy(options.outfile,argv[i]);
		}
		else if(strcmp(argv[i],OP_PRODNAME)==0)
		{
			i++;
			strcpy(options.prodname,argv[i]);
		}
		else if(strcmp(argv[i],OP_RESO)==0)
		{
			i++;
			sscanf(argv[i],"%d",&options.reso);
		}
		else if(strcmp(argv[i],OP_RANGE)==0)
		{
			i++;
			sscanf(argv[i],"%d",&options.range);
		}
	}
	if((strlen(options.infile)==0)||(strlen(options.prodname)==0))
	{
		printf("input file and product name is needed\n");
		help();
	}
	//code to read new basedata 
	struct basedataImage  gdi;
	int ret=loadBasedataImage(options.infile,gdi);
	if(ret!=1)
		printf("load file %s failed\n",options.infile);
	//addd base data quality alogrithm here

	//code to create new basedata file
	ret= writeBasedataImage(options.outfile,gdi);
	if(ret!=1)
	{
		printf("write file %s failed\n",options.outfile);
	}
	
	//code to create ppi product from basedata
    	struct PPIProdImage  pdi;
	createPPIProduct(gdi,pdi,options.reso,options.range,options.prodname);
	char *ppiPath="./product_ppi";
	ret=writeProductImage(ppiPath,pdi);
	return 0;
}
