#ifndef NJU_METSTAR_QC_H
#define NJU_METSTAR_QC_H
#include "generic_basedata_cv.h"
#define QC_OK 0
//quaulity control for one cut data
//return QC_OK for succeed,otherwise define error code 
int basedata_cut_qc(const  geneCutConfig &cut_config,const cvRadial &rawRadials,cvRadial &qcRadials);
//select proper data from volume scan data and create rain rate from it as a PPI product
//beam blockage should be processed ,HSR or similar strategy should be used
//we just create RR from elevation 1.5 fro demo
int basedata2rr(const basedataImage &bdi, struct PPIProdImage & pdi);
#endif
