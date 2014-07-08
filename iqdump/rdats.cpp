#include "rdats.h"
#include<vector>
#include <stdio.h>
#include <string.h>
size_t getSweepLength(TSSweepHeader *swphdr)
{
	int chan=swphdr->chan;
	if(chan==0) chan=1;
	
	return sizeof(*swphdr)+chan*swphdr->binnum*2*sizeof(float);
}
TSSweepHeader *getNextSwpHeader(TSSweepHeader *swphdr)
{
	int swplen=getSweepLength(swphdr);
	return (TSSweepHeader*) ((char*)swphdr+swplen);
}
Iqcmpl *getIQData(TSSweepHeader *swphdr)
{
	return (Iqcmpl*)((char*)swphdr+sizeof(TSSweepHeader));
}
vector<char> fileCache;
int scanIQFile(const char*fname,TSHeader *tsh,SweepHeaderList &swplist)
{
	FILE *fp=fopen(fname,"rb");
	if(fp==NULL)
		return 0;
	fseek(fp,0,SEEK_END);
    int fileLength=ftell(fp);
	fileCache.resize(fileLength);
	rewind(fp);
	fread(&fileCache[0],1,fileLength,fp);
/*
	// 创建文件内核对象，其句柄保存于hFile
	HANDLE hFile;
	int error;
	hFile = CreateFile((LPCSTR)fname,GENERIC_READ ,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		error=GetLastError();
	}
	 DWORD dwBytesInBlock,fileLength;
	 dwBytesInBlock= GetFileSize(hFile,&fileLength);  
	 if(INVALID_FILE_SIZE==dwBytesInBlock)
	 {
		error=GetLastError();
	 }
	//映射对象
	HANDLE hFileMapping = CreateFileMapping(hFile,NULL,PAGE_READONLY,0,dwBytesInBlock,NULL);
	
	if (hFileMapping==NULL)
	{
		error=GetLastError();
		return false;
	}
	//这里赋值了一个文件映射的指针，地址从文件头开始
	TCHAR *pbFile = (TCHAR *)MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
*/
	char *pbFile=&fileCache[0];
	TSHeader *IQFileHead=(TSHeader *)pbFile; 
	memcpy(tsh,IQFileHead,sizeof(*tsh));

	TSSweepHeader *SWFileHead =(TSSweepHeader*)(pbFile+sizeof(*IQFileHead)+256);
	TSSweepHeader *nexSWFileHead;
	nexSWFileHead=SWFileHead;

	size_t totalen=fileLength;
	 
	size_t datalen;
	datalen=sizeof(IQFileHead)+256;

	while(datalen<totalen)
	{	
		swplist.push_back(nexSWFileHead);
		size_t swpLEN=getSweepLength(nexSWFileHead);	 
		nexSWFileHead=getNextSwpHeader(nexSWFileHead);
		datalen=datalen+swpLEN;	
	}
	return 1;
}
