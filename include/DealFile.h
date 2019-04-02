#ifndef _DEALFILE_H_
#define _DEALFILE_H_
double **ReadFile(const char *pFileName,unsigned int pRow,unsigned int pCol,unsigned int **pClassVec);
void PrintModelFile(double **pFeatureVec,unsigned int pRow,unsigned int pCol,const char *pFileName);
void FreeFile(double **pFeatureVec,unsigned int pRow,unsigned int pCol,unsigned int *pClassVec);
double **LoadModelFile(const char *pFileName,unsigned int pRow,unsigned int pCol,unsigned int *pClassNum,unsigned int **pClassVec);
void PrintFile(double **pFeatureVec,unsigned int pRow,unsigned int pCol);
#endif