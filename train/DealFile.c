#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Array2D.h"
#include "DealFile.h"

/**
函数名称：ReadFile
函数功能：读取以逗号分隔的文件，一般是训练样本特征文件或是检测样本特征文件
**/
double **ReadFile(const char *pFileName,unsigned int pRow,unsigned int pCol,unsigned int **pClassVec)
{
	FILE *fp;
	if((fp=fopen(pFileName,"r"))==NULL)
	{
		printf("Can not open train sample file!\n");
		exit(1);
	}
	double **pFeatureVec=NULL;
	create_2D_array(&pFeatureVec,pRow,pCol);
	*pClassVec =(unsigned int *)malloc(pRow*sizeof(unsigned int));
	memset(*pClassVec,0,pRow);
	for(unsigned int i=0;i!=pRow;++i)
	{
		for(unsigned int j=0;j!=pCol;++j)
		{
			fscanf(fp,"%lf,",(*(pFeatureVec+i)+j));
			//printf("%lf,",*(*(pFeatureVec+i)+j));
		}
		fscanf(fp,"%d\n",*pClassVec+i);	
		//printf("%d\n",*(*pClassVec+i));
	}
	fclose(fp);
	return pFeatureVec;
}

/**
函数名称：LoadModelFile
函数功能：加载模型文件
**/
double **LoadModelFile(const char *pFileName,unsigned int pRow,unsigned int pCol,unsigned int *pClassNum,unsigned int **pClassVec)
{
	FILE *fp;
	if((fp=fopen(pFileName,"r"))==NULL)
	{
		printf("Can not open train sample file!\n");
		exit(1);
	}
	double **pFeatureVec=NULL;
	create_2D_array(&pFeatureVec,pRow,pCol);
	*pClassVec =(unsigned int *)malloc(pRow*sizeof(unsigned int));
	memset(*pClassVec,0,pRow);
	
	fscanf(fp,"%d\n",pClassNum);
	for(unsigned int i=0;i!=pRow;++i)
	{
		for(unsigned int j=0;j!=pCol;++j)
		{
			fscanf(fp,"%lf,",(*(pFeatureVec+i)+j));
		}
		fscanf(fp,"%d\n",*pClassVec+i);	
	}
	fclose(fp);
	return pFeatureVec;
}
/**
函数名称：FreeFile
函数功能：释放文件所占内存
**/
void FreeFile(double **pFeatureVec,unsigned int pRow,unsigned int pCol,unsigned int *pClassVec)
{
	destroy_2D_array(pFeatureVec,pRow,pCol);
	free(pClassVec);
	pClassVec=NULL;
}

/**
函数名称：PrintModelFile
函数功能：打印模型参数文件
**/
void PrintModelFile(double **pFeatureVec,unsigned int pRow,unsigned int pCol,const char *pFileName)
{
	FILE *pfp;
	if((pfp=fopen(pFileName,"a"))==NULL)
	{
		printf("model file open wrong!\n");
		exit(1);
	}
	fprintf(pfp,"%d\n",pCol);
	for(unsigned int i=0;i!=pRow;++i)
	{
		for(unsigned int j=0;j!=2*pCol;++j)
		{
			fprintf(pfp,"%lf,",pFeatureVec[i][j]);
		}
		fprintf(pfp,"%d\n",i);	
	}
	fclose(pfp);
}

/**
函数名称：PrintFile
函数功能：打印文件
**/
void PrintFile(double **pFeatureVec,unsigned int pRow,unsigned int pCol)
{
	for(unsigned int i=0;i!=pRow;++i)
	{
		for(unsigned int j=0;j!=2*pCol;++j)
		{
			printf("%lf,",pFeatureVec[i][j]);
		}
		printf("\n");	
	}
}
