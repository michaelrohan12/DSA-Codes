#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void swap(int* a,int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void heapify(int *H,int n){
    int i,j,k,v,heap;
    for(i=floor(n/2);i>=1;i--){
        k=i;
        v=H[k];
        heap=0;
        while(!heap && 2*k<=n){
            j=2*k;
            if(j<n){
                if(H[j]<H[j+1])
                    j=j+1;
            }
            if(v>=H[j])
                heap=1;
            else{
                H[k]=H[j];
                k=j;
            }
        }
        H[k]=v;
    }
}

int* heap_sort(int *H,int n){
    int i=n-1;
    int* result = malloc(n*sizeof(int));
    while(n!=1){
        swap(&H[1],&H[n]);
        result[i--]=H[n];
        n--;
        heapify(H,n);
    }
    result[i]=H[1];
    return result;
}

int main()
{
    int n;
    printf("Enter the number of elements\n");
    scanf("%d",&n);
    int H[n+1],i;
    printf("Enter elements\n");
    H[0]=0;
    for(i=1;i<=n;i++){
        scanf("%d",&H[i]);
    }
    printf("Elements before sorting\n");
    for(i=1;i<=n;i++){
        printf("%d\t",H[i]);
    }
    printf("\n");
    heapify(H,n);
    printf("Elements after heapification\n");
    for(i=1;i<=n;i++){
        printf("%d\t",H[i]);
    }
    printf("\n");
    int* result = malloc(n*sizeof(int));
    result = heap_sort(H,n);
    printf("Elements after sorting in non-decreasing order\n");
    for(i=0;i<n;i++){
        printf("%d\t",result[i]);
    }
    printf("\n");
    return 0;
}
