#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Classify.h"
#define PI 3.1415
static unsigned int JudgeClass(double *pTestSampleFeatureRow,unsigned int pCol1,double **pModelParaTable,unsigned int pClassNum, double *pClassProbability)
{
	double pProbabilityAccumulation=0;
	for(unsigned int i=0;i!=pClassNum;++i)
	{
		pProbabilityAccumulation=0;
		for(unsigned int j=0;j!=pCol1;++j)
		{
			pProbabilityAccumulation+=log((1/(sqrt(2*PI)*sqrt(pModelParaTable[j][2*i+1])))*exp(-pow(pTestSampleFeatureRow[j]-pModelParaTable[j][2*i],2)/(2*pModelParaTable[j][2*i+1])));
			//pProbabilityAccumulation*=(1/(sqrt(2*PI)*sqrt(pModelParaTable[j][2*i+1])))*exp(-pow(pTestSampleFeatureRow[j]-pModelParaTable[j][2*i],2)/(2*pModelParaTable[j][2*i+1]));
		}
		pClassProbability[i]=pProbabilityAccumulation;
	}
	
	double pMaxProbability=pClassProbability[0];
	unsigned int pCode=0;
	for(unsigned int k=1;k!=pClassNum;++k)
	{
		//printf("%lf\t",pClassProbability[k]);
		if(pClassProbability[k]>=pMaxProbability)
		{
			pMaxProbability=pClassProbability[k];
			pCode=k;
		}
	}
	//printf("\n");
	
	return pCode;
}

unsigned int *Classify(double **pTestSampleFeatureVec,unsigned int pRow1,unsigned int pCol1,double **pModelParaTable,unsigned int pClassNum)
{
	unsigned int *RetValVec = (unsigned int*)malloc(sizeof(unsigned int)*pRow1);
	memset(RetValVec,0,pRow1);
	double *pClassProbability =(double *)malloc(sizeof(double)*pClassNum);
	unsigned int pClassCode = 0;
	for(unsigned int i=0;i!=pRow1;++i)
	{
		pClassCode = JudgeClass(pTestSampleFeatureVec[i],pCol1,pModelParaTable,pClassNum,pClassProbability);
		RetValVec[i]=pClassCode;
	}
	free(pClassProbability);
	pClassProbability=NULL;
	return RetValVec;
}

static unsigned int ** CreateConfusionMatrix(unsigned int len,unsigned int width)
{
	unsigned int i,m,n;
	unsigned int **arr = (unsigned int  **)malloc(len*sizeof(unsigned int *));

	for(i = 0; i!=len;++i)
		arr[i]=(unsigned int *)malloc(width*sizeof(unsigned int));
	for(m=0; m!=len;++m)
		for( n=0;n!=width;++n)
			arr[m][n]=0;
		return arr;
}


static void DestroyConfusionMaxtrix(unsigned **arr,unsigned int len,unsigned int width)
{

	unsigned int i;
	for(i = 0; i!=len;++i)
	{
		free(arr[i]);
		arr[i]=NULL;
	}		
	free(arr);
	arr=NULL;
}
static void PrintConfusionMatrix(unsigned int **pConfusionMatrix,unsigned int pClassNum)
{
	for(unsigned int i=0;i!=pClassNum;++i)
	{
		for(unsigned int j=0;j!=pClassNum;++j)
		{
			printf("%d\t",pConfusionMatrix[i][j]);
		}
		printf("\n");
	}
}

static double GetAccuracy(unsigned int **pConfusionMatrix,unsigned int pClassNum,unsigned int pTestSampleNum)
{
	unsigned int pTPPlusTN=0;
	for(unsigned int i=0;i!=pClassNum;++i)
	{
		for(unsigned int j=0;j!=pClassNum;++j)
		{
			if(i==j)
				pTPPlusTN+=pConfusionMatrix[i][j];
		}
	}
	return (double)pTPPlusTN/(double)pTestSampleNum;
}
void EvaluateResult(unsigned int *TestSampleClassVec,unsigned int *ResultVec,unsigned int pVecLen,unsigned int pClassNum)
{
	unsigned int ** pConfusionMatrix=CreateConfusionMatrix(pClassNum,pClassNum);
	for(unsigned int i=0;i!=pVecLen;++i)
	{
		++pConfusionMatrix[TestSampleClassVec[i]][ResultVec[i]];
	}
	PrintConfusionMatrix(pConfusionMatrix,pClassNum);
	printf("Classification Accuracy is %lf\n",GetAccuracy(pConfusionMatrix,pClassNum,pVecLen));
	DestroyConfusionMaxtrix(pConfusionMatrix,pClassNum,pClassNum);
}
