#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "PES1UG19CS272_H.h"

vertex *get_new_vertex(int destination, int weight){
    vertex *new_vertex = (vertex *)malloc(sizeof(vertex));
    new_vertex->weight = weight;
    new_vertex->destination = destination;
    new_vertex->next_vertex = NULL;
    return new_vertex;
}

graph *get_new_graph(int num_vertices){
    graph *new_graph = (graph *)malloc(sizeof(graph));
    new_graph->num_vertices = num_vertices + 1;
    new_graph->array_vertices = (adjacency_list *)malloc(new_graph->num_vertices * sizeof(adjacency_list));
    for (int i = 1; i < num_vertices; ++i){
        new_graph->array_vertices[i].head_vertex = NULL;
    }
    return new_graph;
}


void insert_vertex(graph *input_graph, int source, int destination, int weight){
    // Add an edge from src to dest. 
    // A new node is added to the adjacency
    // list of src.  The node is
    // added at the beginning
    vertex* newNode = get_new_vertex(destination, weight);
    newNode->next_vertex = input_graph->array_vertices[source].head_vertex;
    input_graph->array_vertices[source].head_vertex = newNode;
}

//head functions
heap_node *get_new_heap_node(int vertex, int distance){
    heap_node *new_heap_node = (heap_node*)malloc(sizeof(heap_node));
    new_heap_node->distance = distance;
    new_heap_node->vertex = vertex;
    new_heap_node->previous = -1;
    return new_heap_node;
}

min_heap *get_new_min_heap(int num_vertices){
    min_heap *new_min_heap = (min_heap *)malloc(sizeof(min_heap));
    new_min_heap->index_array = (int *)malloc(num_vertices * sizeof(int));
    new_min_heap->current_size = 0;
    new_min_heap->capacity = num_vertices;
    new_min_heap->array_heap_nodes = (heap_node **)malloc(num_vertices * sizeof(heap_node *));
    return new_min_heap;
}

void swap_heap_nodes(heap_node **first, heap_node **second){
    heap_node *temp_node = *first;
    *first = *second;
    *second = temp_node;
}

void min_heapify(min_heap *input_heap, int idx){
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx;
    right = 2 * idx + 1;

    if(left <= input_heap->current_size && input_heap->array_heap_nodes[left]->distance < input_heap->array_heap_nodes[smallest]->distance){
        smallest = left;
    }
      
    if(right <= input_heap->current_size && input_heap->array_heap_nodes[right]->distance < input_heap->array_heap_nodes[smallest]->distance){
        smallest = right;
    }

    if(smallest != idx){
        
        heap_node *smallestNode = input_heap->array_heap_nodes[smallest];
        heap_node *idxNode = input_heap->array_heap_nodes[idx];

        input_heap->index_array[smallestNode->vertex] = idx;
        input_heap->index_array[idxNode->vertex] = smallest;
 
        swap_heap_nodes(&input_heap->array_heap_nodes[smallest], &input_heap->array_heap_nodes[idx]);
 
        min_heapify(input_heap, smallest);
    }
}

int is_heap_empty(min_heap *input_heap){
    return input_heap->current_size == 0;
}

heap_node *extract_min_node(min_heap *input_heap){
    if (is_heap_empty(input_heap)){
        return NULL;
    }
 
    heap_node* root = input_heap->array_heap_nodes[1];
    heap_node* lastNode = input_heap->array_heap_nodes[input_heap->current_size];
    input_heap->array_heap_nodes[1] = lastNode;
    input_heap->array_heap_nodes[input_heap->current_size] = root;

    input_heap->index_array[root->vertex] = input_heap->current_size;
    input_heap->index_array[lastNode->vertex] = 1;

    --input_heap->current_size;
    min_heapify(input_heap, 1);
    heap_node* newlastNode = input_heap->array_heap_nodes[input_heap->current_size];

    return root;
}

void update(min_heap *input_heap, int v, int u, int dist){
    int i = input_heap->index_array[v];

    input_heap->array_heap_nodes[i]->distance = dist;
    input_heap->array_heap_nodes[i]->previous = u;

    while (i > 1 && input_heap->array_heap_nodes[i]->distance < input_heap->array_heap_nodes[i / 2]->distance){
        // Swap this node with its parent
        input_heap->index_array[input_heap->array_heap_nodes[i]->vertex] = i/2;
        input_heap->index_array[input_heap->array_heap_nodes[i/2]->vertex] = i;
        swap_heap_nodes(&input_heap->array_heap_nodes[i], &input_heap->array_heap_nodes[i / 2]);
 
        // move to parent index
        i = i / 2;
    }
}

int is_in_heap(min_heap *input_heap, int v){
    if (input_heap->index_array[v] <= input_heap->current_size){
        return 1;
    }
    return 0;
}

void display_solution(int dist[], int n, int src, min_heap *heap){
    for (int i = 1; i < n; ++i) {
        if(i == src){
            continue;
        }
        printf("vertex => %d :\t", i);
        display_path(heap,i,src);
        if(dist[i] != INT_MAX) {
            printf("%d \n", dist[i]);
        } 
        else{
            printf("\n");
        }
    }
}

void display_path(min_heap *input_heap, int i, int src){

    int pos = input_heap->index_array[i];
    heap_node* min_node = input_heap->array_heap_nodes[pos];
    int p = min_node->previous;
    if (p == -1) {
        printf("NO PATH ");
        return;
    }
    printf("%d ", i);
    while (min_node->previous != 0) {
        p = min_node->previous;
        printf("%d ", p);
        pos = input_heap->index_array[p];
        min_node = input_heap->array_heap_nodes[pos];
    }
}

void dijkstra(graph *input_graph, int source){
    
    int num_vertices = input_graph->num_vertices;
    int distance[num_vertices];    
 
    min_heap *input_heap = get_new_min_heap(num_vertices);
 
    for (int i = 1; i < num_vertices; ++i){
        distance[i] = INT_MAX;
        input_heap->array_heap_nodes[i] = get_new_heap_node(i, distance[i]);
        input_heap->index_array[i] = i;
    }
 
    input_heap->index_array[source] = source;
    distance[source] = 0;

    update(input_heap, source, 0, distance[source]);

    input_heap->current_size = input_graph->num_vertices - 1;
   
    while(!is_heap_empty(input_heap)){

        heap_node *min_node = extract_min_node(input_heap);
        int min_node_vertex = min_node->vertex;

        vertex *traverse = input_graph->array_vertices[min_node_vertex].head_vertex;
        while(traverse != NULL){
            int dest_vertex = traverse->destination;
            if(is_in_heap(input_heap, dest_vertex) && distance[min_node_vertex] != INT_MAX && ((traverse->weight + distance[min_node_vertex]) < distance[dest_vertex])){
                distance[dest_vertex] = distance[min_node_vertex] + traverse->weight;
                update(input_heap, dest_vertex, min_node_vertex, distance[dest_vertex]);
            }
            traverse = traverse->next_vertex;
        }
    }
    display_solution(distance, num_vertices, source, input_heap);
}