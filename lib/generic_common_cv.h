// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#ifndef GENERIC_COMMON_CONVERT_H
#define GENERIC_COMMON_CONVERT_H
#include "genericTask.h"
#include "genericHeader.h"
#include <stdio.h>
typedef shortVec ubytes;
typedef vector<geneCutConfig> cvCutConfig;
struct commonImage{
	geneHeader uniHeader;
	geneSiteConfig siteInfo;
	geneTaskConfig taskConf;
	cvCutConfig cuts;
};
int loadCommonHeader(FILE *fp,int t,commonImage*cmn);
int writeCommHeader(FILE *fp ,commonImage*cmn);
int loadTaskConfig(const char *fpath,commonImage &ci,char *error);
#endif
