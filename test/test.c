#include <stdio.h>
#include <stdlib.h>
#include "DealFile.h"
#include "Classify.h"

int main(int argc,char **argv)
{
	if(8!=argc)
	{
		printf("\nFirst parameter is path of test sample feature file!\n");
		printf("Second parameter is line numbers of test sample feature file!\n");
		printf("Third parameter is feature numbers of test sample feature file!\n");
		printf("Fourth parameter is path of model file!\n");
		printf("Fifth parameter is line numbers of model file!\n");
		printf("Sixth parameter is column numbers of model file sparated by comma!\n");
		printf("Seventh parameter is path of result file!\n\n");
		exit(1);
	}
	double **TestSampleFeatureVec=NULL;			//检测样本特征向量
	double **ModelParaTable=NULL;				//模型参数表
	unsigned int *TestSampleClassVec=NULL;		//检测样本类别向量
	unsigned int *ModelAttributeVec=NULL;		//模型对应属性向量
	unsigned int ClassNum=0;					//类别个数
	unsigned int *ResultVec=NULL;
	TestSampleFeatureVec=ReadFile(argv[1],atoi(argv[2]),atoi(argv[3]),&TestSampleClassVec);
	
	ModelParaTable=LoadModelFile(argv[4],atoi(argv[5])-1,atoi(argv[6])-1,&ClassNum,&ModelAttributeVec);
	
	ResultVec=Classify(TestSampleFeatureVec,atoi(argv[2]),atoi(argv[3]),ModelParaTable,ClassNum);
	
	EvaluateResult(TestSampleClassVec,ResultVec,atoi(argv[2]),ClassNum);
	
	FreeFile(TestSampleFeatureVec,atoi(argv[2]),atoi(argv[3]),TestSampleClassVec);
	
	FreeFile(ModelParaTable,atoi(argv[5])-1,atoi(argv[6])-1,ModelAttributeVec);
	
	free(ResultVec);
	
	ResultVec=NULL;
	return 0;
}