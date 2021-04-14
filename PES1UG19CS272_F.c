#include<stdio.h>
#include<stdlib.h>
#include "PES1UG19CS272_H.h"

int main(){

    FILE *fptr;
    fptr = fopen("adjacencylist.txt", "r");
    int ch;
    if(fptr == NULL) {
        printf("NULL\n");
        return 0;
    }
    int V;
    fscanf(fptr,"%d",&V);

    graph *input_graph = get_new_graph(V);
    char line[1000];
    fgets(line,sizeof(line),fptr);
    while(fgets(line,sizeof(line),fptr)) {
            char *start = line;
            int field;
            int n;
            int size = 0;
            int tempArray[100];
            while (sscanf(start,"%d%n",&field,&n) == 1) {
                start += n;
                tempArray[size] = field;
                size++;
            }
            //printf("\n");

            int src = tempArray[0];
            for (int i = 1; i < size; i++) {
                int dest = tempArray[i];
                i++;
                int weight = tempArray[i];
                insert_vertex(input_graph,dest,src,weight);
            }
    }
    // printGraph(graph);
    dijkstra(input_graph, 20);
  return 0;
}