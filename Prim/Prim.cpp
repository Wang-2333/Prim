#include <iostream>
#include <stdio.h>

#define MaxVerNum 100
#define MaxValue 10000
typedef struct {
    char vexs[MaxVerNum];  //���㼯��
    int edges[MaxVerNum][MaxVerNum];  //�߼���
    int n, e;  //����ͱ�
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
        G.vexs[i] = vertex[i];  //����
    for (i = 0; i < G.n; i++)
        for (j = 0; j < G.n; j++)
            G.edges[i][j] = MaxValue; //��ʼ�������ֵ��û�б�
    for (i = 0; i < G.n; i++)
        G.edges[i][i] = 0;  //��ʼ����Ϊ0

    for (k = 0; k < G.e; k++)
    {
        i = connection[k][0];
        j = connection[k][1];
        G.edges[i][j] = connection[k][2];
        G.edges[j][i] = G.edges[i][j]; //����ͼû����һ��
    }
}

void printMgraph(MGraph& G)
{
    int i, j;
    printf("ͼ�Ľ��������%d  ��������%d\n", G.n, G.e);
    for (i = 0; i < G.n; i++)
    {
        for (j = 0; j < G.n; j++)
            if (G.edges[i][j] == 10000)
                printf("��   "); //"00"��������
            else
                printf("%d   ", G.edges[i][j]);
        printf("\n");
    }
}

//��С������
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
        lowcost[i] = G.edges[u][i]; //u������Ĵ���
        nearvex[i] = u;   //��̴�Ȩ·��
    }
    nearvex[u] = -1;  //���뵽���������㼯��
    int k = 0;
    for (i = 0; i < G.n; i++)
        if (i != u)
        {
            int min = MaxValue;
            int v = u;
            for (j = 0; j < G.n; j++)
                if (nearvex[j] != -1 && lowcost[j] < min) //=-1����ѡ
                {
                    v = j;
                    min = lowcost[j];//���������ⶥ�㵽�������ڶ��������СȨֵ�ıߣ�
                                   //v�ǵ�ǰ������СȨֵ�ı�
                }
            if (v != u)
            {
                T[k].tail = nearvex[v];
                T[k].head = v;
                T[k++].cost = lowcost[v];
                nearvex[v] = -1;  //�ñ߼������������
                for (j = 0; j < G.n; j++)
                    if (nearvex[j] != -1 && G.edges[v][j] < lowcost[j])
                    {
                        lowcost[j] = G.edges[v][j];  //�޸�
                        nearvex[j] = v;
                    }
            }

        }//ѭ��n-1�Σ�����n-1����
}


int main(int argc, const char* argv[]) {
    int i;
    MGraph g;
    CreateMgraph(g);
    printMgraph(g);
    MST t;
    Prim(g, t, 0);
    printf("�����������->Ȩֵ->���\n");
    for (i = 0; i < g.n-1; i++)
        printf("(%d)-->%d-->(%d)\n", t[i].tail, t[i].cost, t[i].head);
    return 1;
}