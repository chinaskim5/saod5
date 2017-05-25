#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

/*          CREATE          */
graph *graph_create(int nvertices)
{
    graph *g = malloc(sizeof(*g));
    g->nvertices = nvertices;
    g->visited = malloc(sizeof(int) * nvertices);
    g->m = malloc(sizeof(int) * nvertices * nvertices);

    graph_clear(g);

    return g;
}

/*          CLEAR          */
void graph_clear(graph *g)
{
    int i, j;
    for (i = 0; i < g->nvertices; i++) {
        g->visited[i] = 0;
        for (j = 0; j < g->nvertices; j++)
            if (i  == j)
                g->m[i * g->nvertices + j] = 0;
            else
                g->m[i * g->nvertices + j] = 65536;
    }
}

/*          FREE          */
void graph_free(graph *g)
{
    if (g) {
        if (g->m)
            free(g->m);
        free(g);
    }
}

/*          SET_EDGE          */
void graph_set_edge(graph *g, int i, int j, int w)
{
    g->m[(i) * g->nvertices + j ] = w;
    g->m[(j) * g->nvertices + i ] = w;
}

/*          GET_EDGE          */
int graph_get_edge(graph *g, int i, int j)
{
    return g->m[(i) * g->nvertices + j ];
}

/*          PRINT          */
void graph_print(graph *g)
{
    int i, j;
    for (i = 0; i < g->nvertices; i++) {
        for (j = 0; j < g->nvertices; j++)
            if (g->m[i * g->nvertices + j] != 65536)
                printf("%3d ", g->m[i * g->nvertices + j]);
            else
                printf("INF ");
        printf("\n");
    }
}

/*          IS_ADJ          */
int is_adj(graph *g, int v1, int v2)
{
    if (g->m[(v1) * g->nvertices + v2 ] > 0 && g->m[v1 * g->nvertices + v2] < 65536)
        return 1;
    return 0;
}

