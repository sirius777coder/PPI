#ifndef TEST_DIJ_OPTIMIZATION_H
#define TEST_DIJ_OPTIMIZATION_H
#include "PPI_new.h"
#ifndef TEST_HEADEE_H
#define TEST_HEADEE_H
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define BUFFMAXSIZE (1000)
#define MAXNODESIZE (100000)
#define BUFFERSIZE 50

//定义无向图中的边（弧）
typedef struct Edge{
    int node;//该边的终点
    int cost;//经过这条边需要的代价
    struct Edge* nextedge;//与该顶点相连的下一条边
}Edge;

//定义无向图中的顶点
typedef struct Node{
    Edge* firstedge;//该顶点所对应的边表的头节点
    int nodeInfo;
}Node;

//定义邻接表
typedef struct {
    Node* list[MAXNODESIZE];
    int nodecount;
    int edgecount;
    int nodeId[MAXNODESIZE];//存储下标和顶点的对应关系
}AdjacentList;


//初始化邻接表
AdjacentList* initList();

//创建新的顶点
Node* createNode(int nodeInfo);

//创建新的边
Edge* createEdge(int node, int cost);


//采用头插法向边表中插入新的边
int insertEdge(Node* firstnode, Edge* newedge);


void inputData();


//构造邻接表
AdjacentList* createList(AdjacentList* list, char* filename);


//计算从源顶点到其他顶点的单源最短路径
void shortestpath(AdjacentList* list, int visited[], int distance[], int prenode[], int src);

int optimize(int left,int right);

#endif //TEST_HEADEE_H

#endif //TEST_DIJ_OPTIMIZATION_H
