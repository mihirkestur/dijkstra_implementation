#include<stdio.h>
#include<stdlib.h>
#include "PES1UG19CS272_H.h"

//allocates memory for a graph structure 
graph *create_graph(){
    graph *new_graph = (graph *)malloc(sizeof(graph));
    return new_graph;
}
//initialise the graph structure
graph *initialise_graph(graph *new_graph){
    new_graph->array_list = (adjacency_list *)malloc(new_graph->num_vertices * sizeof(adjacency_list));
    for (int i = 1; i <= new_graph->num_vertices; i++){
        new_graph->array_list[i].head_vertex = NULL;  
    }
    return new_graph;
}
//gets a new vertex given values
vertex *get_vertex(int destination_vertex, int weight){
    vertex *new_vertex = (vertex *)malloc(sizeof(vertex));
    new_vertex->weight = weight;
    new_vertex->destination_vertex = destination_vertex;
    new_vertex->next_vertex = NULL;
    return new_vertex;
}
//insert the vertex into the list
void insert_vertex(adjacency_list *list, vertex *new_vertex){
    if(list->head_vertex == NULL){
        list->head_vertex = new_vertex;
        return;
    }
    else{        
        vertex *traverse = list->head_vertex;
        while(traverse->next_vertex){
            traverse = traverse->next_vertex;
        }
        traverse->next_vertex = new_vertex;
    }
}
//display the graph
void display_graph(graph *input_graph){
    for(int i = 1; i <= input_graph->num_vertices; i++){
        vertex *temp = input_graph->array_list[i].head_vertex;
        while(temp){
            printf("%d %d ",temp->destination_vertex,temp->weight);
            temp = temp->next_vertex;
        }
        printf("\n");
    }
    
}
//read from input file and store it in the graph
void read_and_store(graph *input_graph){
    int flag = 1;
    FILE *file_ptr = fopen("adjacencylist.txt","r");
    if(file_ptr == NULL){
        printf("No such file exists\n");
        return;
    }
    char line[1000];
    while(fgets(line, sizeof(line), file_ptr)){
        int number, size = 0, n, temp[1000];
        char *start = line;
        if(flag){
            flag = 0;
            input_graph->num_vertices = atoi(line);
            initialise_graph(input_graph);
        }
        else{
            while(sscanf(start, "%d%n", &number, &n) == 1){
                start = start + n;
                temp[size] = number;
                ++size;
            }
            for(int i=1;i<size;i=i+2){
                insert_vertex(&input_graph->array_list[temp[0]], get_vertex(temp[i], temp[i+1]));
            }
        }
    }
    fclose(file_ptr);
}
