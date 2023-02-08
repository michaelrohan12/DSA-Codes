#include<stdio.h>
#include<stdlib.h>

void swap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

int Partition(int *a,int l,int r)
{
    int p = a[l];
    int i = l;
    int j = r+1;
    do
    {
        do
        {
            ++i;
        }while(a[i]<p);
        do
        {
            --j;
        }while(a[j]>p);
        swap(&a[i],&a[j]);
    }while(i<j);
    swap(&a[i],&a[j]);
    swap(&a[l],&a[j]);
    return j;
}

void quicksort(int *a,int l,int r)
{
    if(l<r)
    {
        int s = Partition(a,l,r);
        quicksort(a,l,s-1);
        quicksort(a,s+1,r);
    }
}


int main()
{
    int i,n;
    printf("Enter n\n");
    scanf("%d",&n);
    int *a = (int*)malloc(n*sizeof(int));
    printf("Enter %d numbers\n",n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    printf("Before Sorting\n");
    for(i=0;i<n;i++)
        printf("%d\t",a[i]);
    quicksort(a,0,n-1);
    printf("\nAfter sorting\n");
    for(int i=0;i<n;i++)
        printf("%d\t",a[i]);
    return 0;
}
