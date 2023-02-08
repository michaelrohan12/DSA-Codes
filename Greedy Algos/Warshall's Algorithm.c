#include<stdio.h>

void warshall(int R[5][5])
{
    for(int k=0;k<5;k++)
        for(int i=0;i<5;i++)
            for(int j=0;j<5;j++)
                R[i][j]= R[i][j] || (R[i][k] & R[k][j]);
}

int main()
{
    int R[5][5] = {
        {0,1,0,0,0},
        {1,0,0,1,0},
        {0,1,0,0,0},
        {0,0,0,0,0}
    };
    int a[5][5],count=0;
    warshall(R);
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(R[i][j]==0){
                count++;
            }
        }
    }
    int result = count - (2*((5*5)-count)) - 5;
    printf("\n%d\n",result);
    return 0;
}
