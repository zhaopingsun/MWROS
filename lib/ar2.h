// **********************************************************************
//
// Copyright (c) 1996-2014 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef RADAR_BASE_DATA_H
#define RADAR_BASE_DATA_H
/*basedata
int const CUT_START=0;
int const CUT_MID=1;
int const CUT_END=2;
int const VOL_START=3;
int const VOL_END=4;
*/
typedef struct {
 //CTM Header (6 halfwords)
 short int  CTMHeader[6];
 
 //Message Header (8 halfwords)
 short   int     MsgSize; /* from this byte to end in halfwords
           should be 1208 for digital radar data */
 unsigned char   MsgType; //Message Type
 unsigned char   ChannelID;
 short   int     Sequence;
 short   int     JulianData1;
 unsigned int    mSeconds1;
 short   int     Segments; //分段号
 short   int     SegmentNo; //段中序数
    
 //Digigal Radar data Header (50 halfwords)
 int    mSeconds2;
 short int  JulianDate2;
 short int  URange; //不模糊距离
 unsigned short  Az;// (coded: (val/8)*(180/4096) = DEG)
 unsigned short    RadialNumber;
 /*     * 0 = start of new elevation
        * 1 = intermediate radial
       * 2 = end of elevation
       * 3 = beginning of volume scan
        * 4 = end of volume scan */

 short   int  RadialStatus;
 unsigned short   El;
 short int  ElNumber;
 short int  RangeToFirstGateOfReflectivity;
 short int  RangeToFirstGateOfDoppler;
 short int  GateSizeOfReflectivity;
 short int  GateSizeOfDoppler;
 short int  GatesNumberOfReflectivity;
 short int  GatesNumberOfDoppler;
 short   int     SectorNum;
 float           Calibration; //系统增益标定常数
 short int  PtrOfReflectivity;
 short int  PtrOfVelocity;
 short int  PtrOfWidth;
 short int  ResolutionOfVelocity;
 short int  VcpNumber;
 short   int     ReservedVV[4]; //Reserved for V&V Simulator
 short   int     PtrofReflectivityArchive;
 short   int     PtrofVelocityArchive;
 short   int     PtrofSpectrumArchive;
 short int  Nyquist;
 short   int     AttenuationFactor;
 short   int     ThrRangeAmbiguous; /*Threshold parameter for minimum 
                           difference in echo power between two resolution volumes for them not to be labeled range ambiguous. */
 short int  Reserved[17];
 
 //DAta Block (1152 halfwords)
// short   int  Echodata[1152]; // for S band
 //short int Echodata[2002]; // for C band
}Basedata;
int const SA_MSG_SIZE=1152;
int const SA_BD_RADIAL_LEN=2432;
#endif
