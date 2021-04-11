#include<stdio.h>
#include<stdlib.h>
#include "PES1UG19CS272_H.h"

//initialise the graph structure
graph *initialise_graph(int num_vertices){
    graph *new_graph = (graph *)malloc(sizeof(graph));
    new_graph->array_list = (adjacency_list *)malloc(num_vertices * sizeof(adjacency_list));
    new_graph->num_vertices = num_vertices;
    for (int i = 1; i <= num_vertices; i++){
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

void insert_vertex(adjacency_list *list, int destination, int weight){
    vertex *new_vertex = get_vertex(destination,weight);
    if(list->head_vertex == NULL){
        list->head_vertex = new_vertex;
        return;
    }
    else{        
        while(list->head_vertex->next_vertex){
            list->head_vertex = list->head_vertex->next_vertex;
        }
        list->head_vertex->next_vertex = new_vertex;
    }
}

void display_graph(graph *input_graph){
    for(int i = 1; i <= input_graph->num_vertices; i++){
        vertex *temp = input_graph->array_list[i].head_vertex;
        while(temp){
            printf("dst %d  wt %d ",temp->destination_vertex,temp->weight);
            temp = temp->next_vertex;
        }
        printf("\n");
    }
    
}

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
        }
        else{
            while(sscanf(start, "%d%n", &number, &n) == 1){
                start = start + n;
                temp[size] = number;
                ++size;
            }
            for(int i=1;i<size;i=i+2){
                printf("%d  %d  %d\n",temp[0], temp[i], temp[i+1]);
                insert_vertex(&input_graph->array_list[temp[0]], temp[i], temp[i+1]);
            }
        }
    }
    fclose(file_ptr);
}
