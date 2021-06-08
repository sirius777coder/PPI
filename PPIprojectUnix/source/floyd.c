#include "floyd.h"
#include "PPI_new.h"
void floyd(Graph *g)//arr为有权无方向图邻接矩阵的拷贝（要对数组进行原地操作，不能直接传邻接矩阵，且infinity要设置大）；n为节点的数量；
{
    int i=0,j=0,k=0;
    //k代表更新的次数，必须放在最外面
    for (k=0;k<g->vexnum;k++)
    {
        //i,j代表矩阵的元素，可以交换位置
        for (i=0;i<g->vexnum;i++)
        {
            for (j=0;j<g->vexnum;j++)
            {
                g->matrix[i][j]=g->matrix[i][j]<(g->matrix[i][k]+g->matrix[k][j])?g->matrix[i][j]:(g->matrix[i][k]+g->matrix[k][j]);
            }
        }
        if (k%100==0) printf("epoch%d---------------\n",k);
    }
}
void count_dis(Graph *g)//输入一个已经利用floyd排好顺序的结构体
{
    double temp=0;
    int n=0;
    int i=0,j=0,max=0;
    for (i=0;i<g->vexnum;i++)
    {
        for (j=0;j<g->vexnum;j++)
        {
            if (g->matrix[i][j]!=INF)
            {
                temp+=g->matrix[i][j];
                max=max>g->matrix[i][j]?max:g->matrix[i][j];
                n++;
            }
        }
    }
    double res=temp/n/2;
    printf("average minimum distance:%f\n",res);
    printf("max of the minimum distance:%d\n",max);
}