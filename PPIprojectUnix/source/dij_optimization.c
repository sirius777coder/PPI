#include "dij_optimization.h"

//初始化邻接表
AdjacentList* initList() {
    AdjacentList* list = (AdjacentList*)malloc(sizeof(AdjacentList));
    if (list == NULL) {
        printf("can not create a list\n");
        return NULL;
    }
    memset(list->list, 0, sizeof(list->list));
    list->nodecount = 0;
    list->edgecount = 0;
    return list;
}

//创建新的顶点
Node* createNode(int nodeInfo) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("can not create a node\n");
        return NULL;
    }
    node->firstedge = NULL;
    node->nodeInfo = nodeInfo;
    return node;
}

//创建新的边
Edge* createEdge(int node, int cost) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    if (edge == NULL) {
        printf("can not create an edge\n");
        return NULL;
    }
    edge->cost = cost;
    edge->node = node;
    edge->nextedge = NULL;
    return edge;
}


//采用头插法向边表中插入新的边
int insertEdge(Node* firstnode, Edge* newedge) {
    if (firstnode == NULL) {
        return 0;
    }
    if (firstnode->firstedge == NULL) {
        firstnode->firstedge = newedge;
        return 1;
    }
    newedge->nextedge = firstnode->firstedge;
    firstnode->firstedge = newedge;
    return 1;
}


void inputData()
{
    FILE*fp;
    char buff[BUFFMAXSIZE];
    char w[10],v[10];
    int countEdge = 0;
    int countNode = 0;
    fp = fopen("tar.csv", "r");
    while (!feof(fp))
    {
        fgets(buff, BUFFMAXSIZE, fp);
        sscanf(buff, "%s,%s", w,v);
        printf("%s %s\n", w,v);
        countEdge++;
    }

}


//构造邻接表
AdjacentList* createList(AdjacentList* list, char* filename) {
    FILE* infile;
    Edge* edge;
    char buffer[BUFFERSIZE];
    if ((infile = fopen(filename, "rt")) == NULL) {
        fputs(" Couldn't open the file.\n", stdout);
        return NULL;
    }
    char* p;//保存每一行最开始的顶点号
    //根据逗号分割字符串后，用于保存边表元素的右半部分
    int right, left;
    char isRightIn, isLeftIn;
    int rightId, leftId;
    int countNode = 0;
    int i;
    while (!feof(infile)) {
        if (fgets(buffer, BUFFERSIZE, infile) == NULL) {
            break;
        }
        buffer[strlen(buffer)] = '\0';
        sscanf(buffer, "%d,%d", &right, &left);
        isRightIn = 0;
        isLeftIn = 0;
        for(i=0; i<countNode; ++i)
        {
            if (list->nodeId[i] == right){
                isRightIn = 1;
                rightId = i;
            }
            if (list->nodeId[i] == left){
                isLeftIn = 1;
                leftId = i;
            }
            if (isRightIn && isLeftIn)
                break;
        }
        if (!isRightIn){
            list->list[countNode] = createNode(right);
            rightId = countNode;
            list->nodeId[countNode++] = right;
            list->nodecount++;

        }
        if (!isLeftIn){
            list->list[countNode] = createNode(left);
            leftId = countNode;
            list->nodeId[countNode++] = left;
            list->nodecount++;
        }
        edge = createEdge(leftId, 1);
        int res = insertEdge(list->list[rightId], edge);
        if (res == 0) {
            printf("can not insert edge %d,%d \n", leftId, rightId);
            exit(EXIT_FAILURE);
        }
        list->edgecount++;
    }
    return list;
}


//计算从源顶点到其他顶点的单源最短路径
void shortestpath(AdjacentList* list, int visited[], int distance[], int prenode[], int src) {
    int count = 0;//记录直接与源点相连的顶点个数
    visited[src] = 1;//源点已经添加到最短路径中
    distance[src] = 0;
    count++;
    int i;
    //如果有顶点和源点直接相连，另外设置距离
    if (list->list[src] != NULL) {
        Edge* p = list->list[src]->firstedge;
        for (; p != NULL; ) {
            distance[p->node] = p->cost;
            prenode[p->node] = src;//这些顶点的前驱顶点为源点
            p = p->nextedge;
        }
    }

    while (count <= list->nodecount) {
        int min = INF;
        int target_node = 0;
        //首先在剩余节点中寻找距离最新加入最短路径的顶点，最近的那一个
        for (i = 1; i <= list->nodecount; i++) {
            if (visited[i] == 0 && min > distance[i]) {
                min = distance[i];
                target_node = i;
            }
        }
        visited[target_node] = 1;//将最短距离顶点加入最短路径中
        count++;
        //已新加入的顶点为中介，更新剩余未加入最短路径的顶点的距离
        if (list->list[target_node] != NULL) {
            Edge* p = list->list[target_node]->firstedge;
            for (; p != NULL; ) {
                if (visited[p->node] == 0 && distance[target_node] + p->cost < distance[p->node]) {
                    distance[p->node] = distance[target_node] + p->cost;
                    prenode[p->node] = target_node;
                }
                p = p->nextedge;
            }
        }


    }


}

int optimize(int left,int right) {
    AdjacentList* list;
    list = initList();
    list = createList(list, "../data/Sacer/tar.csv");
    int visited[MAXNODESIZE] = {0};//标记顶点是否已经被记录为最短路径
    int distance[MAXNODESIZE];//标记从源点到其他顶点的路径长度
    int prenode[MAXNODESIZE] = {0};//如果某个顶点要加入最短路径，记录该顶点在最短路径中的前一个顶点
    //初始将每个顶点的距离设置为无穷大
    int i, j;
    for (i = 0; i < MAXNODESIZE; i++) {
        distance[i] = INF;
    }

    int src=-1,  dest=-1;
    for(i=0; i<list->nodecount;++i){
        if( list->nodeId[i] == left)
            src = i;
        if (list->nodeId[i] == right)
            dest = i;
        if (dest != -1 && src != -1)
            break;
    }
    if (dest == -1 || src == -1)
        printf("输入的编号不合法\n");

    shortestpath(list, visited, distance, prenode, src);
    int path[MAXNODESIZE] = { 0 };//用于保存路径信息

    //输出最短路径信息
    for (i = 1; i <= MAXNODESIZE; i++) {
        if (i != dest)
            continue;
        if (distance[i] == INF) {
            printf("顶点 %d 到顶点 %d 之间没有最短路径\n", list->nodeId[src], list->nodeId[i]);
        }
        else {
            int p = i;
            int n = 0;
            while (p != 0) {
                path[n] = p;
                p = prenode[p];//使p指向自己的前驱节点
                n++;
            }
            //n为路径中节点数量
            printf("顶点 %d 到顶点 %d 之间的最短路径为: ", list->nodeId[src], list->nodeId[i]);
            printf("%d", list->nodeId[path[n - 1]]);
            for (j = n - 2; j >= 0; j--) {
                printf("—>%d", list->nodeId[path[j]]);
            }
            printf("   路径长度为 %d\n", distance[i]);
        }
        memset(path, 0, MAXNODESIZE);
    }

    return 0;
}

