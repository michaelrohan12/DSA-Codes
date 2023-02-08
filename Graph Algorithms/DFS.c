#include<stdio.h>

int v = 5;
int m[5][5] = {{0,1,1,0,0}, {1,0,0,1,1}, {1,0,0,0,1}, {0,1,0,0,0},
{0,1,1,0,0}};
int source = 4, visited[10];

void dfs(int m[5][5], int v, int source) {
    int i;
    visited[source] = 1;
    for(i=0; i<v; i++) {
            if(m[source][i] == 1 && visited[i] == 0) {
                printf("%d\t", i);
                dfs(m, v, i);
            }
    }
}

int main() {
    int i;
    for (i= 0; i < v; i ++)
        visited[i] = 0;
    printf("The DFS Traversal is... \n");
    printf("%d\t", source);
    dfs(m, v, source);
    return 0;
}

