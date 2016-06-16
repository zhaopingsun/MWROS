// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#ifndef GENERIC_RPODUCT_CONVERT_H
#define GENERIC_RPODUCT_CONVERT_H
#include"genericProduct.h"
#include "generic_common_cv.h"
#include<list>
struct cv_prodRadial
{
	geneRadialDataHeader header;
	ubytes data;
};
typedef list<cv_prodRadial>geneProdRadial;
struct ProdBaseImage: public commonImage
{
	geneProdCommHeader header;
	geneProdSpec  spec;
};
struct PPIProdImage:public ProdBaseImage
{
	geneRadialProdHeader radialHeader;
	geneProdRadial radials;
};
int loadProductImage(const char*fpath,struct PPIProdImage &pdi);
int writeProductImage(const char*fpath,struct PPIProdImage &pdi);
#endif
