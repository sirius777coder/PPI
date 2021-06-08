#include <stdio.h>
#include <stdlib.h>
#include "PPI_new.h"
#include "BF.h"
void Bellman_ford(Graph *g,int start,int max)
{
    int flag;
	int i, j;
	for(i=0;i<=max;i++)
	{
		dis[i]=INF;
	}
    dis[start]=0;

		for(i=0;i<=max;i++)
		{
			for (j=0;j<=max;j++)
			{
				if(dis[j]>dis[i]+g->matrix[i][j])
				{
					dis[j]=dis[i]+g->matrix[i][j];

				}
			}
		}

}
