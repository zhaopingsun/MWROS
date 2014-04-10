// **********************************************************************
//
// Copyright (c) 1996-2014 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#include "generic_basedata_cv.h"
#include <iostream>
#include "NameIndex.h"
#include "geneCodeData.h"
//#include <unistd.h>
#include "generic_dump.h"
using namespace std;
bool gDumpCode=false;
int const DT_ALL=-1;
void dumpRadials(cvRadial &rads,int lineWidth,int dt)
{
	cvRadial::iterator it;
	for(it=rads.begin();it!=rads.end();it++)
	{
		printf("state %d,seqNum %d,radIdx %d,elIdx %d",
				it->state,it->seqNum,it->radIdx,it->elIdx);
		printf("el %.2f az %.2f momNum %d time %d timeusec %d\n",
				it->el,it->az,it->momNum,it->timeSec,it->timeUsec);
		cvGeneMom::iterator iit;	
		for(iit=it->mom.begin();iit!=it->mom.end();iit++)
		{
			int mdt=iit->udt.type;
			if(!(dt==mdt||dt==DT_ALL))
				continue;
			printf("type %s scale %d  offset %d size %d\n",
					RdtToStr(iit->udt.type),iit->udt.scale,
					iit->udt.offset,iit->udt.binSize);
			int binnum=lineWidth;

			for(int i=0;i<iit->data.size();i++)
			{
				if(i%binnum==0)
				{
					if(i!=0) printf("\n");
					printf("%03d: ",i+1);
				}
				short code=iit->data[i];
				
				if(gDumpCode)
				{
					printf("%6d ",code);
				}
				else
				{
					if(isSpecCode(code))
					{
						printf("  NA  ");
					}
					else
					{
						float val=decodeData(iit->udt.offset,iit->udt.scale,code);
						printf("% 3.2f ",val);
					}

				}

			}
			printf("\n");
		}
	}
}
const char* OP_IF="--if";
const char *OP_CODE="--code";
const char *OP_BINCNT="--width";
const char *OP_DT="--data";
const char *OP_BR="--br";
void help()
{
	printf("new AR2 basedata file dumper \n");
#define DUMP_OP(a,desp) printf("\t %s: %s\n",a,desp);	
	DUMP_OP(OP_IF,"basedata file");
	DUMP_OP(OP_CODE,"dump moment data as code, default is real value");
	DUMP_OP(OP_BR,"dump brief decription of basedata");
	DUMP_OP(OP_DT,"the data type name to be dumped,all available data is dumped by default.the name can be found in taskconfig");
	DUMP_OP(OP_BINCNT,"bin number count per line");
	exit(0);	
}
int main(int argc,char*argv[])
{
	bool gVerbose=false;
	int lineWidth=30;
	bool gBrief=false;
	int dt=-1;
	char const  *fpath=NULL;
	for(int i=1;i<argc;i++)
	{
		if(strcmp("--help",argv[i])==0)
		{
			help();
		}
		else if(strcmp(OP_IF,argv[i])==0)
		{
			i++;
			fpath=argv[i];
		}
		else if(strcmp(OP_CODE,argv[i])==0)
		{
			gDumpCode=true;
		}
		else if(strcmp(OP_BR,argv[i])==0)
		{
			gBrief=true;
		}
		else if(strcmp(OP_BINCNT,argv[i])==0)
		{
			i++;
			sscanf(argv[i],"%d",&lineWidth);
		}
		else if(strcmp(OP_DT,argv[i])==0)
		{
			i++;
			dt=RdtToIndex(argv[i]);
		}
	}

	basedataImage bdi;
	int ret=loadBasedataImage(fpath,bdi);
	if(ret<1)
	{
		printf("load file %s failed \n",fpath);
		return -1;
	}
	if(!gBrief)
	{
		dumpCommHeader(&bdi);
		dumpRadials(bdi.radials,lineWidth,dt);
	}
	else
	{
		printf("%s: %s(",fpath,bdi.taskConf.name);
		for(int i=0;i<bdi.cuts.size();i++)
		{
			printf("%.2f ",bdi.cuts[i].el);
		}
		printf(")\n");
	}

	return 0;
}
