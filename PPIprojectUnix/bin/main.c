#include "PPI_new.h"
#include "PPI_optimization.h"
#include "0pro.h"
#include "floyd.h"
#include "dij.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dij_optimization.h"
Graph g1; /* base adjacent matrix */
Graph g2; /* copied adjacent matrix */
AL_graph lg; /* adjacent list */
int prev[MAX_VERTEX_NUM] = {0} ;
int dist[MAX_VERTEX_NUM] = {0} ;
int main(int argc,char **argv)
{
    if (argc==1)
    {
        printf("please input right choices or use man to get help!\n");
        exit(2);
    }
    else
    {
        if (!strcmp(argv[1],"-a")&&argc==4)//输出酵母细胞任意两个蛋白质的最短路径
        {
            char *path1="../data/Sacer/finalize2.txt";
            char *path2="../data/Sacer/tar.csv";
            g1.vexnum= vertex_arr(&g1,path1);
            vertex_arr(&g1,path1);
            matrix(&g1,path2,g1.vexnum);
            g2=g1;
            int temp[2]={atoi(argv[2]),atoi(argv[3])};
            int index[2];
            get_index(temp,index,g2.vex,g2.vexnum);
            dijkstra(&g2,index[0],index[1],prev,dist,g2.vexnum);
        }
        else if (!strcmp(argv[1],"-a")&&argc!=4)
        {
            printf("you must input two protein id!\n");
            exit(3);
        }
        else if (!strcmp(argv[1],"-m")&&argc==2)//输出酵母细胞经过弗洛伊德矩阵排序后的邻接矩阵
        {
            char *path1="../data/Sacer/finalize2.txt";
            char *path2="../data/Sacer/tar.csv";
            g1.vexnum= vertex_arr(&g1,path1);
            vertex_arr(&g1,path1);
            matrix(&g1,path2,g1.vexnum);
            g2=g1;
            floyd(&g2);
            show_matrix(&g2,g2.vexnum,g2.vexnum);
        }
        else if (!strcmp(argv[1],"-m")&&argc!=2)
        {
            printf("you only need to input -m\n");
            exit (3);
        }
        else if (!strcmp(argv[1],"-p")&&argc==4)
        {
            optimize(atoi(argv[2]),atoi(argv[3]));
        }
        else if (!strcmp(argv[1],"-p")&&argc!=4)
        {
            printf("wrong input numbers!\n");
            exit(3);
        }
        else if (!strcmp(argv[1],"-l")&&argc==2)//输出酵母细胞的邻接表
        {
            char *path1="../data/Sacer/finalize2.txt";
            char *path2="../data/Sacer/tar.csv";
            g1.vexnum= vertex_arr(&g1,path1);
            vertex_arr(&g1,path1);
            matrix(&g1,path2,g1.vexnum);
            g2=g1;
            m2l(&g1,&lg);
            show_list(&lg);
        }
        else if (!strcmp(argv[1],"-l")&&argc!=2)
        {
            printf("you only need to input -l!\n");
            exit (3);
        }
        else if (!strcmp(argv[1],"-1l")&&argc==3)//输出酵母细胞任意一个蛋白质的邻接蛋白质
        {
            char *path1="../data/Sacer/finalize2.txt";
            char *path2="../data/Sacer/tar.csv";
            g1.vexnum= vertex_arr(&g1,path1);
            vertex_arr(&g1,path1);
            matrix(&g1,path2,g1.vexnum);
            g2=g1;
            m2l(&g1,&lg);
            s1p(&lg, atoi(argv[2]));
        }
        else if (!strcmp(argv[1],"-1l")&&argc!=3)
        {
            printf("you need to input a protein id\n");
            exit(3);
        }
        else if (!strcmp(argv[1],"--a")&&argc==6)//输出用户自定义文件中任意两个蛋白的最短路径
        {
            char *path1=argv[3];
            char *path2=argv[4];
            g1.vexnum= vertex_arr(&g1,path1);
            vertex_arr(&g1,path1);
            matrix(&g1,path2,g1.vexnum);
            g2=g1;
            int temp[2]={atoi(argv[5]),atoi(argv[6])};
            int index[2];
            get_index(temp,index,g2.vex,g2.vexnum);
            dijkstra(&g2,index[0],index[1],prev,dist,g2.vexnum);
        }
        else if (!strcmp(argv[1],"--a")&&argc!=6)
        {
            printf("you must input two protein id!\n");
            exit(3);
        }
        else if (!strcmp(argv[1],"--m")&&argc==4)//用户所给文件经过弗洛伊德排序的邻接矩阵
        {
            char *path1=argv[2];
            char *path2=argv[3];
            g1.vexnum= vertex_arr(&g1,path1);
            vertex_arr(&g1,path1);
            matrix(&g1,path2,g1.vexnum);
            g2=g1;
            floyd(&g2);
            show_matrix(&g1,g1.vexnum,g1.vexnum);
        }
        else if (!strcmp(argv[1],"--m")&&argc!=4)
        {
            printf("you only need to input -m\n");
            exit (3);
        }
        else if (!strcmp(argv[1],"--l")&&argc==4)//用户所给文件的邻接表
        {
            char *path1=argv[2];
            char *path2=argv[3];
            g1.vexnum= vertex_arr(&g1,path1);
            vertex_arr(&g1,path1);
            matrix(&g1,path2,g1.vexnum);
            g2=g1;
            m2l(&g1,&lg);
            show_list(&lg);
        }
        else if (!strcmp(argv[1],"--l")&&argc!=4)
        {
            printf("wrong input!\n");
            exit(3);
        }
        else if (!strcmp(argv[1],"--1l")&&argc==5)//用户所给文件的任意一个蛋白质的邻接蛋白质
        {
            char *path1=argv[2];
            char *path2=argv[3];
            g1.vexnum= vertex_arr(&g1,path1);
            vertex_arr(&g1,path1);
            matrix(&g1,path2,g1.vexnum);
            g2=g1;
            m2l(&g1,&lg);
            s1p(&lg,atoi(argv[4]));
        }
        else if (!strcmp(argv[1],"--1l")&&argc!=5)
        {
            printf("wrong input!\n");
            exit(3);
        }
        else if (!strcmp(argv[1],"--0")&&argc==4)//用户所给文件的中心蛋白
        {
            char *path1=argv[2];
            char *path2=argv[3];
            g1.vexnum= vertex_arr(&g1,path1);
            vertex_arr(&g1,path1);
            matrix(&g1,path2,g1.vexnum);
            m2l(&g1,&lg);
            find0pro(&lg);
        }
        else if (!strcmp(argv[1],"-0")&&argc==2)//用户所给文件的中心蛋白
        {
            char *path1="../data/Sacer/finalize2.txt";
            char *path2="../data/Sacer/tar.csv";
            g1.vexnum= vertex_arr(&g1,path1);
            vertex_arr(&g1,path1);
            matrix(&g1,path2,g1.vexnum);
            m2l(&g1,&lg);
            find0pro(&lg);
        }
        else if (!strcmp(argv[1],"--0")&&argc!=2)
        {
            printf("wrong input!\n");
            exit(3);
        }
        else
        {
            printf("please input right numbers or use man to get help!\n");
            exit(4);
        }
    }
    exit(0);
}
