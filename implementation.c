#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "header.h"

//function to get new vertex
vertex *get_new_vertex(int destination, int weight){
    vertex *new_vertex = (vertex *)malloc(sizeof(vertex));
    new_vertex->weight = weight;
    new_vertex->destination = destination;
    new_vertex->next_vertex = NULL;
    return new_vertex;
}
//function to get new graph structure
graph *get_new_graph(int num_vertices){
    graph *new_graph = (graph *)malloc(sizeof(graph));
    new_graph->num_vertices = num_vertices + 1;
    new_graph->array_list = (adjacency_list *)malloc(new_graph->num_vertices * sizeof(adjacency_list));
    for (int i = 1; i < num_vertices; ++i){
        new_graph->array_list[i].head_vertex = NULL;
    }
    return new_graph;
}
//inserts a vertex into the graph
void insert_vertex(graph *input_graph, int source, int destination, int weight){
    vertex *new_node = get_new_vertex(destination, weight);
    //add vertex to the start of list 
    new_node->next_vertex = input_graph->array_list[source].head_vertex;
    input_graph->array_list[source].head_vertex = new_node;
}
//gets a new node for the heap structure
heap_node *get_new_heap_node(int vertex, int distance){
    heap_node *new_heap_node = (heap_node*)malloc(sizeof(heap_node));
    new_heap_node->distance = distance;
    new_heap_node->vertex = vertex;
    new_heap_node->previous = -1;
    return new_heap_node;
}
//gets a new min heap structure
min_heap *get_new_min_heap(int num_vertices){
    min_heap *new_min_heap = (min_heap *)malloc(sizeof(min_heap));
    new_min_heap->index_array = (int *)malloc(num_vertices * sizeof(int));
    new_min_heap->array_heap_nodes = (heap_node **)malloc(num_vertices * sizeof(heap_node *));
    new_min_heap->capacity = num_vertices;
    new_min_heap->current_size = 0;
    return new_min_heap;
}
//swaps any two nodes in the heap structure
void swap_heap_nodes(heap_node **first, heap_node **second){
    heap_node *temp_node = *first;
    *first = *second;
    *second = temp_node;
}
//min heapifies the min heap structure
void min_heapify(min_heap *input_heap, int index){
    int smallest = index, left = 2 * index, right = 2 * index + 1;

    if((left <= input_heap->current_size) 
    && (input_heap->array_heap_nodes[left]->distance < input_heap->array_heap_nodes[smallest]->distance)){
        smallest = left;
    }
    if((right <= input_heap->current_size) 
    && (input_heap->array_heap_nodes[right]->distance < input_heap->array_heap_nodes[smallest]->distance)){
        smallest = right;
    }
    if(smallest != index){
        heap_node *min_node = input_heap->array_heap_nodes[smallest];
        heap_node *index_node = input_heap->array_heap_nodes[index];
        input_heap->index_array[min_node->vertex] = index;
        input_heap->index_array[index_node->vertex] = smallest;
        //swap
        swap_heap_nodes(&input_heap->array_heap_nodes[smallest], &input_heap->array_heap_nodes[index]);
        //heapify since property is disturbed
        min_heapify(input_heap, smallest);
    }
}
//returns 1 or 0 if its empty or not
int is_heap_empty(min_heap *input_heap){
    return (input_heap->current_size == 0);
}
//obtains the node with minimum distance
heap_node *extract_min_node(min_heap *input_heap){
    if(is_heap_empty(input_heap)){
        return NULL;
    }
 
    heap_node* root_node = input_heap->array_heap_nodes[1];
    heap_node* last_node = input_heap->array_heap_nodes[input_heap->current_size];
    input_heap->array_heap_nodes[1] = last_node;
    input_heap->array_heap_nodes[input_heap->current_size] = root_node;

    input_heap->index_array[root_node->vertex] = input_heap->current_size;
    input_heap->index_array[last_node->vertex] = 1;
    //decrement the current size since it is removed
    --input_heap->current_size;
    //heapify from 1
    min_heapify(input_heap, 1);
    heap_node *new_last_node = input_heap->array_heap_nodes[input_heap->current_size];
    return root_node;
}
//updates the distance values in min heap strucutre
void update(min_heap *input_heap, int dest_vertex, int min_vertex, int distance){
    int i = input_heap->index_array[dest_vertex];
    input_heap->array_heap_nodes[i]->distance = distance;
    input_heap->array_heap_nodes[i]->previous = min_vertex;
    while(i > 1 
    && (input_heap->array_heap_nodes[i]->distance < input_heap->array_heap_nodes[i / 2]->distance)){
        input_heap->index_array[input_heap->array_heap_nodes[i]->vertex] = i/2;
        input_heap->index_array[input_heap->array_heap_nodes[i/2]->vertex] = i;
        swap_heap_nodes(&input_heap->array_heap_nodes[i], &input_heap->array_heap_nodes[i / 2]);
        //move to the parent index
        i = i / 2;
    }
}
//checks if node is in the min heap structure
int is_in_heap(min_heap *input_heap, int vertex){
    //return 1 if its there else 0
    if(input_heap->index_array[vertex] <= input_heap->current_size){
        return 1;
    }
    return 0;
}
//displays the solution
void display_solution(int dist[], int num_vertices, int source, min_heap *heap){
    for(int i = 1; i < num_vertices; ++i){
        if(i == source){
            continue;
        }
        printf("%d ", i);
        display_path(heap, i);
        if(dist[i] != INT_MAX) {
            printf("%d \n", dist[i]);
        } 
        else{
            printf("\n");
        }
    }
}
//helper function to display the solution path 
void display_path(min_heap *input_heap, int vertex){
    //note the position in the index array
    int index = input_heap->index_array[vertex];
    heap_node *min_node = input_heap->array_heap_nodes[index];
    int prev = min_node->previous;
    //if theres no path
    if(prev == -1){
        printf("NO PATH ");
        return;
    }
    //if theres a path
    printf("%d ", vertex);
    while(min_node->previous != 0){
        prev = min_node->previous;
        printf("%d ", prev);
        index = input_heap->index_array[prev];
        min_node = input_heap->array_heap_nodes[index];
    }
}
//implementation of the dijkstra algorithm
void dijkstra(graph *input_graph, int source){
    //note the vertices
    int num_vertices = input_graph->num_vertices;
    int distance[num_vertices];    
    //create a min heap
    min_heap *input_heap = get_new_min_heap(num_vertices);
    /*initialize all the distances as int max (infinity), and index array holds the position of
    the nodes in the heap*/
    for (int i = 1; i < num_vertices; ++i){
        distance[i] = INT_MAX;
        input_heap->array_heap_nodes[i] = get_new_heap_node(i, distance[i]);
        input_heap->index_array[i] = i;
    }
    //set the distance of the source node as 0
    input_heap->index_array[source] = source;
    distance[source] = 0;
    //update heap structure
    update(input_heap, source, 0, distance[source]);
    //set the current size of heap structure
    input_heap->current_size = input_graph->num_vertices - 1;
    //as long as heap is not empty run loop
    while(!is_heap_empty(input_heap)){
        //get the min node
        heap_node *min_node = extract_min_node(input_heap);
        int min_node_vertex = min_node->vertex;
        //traverse through all connections for this node
        vertex *traverse = input_graph->array_list[min_node_vertex].head_vertex;
        while(traverse != NULL){
            //if theres a suitable vertex then update the graph
            int dest_vertex = traverse->destination;
            if(is_in_heap(input_heap, dest_vertex) && distance[min_node_vertex] != INT_MAX && ((traverse->weight + distance[min_node_vertex]) < distance[dest_vertex])){
                distance[dest_vertex] = distance[min_node_vertex] + traverse->weight;
                update(input_heap, dest_vertex, min_node_vertex, distance[dest_vertex]);
            }
            traverse = traverse->next_vertex;
        }
    }
    //finally display the solution
    display_solution(distance, num_vertices, source, input_heap);
}