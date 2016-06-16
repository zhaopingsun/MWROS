#ifndef NJU_METSTAR_QC_H
#define NJU_METSTAR_QC_H
#include "generic_basedata_cv.h"
#define QC_OK 0
//quaulity control for one cut data
//return QC_OK for succeed,otherwise define error code 
int basedata_cut_qc(const  geneCutConfig &cut_config,const cvRadial &rawRadials,cvRadial &qcRadials);
#endif
