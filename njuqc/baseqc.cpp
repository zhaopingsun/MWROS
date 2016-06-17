#include <stdio.h>
#include <string.h>
#include "generic_basedata_cv.h"
/*
 * basedata quality control demo program
 * */

const char* OP_IF="--if";
const char* OP_OF="--of";
int basedata_cut_qc(const  geneCutConfig &cut_config,const cvRadial &rawRadials,cvRadial &qcRadials)
{
	qcRadials=rawRadials;
}
void help()
{
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
		basedata_cut_qc(bdi.cuts[ci],rawRadials,qcRadials);
		qcbdi.radials.insert(qcbdi.radials.end(),qcRadials.begin(),qcRadials.end());	
	}
	writeBasedataImage(ofpath,bdi);
	
}
