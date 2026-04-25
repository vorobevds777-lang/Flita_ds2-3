#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int u;
    int v;
};

int main() {
    setlocale(LC_ALL, "RU");
    FILE *f = fopen("graph.txt", "r");
    if (f == NULL) {
        printf("Файл graph.txt не найден\n");
        return 1;
    }

    int n, m;
    fscanf(f, "%d %d", &n, &m);

    int inc[100][100];
    printf("Матрица инцидентности (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(f, "%d", &inc[i][j]);
            printf("%d ", inc[i][j]);
        }
        printf("\n");
    }
    fclose(f);

    struct Edge edges[100];
    // Преобразуем матрицу инцидентности в список рёбер
    for (int j = 0; j < m; j++) {
        int v1 = -1, v2 = -1;
        for (int i = 0; i < n; i++) {
            if (inc[i][j] != 0){
                if (v1 == -1) v1 = i;
                else v2 = i;
            }
        }
        edges[j].u = v1;
        if (v2 == -1) {
            edges[j].v = v1;
        }
        else {
            edges[j].v = v2;
        }
    }

    printf("\nСписок рёбер:\n");
    for (int j = 0; j < m; j++)
        printf("V%d -- V%d\n", edges[j].u + 1, edges[j].v + 1);
        
    
    int visited[100] = {0};
    // Создаём матрицу смежности
    int adj[100][100] = {{0}};
    for (int j = 0; j < m; j++) {
        adj[edges[j].u][edges[j].v] = 1;
        adj[edges[j].v][edges[j].u] = 1;
    }

    int stack[100], top = -1;
    stack[++top] = 0;
    visited[0] = 1;
    while (top >= 0) {
        int v = stack[top--];
        for (int i = 0; i < n; i++){
            if (adj[v][i]==1 && visited[i]==0) {
                visited[i] = 1;
                stack[++top] = i;
            }
        }
    }

    int connected = 1;
    for (int i = 0; i < n; i++)
        if (!visited[i]) connected = 0;
        printf("\nГраф ");
        if (connected) {
        printf("связный\n");
        }
        else {
        printf("НЕ связный\n");
        }

    FILE *dot = fopen("graph.dot", "w");
    if (dot != NULL) {
        fprintf(dot, "graph G {\n");
        for (int j = 0; j < m; j++)
            fprintf(dot, "  V%d -- V%d\n", edges[j].u + 1, edges[j].v + 1);
        fprintf(dot, "}\n");
        fclose(dot);
        printf("\nСоздан файл graph.dot для визуализации\n");
        printf("Чтобы увидеть граф, выполните: dot -Tpng graph.dot -o graph.png\n");
    }

    return 0;
