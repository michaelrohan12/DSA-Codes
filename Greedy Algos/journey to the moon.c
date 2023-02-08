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
 * Complete the 'journeyToMoon' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY astronaut
 */
void initialize(int arr[ ],int size [],int n)
{
    for(int i=0;i<n;i++)
    {
        arr[ i ] = i ;
        size[ i ] = 1;
    }
}

int root(int arr[ ],int i)
{
    while(arr[ i ] != i)
    {
        arr[ i ] = arr[ arr[ i ] ] ;
        i = arr[ i ];
    }
    return i;
}

int Find(int *arr, int x) {
    if(arr[x] != x) {
        arr[x] = Find(arr, arr[x]);
    }
    return arr[x];
}

void weighted_union(int arr[ ],int size[ ],int A,int B)
{
    int root_A = root(arr,A);
    int root_B = root(arr,B);
    if(size[root_A] < size[root_B])
    {
        arr[ root_A ] = arr[root_B];
        size[root_B] += size[root_A];
    }
    else
    {
        arr[ root_B ] = arr[root_A];
        size[root_A] += size[root_B];
    }
}

long long journeyToMoon(int n, int astronaut_rows, int astronaut_columns, int** astronaut) {
    int i,j,a,b,arr[n],size[n];
    long long count=0;
    initialize(arr,size,n);
    for(i=0;i<astronaut_rows;i++){
        a = Find(arr, astronaut[i][astronaut_columns-2]);
        b = Find(arr,astronaut[i][astronaut_columns-1]);
        if(a != b)
            weighted_union(arr,size,astronaut[i][astronaut_columns-2],astronaut[i][astronaut_columns-1]);
    }
    int temp1[n],temp2[n],k = 0;
    for(i=0;i<n;i++) {
        if(arr[i] == i) {
            temp1[k++] = size[i];
        }
    }
    temp2[0] = temp1[0];
    for(i=1;i<k;i++) {
        temp2[i] = temp2[i-1] + temp1[i];
    }
    for(i=0;i<k-1;i++) {
        a = temp1[i];
        b = temp2[k-1] - temp2[i];
        count += a*b;
    }
    return count;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int p = parse_int(*(first_multiple_input + 1));

    int** astronaut = malloc(p * sizeof(int*));

    for (int i = 0; i < p; i++) {
        *(astronaut + i) = malloc(2 * (sizeof(int)));

        char** astronaut_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 2; j++) {
            int astronaut_item = parse_int(*(astronaut_item_temp + j));

            *(*(astronaut + i) + j) = astronaut_item;
        }
    }

    long long result = journeyToMoon(n, p, 2, astronaut);

    fprintf(stdout, "%lld\n", result);

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
