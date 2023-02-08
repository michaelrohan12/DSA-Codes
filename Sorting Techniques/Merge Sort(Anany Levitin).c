#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void copy1(int *A,int *B,int n){
    for(int i=0;i<floor(n/2);i++){
        B[i]=A[i];
    }
}

void copy2(int *A,int *C,int n){
    int j = floor(n/2);
    for(int i=0;i<ceil(n/2);i++){
        C[i]=A[j++];
    }
}

void copy3(int *C,int *A,int j,int k,int p,int q){
    for(int i=k;i<(p+q);i++){
        A[i]=C[j++];
    }
}

void copy4(int *B,int *A,int i,int k,int p,int q){
    for(int j=k;j<(p+q);j++){
        A[j]=B[i++];
    }
}

void Merge(int *B,int *C,int *A,int p,int q){
    int i=0,j=0,k=0;
    while(i<p && j<q){
        if(B[i]<=C[j]){
            A[k]=B[i];
            i++;
        }
        else{
            A[k]=C[j];
            j++;
        }
        k++;
    }
    if(i==p)
        copy3(C,A,j,k,p,q);
    else
        copy4(B,A,i,k,p,q);
}

void Mergesort(int *A,int n){
    int p = floor(n/2);
    int q = ceil(n/2);
    int B[p],C[q];
    if(n>1){
        copy1(A,B,n);
        copy2(A,C,n);
        Mergesort(B,p);
        Mergesort(C,q);
        Merge(B,C,A,p,q);
    }
}

int main()
{
    int n=6;
    int A[6] = {33,22,1,74,12,45};
    Mergesort(A,n);
    for(int i=0;i<n;i++){
        printf("%d\t",A[i]);
    }
    printf("\n");
    return 0;
}

