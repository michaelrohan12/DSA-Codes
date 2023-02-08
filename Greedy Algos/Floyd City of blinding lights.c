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

int min(int a,int b)
{
    if(a<b)
        return a;
    else
        return b;
}

void floyd(int* road_from,int* road_to,int* road_weight,int road_edges,int road_nodes,int D[road_nodes][road_nodes]){
    int i,j,k;
    for(i=0;i<road_nodes;i++){
        for(j=0;j<road_nodes;j++){
            if(i!=j)
                D[i][j]=701;
            else
                D[i][j]=0;
        }
    }
    for(i=0;i<road_edges;i++){
        D[road_from[i]-1][road_to[i]-1]=road_weight[i];
    }
    for(int k=0;k<road_nodes;k++)
        for(int i=0;i<road_nodes;i++)
            for(int j=0;j<road_nodes;j++)
                    D[i][j]= min(D[i][j],D[i][k] + D[k][j]);
}


int main()
{
    char** road_nodes_edges = split_string(rtrim(readline()));

    int road_nodes = parse_int(*(road_nodes_edges + 0));
    int road_edges = parse_int(*(road_nodes_edges + 1));

    int* road_from = malloc(road_edges * sizeof(int));
    int* road_to = malloc(road_edges * sizeof(int));
    int* road_weight = malloc(road_edges * sizeof(int));

    for (int i = 0; i < road_edges; i++) {
        char** road_from_to_weight = split_string(ltrim(readline()));

        int road_from_temp = parse_int(*(road_from_to_weight + 0));
        int road_to_temp = parse_int(*(road_from_to_weight + 1));
        int road_weight_temp = parse_int(*(road_from_to_weight + 2));

        *(road_from + i) = road_from_temp;
        *(road_to + i) = road_to_temp;
        *(road_weight + i) = road_weight_temp;
    }

    int D[road_nodes][road_nodes];
    floyd(road_from,road_to,road_weight,road_edges,road_nodes,D);

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int x = parse_int(*(first_multiple_input + 0));

        int y = parse_int(*(first_multiple_input + 1));

        if(D[x-1][y-1]!=701)
            printf("%d\n",D[x-1][y-1]);
        else
            printf("-1\n");
    }
    for(int i=0;i<road_nodes;i++){
        for(int j=0;j<road_nodes;j++){
            printf("%d\t",D[i][j]);
        }
        printf("\n");
    }

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
