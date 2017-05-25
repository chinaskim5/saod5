#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

/*          CREATE          */
heap *heap_create(int maxsize)
{
    heap *h = malloc(sizeof(*h));
    if (h) {
        h->maxsize = maxsize;
        h->nnodes = 0;
        h->nodes = malloc(sizeof(*h->nodes) * (maxsize + 1));
        if (!h->nodes) {
            free(h);
            return NULL;
        }
    }
    return h;
}

/*          FREE          */
void heap_free(heap *h)
{
    if (h) {
        if (h->nodes)
            free(h->nodes);
        free(h);
    }
}

/*          SWAP          */
void heap_swap(heapnode *a, heapnode *b)
{
    heapnode tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

/*          MIN          */
heapnode *heap_min(heap *h)
{
    if (h->nnodes == 0)
        return NULL;
    return &h->nodes[1];
}

/*          INSERT          */
int heap_insert(heap *h, int key, int value)
{
    if (h->nnodes >= h->maxsize) {
        return -1;
    }

    h->nnodes++;
    h->nodes[h->nnodes].key = key;
    h->nodes[h->nnodes].value = value;

    int i;
    for (i = h->nnodes; i > 1 && h->nodes[i].key < h->nodes[i / 2].key; i /= 2)
        heap_swap(&h->nodes[i], &h->nodes[i / 2]);

    return 0;
}

/*          EXTRACT_MIN          */
heapnode heap_extract_min(heap *h)
{
    if (h->nnodes == 0)
        return (heapnode){0, 0};
    heapnode maxnode = h->nodes[1];
    h->nodes[1] = h->nodes[h->nnodes];
    h->nnodes--;
    heap_heapify(h, 1);

    return maxnode;
}

/*          HEAPIFY          */
void heap_heapify(heap *h, int index)
{
    for (;;) {
        int left = 2 * index;
        int right = 2 * index + 1;

        int smallest = index;
        if (left <= h->nnodes && h->nodes[left].key < h->nodes[index].key)
            smallest = left;
        if (right <= h->nnodes && h->nodes[right].key < h->nodes[smallest].key)
            smallest = right;

        if (smallest == index)
            break;

        heap_swap(&h->nodes[index], &h->nodes[smallest]);
        index = smallest;
    }
}

/*          DECREASE_KEY          */
int heap_decrease_key(heap *h, int index, int key)
{
    if (h->nodes[index].key < key)
        return -1;

    h->nodes[index].key = key;
    for (; index > 1 && h->nodes[index].key < h->nodes[index / 2].key; index /= 2)
        heap_swap(&h->nodes[index], &h->nodes[index / 2]);

    return index;
}
