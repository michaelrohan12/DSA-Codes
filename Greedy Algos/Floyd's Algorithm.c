#include<stdio.h>
#include<limits.h>
int min(int a,int b)
{
    if(a<b)
        return a;
    else
        return b;
}

void floyd(int D[4][4])
{
    for(int k=0;k<4;k++)
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                if(D[i][k]!=INT_MAX && D[k][j]!=INT_MAX)
                    D[i][j]= min(D[i][j],D[i][k] + D[k][j]);
}

int main()
{
    int D[4][4] = {
        {0,INT_MAX,3,INT_MAX},
        {2,0,INT_MAX,INT_MAX},
        {INT_MAX,7,0,1},
        {6,INT_MAX,INT_MAX,0}
    };
    floyd(D);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("%d ",D[i][j]);
        }
        printf("\n");
    }
    return 0;
}
