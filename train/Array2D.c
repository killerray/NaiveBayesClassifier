#include <stdlib.h>
#include <stdio.h>
#include "Array2D.h"
void create_2D_array(TYPE ***arr,unsigned int len,unsigned int width)
{
	unsigned int i,m,n;
	*arr = (TYPE **)malloc(len*sizeof(TYPE *));

	for(i = 0; i!=len;++i)
		(*arr)[i]=(TYPE *)malloc(width*sizeof(TYPE));
	for(m=0; m!=len;++m)
		for( n=0;n!=width;++n)
			(*arr)[m][n]=0;
}


void destroy_2D_array(TYPE **arr,unsigned int len,unsigned int width)
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
