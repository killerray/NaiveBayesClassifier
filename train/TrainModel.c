#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Array2D.h"
#include "TrainModel.h"
#include "gauss.h"

#define PARA_NUM 2
/**
函数名称：CountClass
函数功能：统计类别个数
**/
unsigned int CountClass(unsigned int *pClassVec,unsigned int pClassVecLen)
{
	int pVec[100];
	memset(pVec,-1,sizeof(pVec));
	
	for(unsigned int i=0;i!=pClassVecLen;++i)
	{
		pVec[pClassVec[i]]=pClassVec[i];
	}
	int RetVal=0;
	for(unsigned int j=0;j!=sizeof(pVec)/sizeof(int);++j)
	{
		if(-1!=pVec[j])
			++RetVal;
		else
			return RetVal;
	}
	return RetVal;
}

/**
函数名称：CalculateAveVar
函数功能：计算平均数和方差
**/
static void CalculateAveVar(double **pFeatureVec,double ** pParaTable,unsigned int *pClassVec,unsigned int pRow,unsigned int i,unsigned int j)
{
	int pTempCount=0;
	double pTempAve=0;
	double pTempVar=0;
	for(unsigned int k=0;k!=pRow;++k)
	{
		if(pClassVec[k]==j)
		{
			++pTempCount;
			pTempAve+=pFeatureVec[k][i];
		}
	}
	if(pTempCount)
	{
		pTempAve/=pTempCount;
	}
	else
	{
		pTempAve=0;
	}
	pParaTable[i][PARA_NUM*j]=pTempAve;

	if(pTempCount)
	{
		for(unsigned int k=0;k!=pRow;++k)
		{
			if(pClassVec[k]==j)
			{
				pTempVar+=(pFeatureVec[k][i]-pTempAve)*(pFeatureVec[k][i]-pTempAve);
			}
		}
		pParaTable[i][PARA_NUM*j+1]=pTempVar/(double)(pTempCount-1);
	}
	else
	{
		pParaTable[i][PARA_NUM*j+1]=0;
	}	
}

/**
函数名称：AddGaussianWhiteNoise
函数功能：为数据增加高斯白噪声
**/
static void AddGaussianWhiteNoise(double **pFeatureVec,unsigned int i,unsigned int pRow)
{
	for(unsigned int m=0;m!=pRow;++m)
	{
		pFeatureVec[m][i]+=rand_gauss();
	}
}

/**
函数名称：TrainModel
函数功能：求取模型参数；每个属性，分别为每个类别，估计条件概率。
**/
double ** TrainModel(double **pFeatureVec,unsigned int pRow,unsigned int pCol,unsigned int *pClassVec,unsigned int ClassNum)
{
	double **pParaTable=NULL;
	create_2D_array(&pParaTable,pCol,PARA_NUM*ClassNum);
	
	for(unsigned int i=0;i!=pCol;++i)
	{
		for(unsigned int j=0;j<ClassNum;++j)
		{
			CalculateAveVar(pFeatureVec,pParaTable,pClassVec,pRow,i,j);
		}
		for(unsigned int m=0;m!=ClassNum;++m)
		{
			if(0==pParaTable[i][PARA_NUM*m+1])
			{
				AddGaussianWhiteNoise(pFeatureVec,i,pRow);
				for(unsigned int j=0;j<ClassNum;++j)
				{
					CalculateAveVar(pFeatureVec,pParaTable,pClassVec,pRow,i,j);
				}
				break;
			}
		}
	}
	return pParaTable;
}

/**
函数名称：FreeTable
函数功能：释放模型参数表内存
**/
void FreeTable(double **pParaTable,unsigned int pRow,unsigned int pCol)
{
	destroy_2D_array(pParaTable,pRow,pCol);
}
