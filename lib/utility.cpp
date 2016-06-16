// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#include "utility.h"
#include<stdio.h> 
#include "proj_api.h"
void swap(short &d)
{
	unsigned short dd=d;	
	d=(dd%256)*256+dd/256;
}

void swap(unsigned short &d)
{
	short x=d;
	swap(x);
	d=x;
}
/*
 * \notice this very strange ,it's not the really big-endian.this should called
 *  16bit  atomic element size. for example number 0X0A0B0C0D stored as 0x0B0A0D0C
 */
void swap(int &d)
{
	int x=d;
	short *ps=(short*)&x;
	swap(ps[1]);
	swap(ps[0]);
	d=ps[0]*65536+ps[1];
//	printf("%d %d  %d\n",ps[0],ps[1],d);
}
void LogMessage(char *msg,int level)
{
	printf("%s\n",msg);
}
float const BIT_PER_DEG=180.0/4096;
float DecodeAnteAngleDeg(short ang)
{
	float a= ang*BIT_PER_DEG;
	if(a<0)
		a+=360;
	return a;
}
short CodeAnteAngleDeg(float ang)
{
	return short(8*ang/BIT_PER_DEG);
}
void GetCode16Form(short  &offset,short &scale)
{
	offset=20000;
	scale=100;
}
float DecodeVW8(char c)
{
	unsigned char d=c;
	return (d-129)/2.0;
}
float DecodeRef8(char c)
{
	unsigned char d=c;
	return (d-66.0)/2.0;
}
short Code16(float val)
{
	short sc,of;
	GetCode16Form(of,sc);
	return val*sc+of;
	
}
float Decode16(short code)
{
	short sc,of;
	GetCode16Form(of,sc);
	return (code-of)*1.0/sc;
}
/**
 [0,2PI)
 in radar polar system, zero start from north, so we should use (x,y).
*/
float atanDeg(float y,float x)
{
	float rad=atan2(y,x);
	float deg=rad*RAD_TO_DEG;	
	if(deg<0)
		deg+=360;
	else if(deg>=360)
		deg-=360;
	return deg;
}

