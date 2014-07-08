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
float DecodeAnteAngleDeg(char ver,unsigned short ang)
{
	if(ver<3)
	{
		return ang*360.0/8192.0; //2**13
	}
	else
	{
		return ang/100.0;
	}
}
