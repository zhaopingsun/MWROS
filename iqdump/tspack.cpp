#include <stdlib.h>
int const LOOK_UP_TABLE_SIZE=65536;
float  gLookupTable[LOOK_UP_TABLE_SIZE];
int gTabledInited=false;
void depackIQ_kernel(unsigned short *code, float *iq,size_t count)
{
	for(int i=0;i<count;i++)
	{
		unsigned short c=code[i];
		float val=0;
		if(c&0xf000)
		{
			int man=c&0x7ff;
			int exp=(c>>12)&0x00f;
			if(c&0x0800)
				man |= 0xFFFFF000 ;
			else
				man |= 0x00000800 ;
			val=((float)man)*((float)(unsigned int)(1<<exp))/3.3554432E7;
		}
		else
			val=((float)(((int)c)<<20))/1.759218603E13;
		iq[i]=val;
	}
}
void buildLookupTable()
{
	if(gTabledInited)
		return;
	unsigned short code=0;
	float val;
	for(;;)
	{
		depackIQ_kernel(&code,&val,1);
		gLookupTable[code]=val;
//		printf("0x%x %d -> %e\n",code,code,val);
		if(0==++code) break;
	}
	gTabledInited=true;
}
void depackIQ(const unsigned short *code, float *iq,size_t count)
{
	//we use lookup table to speed up
	buildLookupTable();
//	#pragma omp parallel for
	for(int i=0;i <count;i++)
	{
		iq[i]=gLookupTable[code[i]];	
	}
}
