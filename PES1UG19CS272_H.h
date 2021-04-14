//represents the vertex structure
typedef struct vertex_structure{
    int weight; 
    int destination;
    struct vertex_structure *next_vertex;
}vertex;
//this points to the head vertex in a list
typedef struct adjacency_list_structure{
   vertex *head_vertex;
}adjacency_list;
//represents the graph as an adjacency list
typedef struct graph_structure{
    int num_vertices;
    adjacency_list *array_list;
}graph;
//represents a single node in a heap structure
typedef struct heap_node_structure{
    int vertex;
    int distance;
    int previous;
}heap_node;
//this forms the min heap structure
typedef struct min_heap_structure{
    int capacity;    
    int current_size; 
    int *index_array;   
    heap_node **array_heap_nodes;
}min_heap;

//function to get new vertex
vertex *get_new_vertex(int, int);
//function to get new graph structure
graph *get_new_graph(int);
//inserts a vertex into the graph
void insert_vertex(graph *, int, int, int);
//gets a new node for the heap structure
heap_node *get_new_heap_node(int, int);
//gets a new min heap structure
min_heap *get_new_min_heap(int);
//swaps any two nodes in the heap structure
void swap_heap_nodes(heap_node **, heap_node **);
//min heapifies the min heap structure
void min_heapify(min_heap *, int);
//returns 1 or 0 if its empty or not
int is_heap_empty(min_heap *);
//obtains the node with minimum distance
heap_node *extract_min_node(min_heap *);
//updates the distance values in min heap strucutre
void update(min_heap *, int, int, int);
//checks if node is in the min heap structure
int is_in_heap(min_heap *, int);
//displays the solution
void display_solution(int dist[], int, int, min_heap *);
//helper function to display the solution path 
void display_path(min_heap *, int);
//implementation of the dijkstra algorithm
void dijkstra(graph *, int);