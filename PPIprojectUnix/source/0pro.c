#include "0pro.h"
#include "PPI_optimization.h"
#include "PPI_new.h"
void find0pro(AL_graph *lg)
{
    int i=0,max=0,temp_max=0,index=0;//index表示中心蛋白的序号，max表示他对应连接的蛋白质
    for (i=0;i<lg->vexnum;i++)
    {
        temp_max=0;
        struct node*temp;
        temp=lg->adj_list[i];
        while (temp->next!=NULL)
        {
            temp_max++;
            temp=temp->next;
        }
        if (temp_max>max)
        {
            max=temp_max;
            index=i;
        }
    }
    printf("the most important protein : %d\n",lg->adj_list[index]->id);
}
