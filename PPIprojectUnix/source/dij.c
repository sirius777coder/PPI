#include "PPI_new.h"
#include "dij.h"
#include <stdio.h>
#include <stdlib.h>
void dijkstra(Graph *g, int vs, int stop,int prev[], int dist[],int max)
{
    int i,j,k;
    int min;
    int tmp;
    int flag[max];


    // 初始化
    for (i = 0; i <g->vexnum; i++)
    {
        flag[i] = 0;              // 顶点i的最短路径还没获取到。
        prev[i] = 0;              // 顶点i的前驱顶点为0。
        dist[i] =g->matrix[vs][i];// 顶点i的最短路径为"顶点vs"到"顶点i"的权。
    }

    // 对"顶点vs"自身进行初始化
    flag[vs] = 1;
    dist[vs] = 0;

    // 遍历G.vexnum-1次；每次找出一个顶点的最短路径。
    for (i = 1; i <g->vexnum; i++)
    {
        // 寻找当前最小的路径；
        // 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
        min = INF;
        for (j = 0; j <g->vexnum; j++)
        {
            if (flag[j]==0 && dist[j]<min)
            {
                min = dist[j];
                k = j;
            }
        }
        // 标记"顶点k"为已经获取到最短路径
        flag[k] = 1;

        // 修正当前最短路径和前驱顶点
        // 即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
        for (j = 0; j <g->vexnum; j++)
        {
            tmp = (g->matrix[k][j]==INF ? INF : (min +g->matrix[k][j])); // 防止溢出
            if (flag[j] == 0 && (tmp  < dist[j]) )
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }

    // 打印dijkstra最短路径的结果
    printf("dijkstra(%d): \n",g->vex[vs]);
    for (i = 0; i <g->vexnum; i++){
        if (stop == i){
            if (dist[i]!=INF) printf("  shortest(%d, %d)=%d\n",g->vex[vs],g->vex[i], dist[i]);
            else printf("irreverent!\n");
            break;
        }
    }
}
