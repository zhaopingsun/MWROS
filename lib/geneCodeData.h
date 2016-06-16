// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#ifndef GENE_CODE_DATA_H
#define GENE_CODE_DATA_H

#include "genericBasedata.h"
short const NOT_DATA=0;
short const OK_DATA=4;
short const RF_DATA=1;
const short NOT_SCANNED=2;
const short HGT_NA=3;           // data unknown / height not available
const short MIN_DATA = 5;       // coding data start from
const short MAX_DATA = 255;     // coding data start from
short const NO_SIGNAL=NOT_DATA;
const short MAX_SPEC_CODE=4;

bool getFormulaByte2(int type,int &,int &);
bool getFormulaByte1(int type,int &,int &);

bool getFormulaByte2(int type,geneUniDataType &udt);
bool getFormulaByte1(int type,geneUniDataType &udt);
short codeData(int of,int sl,float val);
short codeData(geneUniDataType &udt,float val);
float decodeData(int of,int sl,short code);
float decodeData(geneUniDataType &udt,short code);
bool isSpecCode(short data);
//round to 0-360
float roundDegree(float a);
#endif
