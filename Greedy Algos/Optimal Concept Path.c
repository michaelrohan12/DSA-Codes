#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int i=0,source=0;

int min(int a,int b,int* path)
{
    if(a<b)
        return a;
    else{
        path[i]=source;
        return b;
    }
}

int main()
{
    int n,c,a,b,wt;
    scanf("%d",&n);
    scanf("%d",&c);
    int arr[n][n];
    for(int j=0;j<n;j++){
        for(int k=0;k<n;k++){
            if(j==k)
                arr[j][k]=0;
            else
                arr[j][k]=60;
        }
    }
    for(int k=0;k<c;k++){
        scanf("%d %d %d",&a,&b,&wt);
        arr[a][b]=wt;
    }
    int dist[n],visited[n],path[n],min_wt,min_index,flag1=1,flag2=1,total=0;
    memset(visited,0,n*sizeof(int));
    memset(path,0,n*sizeof(int));
    for(i=0;i<n;i++){
        dist[i] = arr[source][i];
    }
    visited[0]=1;
    while(flag1)
    {
        flag1=0;
        flag2=1;
        for(i=1;i<n;i++)
        {
            if(visited[i]==0){
                flag1=1;
                if(flag2){
                    flag2=0;
                    dist[i]=min(dist[i],total+arr[source][i],path);
                    min_wt=dist[i];
                    min_index=i;
                }
                else{
                    dist[i]=min(dist[i],total+arr[source][i],path);
                    if(min_wt>dist[i]){
                        min_wt=dist[i];
                        min_index=i;
                    }
                }

            }
        }
        if(flag1==0){
            break;
        }
        visited[min_index]=1;
        source=min_index;
        total=min_wt;
    }
    int q,index;
    scanf("%d",&q);
    for(int k=0;k<q;k++){
        scanf("%d",&index);
        printf("%d\n",dist[index]);
    }
    return 0;
}

