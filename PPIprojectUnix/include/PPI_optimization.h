#include "PPI_new.h"
#ifndef TEST_PPI_OPTIMIZATION_H
#define TEST_PPI_OPTIMIZATION_H
/* this c file is used for adjacency matrix to adjacency list */

struct node{
    int id;
    struct node* next;
};//定义邻接表的节点类型
typedef struct {
    int vexnum;
    int edgenum;
    struct node* adj_list[MAX_VERTEX_NUM];//图结构体中的邻接表
}AL_graph;//用邻接表来表达的图结构体

void m2l(Graph *g,AL_graph *lg);
void show_list(AL_graph *lg);
void s1p(AL_graph *lg,int id);

#endif //TEST_PPI_OPTIMIZATION_H
