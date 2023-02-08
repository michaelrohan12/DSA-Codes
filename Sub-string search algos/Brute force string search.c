#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int brute_force_search(char* string,char* sub_string){
    int i,j,m=strlen(sub_string),n=strlen(string);
    for(i=0;i<=(n-m);i++){
        j = 0;
        while(j<m && string[i+j]==sub_string[j]){
            j++;
        }
        if(j==m)
            return i;
    }
    return -1;
}

int main()
{
    char string[100],sub_string[100];
    printf("Enter the searching string\n");
    scanf("%[^\n]s",string);
    printf("Enter the sub-string to be searched\n");
    scanf("%s",sub_string);
    int result = brute_force_search(string,sub_string);
    if(result==-1)
        printf("String not found!!\n");
    else
        printf("String found at %d index\n",result);
    return 0;
}
