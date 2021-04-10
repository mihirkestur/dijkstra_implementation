#include<stdio.h>
#include<stdlib.h>
#include "PES1UG19CS272_H.h"
int DEBUG;
int num_vertices;
void read_and_store(){
    FILE *file_ptr = fopen("adjacencylist.txt","r");
    if(file_ptr == NULL){
        printf("No such file exists\n");
        return;
    }
    char line[1000];
    num_vertices = -1;
    while(1){
        fgets(line, sizeof(line), file_ptr);
        if(feof(file_ptr)){ 
            break;
        }
        if(num_vertices == -1){
            num_vertices = atoi(line);
        }
        if(DEBUG){
            printf("%s", line);
        }
    }
    if(DEBUG){
        printf("Vertices = %d\n", num_vertices);
    }
    fclose(file_ptr);
}

//gets adjacency list node
list *get_list_node(int number, vertex *head, list *next){
    list *new_list_node = (list *)malloc(sizeof(list));
    new_list_node->vertex_number = number;
    new_list_node->head_vertex = head;
    new_list_node->next_list_node = next;
    return new_list_node;
}

//gets a new vertex given values
vertex *get_vertex_node(int weight, vertex *next_vertex){
    vertex *new_vertex_node = (vertex *)malloc(sizeof(vertex));
    new_vertex_node->weight = weight;
    new_vertex_node->next_vertex_node = next_vertex;
    return new_vertex_node;
}