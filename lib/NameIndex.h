// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#ifndef RADAR_PRODUCT_NAME_H
#define RADAR_PRODUCT_NAME_H
#include<string>
using namespace std;
/**
  convert radar data type  string type to index 
  -1 for invalid string
  */
int RdtToIndex(const char *rdtstr);
int RdtToIndex(const string &rdtstr);
/** 
  convert radar data type index to string
  NULL for invalid data type
 */
const char * RdtToStr(const int rdti);
const char * RdtToShortStr(const int rdti);
/**
  convert product name string to index
  -1 for invliad string
  */
int ProdTypeToIndex(const char *prodstr);
int ProdTypeToIndex(const string &prodstr);
/**
  convert product name index to string;
  NULL for invalid index
  */
const char * ProdTypeToStr(const int prodi);
const char *RdtUnit(int rdt);
/**
  convert product type to Unit name;
*/
const char * RdtUnitName(const int prodi);

/**
  get product supporting task mask
*/
int GetProdTaskMask(int prodtype);
#endif

/**
   get corrected data type of input
*/
int getCorrectedRdt(int type);
int getBasedRdt(int type);
