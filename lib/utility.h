// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#ifndef PUP_UITIL_H
#define PUP_UITIL_H
#include <time.h>
#include <math.h>
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define CP_TO_BIN(AD,b) \
	b.resize(sizeof(AD)) ;\
	memcpy(&b[0],&AD,sizeof(AD));

#define CP_FROM_BIN(AD,b) \
	if(sizeof(AD)==b.size()) \
	 	memcpy(&AD,&b[0],b.size());\
	else \
		printf("%s size %d not match  with bin size %d",#AD,sizeof(AD),b.size());

#define MIN(a,b) \
(( (a)>(b))?(b):(a))
#define MAX(a,b) \
(( (a)<(b))?(b):(a))
#define Deg2Rad(a) \
    ((a)*M_PI/180.0)
#define SQUARE(a) \
    ((a)*(a))
void swap(short &d);
void swap(unsigned short &d);
void swap(int &d);
void LogMessage(char *msg,int level=0);
time_t JuData2time(int day,int sec);
float DecodeAnteAngleDeg(short ang);
short CodeAnteAngleDeg(float ang);
float DecodeVW8(char c);
float DecodeRef8(char c);
short Code16(float val);
float Decode16(short code);
void GetCode16Form(short  &offset,short &scale);
float atanDeg(float y,float x);
/**
  internal code decode az el
  */
#define INT_DEC_ANG( ang) \
        ((ang)/10.0)
#define INT_CODE_ANG(ang) \
        (nearbyint(ang*10.0))
#endif
