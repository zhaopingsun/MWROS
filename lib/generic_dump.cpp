// **********************************************************************
//
// Copyright (c) 1996-2014 Beijing Metstar Radar, Inc. All rights reserved.
//
// This copy of the source code is licensed to you under the terms described in the
// METSTAR_LICENSE file included in this distribution.
//
// **********************************************************************
#include "generic_dump.h"
#include <string.h>
void dumpHeader( geneHeader &hdr)
{
	char mg[32]={0};
	memcpy(mg,&hdr.magic,sizeof(hdr.magic));
	printf("magic %s ,major ver %d ,minor ver %d,type %d\n",
			mg,hdr.majorVer,hdr.minorVer,
			hdr.msgType);
}
void dumpSite(geneSiteConfig &si)
{

	printf("code %s name %s\n",si.code,si.name);
	printf("lat %.4fDeg lon %.4fDeg hgt %dM,ground %dM\n",si.lat,si.lon,si.height,si.ground);
	printf("freq %.2fMHz beamwidth Horic %.2fDeg,Vert %.2fDeg \n",si.freq,si.beamwidth,si.beamwidthVert);
}
void 	dumpTask(geneTaskConfig &task)
{
	printf("name %s\n",task.name);
	printf("task desp %s\n",task.desp);

	printf("pol %d(%s),pulsewidth %d,scantype %d(%s)\n",task.pol,PolDesp(task.pol),task.pulseWidth,task.scanType,ScanTypeDesp(task.scanType));
	printf("start time %d, cut number %d\n",task.startTime,task.cutNum);

	printf("Hori noise %.2f Vert noise %.2f\n", task.horNoise,task.verNoise);
	printf("Hori syscal %.2f Vert syscal %.2f\n", task.horCalib,task.horCalib);
	printf("Hori Noise Temp %.2f Vert Noise Temp %.2f\n", task.horNoiseTemp,task.verNoiseTemp);
	printf("zdr offset %.2f dB phidp offset %.2fDeg\n", task.zdrCal,task.phaseCal);


}
void	dumpCuts(cvCutConfig &cuts)
{
	for(int i=0;i<cuts.size();i++)
	{
		printf("---------------------------cut %d-------------------------\n",i+1);
		int pm=cuts[i].processMode;
		int wf=cuts[i].waveForm;
		int uf=cuts[i].unfoldMode;

		printf("pm %d(%s) wf %d(%s) prf %.0f hz prf2 %.0f hz,unfold mode %d(%s)\n",
				pm,ProcessModeDesp(pm),wf,WaveformDesp(wf),
				cuts[i].prf,cuts[i].prf2,uf,unfoldModeDesp(uf));
		printf("el %.2fdeg angle reso %.2fdeg log reso %dm dop reso %dm\n",
				cuts[i].el,cuts[i].angleReso,
				cuts[i].logReso,cuts[i].dopReso);
		printf("scan speed %.2fdeg/s, max range %dm ,max range2 %dm, start range %dm\n",
				cuts[i].scanSpeed,cuts[i].maxRange,cuts[i].maxRange2,
				cuts[i].startRange);
		printf("start angle %.2fdeg,stop angle %.2fdeg\n",cuts[i].startAngle,cuts[i].endAngle);
		printf("sample %d samples2 %d nyq %.2fm/s atmos %f \n",
				cuts[i].samples,cuts[i].samples,cuts[i].nyquist,cuts[i].atmos);
		int gcf=cuts[i].gcFilter;
		int gcc=cuts[i].gcCf;
		int gcwin=cuts[i].gcWin;
		printf("GC Filter %d(%s), GC Classifier %d(%s),gc Win %d(%s)\n",gcf,GCFilterDesp(gcf),gcc,GCCDesp(gcc),
			gcwin,GCWinDesp(gcwin)	);
	        printf("GC NotchWidth %d,GC minWidth %d,GC Edges %d\n",cuts[i].gcNw,cuts[i].gcfMinWidth,
				cuts[i].gcfEdgePoints);
		char desp[256]={0};
		formatMomMask(cuts[i].momMask,cuts[i].momSizeMask,desp);
		printf("Mom Data:  %s\n",desp);
#define DUMP_QC_MASK(a) \
		if(cuts[i].qcMask.a!=0) \
		{memset(desp,0,sizeof(desp));formatQcMask(cuts[i].qcMask.a,desp);printf("%s %s\n",#a,desp); }
		DUMP_QC_MASK(dbt);
		DUMP_QC_MASK(dbz);
		DUMP_QC_MASK(vel);
		DUMP_QC_MASK(wid);
		DUMP_QC_MASK(dpvar);
		printf("QC Thresh: LOG %.1f SQI %.1f SIG %.1f CSR %.1f DPLOG %.1f \n",cuts[i].qcThresh.log,cuts[i].qcThresh.sqi,cuts[i].qcThresh.sig,cuts[i].qcThresh.csr, cuts[i].qcThresh.dplog);
	

	}

}
void dumpCommHeader(struct commonImage *img)
{
	if(img==NULL)
		return;
	dumpHeader(img->uniHeader);
	dumpSite(img->siteInfo);
	dumpTask(img->taskConf);
	dumpCuts(img->cuts);
}
