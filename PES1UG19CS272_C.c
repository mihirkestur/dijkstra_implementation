#include<stdio.h>
#include "PES1UG19CS272_H.h"

int main(){
    graph *input_graph = create_graph();
    read_and_store(input_graph);
    display_graph(input_graph);
    return 0;
}