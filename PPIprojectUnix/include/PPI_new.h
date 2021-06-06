#ifndef TEST_PPI_NEW_H
#define TEST_PPI_NEW_H
#include <stdio.h>
#include <stdlib.h>
#define INF 999
#define MAX_VERTEX_NUM 9999
typedef struct {
    int vexnum,edgnum;
    int vex[MAX_VERTEX_NUM];
    int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
}Graph;//邻接矩阵表示的图结构体
int *get_number2(char delimiter,int *temp,const char *p);//从一个字符串中拿出两个整数
int *get_index(const int *number,int *index,const int *vex,int max);//从图的顶点数组中取出对应的坐标,number代表取出的两个数字,index表示对应的下标，vex代表顶点的一维数组
int vertex_arr(Graph *g,char *path);//返回一共有多少个蛋白,path代表着所有蛋白质名称的数组,构建g1.vex
void matrix(Graph *g,char *path,int n);
void show_matrix(Graph *g,int n,int m);
#endif //TEST_PPI_NEW_H
