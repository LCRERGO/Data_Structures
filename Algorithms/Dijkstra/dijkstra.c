#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Adjacency Node List */
typedef struct adj_list_node AdjListNode;
struct adj_list_node {
    int dest;
    int weight;
    AdjListNode *next;
};

/* Adjacency List */
typedef struct adj_list AdjList;
struct adj_list 
{
    AdjListNode *head;
};

/* The graph, V is the number of vertices */
typedef struct graph Graph;
struct graph {
    int V;
    AdjList *array;
};

typedef struct min_heap_node MinHeapNode;
struct min_heap_node
{
    int v;
    int dist;
};

typedef struct min_heap MinHeap;
struct min_heap
{
    int size;
    int capacity;
    int *pos;
    MinHeapNode **array;
};

/* graph related functions */
AdjListNode *
new_adj_adj_list_node(int dest, int weight)
{
    AdjListNode * new_node =
        (AdjListNode *)malloc(sizeof(AdjListNode));

    new_node->dest = dest;
    new_node->weight = weight;
    new_node->next = NULL;

    return new_node;
}

Graph *
create_graph(int V)
{
    int i;
    Graph *graph;

    graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList *)malloc(V * sizeof(AdjList));

    for (i = 0; i < V; i++)
        graph->array[i].head = NULL;

    return graph;
}

void
add_edge(Graph *graph, int src, int dest, int weight)
{
    AdjListNode *new_node = new_adj_adj_list_node(dest, weight);
    new_node->next = graph->array[src].head;
    graph->array[src].head = new_node;

    /* In case the graph is undirected */
    new_node = new_adj_adj_list_node(src, weight);
    new_node->next = graph->array[dest].head;
    graph->array[dest].head = new_node;
}

/* heap related functions */
MinHeapNode *
new_min_heap_node(int v, int dist)
{
    MinHeapNode * min_heap_node =
        (MinHeapNode *)malloc(sizeof(MinHeapNode));

    min_heap_node->v = v;
    min_heap_node->dist = dist;
    return min_heap_node;
}

MinHeap *
create_min_heap(int capacity)
{
    MinHeap *min_heap;

    min_heap =
        (MinHeap *)malloc(sizeof(MinHeap));
    min_heap->pos = (int *) malloc(capacity * sizeof(int));
    min_heap->size = 0;
    min_heap->capacity = capacity;
    min_heap->array =
        (MinHeapNode **)malloc(capacity * sizeof(MinHeap));

    return min_heap;
}

void
swap_min_heap_node(MinHeapNode **a, MinHeapNode **b)
{
    MinHeapNode *t;
    t = *a;
    *a = *b;
    *b = t;
}

void
min_heapify(MinHeap *min_heap, int idx)
{
    int smallest;
    const int left = 2 * idx + 1, right = 2 * idx + 2;
    smallest = idx;

    if (left < min_heap->size &&
            min_heap->array[left]->dist < min_heap->array[smallest]->dist)
        smallest = left;

    if (right < min_heap->size &&
            min_heap->array[right]->dist < min_heap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx)
    {
        MinHeapNode *smallest_node = min_heap->array[smallest];
        MinHeapNode *idx_node = min_heap->array[idx];

        min_heap->pos[smallest_node->v] = idx;
        min_heap->pos[idx_node->v] = smallest;

        swap_min_heap_node(&min_heap->array[smallest], &min_heap->array[idx]);
        min_heapify(min_heap, smallest);    
    }
}

int
is_empty(MinHeap * min_heap) {
    return min_heap->size == 0;
}

MinHeapNode *
extract_min(MinHeap *min_heap)
{
    if (is_empty(min_heap))
        return NULL;
    MinHeapNode *root, *last_node;

    root = min_heap->array[0];
    last_node = min_heap->array[min_heap->size - 1];
    min_heap->array[0] = last_node;

    min_heap->pos[root->v] = min_heap->size - 1;
    min_heap->pos[last_node->v] = 0;

    --min_heap->size;
    min_heapify(min_heap, 0);

    return root;
}

void
decrease_key(MinHeap * min_heap, int v, int dist)
{
    int i = min_heap->pos[v];
    min_heap->array[i]->dist = dist;

    while (i && min_heap->array[i]->dist < min_heap->array[(i-1) / 2]->dist) {
        min_heap->pos[min_heap->array[i]->v] = (i-1)/2;
        min_heap->pos[min_heap->array[(i-1)/2]->v] = i;
        swap_min_heap_node(&min_heap->array[i], &min_heap->array[(i-1) / 2]);

        i = (i-1)/2;
    }
}


int
is_in_min_heap(MinHeap *min_heap, int v)
{
    if (min_heap->pos[v] < min_heap->size)
        return 1;
    return 0;
}

void
print_arr(int dist[], int n)
{
    int i;

    printf("Vertex Distance from Source\n");
    for(i = 0; i < n; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

void
dijkstra(Graph *graph, int src)
{
    int V = graph->V;
    int dist[V];
    MinHeap *min_heap = create_min_heap(V);

    for (int v = 0; v < V; v++) {
        dist[v] = INT_MAX;
        min_heap->array[v] = new_min_heap_node(v, dist[v]);
        min_heap->pos[v] = v;
    }

    min_heap->array[src] = new_min_heap_node(src, dist[src]);
    min_heap->pos[src] = src;
    dist[src] = 0;
    decrease_key(min_heap, src, dist[src]);

    min_heap->size = V;

    while (!is_empty(min_heap)) {
        MinHeapNode *min_heap_node = extract_min(min_heap);
        int u = min_heap_node->v;

        AdjListNode *p_crawl = graph->array[u].head;
        while (p_crawl) {
            int v = p_crawl->dest;

            if (is_in_min_heap(min_heap, v) && dist[u] != INT_MAX &&
                    p_crawl->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + p_crawl->weight;
                decrease_key(min_heap, v, dist[v]);
            }
            p_crawl = p_crawl->next;
        }
    }

    print_arr(dist, V);
}

int
main(int argc, char *argv[])
{
    int V = 9; 
    Graph *graph = create_graph(V); 
    add_edge(graph, 0, 1, 4); 
    add_edge(graph, 0, 7, 8); 
    add_edge(graph, 1, 2, 8); 
    add_edge(graph, 1, 7, 11); 
    add_edge(graph, 2, 3, 7); 
    add_edge(graph, 2, 8, 2); 
    add_edge(graph, 2, 5, 4); 
    add_edge(graph, 3, 4, 9); 
    add_edge(graph, 3, 5, 14); 
    add_edge(graph, 4, 5, 10); 
    add_edge(graph, 5, 6, 2); 
    add_edge(graph, 6, 7, 1); 
    add_edge(graph, 6, 8, 6); 
    add_edge(graph, 7, 8, 7); 

    dijkstra(graph, 0); 

    return 0;
}
