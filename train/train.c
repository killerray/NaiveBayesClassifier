#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DealFile.h"
#include "TrainModel.h"
int main(int argc,char **argv)
{
	if(5!=argc)
	{
		printf("\n");
		printf("first parameter is train sample feature file path.\n");
		printf("second parameter is line numbers of train sample feature file.\n");
		printf("third parameter is numbers of feature.\n");
		printf("fourth parameter is model file path.\n");
		printf("\n");
		exit(1);
	}

	unsigned int *TrainSampleClassVec=NULL;				//训练样本对应类别向量
	double **TrainSampleFeatureVec=NULL;				//训练样本特征向量
	double **ParaTable=NULL;							//模型参数表
	unsigned int ClassNum=0;							//训练样本类别个数
	
	//读取训练样本特征文件
	TrainSampleFeatureVec=ReadFile(argv[1],atoi(argv[2]),atoi(argv[3]),&TrainSampleClassVec);
	//PrintFile(TrainSampleFeatureVec,atoi(argv[2]),atoi(argv[3]));
	//获得类别个数
	ClassNum = CountClass(TrainSampleClassVec,atoi(argv[2]));
	
	
	//训练模型，获得参数
	ParaTable=TrainModel(TrainSampleFeatureVec,atoi(argv[2]),atoi(argv[3]),TrainSampleClassVec,ClassNum);
	
	
	//打印模型参数
	PrintModelFile(ParaTable,atoi(argv[3]),ClassNum,argv[4]);
	
	//释放特征文件内存
	FreeFile(TrainSampleFeatureVec,atoi(argv[2]),atoi(argv[3]),TrainSampleClassVec);
	
	//释放模型参数表内存
	FreeTable(ParaTable,atoi(argv[3]),2*ClassNum);
	
	return 0;
}
