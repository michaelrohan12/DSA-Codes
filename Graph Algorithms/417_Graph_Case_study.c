#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 9999

int completed[5];
int cost;
/*char places[11][50] = {"KLE TU","Lingaraj Nagar Samudaya Bhavan","Urban Oasis Mall","KIMS",
    "Deshpande Nagar","Keshwapur","Vijay Nagar","Raj Nagar","Bhavani Nagar",
    "Railway Ground","Madhura Estate"};
/*int weights[11][11] = {
        {0,4,10,5,8,6,8,9,10,9,12},
        {4,0,11,12,17,15,17,13,19,19,21},
        {10,11,0,12,12,13,15,18,14,14,17},
        {5,12,12,0,8,6,8,10,9,8,13},
        {8,17,12,8,0,7,9,10,6,5,9},
        {6,15,13,6,7,0,2,7,1,5,6},
        {8,17,15,8,9,2,0,7,6,6,6},
        {9,13,18,10,10,7,7,0,10,10,10},
        {10,19,14,9,6,1,6,10,0,2,6},
        {9,19,14,8,5,5,6,10,2,0,6},
        {12,21,17,13,9,6,6,10,6,6,0}
        };*/
int weights[5][5]={
        {0,24,11,10,9},
        {24,0,2,5,11},
        {11,2,0,8,7},
        {10,5,8,0,6},
        {9,11,7,6,0}
        };

int least(int p){
    int i,np=MAX;
    int min=MAX,pmin;
    for(i=0;i<5;i++){
        if ((weights[p][i] != 0) && (completed[i] == 0))
      if (weights[p][i] + weights[i][p] < min) {
        min = weights[i][0] + weights[p][i];
        pmin = weights[p][i];
        np = i;
      }
    }
    if(min!=MAX)
        cost+=pmin;
    return np;
}

void min_cost(int place){
    int nplace;
    completed[place]=1;
    printf("%d-->",place+1);
    nplace=least(place);
    if(nplace==MAX){
        nplace=0;
        printf("%d",nplace+1);
        cost+=weights[place][nplace];
        return;
    }
    min_cost(nplace);
}

int main(){
    printf("The path is:\n");
    min_cost(0);
    printf("\n\nMinimum cost is %d\n",cost);
    return 0;
}
