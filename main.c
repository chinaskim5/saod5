#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "graph.h"

#define SIZE 4

int shortest_path(graph *g, int src, int *d, int *prev)
{
    int i, u, v;
    heap *q = heap_create(100);
    heapnode ver;

    for (i = 0; i < g->nvertices; i++) {
        if (i != src) {
            d[i] = 65536;
            prev[i] = -1;
            heap_insert(q, i, d[i]);
        }
    }

    d[src] = 0;
    prev[src] = -1;
    heap_insert(q, src, d[src]);

    for (i = 0; i < g->nvertices; i++) {
        ver = heap_extract_min(q);
        v = ver.key;
        g->visited[v] = 1;

        for (u = 0; u < g->nvertices; u++) {
            if (is_adj(g, u, v) /*&& !g->visited[u]*/) {
                int alt = graph_get_edge(g, v, u);
                printf("\tEdge: (%d %d) = %d\n", v + 1, u + 1, alt);
                printf("D[v] = %d     D[u] = %d\n", d[v], d[u]);
                if (d[v] + alt < d[u]) {
                    d[u] = d[v] + alt;
                    prev[u] = v;
                    heap_decrease_key(q, u, alt);
                }
            }
        }
    }

    return 0;
}

int find_path(graph *g, int src, int dst)
{
    int d[g->nvertices], prev[g->nvertices], i;
    shortest_path(g, src, d, prev);

    printf("D: ");
    for (i = 0; i < g->nvertices; i++)
        printf("%d ", d[i]);
    printf("\n");

    printf("PREV: ");
    for (i = 0; i < g->nvertices; i++)
        printf("%d ", prev[i]);
    printf("\n");


    int  pathlen = 1, j;
    i = dst;
    while (i != src) {
        pathlen++;
        i = prev[i];
    }
/*
    j = 0;
    i = dst;

    while (i != src) {
        path[pathlen - j] = i;
        i = prev[i];
        j++;
    }
*/
    return pathlen;
}

int main()
{
    FILE *f = fopen("graph.txt", "r");
    graph *g;
    if (!f) {
        g = graph_create(4);
        graph_set_edge(g, 0, 1, 8);
        graph_set_edge(g, 0, 2, 4);
        graph_set_edge(g, 1, 2, 3);
        graph_set_edge(g, 1, 3, 6);
        graph_set_edge(g, 2, 3, 5);
        graph_print(g);
    }
    else {
        int size = 0, v1 = -1, v2 = -1, w = -1;
        if (!fscanf(f, "%d", &size) || size <= 0 || size > 20) {
            printf("Invalid size!\n");
            return 1;
        }
        g = graph_create(size);

        while (!feof(f)) {
            if (!fscanf(f, "%d %d %d", &v1, &v2, &w) || v1 <= 0 || v2 <= 0 || w <= 0 || v1 > size || v2 > size || w > 999) {
                printf("Invalid data\n");
                return 1;
            }
            graph_set_edge(g, v1 - 1, v2 - 1, w);
        }
        fclose(f);
    }

    printf("GRAPH:\n");
    graph_print(g);
    find_path(g, 0, 1);
    graph_free(g);

    return 0;
}
