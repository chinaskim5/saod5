#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
    int nvertices;
    int *m;
    int *visited;
} graph;

graph *graph_create(int nvertices);
void graph_clear(graph *g);
void graph_free(graph *g);
void graph_set_edge(graph *g, int i, int j, int w);
int graph_get_edge(graph *g, int i, int j);

void graph_print(graph *g);
int is_adj(graph *g, int v1, int v2);

#endif
