// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#ifndef RPG_CONVERT_BASEDATA_COVERTER_H
#define RPG_CONVERT_BASEDATA_COVERTER_H
#include "genericBasedata.h"
#include "genericHeader.h"
#include "genericTask.h"
#include "generic_common_cv.h"
#include<vector>
#include<list>
using namespace std;
#define NOPRF 0
#define PRF1 322
#define PRF2 446
#define PRF3 644
#define PRF4 857
#define PRF5 1014
#define PRF6 1095
#define PRF7 1181
#define PRF8 1282
struct cv_geneMom 
{
	geneMomHeader udt;
	ubytes data;	
};
typedef list<cv_geneMom> cvGeneMom;
struct cv_geneRadial:public geneRadialHeader
{
	cvGeneMom mom;
};
typedef list<cv_geneRadial> cvRadial;
struct basedataImage :public commonImage{
	cvRadial radials;
};
struct cv_cutmark{
	cvRadial::iterator begin;
	cvRadial::iterator end;
	size_t radNum;
};
typedef list<cv_cutmark>cvCutMark;
int loadBasedataImage(const char *fpath,struct basedataImage &gdi);
int writeBasedataImage(const char*fpath,struct basedataImage &gdi);
bool fakeVcpTaskConfig(int vcp,geneTaskConfig &task,cvCutConfig &cuts);
void fakeSiteInfo(const char *name,geneSiteConfig &sc);
void searchCuts(struct basedataImage &bdi,cvCutMark &cutMarks);
void uniCopyFromShort(unsigned char *dest,unsigned short *src,size_t binnum,size_t binSize);
void uniCopyToShort(unsigned short *dest,unsigned char *src,size_t binnum,size_t binSize);
void decodeMomData(const cv_geneMom &gm,float *data,float def);
void updateRadailLength(struct basedataImage &gdi);
time_t compTaskRunTime(geneTaskConfig &tc,cvCutConfig &cuts);
bool searchNearestAz(float faz,const cvRadial::iterator bit,const cvRadial::iterator eit,cvRadial::iterator &mit);
#endif
