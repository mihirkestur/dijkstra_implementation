#include<stdio.h>
#include<stdlib.h>
#include "PES1UG19CS272_H.h"

int main(){
    //read the input file
    FILE *file_pointer = fopen("adjacencylist.txt", "r");//open file in read mode
    if(file_pointer == NULL){
        printf("No such file exists\n");
        return 0;
    }
    //get number of vertices (also represents the source vertex)
    int num_vertices;
    fscanf(file_pointer, "%d", &num_vertices);
    //create the graph structure
    graph *input_graph = get_new_graph(num_vertices);
    //put all vertices/connections in the graph
    char line[100000];
    fgets(line, sizeof(line), file_pointer);
    //until EOF run loop
    while(fgets(line,sizeof(line),file_pointer)){
        char *start = line;
        int number, offset, size = 0, num_array[100000];
        while(sscanf(start, "%d%n", &number, &offset)){
            start = start + offset;
            num_array[size] = number;
            ++size;
        }
        /*reversing the source and destination to reverse the edges,
        this is done to convert single destination path problem to 
        single source path problem*/
        int destination = num_array[0]; //first number is the destination
        for(int i = 1; i < size; i = i + 2){
            int source = num_array[i], weight = num_array[i+1];
            insert_vertex(input_graph, source, destination, weight);
        }
    }
    //invoking the dijkstra function once to obtain the solution
    dijkstra(input_graph, num_vertices);
    return 0;
}