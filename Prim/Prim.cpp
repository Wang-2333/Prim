#include <iostream>
#include <stdio.h>

#define MaxVerNum 100
#define MaxValue 10000
typedef struct {
    char vexs[MaxVerNum];  //顶点集合
    int edges[MaxVerNum][MaxVerNum];  //边集合
    int n, e;  //顶点和边
}MGraph;

char vertex[] = "0123456";
int nvertex = 7, nedges = 9;
int connection[][3] = { {0,1,28},{0,5,10},{1,2,16},{1,6,14},{2,3,12},{3,4,22},{3,6,18},{4,5,25},{4,6,24} };

void CreateMgraph(MGraph& G)
{
    int i, j, k;
    G.n = nvertex;
    G.e = nedges;
    for (i = 0; i < G.n; i++)
        G.vexs[i] = vertex[i];  //顶点
    for (i = 0; i < G.n; i++)
        for (j = 0; j < G.n; j++)
            G.edges[i][j] = MaxValue; //初始化边最大值，没有边
    for (i = 0; i < G.n; i++)
        G.edges[i][i] = 0;  //初始化边为0

    for (k = 0; k < G.e; k++)
    {
        i = connection[k][0];
        j = connection[k][1];
        G.edges[i][j] = connection[k][2];
        G.edges[j][i] = G.edges[i][j]; //有向图没有这一行
    }
}

void printMgraph(MGraph& G)
{
    int i, j;
    printf("图的结点总数：%d  边总数：%d\n", G.n, G.e);
    for (i = 0; i < G.n; i++)
    {
        for (j = 0; j < G.n; j++)
            if (G.edges[i][j] == 10000)
                printf("∞   "); //"00"代表无穷
            else
                printf("%d   ", G.edges[i][j]);
        printf("\n");
    }
}

//最小生成树
typedef struct
{
    int head, tail, cost;
}MST[MaxVerNum];

void Prim(MGraph& G, MST& T, int u)
{
    int i, j;
    int* lowcost = new int[G.n];
    int* nearvex = new int[G.n];
    for (i = 0; i < G.n; i++)
    {
        lowcost[i] = G.edges[u][i]; //u到各点的代价
        nearvex[i] = u;   //最短带权路径
    }
    nearvex[u] = -1;  //加入到生成树顶点集合
    int k = 0;
    for (i = 0; i < G.n; i++)
        if (i != u)
        {
            int min = MaxValue;
            int v = u;
            for (j = 0; j < G.n; j++)
                if (nearvex[j] != -1 && lowcost[j] < min) //=-1不参选
                {
                    v = j;
                    min = lowcost[j];//求生成树外顶点到生成树内顶点具有最小权值的边，
                                   //v是当前具有最小权值的边
                }
            if (v != u)
            {
                T[k].tail = nearvex[v];
                T[k].head = v;
                T[k++].cost = lowcost[v];
                nearvex[v] = -1;  //该边加入生成树标记
                for (j = 0; j < G.n; j++)
                    if (nearvex[j] != -1 && G.edges[v][j] < lowcost[j])
                    {
                        lowcost[j] = G.edges[v][j];  //修改
                        nearvex[j] = v;
                    }
            }

        }//循环n-1次，加入n-1条边
}


int main(int argc, const char* argv[]) {
    int i;
    MGraph g;
    CreateMgraph(g);
    printMgraph(g);
    MST t;
    Prim(g, t, 0);
    printf("生成树：结点->权值->结点\n");
    for (i = 0; i < g.n-1; i++)
        printf("(%d)-->%d-->(%d)\n", t[i].tail, t[i].cost, t[i].head);
    return 1;
}