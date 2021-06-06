#include "PPI_optimization.h"
#include "PPI_new.h"
#include <stdio.h>
#include <stdlib.h>
void m2l(Graph *g,AL_graph *lg)//代表给定一个adjacency matrix结构体，转化为adjacency list结构体
{
    lg->vexnum=g->vexnum;
    lg->edgenum=g->edgnum;
    int i=0,j=0;
    for (i=0;i<g->vexnum;i++)//寻找每一个head节点
    {
        struct node* head=(struct node*) malloc(sizeof (struct node));
        head->id=g->vex[i];
        struct node* temp=head;
        for (j=0;j<g->vexnum;j++)
        {
            if (g->matrix[i][j]!=INF)
            {
                struct node* rec_node= malloc(sizeof(struct node));
                rec_node->id=g->vex[j];
                temp->next=rec_node;
                temp=rec_node;
            }
            if (j==g->vexnum-1) temp->next=NULL;
        }
        lg->adj_list[i]=head;
    }
}

void show_list(AL_graph *lg)//展示邻接表
{
    int i=0;
    for (i=0;i<lg->vexnum;i++)
    {
        printf("%d->",lg->adj_list[i]->id);
        struct node *temp=lg->adj_list[i]->next;
        while (temp!=NULL)
        {
            printf("%d",temp->id);
            temp=temp->next;
            if (temp!=NULL) printf("->");
        }
        printf("\n");
    }
}
