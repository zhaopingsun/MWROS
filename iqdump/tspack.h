#ifndef RDA_TASPACK_H
#define RDA_TASPACK_H
void depackIQ_kernel(unsigned short *code, float *iq,size_t count);
void depackIQ(const unsigned short *code, float *iq,size_t count);
#endif
