// **********************************************************************
//
// Copyright (c) 1996-2014 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#ifndef RADAR_PRODUCT_TYPE_H
#define RADAR_PRODUCT_TYPE_H
/*
 product type defination
*/
const short PT_PPI	=   1;
const short PT_RHI	=   2;
const short PT_CAPPI    =   3;
const short PT_MAX	=   4;
const short PT_RAW	=   5;
const short PT_ET	=   6;
const short PT_BEAM	=   7;
const short PT_VCS	=   8;
const short PT_LRA	=   9;
const short PT_LRM	=  10;
const short PT_LTA	=  11;
const short PT_LTM	=  12;
const short PT_SRR	=  13;
const short PT_SRM	=  14;
const short PT_SWA	=  15;
const short PT_SWA4	=  16;
const short PT_HVVP	=  17; //NJU HVVP
const short PT_CM	=  19;
const short PT_WER	=  20;
const short PT_APR	=  21;
const short PT_CFC	=  22;
const short PT_VIL	=  23;
const short PT_HSR	=  24;
const short PT_OHP	=  25;
const short PT_THP	=  26;
const short PT_STP	=  27;
const short PT_USP	=  28;
const short PT_CATCH	=  29;
const short PT_SPD	=  30;
const short PT_VAD	=  31;
const short PT_VWP	=  32;
const short PT_WIND	=  33;
const short PT_SHEAR	=  34;
const short PT_CR       =  35;   // only import from CINRAD, not for request
const short PT_SWP	=  36;
const short PT_STI	=  37;
const short PT_HI	=  38;
const short PT_M	=  39;
const short PT_TVS	=  40;
const short PT_SS	=  41;
const short PT_MBO	=  42;
const short PT_VERG	=  43;
const short PT_UAM	=  44;
const short PT_FTM	=  45;
const short PT_HMAX     =  46;
const short PT_EB	=  47;
const short PT_GAGE     =  48;
const short PT_CTR      =  49;   // contour
const short PT_ML       =  50;
const short PT_HCL      =  51;
const short PT_QPE      =  52;
const short PT_COMP     =  53;
const short PT_COMP_MAX =  54;
const short PT_MBD      =  55;   // mircoburst detection
const short PT_GFD      =  56;   // gust front detection
const short PT_SWIS     =  57;
const short PT_DSD      =  58;
const short PT_COMP_VCS =  59;
const short PT_COMP_WIND =  60;

/* user defined products */
const short PT_USER     =  91;

/* following products are not displayable */ 
const short PT_ML_T     = 101;   // internal melting layer product
const short PT_PDA_T	= 102;   // internal Precipitation Detection Algorithm output
const short PT_PDA	= 103;   // Precipitation Detection Algorithm output
const short PT_OHP_T	= 104;   // OHP product without gage adjustmentation
const short PT_IGST     = 105;   // ingest product pre-created for a few raster products
const short PT_IGST_MAT = 106;   // ingest product of virtual site
const short PT_HCL_T    = 107;   // cached cut of hcl data
const short PT_QPE_T    = 108;   // cached cut of qpe data
const short PT_MB_T     = 109;
const short PT_GF_T     = 110;   // combined interest image generated per scan for gust front detection
const short PT_PPI_T    = 111;   // ppi with constant az delta, for building rain prod
const short PT_WIND_T	= 112;   // wind field base cut

/* maximum number of product type */
const short PT_MAXVALUE = 200;
#endif
