// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#include "geneCodeData.h"
#include "radar_dt.h"
#include <math.h>
/* default code scale/offet for all data type */
//data type value within [0,1];
bool range01(int type)
{
	return (type==RDT_PROB||type==RDT_SQI||type==RDT_CC||type==RDT_CP);
}
//range for degree [0-360];
bool rangedeg(int type)
{
	return type==RDT_PDP||type==RDT_DEG||type==RDT_PDPC;
}
bool getFormulaByte2(int type,int &scale,int &offset)
{
    if(type==RDT_HGT)
    {
        scale = 1000;
        offset = 100;
    }
    else if(type==RDT_RR)
    {
        scale = 10;
        offset = 10000;
    }
    else if(type==RDT_SHR)
    {
        scale = 10;
        offset = 20000;
    }
    else if(rangedeg(type)|| type==RDT_RAIN)
    {
        scale = 50;
        offset = 100;
    }
    else if(type==RDT_HCL)
    {
        scale = 1;
        offset = 100;
    }
    else if(type==RDT_RDD)
    {
        scale = 100;
        offset = 100;
    }
    else if(type==RDT_RDN)
    {
        scale = 1;
        offset = 100;
    }
    //data range within 
    else if (range01(type))
    {
        scale = 10000;
        offset = 100;
    }
    else
    {
        scale = 100;
        offset = 20000;
    }
    return true;
}

/* get default coding formula for base data, using 1 byte for each bin */
bool getFormulaByte1(int type,int &scale,int &offset)
{
    if (type==RDT_DBZ||type==RDT_DBT||type==RDT_SNR)
    {
        offset=66;
        scale=2;
    }
    else if (type==RDT_VEL||type==RDT_WID)
    {
        offset=129;
        scale=2;
    }
    else if (range01(type))
    {
        offset = MIN_DATA;
        scale = 200;
    }
    else if (type==RDT_ZDR)
    {
        offset = 130;
        scale = 16;
    }
    else if (type==RDT_LDR)
    {
        offset = 225;
        scale = 5;
    }
    else if (rangedeg(type))
    {
        offset = MIN_DATA;
        scale = 1;
    }
    else if (type==RDT_KDP)
    {
        offset = 130;
        scale = 5;
    }
    else if (type==RDT_HCL||type==RDT_CF)
    {
        offset = MIN_DATA;
        scale = 1;
    }
    else if (type==RDT_RR||type==RDT_RAIN)
    {
        offset = MIN_DATA;
        scale = 1;
    }
    else if (type==RDT_HGT)
    {
        offset = MIN_DATA;
        scale = 10;
    }
    else if (type==RDT_VIL)
    {
        offset = MIN_DATA;
        scale = 2;
    }
    else if (type==RDT_SHR)
    {
        offset = MIN_DATA;
        scale = 2;
    }
    else
        return false;
    return true;
}

bool getFormulaByte2(int type,geneUniDataType &udt)
{
    udt.type=type;
    udt.binSize = 2;
    udt.flag = 0;
    return getFormulaByte2(udt.type,udt.scale,udt.offset);
}

bool getFormulaByte1(int type,geneUniDataType &udt)
{
    udt.type=type;
    udt.binSize = 1;
    udt.flag = 0;
    return getFormulaByte1(udt.type,udt.scale,udt.offset);
}


bool isSpecCode(short data)
{
    if(data>MAX_SPEC_CODE)
        return false;
    return true;
}
short codeData(int of,int sl,float val)
{
    short res= (short)( val*sl+of+0.5);
    return res>=MIN_DATA?res:0;
}
short codeData(geneUniDataType &udt,float val)
{
    return codeData(udt.offset,udt.scale,val);
}
float decodeData(int of,int sl,short code)
{
    return 1.0*(code-of)/sl	;
}
float decodeData(geneUniDataType &udt,short code)
{
    return decodeData(udt.offset,udt.scale,code);
}
float roundDegree(float a)
{
	float phi=a;	
	float phi_ratio=phi/360.0;
	phi-=floor(phi_ratio)*360;
	return phi;
}
