#include "PPI_new.h"
#include <stdio.h>
#include <stdlib.h>
/* this c file is used for create adjacent matrix structure */

//create graph
int *get_number2(char delimiter,int *temp,const char *p)//从一个字符串中拿出两个整数
{
    int i=0;
    temp[0]=0;
    temp[1]=0;
    while (p[i]!=delimiter)
    {
        temp[0]=(int)(p[i]-'0')+temp[0]*10;
        i++;
    }
    i++;
    while (p[i]!='\0'&&p[i]!='\n')
    {
        temp[1]=(int)(p[i]-'0')+temp[1]*10;
        i++;
    }
    return temp;
}
int *get_index(const int *number,int *index,const int *vex,int max)//从图的顶点数组中取出对应的坐标,number代表取出的两个数字,index表示对应的下标，vex代表顶点的一维数组
{
    int i=0;
    int flag1=0,flag2=0;
    for (i=0;i<max;i++)
    {
        if (!flag1)
        {
            if (vex[i]==number[0])
            {
                index[0]=i;
                flag1=1;
            }
        }
        if (!flag2)
        {
            if (vex[i]==number[1])
            {
                index[1]=i;
                flag2=1;
            }
        }
        if (flag1==1&&flag2==1) break;
    }
    return index;
}
int vertex_arr(Graph *g,char *path)//返回一共有多少个蛋白
{
    char p[15];
    FILE *fp= fopen(path,"r");
    int i=0;
    while (1)
    {
        fgets(p,15,fp);
        if (!feof(fp))
        {
            g->vex[i]= atoi(p);
            i++;
        }
        else break;
    }
    fclose(fp);
    return i;
}//path代表着所有蛋白质名称的数组,构建g1.vex
void matrix(Graph *g,char *path,int n)
{
    int n1=0,n2=0;
    for (n1=0;n1<n;n1++)
    {
        for (n2=0;n2<n;n2++)
        {
            g->matrix[n1][n2]=INF;
        }
    }
    int i=0;
    FILE *fp= fopen(path,"r");
    char p[30];
    int temp[2]={0},index[2]={0};
    while (1)
    {
        fgets(p,30,fp);
        if (!feof(fp))
        {
            get_number2(',',temp,p);
            get_index(temp,index,g->vex,MAX_VERTEX_NUM);
            g->matrix[index[0]][index[1]]=1;
            g->matrix[index[1]][index[0]]=1;
            i++;
            if (i%100000==0) printf("epoch%d\n",i);
        }
        else break;
    }
    g->edgnum=i;
    fclose(fp);

}
void show_matrix(Graph *g,int n,int m)
{
    int i=0,j=0;
    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            printf("%d ",g->matrix[i][j]);
        }
        printf("\n");
    }
}







