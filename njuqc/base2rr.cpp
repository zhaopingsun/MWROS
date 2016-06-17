#include <stdio.h>
#include <string.h>
#include "generic_basedata_cv.h"
#include "generic_product_cv.h"
#include "radar_dt.h"
#include "prodtype.h"
#include "proj_type.h"
#include "geneCodeData.h"
#include <time.h>
#include <math.h>
#include <unistd.h>

/**
  compute rain rate product from basedata demo
 * */
const char* OP_IF="--if";
const char* OP_OF="--of";
void help()
{
	printf("useage  base2rr --if Z9200.20160311.000812.AR2 --of rr.prod\n");
	printf("PUP can display the rr.prod\n");
	_exit(-1);

}

int basedata2rr(basedataImage &gdi, struct PPIProdImage & pdi,int reso,int range,char *prodName)
{
	 int proddt=RDT_RR;
	 int rr_scale,rr_offset;
	getFormulaByte1(proddt,rr_scale,rr_offset);
#define CP_MEM(a) pdi.a=gdi.a
	CP_MEM(uniHeader);
	pdi.uniHeader.majorVer=MAJOR_VER;
	pdi.uniHeader.minorVer=MINOR_VER;
	pdi.uniHeader.msgType=GDT_PRODUCT;
	CP_MEM(siteInfo);
	CP_MEM(taskConf);
	CP_MEM(cuts);
	//make pch
	geneProdCommHeader pch;
	strcpy(pch.prodName,prodName);
	pch.prodType=pdi.uniHeader.prodType=PT_PPI;
	time_t tim;
	time(&tim);
	pch.prodGenTime=tim;
	pch.volStartTime=gdi.taskConf.startTime;
	pch.dataStartTime=pch.volStartTime;
	int radnum;
	cv_geneRadial lastradial=gdi.radials.back();
	cv_geneRadial firstradial=gdi.radials.front();
	 pch.dataEndTime=lastradial.timeSec;
	 pch.projType =PROJ_NONE;
	
	 pch.momType1=proddt;
	 pdi.header=pch;
   
	
	 geneProdPpiSpec spec;
	 spec.elevation=firstradial.el;
	 pdi.spec.ppi=spec;
	float A=300,B=1.4;
//
	 //search for dbz data
	 const  cv_geneMom *pMom=NULL; //gMom->
	 cvGeneMom::iterator mit;
	 for(mit=firstradial.mom.begin();mit!=firstradial.mom.end();mit++)
	 {
		 if( mit->udt.type==RDT_DBZ)
		 {
			 pMom=&*mit;
		 }
	 }
	 if(pMom==NULL)
	 {
		 printf("can not found dt %d\n",proddt);
		 return -1;
	 }
	 //search cuts
	 cvCutMark cm;
	 searchCuts(gdi,cm);
	 geneRadialProdHeader grph;
	 grph.dataType.binSize=pMom->udt.binSize;
	 grph.dataType.offset=rr_offset ;
	 grph.dataType.scale=rr_scale;
	 grph.dataType.type=RDT_RR;
	 grph.max=grph.min=0;
	 grph.radNum=gdi.radials.size();
	 grph.reso=reso;
	 grph.startRange=gdi.cuts[0].startRange;
	 grph.maxRange=gdi.cuts[0].maxRange;
	 grph.reso=gdi.cuts[0].logReso;
	 grph.radNum=cm.front().radNum;
	// grph.
	// firstradial.
	 //grph.
	// grph.maxRange=firstradial.
	 pdi.radialHeader=grph;
	 

	 //create radials
	 cvRadial::iterator rit;
	 //only first cut is used
	 int max=-1000;
	 for(rit=cm.front().begin;rit!=cm.front().end;rit++)
	 {
	 	for(mit=rit->mom.begin();mit!=rit->mom.end();mit++)
		{
		 	if( mit->udt.type==RDT_DBZ)
			{
				cv_prodRadial prodRad;
				prodRad.data=mit->data;
				for(int i=0;i<mit->data.size();i++)
				{
					short c=mit->data[i];
					if(!isSpecCode(c))
					{
						//covert dbz to RR
						float dbz=decodeData(mit->udt,c);
						float rr=pow(pow(10,dbz/10.0)/A,1/B);
						prodRad.data[i]=codeData(rr_offset,rr_scale,rr);
					}
				}
				prodRad.header.angStart=rit->az;
				prodRad.header.angReso=gdi.cuts[0].angleReso;
				prodRad.header.binNum=mit->data.size();
				pdi.radials.push_back(prodRad);
				//search max 
				for(int i=0;i<mit->data.size();i++)
				{
					int code=prodRad.data[i];
					if(!isSpecCode(code))
					{
						if(code>max)
							max=code;
					}
				}
			}
		}
	 }
	 pdi.radialHeader.max=max;
}
int main(int argc ,char *argv[])
{
	bool gVerbose=false;
	int lineWidth=30;
	bool gBrief=false;
	int dt=-1;
	char const  *fpath=NULL;
	char const *ofpath=NULL;
	for(int i=1;i<argc;i++)
	{
		if(strcmp("--help",argv[i])==0)
		{
			help();
		}
		else if(strcmp(OP_IF,argv[i])==0)
		{
			i++;
			fpath=argv[i];
		}
		else if(strcmp(OP_OF,argv[i])==0)
		{
			i++;
			ofpath=argv[i];
		}
	}
	if(fpath==NULL||ofpath==NULL)
	{
		help();
	}

	basedataImage bdi,qcbdi;
	qcbdi=bdi;
	qcbdi.radials.empty();
	int ret=loadBasedataImage(fpath,bdi);
	cvCutMark cutMarks;
	searchCuts(bdi,cutMarks);
	cvCutMark::iterator cmi;
	int ci=0;
	for(cmi=cutMarks.begin();cmi!=cutMarks.end();cmi++,ci++)
	{
		cvRadial rawRadials(cmi->begin,cmi->end),qcRadials;
	//	cvRadial::iterator rit=cmi->begin;
	//	basedata_cut_qc(bdi.cuts[ci],rawRadials,qcRadials);
		qcbdi.radials.insert(qcbdi.radials.end(),qcRadials.begin(),qcRadials.end());	
	}
//	writeBasedataImage(ofpath,bdi);
	PPIProdImage prod;
	basedata2rr(bdi, prod,250,100,"rr_demo");
	writeProductImage(ofpath,prod);
	
}
