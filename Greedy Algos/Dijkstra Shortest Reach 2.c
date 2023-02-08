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

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);


int index=0;

int min(int a,int b,int* path,int s)
{
    if(a<b)
        return a;
    else{
        path[index]=s;
        return b;
    }
}
/*
 * Complete the 'shortestReach' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY edges
 *  3. INTEGER s
 */

/*
 * To return the integer array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * int* return_integer_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static int a[5] = {1, 2, 3, 4, 5};
 *
 *     return a;
 * }
 *
 * int* return_integer_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     int *a = malloc(5 * sizeof(int));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1;
 *     }
 *
 *     return a;
 * }
 *
 */
int* shortestReach(int n, int edges_rows, int edges_columns, int** edges, int s, int* result_count) {
    int i,j,arr[n+1][n+1];
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(i==j){
                arr[i][j]=0;
            }
            else{
                arr[i][j]=999999;
            }
        }
    }

    for(i=0;i<edges_rows;i++){
        arr[edges[i][0]][edges[i][1]]=edges[i][2];
        arr[edges[i][1]][edges[i][0]]=edges[i][2];
    }

    int dist[n+1],visited[n+1],path[n+1],min_wt,min_index,flag1=1,flag2,total=0;
    memset(visited,0,(n+1)*sizeof(int));
    for(i=1;i<=n;i++)
    {
        path[i]=s;
    }
    for(i=1;i<=n;i++){
        dist[i] = arr[s][i];
    }
    visited[s]=1;
    while(flag1)
    {
        flag1=0;
        flag2=1;
        for(index=1;index<=n;index++)
        {
            if(visited[index]==0){
                flag1=1;
                if(flag2){
                    flag2=0;
                    dist[index]=min(dist[index],total+arr[s][index],path,s);
                    min_wt=dist[index];
                    min_index=index;
                }
                else{
                    dist[index]=min(dist[index],total+arr[s][index],path,s);
                    if(min_wt>dist[index]){
                        min_wt=dist[index];
                        min_index=index;
                    }
                }

            }
        }
        if(flag1==0){
            break;
        }
        visited[min_index]=1;
        s=min_index;
        total=min_wt;
    }
    int *result = malloc(n*sizeof(int));
    i=1;
    j=0;
    while(i<=n)
    {
        if(dist[i]!=0){
            *(result+j)=(*(dist+i));
            j++;
        }
        i++;
    }
    *result_count = j;
    for(i=1;i<=n;i++){
        printf("%d %d %d\n",dist[i],path[i],*result_count);
    }
    for(i=0;i<*result_count;i++){
        printf("\n%d\n",result[i]);
    }

    return result;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
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

        int s = parse_int(ltrim(rtrim(readline())));


        int result_count;
        int* result = shortestReach(n, m, 3, edges, s, &result_count);

        for (int i = 0; i < result_count; i++) {
            fprintf(fptr, "%d", *(result + i));

            if (i != result_count - 1) {
                fprintf(fptr, " ");
            }
        }

        fprintf(fptr, "\n");
    }

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
