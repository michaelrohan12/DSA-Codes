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

int Partition(MST *M,int l,int r)
{
    int p = M[l].w;
    int i = l;
    int j = r+1;
    do
    {
        do
        {
            ++i;
        }while(M[i].w<p);
        do
        {
            --j;
        }while(M[j].w>p);
        swap(&M[i],&M[j]);
    }while(i<j);
    swap(&M[i],&M[j]);
    swap(&M[l],&M[j]);
    return j;
}

void quicksort(MST *M,int l,int r)
{
    if(l<r)
    {
        int s = Partition(M,l,r);
        quicksort(M,l,s-1);
        quicksort(M,s+1,r);
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
    int i,j,cost=0,step=0,count=0;
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
    printf("Total cost:%d",cost);
}

int main()
{
    int i,n,k;
    printf("Enter number of vertices:");
    scanf("%d",&n);
    int a[n];
    for(i=0;i<n;i++)
    {
        a[i]=i;
    }
    printf("Enter number of edges:");
    scanf("%d",&k);
    printf("Enter edges with u and v vertices and the weight of each edge\n");
    printf("u v w\n");
    for(i=0;i<k;i++)
    {
        scanf("%d%d%d",&M[i].u,&M[i].v,&M[i].w);
    }
    quicksort(M,0,k-1);
    minimum_spanning_tree(a,M,n);
    return 0;
}
