#ifndef _TRAINMODEL_H_
#define _TRAINMODEL_H_
double ** TrainModel(double **pFeatureVec,unsigned int pRow,unsigned int pCol,unsigned int *pClassVec,unsigned int ClassNum);
void FreeTable(double **pParaTable,unsigned int pRow,unsigned int pCol);
unsigned int CountClass(unsigned int *pClassVec,unsigned int pClassVecLen);
#endif
