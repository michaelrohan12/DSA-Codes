#include<stdio.h>
#include<stdlib.h>

typedef struct Kruskal
{
    int u;
    int v;
    int w;
}MST;

MST M[30];

void swap(MST *a,MST *b)
{
    MST temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void bubblesort(MST *M,int n)
{
    int i,j;
    for(i=0;i<=n-2;i++)
    {
        for(j=0;j<=n-2-i;j++)
        {
            if(M[j].w>M[j+1].w)
            {
                swap(&M[j],&M[j+1]);
            }
        }
    }
}


void union_find(int *a,int i,int j,int n)
{
    int k;
    for(k=0;k<n;k++)
    {
        if(a[k]==i)
        {
            a[k]=j;
        }
    }
}

void minimum_spanning_tree(int *a,MST *M,int n)
{
  int count=0,i,j,step=0,cost=0;
  while(count<n-1)
  {
      i=a[M[step].u];
      j=a[M[step].v];
      if(i!=j)
      {
          printf("(%d,%d)\n",M[step].u,M[step].v);
          cost+=M[step].w;
          union_find(a,i,j,n);
          count++;
      }
      step++;
  }
  printf("total_cost %d",cost);
}


int main()
{
    int i,n,k;
    printf("enter the no of vertices\n");
    scanf("%d",&n);
    int a[n];
    for(i=0;i<n;i++)
    {
        a[i]=i;
    }
    printf("enter the no of edges\n");
    scanf("%d",&k);
    printf("enter the edges with u,v vertices and weight of each edge\n");
    printf("u v w\n");
    for(i=0;i<k;i++)
    {
        scanf("%d%d%d",&M[i].u,&M[i].v,&M[i].w);
    }
    bubblesort(M,k);
    minimum_spanning_tree(a,M,n);
    return 0;
}

/**0 1 8
0 7 16
1 2 16
1 7 22
2 3 14
2 5 8
2 8 4
3 4 18
3 5 28
4 5 20
5 6 4
6 8 12
6 7 2
7 8 14**/
