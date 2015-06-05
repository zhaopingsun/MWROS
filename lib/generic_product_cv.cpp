// **********************************************************************
//
// Copyright (c) 1996-2014 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#include "generic_product_cv.h"
#include "generic_common_cv.h"
#include <stdlib.h>
#include <string.h>
int const RADIAL_PROD_COMM_LEN=sizeof(geneProdSpec)+ \
	     sizeof(geneRadialProdHeader)+sizeof(geneProdCommHeader);
const size_t RDH_LEN=sizeof(geneRadialDataHeader);
size_t compRadialBinNum(geneRadialProdHeader &radialHeader)
{
	return (radialHeader.maxRange)/radialHeader.reso;
}
int loadProductImage(const char*fpath,struct PPIProdImage &pdi)
{
	FILE *fp=fopen(fpath,"rb");
	if(fp==NULL)
		return -1;
	int ret=loadCommonHeader(fp,GDT_PRODUCT,&pdi);
	if(ret!=1)
		return ret;
	ret=fread(&pdi.header,RADIAL_PROD_COMM_LEN,1,fp);
	if(ret!=1)
	{
		fclose(fp);
		return -6;
	}
	if(pdi.radialHeader.dataType.binSize==2)
	{
		fprintf(stderr,"2 bytes data is not supported\n");
		exit(-7);
	}
	size_t binNum=compRadialBinNum(pdi.radialHeader);
	int binSize=pdi.radialHeader.dataType.binSize;
	int const DATA_LEN=pdi.radialHeader.dataType.binSize*binNum;
	int const RADIAL_LEN=DATA_LEN+RDH_LEN;
	char *buf=(char*) malloc(RADIAL_LEN*2);
	cv_prodRadial rad;	
	rad.data.resize(binNum);
	for(int i=0;i<pdi.radialHeader.radNum;i++)
	{
		ret=fread(&buf[0],1,RADIAL_LEN,fp);
		if(ret!=RADIAL_LEN)
		{
			break;
		}

		memcpy(&rad.header,&buf[0],RDH_LEN);
		if(binSize==2)
			memcpy(&rad.data[0],&buf[RDH_LEN],DATA_LEN);
		else
		{
			for(int i=0;i<binNum;i++)
				rad.data[i]=buf[RDH_LEN+i];
		}
		pdi.radials.push_back(rad);
	}
	free(buf);
	fclose(fp);
	return 1;
}
int writeProductImage(const char*fpath,struct PPIProdImage &pdi)
{
	FILE *fp=fopen(fpath,"wb+");
	if(fp==NULL)
		return -1;
	int ret=writeCommHeader(fp,&pdi);
	if(ret!=1)
		return ret;
	ret=fwrite(&pdi.header,RADIAL_PROD_COMM_LEN,1,fp);
	if(ret!=1)
	{
		return -6;
		fclose(fp);
	}
	pdi.radialHeader.radNum=pdi.radials.size();
	size_t binNum=compRadialBinNum(pdi.radialHeader);
	int binSize=pdi.radialHeader.dataType.binSize;
	int const DATA_LEN=binSize*binNum;
	int const RADIAL_LEN=DATA_LEN+RDH_LEN;
	char* buf=(char*)malloc(RADIAL_LEN*2);
	geneProdRadial::iterator it;	
	for(it=pdi.radials.begin();it!=pdi.radials.end();it++)
	{
		memcpy(buf,&(it->header),RDH_LEN);
		if(binSize==2)
			memcpy(&buf[RDH_LEN],&(it->data[0]),DATA_LEN);
		else
		{
			for(int i=0;i<binNum;i++)
			{
				buf[RDH_LEN+i]=it->data[i];
			}
		}
		ret=fwrite(&buf[0],1,RADIAL_LEN,fp);
		if(ret!=RADIAL_LEN)
		{
			fprintf(stderr,"write radial failed\n");
			free(buf);
			fclose(fp);
			return -2;
		}
	}
	free(buf);
	return 1;
}
