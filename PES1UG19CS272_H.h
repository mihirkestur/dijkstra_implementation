extern int DEBUG;
extern int num_vertices;

//vertex structure
typedef struct vertex_structure{
    int weight;
    struct vertex_structure *next_vertex_node;
}vertex;

//adjacency list containing all vertices
typedef struct adjacency_list_structure{
    int vertex_number;
    vertex *head_vertex;
    struct adjaceny_list_structure *next_list_node;
}list;

//read the inputs in the file and store the content in the adjacency list
void read_and_store();
//gets new vertex node
vertex *get_vertex_node(int, vertex *);
//gets adjacency list node
list *get_list_node(int, vertex *, list *);