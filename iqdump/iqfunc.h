#ifndef RDA_IQ_CACULATE_H
#define RDA_IQ_CACULATE_H
#ifndef MAX
#define MAX( a, b ) (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
#define MIN( a, b ) (((a) < (b)) ? (a) : (b))
#endif
int const MAX_RANGE_BIN_NUM=2048;
int const MAX_SWEEP_NUM=256;
float DecodeAnteAngleDeg(short ang);
float Decibel(float temp);
void Decibel(float *power,float *signal,int binnum);
#define Square(f) ((f)*(f))
template <class T> void FFTShift(float *pdata ,T*shift,int len)
{
	for(int i=0;i<len;i++)
	{
		int oldi=(i+len/2)%len;
		shift[i]=(T)pdata[oldi];
	}
}
#endif
