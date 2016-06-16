// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#ifndef COMM0N_UTIL_NAME_INDEX_H
#define COMM0N_UTIL_NAME_INDEX_H
//#include "boost/assign.hpp"
#include <map>
using namespace std;
//using namespace boost::assign;
typedef map<int,const char* > NameIndexMap;
typedef map<int,int> TypeMaskMap;
int NameToIndex(NameIndexMap &m,const char *rdtstr);
const char *IndexToName(NameIndexMap &m,const int rdti);
#endif
