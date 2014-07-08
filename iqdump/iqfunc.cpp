#include "iqfunc.h"
#include <math.h>
float Decibel(float temp)
{
	float ret;
	if( temp > 0)
	{
		ret = (float)(10.0) *log10f(temp);
	}
	else
	{
		ret= (float)(-128.0);
	}

	return ret;
}
void Decibel(float *power,float *signal,int binnum)
{
	for(int i=0;i<binnum;i++)
	{
		signal[i]=Decibel(power[i]);
	}
}
