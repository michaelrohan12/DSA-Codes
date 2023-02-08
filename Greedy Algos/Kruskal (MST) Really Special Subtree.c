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

/*
 * Complete the 'kruskals' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts WEIGHTED_INTEGER_GRAPH g as parameter.
 */

/*
 * For the weighted graph, <name>:
 *
 * 1. The number of nodes is <name>_nodes.
 * 2. The number of edges is <name>_edges.
 * 3. An edge exists between <name>_from[i] and <name>_to[i]. The weight of the edge is <name>_weight[i].
 *
 */
void swap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

int Partition(int* g_from,int* g_to,int* g_weight,int l,int r)
{
    int p = g_weight[l];
    int i = l;
    int j = r+1;
    do
    {
        do
        {
            ++i;
        }while(g_weight[i]<p);
        do
        {
            --j;
        }while(g_weight[j]>p);
        swap(&g_weight[i],&g_weight[j]);
        swap(&g_from[i],&g_from[j]);
        swap(&g_to[i],&g_to[j]);
    }while(i<j);
    swap(&g_weight[i],&g_weight[j]);
    swap(&g_from[i],&g_from[j]);
    swap(&g_to[i],&g_to[j]);
    swap(&g_weight[l],&g_weight[j]);
    swap(&g_from[l],&g_from[j]);
    swap(&g_to[l],&g_to[j]);
    return j;
}

void quicksort(int* g_from,int* g_to,int* g_weight,int l,int r)
{
    if(l<r)
    {
        int s = Partition(g_from,g_to,g_weight,l,r);
        quicksort(g_from,g_to,g_weight,l,s-1);
        quicksort(g_from,g_to,g_weight,s+1,r);
    }
}

void union_find(int *a,int i,int j,int g_nodes)
{
    int k;
    for(k=1;k<=g_nodes;k++)
    {
        if(a[k]==i)
        {
            a[k]=j;
        }
    }
}

int minimum_wt(int a,int b)
{
    if(a>b)
        return 1;
    else
        return 0;
}

int kruskals(int g_nodes,int g_edges, int* g_from, int* g_to, int* g_weight) {
    int i,j,flag,min,cost=0,step=0,count=0;
    int a[g_nodes+1];
    for(i=1;i<=g_nodes;i++){
        a[i]=i;
    }
    for(i=0;i<=g_edges-2;i++){
        min=i;
        for(j=i+1;j<=g_edges-1;j++){
            if(g_weight[min]==g_weight[j])
            {
               flag = minimum_wt(g_from[min]+g_to[min]+g_weight[min],g_from[j]+g_to[j]+g_weight[j]);
                    if(flag){
                      min=j;
               }
            }
            swap(&g_weight[min],&g_weight[i]);
            swap(&g_from[min],&g_from[i]);
            swap(&g_to[min],&g_to[i]);
        }
    }
    while(count<g_nodes-1)
    {

        i=a[g_from[step]];
        j=a[g_to[step]];
        if(i!=j)
        {
            cost+=g_weight[step];
            union_find(a,i,j,g_nodes);
            count++;
        }
        step++;
    }
    return cost;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** g_nodes_edges = split_string(rtrim(readline()));

    int g_nodes = parse_int(*(g_nodes_edges + 0));
    int g_edges = parse_int(*(g_nodes_edges + 1));

    int* g_from = malloc(g_edges * sizeof(int));
    int* g_to = malloc(g_edges * sizeof(int));
    int* g_weight = malloc(g_edges * sizeof(int));

    for (int i = 0; i < g_edges; i++) {
        char** g_from_to_weight = split_string(ltrim(readline()));

        int g_from_temp = parse_int(*(g_from_to_weight + 0));
        int g_to_temp = parse_int(*(g_from_to_weight + 1));
        int g_weight_temp = parse_int(*(g_from_to_weight + 2));

        *(g_from + i) = g_from_temp;
        *(g_to + i) = g_to_temp;
        *(g_weight + i) = g_weight_temp;
    }
    quicksort(g_from,g_to,g_weight,0,g_edges-1);
    int res = kruskals(g_nodes,g_edges,g_from, g_to, g_weight);

    // Write your code here.
    fprintf(stdout,"%d\n",res);

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
