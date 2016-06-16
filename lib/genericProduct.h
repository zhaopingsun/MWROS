// **********************************************************************
//
// Copyright (c) 1996-2016 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#ifndef GENERIC_PRODUCT_H
#define GENERIC_PRODUCT_H
#include "genericHeader.h"
#include "genericTask.h"
#include "genericBasedata.h"
#pragma pack(push,1)

#define PROD_NAME_LENGTH    (32)
#define MAX_VAD_HEIGHTS     (30)
#define KEY_OPTION_SIZE     (16)

/* product index save file */
typedef struct
{
    char siteCode[SITE_CODE_LENGTH];//site name
    char taskName[TASK_NAME_LENGTH];
    int volStartTime;//volume start time
    int prodGenTime; //product generation time
    int prodType;//product code
    char prodName[PROD_NAME_LENGTH]; // product name, name of product configuration (not product type name)
    int projType;//projection type

    int nopts; //mumber of options
    int options[KEY_OPTION_SIZE];
    char fileName[64];//file short name on disk
    int spare[9];
}geneProductIndex;

/**
  format of product

  geneHeader
  siteConfig
  taskConfig
  taskSpec
  prodCommHeader
  Radial/Raster product Header
  product specific
  data


  */
struct geneProdCommHeader{
    int prodType;
    char prodName[PROD_NAME_LENGTH];
    int prodGenTime;
    int volStartTime;
    int dataStartTime;
    int dataEndTime;
    int projType;
    int momType1;
    int momType2; // 2 data types of base data for operation
    /*
*/
    int spared[16];
};
struct geneRadialProdHeader{
    geneUniDataType dataType;
    int reso;
    int startRange;
    int maxRange;
    int radNum;//number of radials
    int max; //maximum value in code
    int  rangeMax; //range of max data
    float azimuthMax; //azimuth of max data
    int min; //minimum value in code
    int  rangeMin; //range of min data
    float azimuthMin; //azimuth of min data	    
    int spared[2];
};
struct geneRasterProdHeader{
    geneUniDataType dataType;
    int rowReso;
    int colReso;
    int rowNum;
    int colNum;
    int max; //maximum value in code
    int  rangeMax; //range of max data
    float azimuthMax; //azimuth of max data
    int min; //minimum value in code
    int  rangeMin; //range of min data
    float azimuthMin; //azimuth of min data	    
    int spared[2];
};
struct geneWerProdHeader{
    float el;
    int cutTime;
    int centerHeight;
    int spared[5];
};
struct geneRadialDataHeader{
    float angStart;
    float angReso;
    int binNum;
    int spared[5];
};
struct geneProdPpiSpec{
    float elevation;
};

struct geneProdRawSpec : public geneProdPpiSpec{
};

struct geneProdTopBaseSpec{
    float dbzContour;
};
struct geneProdCappiSpec{
    int layerNum;
    int top;
    int bottom;
    int fill;
};

struct geneProdRhiSpec{
    float azimuth;
    int top;
    int bottom;
};
struct geneProdMaxSpec{
    int top;
    int bottom;
};
struct geneProdHsrSpec{
};
struct geneProdSriSpec{
    int zrType;
};
struct geneProdQpeSpec{
};
struct geneProdQpetSpec{
    float elevation;
};
struct geneProdWerSpec {
    int centerRange;
    float centerAzimuth;
    int sideLength;
    int levels;
};
struct geneProdVadSpec {
    int layers;
    short heights[MAX_VAD_HEIGHTS];
};
struct geneProdHvvpSpec {
    int layerNum;
    int bottom;
    int top;
};
struct geneProdVwpSpec :public geneProdVadSpec{
};
struct geneProdVwpHeader{
    float nyquist;
    int volNum;
    float maxSpeed;
    float maxDir;
    float maxHeight;
    int spared[3];
};
struct geneProdVcsSpec {
    float startAz;
    int startRange;
    float endAz;
    int endRange;
    int top;
    int bottom;
};
struct geneProdCsSpec{
    float elevation;
    int radShear;
    int aziShear;
    int eleShear;
};
struct geneProdSLINESpec{
    float elevation;
    int maxRange;
    int dataType;
};

struct geneProdNDOPSpec{
    char mainSite[SITE_CODE_LENGTH];//code of Radar
    int dataType;
    int interval;
    int overlap;
    int height;
};

struct geneProdLramSpec{
    int top;
    int bottom;
};
struct geneProdSwaSpec{
    float elevation;
    int centerRange;
    float centerAzimuth;
    int sideLength;
};
struct geneProdSrrSpec : public geneProdSwaSpec{
    float velSpeed;
    float velDir;
};
struct geneProdHmaxSpec{
    float dbzMin;
};
struct geneProdSrmSpec{
    float elevation;
    float velSpeed;
    float velDir;
};
struct geneProdVilSpec{
    int spared[8];
};
struct geneProdStpSpec{
    int baseProd; //type of product based
    int cappiHeight; //height of cappi in meters, 0 for HSR
    int cappiFill; // false for HSR
    int adjustReq; //adjustment been requested
};

struct geneProdOhpSpec : public geneProdStpSpec{
};

struct geneProdUspSpec : public geneProdStpSpec{
    int hours;
};
struct geneProdSpdSpec : public geneProdStpSpec{
    int maxRange;
};

struct genePrecipAdapt{
    float    minthrfl;
    float    maxthrfl;
    float    reflectlt;
    int rngtltin;
    int rngtltout;
    int maxrngbi;
    int minarecho;
    float    minreflaa;
    int maxarpct;
    float    czm;
    float    czp;
    float    mindbzrfl;
    float    maxdbzrfl;
    int minrngbi;

    //rate
    int maxspdstm;
    float thrmxtdif;
    int minartimc;
    float    prmtimc1;
    float    prmtimc2;
    int mxratchg;
    int rngcutoff;
    float    rngcoef1;
    float    rngcoef2;
    float    rngcoef3;
    float    minprate;
    float    maxprate;

    //   --Accumulation
    int timrestrt;
    int maxtimint;
    int mintimpd;
    int thourli;
    int entimgag;
    int maxprdval;
    int maxhlyval;

    //   --Adjustment
    int timbiest;
    int thrnsets;
    float    resetbi;
    float    resmsqer;
    float    maxmsqer;
    int thrtimdif;
    float    resetbiastime;

    float    sysnoise;
    float    varadjfac;
    float    thgagdisc;
    int maxgagacc;
    float    thrrgacum;
};
struct geneProdStpInfo{
    float gageBias;
    float errorVar;
    int prodAdjusted;
};
struct geneHac{
    int time;
    int prodAdjusted;
    float gageBias;
    float errorVar;
    //	int scanType;
};
typedef vector<geneHac> geneHacSeq;
struct geneProdOhpInfo : public geneProdStpInfo{
};
struct geneProdThpSpec : public geneProdStpSpec{
    int hours;
};
struct geneProdSymbolSpec{
    int maxRange;	//maximum range in meters
};

struct geneProdCatchSpec{
    int maxRange; //maximum range of product in meters
    int baseProd; //product type of catch based
    float threshold;
    int crc; //crc32 of the catch area configuration
};

struct geneProdUamSpec{
    int maxRange; //maximum range of product in meters
    int baseProd1; //product type of UAM based
    int dataType1;
    int baseProd2; //product type of UAM based
    int dataType2;
    int baseProd3; //product type of UAM based
    int dataType3;
    float area; //area threshold of warning
    int forecast; //forecasting time in minutes
    int operation; //logical operation for base products
};
struct geneUAMZone
{
    int range; //range of center in meters
    float azimuth; //azimuth in degree of center
    int a; // horizontal position(deg ==0 ), half long axis of ellipse in meters
    int b; // horizontal position(deg ==0 ), half short axis of ellipse in meters
    int deg; //degree of ellipse in degree
    float max1; //maximum value of data
    float max2; //maximum value of data
    float max3; //maximum value of data
    float area; //area in square km
};
struct geneAzRange
{
    int range; //range in meters
    float azimuth; //azimuth in degrees
};

struct geneProdCtrSpec{
    int maxRange;	//maximum range in meters
    int baseProd; //type of product based
    int levels; //levels of contour lines
    float begin; //start value of contour
    float interval; //interval of levels
};

struct geneProdStiHeader
{
    /* number of storms */
    int nStorms;

    /* number of total continuous storms */
    int nConStorms;

    /* Number of storm components, in COMPSTAK */
    int nCompStk;

    /* average speed, in m/s */
    float avgSpeed;

    /* average direction, in degree */
    float avgDir;
};
struct geneStormMotion{
    /* azimuth of cell, in degrees */
    float azimuth;
    /* range of cell from radar, in meters */
    int  range;
    /* speed of storm, in m/s */
    float speed;
    /* direction of storm, in degree */
    float dir;
    /* forcast error, in meters, current position - last position*last forcast speed */
    int ferr;
    /* mean forcast error, in meters, mean error for specified storm id. */
    int mfe;
};
typedef vector<geneStormMotion> geneStormMotionSeq;
struct geneStormPos{
    /* azimuth of cell, in degrees */
    float azimuth;
    /* range of cell from radar, in meters */
    int  range;
    /* time of position, seconds from midnight of 1970/01/01 */
    int time;
};
typedef vector<geneStormPos> geneStormPosSeq;
struct geneStormAttr{
    /* storm id, 1~260, code defined in CHARIDTABLE */
    int id;
    /* storm type(0=continuous, 1=new, 2=change(N/A)) */
    int type;
    /* number of contimuous volume scans */
    int nVols;
    /* azimuth of storm cell in degrees */
    float azimuth;
    /* range of storm cell in meters */
    int range;
    /* height of storm, in meters */
    int height;
    /* maximum reflectivity, in dbz */
    float maxz;
    /* height of maximum reflectivity, in meters */
    int heightMaxz;
    /* vil */
    float vil;
    /* number of components, in COMPSTAK */
    int ncomp;
    /* first(index) components for the storm, in COMPSTAK */
    int idxcomp;
    /* top of storm, in meters */
    int top;
    /* index of top component, in COMPSTAK */
    int idxtop;
    /* base of storm, in meters */
    int base;
    /* index of base coponent, in COMPSTAK */
    int idxbase;
};
typedef vector<geneStormAttr> geneStormAttrSeq;
struct geneStormComp{
    /* height, in meters */
    int height;
    /* maximum reflectivity, in dbz */
    float maxz;
    /* pointer(index) to next comonent */
    int idxnext;
};
typedef vector<geneStormComp> geneStormCompSeq;
struct geneStormTrackAdapt{
    int DEFDIREC;
    float DEFSPEED;
    int MAXVTIME;
    int NPASTVOL;
    float CORSPEED;
    float SPEEDMIN;
    int ALLOWERR;
    int FRCINTVL;
    int NUMFRCST;
    int ERRINTVL;
};

struct geneProdUserSpec{
    int algorithm; //algorithm used 1~5
    char desc[3][16];
};


/* BEAM Radial data */
struct geneBeamDataHeader{
    float azimuth;
    float elevation;
    int binNum;
    int spared[5];
};

/* HCL  */
struct geneProdHclSpec{
    float elevation;
};

/* IGST  */
struct geneProdIgstSpec{
    int reso;
    int maxRange;
};

/* COMP product */
struct geneProdCompSpec{
    int baseProd; //product type based
    int dataType; //data type of based product
    char mainSite[SITE_CODE_LENGTH]; // product name based
    int interval; //intervals of products generating in seconds
    int overlap; //algorithm for overlapped area
    int alg; //reserved for further use
};

struct geneCompSite
{
    char code[SITE_CODE_LENGTH];//code of Radar
    int  range; //range of site  in meter
    float azimuth; //azimuth of site in degree
    int height;//radar height above sea level

    int volStartTime; //start time of volume scan
    int reso; //resolution of site data in meters
    int maxRange; //max range of site data in meters, Radius
};

/* NGRID product */
struct geneProdNGridSpec{
    int dataType; //data type of based product
    int layerNum; //layer number of cappi divided
    int bottom; //grid height low start in meters
    int top; //grid height high end in meters     
        
    char mainSite[SITE_CODE_LENGTH]; // product name based
    int interval; //intervals of products generating in seconds
    int overlap; //algorithm for overlapped area
    int alg; //reserved for further use
};

struct geneProdCmSpec{
    float elevation;
};

struct geneProdWindSpec
{
    int maxRange;  //maximum range in meters
    int isCappi; //it is a cappi request
    int height; //cappi height in meters
    float el; //elevation of ppi
};

struct geneProdWindTSpec
{
    float el; //elevation of windt
};

struct geneProdMLSpec {
    float elevation;
    int maxRange;	//maximum range in meters
};
struct geneProdMLUnit
{
    float az; //azimuth of point
    int bot; // bottom above msl in meters
    int top; // top above msl in meters
    int TE;  // melting layser top edge in meters
    int TC; // melting layser top center in meters
    int BC; // melting layser bottom edge in meters
    int BE; // melting layser bottom center in meters
};

union geneProdSpec{
    geneProdPpiSpec ppi;
    geneProdCappiSpec cappi;
    geneProdRhiSpec rhi;
    geneProdMaxSpec max;
    geneProdHsrSpec hsr;
    geneProdSriSpec sri;
    geneProdQpeSpec qpe;
    geneProdQpetSpec qpet;
    geneProdVadSpec vad;
    geneProdWerSpec wer;
    geneProdVcsSpec vcs;
    geneProdVwpSpec vwp;
    geneProdHvvpSpec hvvp;
    geneProdTopBaseSpec tb;
    geneProdLramSpec lram;
    geneProdSwaSpec swa;
    geneProdSrrSpec srr;
    geneProdHmaxSpec hmax;
    geneProdSrmSpec srm;
    geneProdVilSpec vil;
    geneProdStpSpec stp;
    geneProdOhpSpec ohp;
    geneProdThpSpec thp;
    geneProdSpdSpec spd;
    geneProdCsSpec cs;
    geneProdUspSpec usp;
    geneProdSymbolSpec smb;
    geneProdUamSpec uam;
    geneProdCatchSpec cat;
    geneProdCtrSpec ctr;
    geneProdRawSpec raw;
    geneProdUserSpec user;
    geneProdHclSpec hcl;
    geneProdIgstSpec igst;
    geneProdCompSpec comp;
    geneProdNGridSpec ngrid;
    geneProdCmSpec cm;    
    geneProdWindSpec wind;
    geneProdWindTSpec windt;
    geneProdMLSpec ml;
    geneProdSLINESpec sline;
    geneProdNDOPSpec ndop;


    int spared[KEY_OPTION_SIZE];
};
struct geneProdVadHeader{
    float elevation;
    int height;//height of vad in meters
    int slant;//slant range in meters;
    int fitValid;
    float p0;
    float p1;
    float p2;
    float dir;//wind direction
    float speed;//wind speed;
    float rms;
    float nyquist; //m/s
    int pointNum; //number of data points
    int spared[4];
};
struct geneProdVadData{
    float az;
    float vel;
    float ref;
};
typedef vector<geneProdVadData> geneProdVadDataSeq;
struct geneProdVwpData {
    int volStartTime;
    int height;
    int fitValid;
    float dir;
    float speed;
    float rms;
    int spared[2];
};
typedef vector<geneProdVwpData> geneProdVwpDataSeq;
struct geneHITable{
    /* Cell storm Id, 1~260 */
    int id;
    /* azimuth, in deg */
    float azimuth;
    /* range, in meters */
    int range;
    /* posibility of hail  */
    int poh;
    /* posibility of sever hail */
    int posh;
    /* maximum expected hail size, in cm */
    float size;
    /* RCM code of hail */
    int type;
};
struct geneHIAdapt{
    float HT0MSL;
    float HT20MSL;
    float HKECOF1;
    float HKECOF2;
    float HKECOF3;
    float POSHCOF;
    int POSHOFS;
    float HSCOF;
    float HSEXP;
    int LLHKEREF;
    int ULHKEREF;
    int RCMPRBL;
    float WTCOF;
    int MXHLRNG;
    float POHHDTH1;
    float POHHDTH2;
    float POHHDTH3;
    float POHHDTH4;
    float POHHDTH5;
    float POHHDTH6;
    float POHHDTH7;
    float POHHDTH8;
    float POHHDTH9;
    float POHHDTH10;
    int MRPOHTH;
    int RCMPSTV;
    float WTOFS;
};
//TVS Product
struct geneTVSHeader{
    /* number of tvs feature */
    int nTvsFeat;

    /* number of etvs feature */
    int nEtvsFeat;
};
/* tvs feature table */
struct geneTVSTable{
    /* storm id */
    int id;
    /* tvs feature type, 1=TVS, 2=ETVS */
    int type;
    /* azimuth of feature base, in deg */
    float azimuth;
    /* slant range of feature base, in meters */
    int range;
    /* elevation angle */
    float elevation;
    /* low-level delta velocity, in m/s */
    float lldvel;
    /* average delta velocity, in m/s */
    float avgdvel;
    /* maximum delta velocity, in m/s */
    float maxdvel;
    /* height of maximum delta velocity, in meters */
    int hgtdvel;
    /* depth of feature, negative value means
        top is on highest elevation(or base is loweast), in meters */
    int depth;
    /* base height, in meters */
    int base;
    /* top height, in meters */
    int top;
    /* maximum shear, in m/s/km */
    float maxshear;
    /* height of maximum shear, in meters */
    int hgtshear;
};
struct geneTVSAdapt{
    int MINREFL;
    int MINPVDV;
    int MAXPVRNG;
    float MAXPVHT;
    int MAXNUMPV;
    int TH2DDV1;
    int TH2DDV2;
    int TH2DDV3;
    int TH2DDV4;
    int TH2DDV5;
    int TH2DDV6;
    int MIN1DP2D;
    float MAXPVRD;
    float MAXPVAD;
    float MAX2DAR;
    float THCR1;
    float THCR2;
    int THCRR;
    int MAXNUM2D;
    int MIN2DP3D;
    float MINTVSD;
    int MINLLDV;
    int MINMTDV;
    int MAXNUM3D;
    int MAXNUMTV;
    int MAXNUMET;
    float MINTVSBH;
    float MINTVSBE;
    float MINADVHT;
    float MAXTSTMD;
};
/* M product */
struct geneMesoHeader{
    /* number of storms */
    int nStorms;

    /* number of mesocylones */
    int nMesos;

    /* number of features */
    int nFeats;
};
/* meso table */
struct geneMesoTable
{  
    /* feature id */
    int fid;
    /* storm id */
    int sid;
    /* meso azimuth position */
    float azimuth;
    /* meso radial position int meters */
    int range;
    /* meso elevation angle */
    float elevation;
    /* meso highest average shear */
    float avgshear;
    /* meso height in meters */
    int height;
    /* meso azimuthal diameter, in meters */
    int azdm;
    /* meso radial diameter, in meters */
    int radm;
    /* meso average rotational speed */
    float aspd;
    /* meso maximum rotational speed */
    float mspd;
    /* meso top height in meters */
    int top;
    /* meso base height in meters */
    int base;
    /* meso base azimuth angle */
    float baz;
    /* meso base range, in meters */
    int brange;
    /* meso base elevation angle */
    float bel;
    /* meso maximum tangential shear */
    float maxshear;
};
/* feature table */
struct geneFeatureTable{
    /* feature id */
    int fid;
    /* storm id */
    int sid;
    /* feature type, 1=meso, 2=3D correlated shear, 3=uncorrelated shear */
    int type;
    /* feature azimuth angle */
    float azimuth;
    /* feature slant range, in meters */
    int range;
    /* feature elevation angle */
    float elevation;
    /* feature height in meters */
    int height;
    /* feature azimuthal diameter in meters */
    int azdm;
    /* feature range diameter in meters */
    int radm;
    /* feature average shear */
    float avgshear;
    /* feature maximum shear */
    float maxshear;
    /* feature average rotational speed */
    float avgspd;
    /* feature maximum rotational speed */
    float maxspd;
    /* feature top in meters */
    int top;
    /* feature base in meters */
    int base;
    /* feature base az */
    float baz;
    /* feature base range in meters */
    int brange;
    /* feature base elevation */
    float bel;
};
struct geneMesoAdapt{
    int NPVTHR;
    float FHTHR;
    float HMTHR;
    float LMTHR;
    float HSTHR;
    float LSTHR;
    float MRTHR;
    float FMRTHR;
    float NRTHR;
    float FNRTHR;
    float RNGTHR;
    float DISTHR;
    float AZTHR;
};
/* storm structure header */
struct geneSSHeader{
    /* number of storms */
    int nStorms;
};
/* storm structure table */
struct geneSSTable{
    /* storm id */
    int id;
    /* azimuth of storm, in degree */
    float azimuth;
    /* range of storm, in meters */
    int range;
    /* base of storm, in meters */
    int base;
    /* top of storm, in meters */
    int top;
    /* vil */
    float vil;
    /* maximum reflectivity, in dbz */
    float maxz;
    /* height of maximum reflectivity, in meters */
    int hgtMaxz;
};
struct geneCellTrend{
    /* volume start time in seconds */
    int time;
    /* cell height in meters */
    int height;
    /* cell base in meters */
    int base;
    /* cell top in meters */
    int top;
    /* cell vil */
    int vil;
    /* cell maximum reflectivity */
    int maxz;
    /* cell height of maximum reflectivity, in meters */
    int hgtMaxz;
    /* cell posibility of hail */
    int poh;
    /* cell posibility of sever hail */
    int posh;
};
struct geneStormSegAdapt{
    int REFLECTH1;
    int REFLECTH2;
    int REFLECTH3;
    int REFLECTH4;
    int REFLECTH5;
    int REFLECTH6;
    int REFLECTH7;
    int NREFLEVL;
    int NUMAVGBN;
    int SEGRNGMX;
    float MCOEFCTR;
    float MULTFCTR;
    float MWGTFCTR;
    float SEGLENTH1;
    float SEGLENTH2;
    float SEGLENTH3;
    float SEGLENTH4;
    float SEGLENTH5;
    float SEGLENTH6;
    float SEGLENTH7;
    int DRREFDFF;
    int NDROPBIN;
    int NUMSEGMX;
    int RADSEGMX;
};
struct geneStormCentAdapt{
    float CMPARETH1;
    float CMPARETH2;
    float CMPARETH3;
    float CMPARETH4;
    float CMPARETH5;
    float CMPARETH6;
    float CMPARETH7;
    float RADIUSTH1;
    float RADIUSTH2;
    float RADIUSTH3;
    int STMVILMX;
    int MXDETSTM;
    int OVLAPADJ;
    float AZMDLTHR;
    float DEPTHDEL;
    float HORIZDEL;
    float ELVMERGE;
    float HGTMERGE;
    float HRZMERGE;
    int NBRSEGMN;
    int NUMCMPMX;
    int MXPOTCMP;
    int NUMSTMMX;
};

struct geneSWPNode{
    /* range of swp in meters */
    int range;
    /* azimuth of swp in degree */
    float azimuth;
    /* swp value */
    int swp;
};

/* Radar/Gage pair for SPD product */
struct geneRadarGagePair
{
    char code[SITE_CODE_LENGTH]; //code of gage
    char name[SITE_NAME_LENGTH]; //name of gage
    float azimuth; //azimuth of gage in degree
    int range; //distance of gage in meters
    float gageData; //gage rain in mm
    float prodData; //radar rain in mm
    int used; //pair of data used or not
};

/* Gage site and data for GAGE product */
struct geneGageSite
{
    char code[SITE_CODE_LENGTH]; //code of gage
    char name[SITE_NAME_LENGTH]; //name of gage
    int type; //1=rain gage, 2=disdrometer
    float azimuth; //azimuth of gage in degree
    int range; //distance of gage in meters
};

struct geneGageData
{
    int timeSpan; //time span of rain accumulation in seconds
    int timeEnd; //end time of accumulation
    float rain; //rain accumulation in mm
    float a; //ZR relation const
    float b; //ZR relation exponent
};

/* position for COUTOUR product */
struct geneLineSeg
{
    int x1; //start x
    int y1; //start y
    int x2; //end x
    int y2; //end y
};

/* WIND product */
struct geneProdWindHeader
{
    int rowReso;
    int colReso;
    int rowSideLength;
    int colSideLength;
    float windSpeedMax;
    float windSpeedMin;
    geneUniDataType dataTypeSpeed;
    geneUniDataType dataTypeDirection;
};

struct geneWindCode
{
    short speed;
    short direction;
};

/* Microburst Product */
struct geneMBTable
{
    float az;			// degree
    int range;      	// meter
    int radius;			// meter
    float strength;		// m/s
};

/*** definition of SWIS product by TJU ***/
//median-altitude radial convergence
struct geneMARC
{
    int minHeight; // unit: m
    int maxHeight; // unit: m
    float maxEl;     // the El of max MARC
    float az;        // unit
    int range;     // unit: m
    float marc;      // unit: m/s
    int radius;    // unit: m
    float maxShear;
};

//
struct geneDCZ
{
    float maxVelDiff;   //unit: m/s
    int maxLength;         //unit: m
    int thick;          //unit: m
};

//Da Wind Area
struct geneDWA
{
    float az;		//degree
    int range;      // unit:m
    float area;  		//km**2
    float maxVelDiff;
    int thick;  //unit m
    float tlAz;   // top-left azimuith
    int tlRange;  // top-left range
    float brAz;   // bottom-right azimuith
    int brRange; // bottom-right range
};

//low level jet
struct geneLLJ
{
    float avgVel; //m/s
    float posVelAz; //degree
    float negVelAz; //degree
};

//severe wind area
struct geneSWA
{
    float maxVel;  //m/s
    float tlAz;    // top left azimuth
    int tlRange; // top left range, unit:m
    float brAz;    // bottom right azimuth
    int brRange; // bottom right range, unit:m
};

#pragma pack(pop)
#endif
