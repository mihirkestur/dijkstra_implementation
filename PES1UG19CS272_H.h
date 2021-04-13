typedef struct vertex_structure{
    int weight;
    int destination;
    struct vertex_structure *next_vertex;
}vertex;

typedef struct adjacency_list_structure{
   vertex *head_vertex;
}adjacency_list;

typedef struct graph_structure{
    int num_vertices;
    adjacency_list *array_vertices;
}graph;

typedef struct heap_node_structure{
    int vertex;
    int distance;
    int previous;
}heap_node;

typedef struct min_heap_structure{
    int capacity;    
    int current_size; 
    int *index_array;   
    heap_node **array_heap_nodes;
}min_heap;


vertex *get_new_vertex(int, int);
graph *get_new_graph(int);
void insert_vertex(graph *, int, int, int);


heap_node *get_new_heap_node(int, int);
min_heap *get_new_min_heap(int);
void swap_heap_nodes(heap_node **, heap_node **);
void min_heapify(min_heap *, int);
int is_heap_empty(min_heap *);
heap_node *extract_min_node(min_heap *);
void update(min_heap *, int, int, int);
int is_in_heap(min_heap *, int);
void display_solution(int dist[], int, int, min_heap *);
void display_path(min_heap *, int, int);
void dijkstra(graph *, int);