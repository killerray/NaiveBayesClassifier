#ifndef _CLASSIFY_H_
#define _CLASSIFY_H_
unsigned int *Classify(double **pTestSampleFeatureVec,unsigned int pRow1,unsigned int pCol1,double **pModelParaTable,unsigned int pClassNum);
void EvaluateResult(unsigned int *TestSampleClassVec,unsigned int *ResultVec,unsigned int pVecLen,unsigned int pClassNum);
#endif