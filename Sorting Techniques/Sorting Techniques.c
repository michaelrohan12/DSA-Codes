#include<stdio.h>
#include<stdlib.h>
#define SIZE 10
// 89 45 68 34 90 29 17
void printarray(int a[SIZE],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",a[i]);
    printf("\n");
}

void swap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void bubble_sort(int a[SIZE],int n)
{
    int i,j,count=0;
    for(i=0;i<=n-2;i++)
    {
        for(j=0;j<=n-2-i;j++)
        {
            if(a[j]>a[j+1])
                swap(&a[j],&a[j+1]);
            else
                count++;
        }
    }
    printf("\nArray after sorting\n");
    printarray(a,n);
    printf("\n%d\n",count/(n-2));
}

void selection_sort(int a[SIZE],int n)
{
    int i,j,min;
    for(i=0;i<=n-2;i++)
    {
        min=i;
        for(j=i+1;j<=n-1;j++)
        {
            if(a[j]<a[min])
                min=j;
        }
        swap(&a[min],&a[i]);
    }
    printf("\nArray after sorting\n");
    printarray(a,n);
}

void insertion_sort(int a[SIZE],int n)
{
    int i,j,v;
    for(i=1;i<=n-1;i++)
    {
        v=a[i];
        j=i-1;
        while(j>=0 && a[j]<v)
        {
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=v;
    }
    printf("\nArray after sorting\n");
    printarray(a,n);
}

int main()
{
    int a[SIZE],i,n,choice;
    printf("Enter the number of elements:");
    scanf("%d",&n);
    printf("Enter the elements\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    while(1)
    {
        printf("\n--SORTING TECHNIQUES--\n");
        printf("1.Bubble Sort\n2.Selection Sort\n3.Insertion Sort\n4. Exit\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:printf("\nArray before sorting\n");
                    printarray(a,n);
                    bubble_sort(a,n);
                    break;
            case 2:printf("Array before sorting\n");
                    printarray(a,n);
                    selection_sort(a,n);
                    break;
            case 3:printf("Array before sorting\n");
                    printarray(a,n);
                    insertion_sort(a,n);
                    break;
            case 4:printf("\nThank you and have a nice day\n");
                    exit(0);
            default:printf("\nInvalid choice!!\n");
        }
    }
    return 0;
}
