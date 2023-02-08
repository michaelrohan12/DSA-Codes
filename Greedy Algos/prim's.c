#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000000
char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'prims' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY edges
 *  3. INTEGER start
 */

 int min(int a,int b,int* path,int i,int start)
{
    if(a<b)
        return a;
    else{
        path[i]=start;
        return b;
    }
}

int prims(int n, int edges_rows, int edges_columns, int** edges, int start) {
    int i,j,arr[n+1][n+1];
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(i!=j)
                arr[i][j] = MAX;
            else
                arr[i][j] = 0;

    for(i=0;i<edges_rows;i++){
        if(arr[edges[i][0]][edges[i][1]]>edges[i][2]){
            arr[edges[i][0]][edges[i][1]]=edges[i][2];
            arr[edges[i][1]][edges[i][0]]=edges[i][2];
        }
    }

    int dist[n+1],path[n+1],visited[n+1],min_wt,min_index,flag1=1,flag2=1,total=0;
    for(i=1;i<=n;i++)
        path[i] = start;
    for(i=1;i<=n;i++)
        dist[i] = arr[start][i];
    memset(visited,0,(n+1)*sizeof(int));
    visited[start] = 1;
    while(flag1)
    {
        flag1=0;
        flag2=1;
        for(i=1;i<=n;i++)
        {
            if(visited[i]==0){
                flag1=1;
                if(flag2){
                    flag2=0;
                    dist[i]=min(dist[i],arr[start][i],path,i,start);
                    min_wt=dist[i];
                    min_index=i;
                }
                else{
                    dist[i]=min(dist[i],arr[start][i],path,i,start);
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
        start=min_index;
        total+=min_wt;
    }
    printf("%d",total);
    return total;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int m = parse_int(*(first_multiple_input + 1));

    int** edges = malloc(m * sizeof(int*));

    for (int i = 0; i < m; i++) {
        *(edges + i) = malloc(3 * (sizeof(int)));

        char** edges_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 3; j++) {
            int edges_item = parse_int(*(edges_item_temp + j));

            *(*(edges + i) + j) = edges_item;
        }
    }

    int start = parse_int(ltrim(rtrim(readline())));

    int result = prims(n, m, 3, edges, start);

    fprintf(stdout, "%d\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}

