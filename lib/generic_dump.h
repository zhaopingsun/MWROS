// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#ifndef  RPG_GENERIC_DUMP_H
#define  RPG_GENERIC_DUMP_H
#include "generic_basedata_cv.h"
#include "NameIndex.h"
#include "geneCodeData.h"
void dumpHeader( geneHeader &hdr);
void dumpSite(geneSiteConfig &si);
void dumpTask(geneTaskConfig &task);
void dumpCuts(cvCutConfig &cuts);
void dumpCommHeader(struct commonImage *img);
void Timeval2String(int sec,int usec,char *buf);
#endif
