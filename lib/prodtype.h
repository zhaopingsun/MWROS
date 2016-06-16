// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
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
const short PT_PPI          =   1;
const short PT_RHI          =   2;
const short PT_CAPPI        =   3;
const short PT_MAX          =   4;
const short PT_RAW          =   5;
const short PT_ET           =   6;
const short PT_BEAM         =   7;
const short PT_VCS          =   8;
const short PT_LRA          =   9;
const short PT_LRM          =  10;
const short PT_LTA          =  11;
const short PT_LTM          =  12;
const short PT_SRR          =  13;
const short PT_SRM          =  14;
const short PT_SWA          =  15;
const short PT_SWA4         =  16;
const short PT_HVVP         =  17; //NJU HVVP
const short PT_CM           =  19;
const short PT_WER          =  20;
const short PT_APR          =  21;
const short PT_CFC          =  22;
const short PT_VIL          =  23;
const short PT_HSR          =  24;
const short PT_OHP          =  25;
const short PT_THP          =  26;
const short PT_STP          =  27;
const short PT_USP          =  28;
const short PT_CATCH        =  29;
const short PT_SPD          =  30;
const short PT_VAD          =  31;
const short PT_VWP          =  32;
const short PT_WIND         =  33;
const short PT_SHEAR        =  34;
const short PT_SWP          =  36;
const short PT_STI          =  37;
const short PT_HI           =  38;
const short PT_M            =  39;
const short PT_TVS          =  40;
const short PT_SS           =  41;
const short PT_MBO          =  42;
const short PT_VERG         =  43;
const short PT_UAM          =  44;
const short PT_FTM          =  45;
const short PT_HMAX         =  46;
const short PT_EB           =  47;
const short PT_GAGE         =  48;
const short PT_CTR          =  49;   // contour
const short PT_ML           =  50;
const short PT_HCL          =  51;
const short PT_QPE          =  52;
const short PT_COMP         =  53;
const short PT_SLINE        =  54;   // shear line
const short PT_MBD          =  55;   // mircoburst detection
const short PT_GFD          =  56;   // gust front detection
const short PT_SWIS         =  57;
const short PT_DSD          =  58;
const short PT_NDOP         =  59;
const short PT_NCATCH       =  60;
const short PT_COMP_VCS     =  61;
const short PT_COMP_MAX     =  62;
const short PT_SRI          =  63;
const short PT_TDWR         =  64;
const short PT_NSCAN        =  65;
const short PT_NUAM         =  66;
const short PT_NGRID        =  67;
const short PT_ERHI         =  68;

/* user defined products */
const short PT_USER         =  91;

/* following products are not displayable */ 
const short PT_ML_T         = 101;   // internal melting layer product
const short PT_PDA_T        = 102;   // internal Precipitation Detection Algorithm output
const short PT_PDA          = 103;   // Precipitation Detection Algorithm output
const short PT_OHP_T        = 104;   // OHP product without gage adjustmentation
const short PT_IGST         = 105;   // ingest product pre-created for a few raster products
const short PT_IGST_MAT     = 106;   // ingest product of virtual site
const short PT_HCL_T        = 107;   // cached cut of hcl data
const short PT_QPE_T        = 108;   // cached cut of qpe data
const short PT_MB_T         = 109;   // cached temp result for mircoburst detection
const short PT_GF_T         = 110;   // cached temp result for gust front detection
const short PT_PPI_T        = 111;   // ppi with constant az delta, for building rain prod
const short PT_WIND_T       = 112;   // wind field base cut
const short PT_RI_VOL       = 113;
const short PT_RI_VOLC      = 114;
const short PT_MALF         = 115;   // system malfunction detection

/* definition for legacy product, read only for compatible  */
const short PT_R            =  151;   //PPI
const short PT_V            =  152;   //PPI
const short PT_SW           =  153;   //PPI
const short PT_CR           =  154;   //MAX
const short PT_CRC          =  155;   //CONTOUR
const short PT_ETC          =  156;   //CONTOUR
const short PT_CS           =  157;   //SHEAR
const short PT_CSC          =  158;   //SHEAR
const short PT_SWR          =  159;   //SWA
const short PT_SWV          =  160;   //SWA
const short PT_SWW          =  161;   //SWA
const short PT_SWS          =  162;   //SWA
const short PT_RCS          =  163;   //VCS
const short PT_ET2          =  164;   //VCS
const short PT_SCS          =  165;   //VCS
const short PT_CAR          =  166;   //CAPPI
const short PT_CAV          =  167;   //CAPPI
const short PT_CAS          =  168;   //CAPPI
const short PT_PPR          =  169;   //PPI
const short PT_PPV          =  170;   //PPI
const short PT_PPS          =  171;   //PPI
const short PT_RHR          =  172;   //RHI
const short PT_RHV          =  173;   //RHI
const short PT_RHS          =  174;   //RHI

/* maximum number of product type */
const short PT_MAXVALUE     = 200;
#endif
