//vertex structure
typedef struct vertex_structure{
    int weight;
    int destination_vertex;
    struct vertex_structure *next_vertex;
}vertex;

//adjacency list 
typedef struct adjacency_list_structure{
    vertex *head_vertex;
}adjacency_list;

//graph structure
typedef struct graph_structure{
    adjacency_list *array_list;
    int num_vertices;
}graph;

//initialise the graph structure
graph *initialise_graph(int);
//gets new vertex node
vertex *get_vertex(int, int);
//insert the vertex
void insert_vertex(adjacency_list *, int, int);

//read the inputs in the file and store the content in the adjacency list
void read_and_store(graph *);
//display graph
void display_graph(graph *);
void dijkstra();