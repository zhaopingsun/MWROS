// **********************************************************************
//
// Copyright (c) 1996-2014 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#include<stdio.h>
#include<string.h>
#include <string>
#include <stdlib.h>
#include "ar2.h"

using namespace std;
void usage()
{
	
	printf("--file base data file\n");
	printf("--data data type to dump (DBZ/DBT/VEL/WID)\n");
	printf("--ele elevation index\n");
	printf("--width bin number per line\n");
	printf("--start start range to dump data(km)\n");
	printf("--stop stop range to dump data(km)\n");
	exit(-1);
}
int main(int argc,char *argv[])
{
	if(argc<2)
		usage();
	char fname[256]={0};
	int width=5,eleIdx=0,dataType=-1,start=0,stop=1000;
	for(int i=1;i<argc;i++)
	{
		if(0==strcmp(argv[i],"--file"))
		{
			i++;
			strcpy(fname,argv[i]);
		}
		else if(0==strcmp(argv[i],"--data"))
		{
			i++;
//			dataType=RdtToIndex(argv[i]);
			if(dataType<0)
			{
				printf("unknown data type %s\n",argv[i]);
			//	exit(-1);
			}
		}
		else if(0==strcmp(argv[i],"--ele"))
		{
			i++;
			sscanf(argv[i],"%d",&eleIdx);
			if(eleIdx<0)
			{
				printf("invalid elevation index %d\n",eleIdx);
				exit(-1);
			}
		}
		else if(0==strcmp(argv[i],"--width"))
		{
			i++;
			sscanf(argv[i],"%d",&width);
		}
		else if(0==strcmp(argv[i],"--start"))
		{
			i++;
			sscanf(argv[i],"%d",&start);
		}
		else if(0==strcmp(argv[i],"--stop"))
		{
			i++;
			sscanf(argv[i],"%d",&stop);
		}
		else
		{
			printf("unkown option %s\n",argv[i]);
			exit(-1);
		}
	}
	FILE *fp=fopen(fname,"rb");
	if(fp==NULL)
	{
		exit(-1);
	}
	unsigned char buf[SA_BD_RADIAL_LEN];
	while(1)
	{
		int len=fread(buf,SA_BD_RADIAL_LEN,1,fp);
		if(len!=1)
		{
			break;
		}
		Basedata *pbd=(Basedata*)buf;
		float COEF=1.0/8*(180.0/4096);
		printf("index %d ,az %.2f, el %.2f \n",pbd->RadialNumber,pbd->Az*COEF,pbd->El*COEF);
		int const DUMP_BIN=30;
		if(dataType>0)
		{
			if(pbd->PtrOfReflectivity!=0)
			{
				printf("Ref\t");
				unsigned char *pStart=buf+sizeof(Basedata)+(pbd->PtrOfReflectivity)-100;
				for(int i=0;i<DUMP_BIN;i++)
				{
					printf("%d ",pStart[i]);
				}
				printf("\n");
			}
			if(pbd->PtrOfVelocity!=0)
			{
				printf("Vel\t");
				unsigned char *pStart=buf+sizeof(Basedata)+(pbd-> PtrOfVelocity)-100;
				for(int i=0;i<DUMP_BIN;i++)
				{
					printf("%d ",pStart[i]);
				}
				printf("\n");
			}
		}/**/
	}
	fclose(fp);
	
}
