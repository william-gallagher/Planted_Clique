#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define n 4096
#define planted_clique_size 200

int total_edges;
int total_vertices;

struct{
  int degree;
  int in_graph;
  int neighbor[n];
} typedef vertex;

void print_graph(vertex graph[n]){

  for(int i=0; i<n; i++){
    printf("row: [%d] [%d]\t", i, graph[i].in_graph);
    printf("Degree %d:\t ", graph[i].degree);
      for(int j=0; j<n; j++){

	if(i == j){
	  printf("- ");
	}
	else if(graph[i].in_graph == 0){
	  printf("%d ", 0);
	}
	else if(graph[j].in_graph == 0){
	  printf("%d ", 0);
	}
	else{
	  printf("%d ", graph[i].neighbor[j]);
	}
      }
      printf("\n");
  }
}

void plant_clique(vertex graph[n], int k){

  int array[n];
  for(int i=0; i<n; i++){
    array[i] = i;
  }
  //shuffle for randomnes
  int j;
  int temp;
  for(int i=0; i<n-1; i++){
    j = rand()%(n-i)+i;

    temp = array[j];
    array[j] = array[i];
    array[i] = temp;

  
  }
  int v;

  //Use the first k most element of shuffled array to determine the vertices to include in the planted clique
  for(int i=0; i<k; i++){
    v = array[i];
    //printf("%d is part of planted clique\n", v);
    for(int j=0; j<n; j++){

      if(v != j){
	if(graph[v].neighbor[j] != 1){
	  graph[v].neighbor[j] = 1;
	  graph[j].neighbor[v] = 1;
	  total_edges += 2;
	  graph[v].degree++;
	  graph[j].degree++;
	}
      }
      else{
	//	printf("v is %d and j is %d\n", v, j);
      }
    }
  }
}

  

int main(){

  srand(0);

  total_edges = 0;
  total_vertices = n;
  
  vertex **graph = malloc(sizeof(graph)* n);

  int removed_list[n];
  int removed_list_index = 0;

  //initial the degree of all vertices to 0
  for(int i=0; i<n; i++){
    graph[i]->degree = 0;
    graph[i]->in_graph = 1;
  }
  
  for(int i=0; i<n; i++){
    
    for(int j=i+1; j<n; j++){

      int r = rand()%2;

      if(r == 1){
	total_edges += 2;
	graph[i]->degree++;
	graph[j]->degree++;
      }
      graph[i]->neighbor[j] = r;
      graph[j]->neighbor[i] = r;

    }
  }
  
  // print_graph(graph);

  printf("%d is the total number of edges\n", total_edges);

  plant_clique(graph, planted_clique_size);

  // print_graph(graph);

  printf("Total edges after planting clique is %d\n", total_edges);

  printf("Lets start removing edges\n\n");

  // printf("Get the vertex with minimum edges..\n");

  

  int min = n;
  int min_vertex = 0;

  //printf("%d and %d \n", total_vertices*(total_vertices-1), total_edges);

  while((total_vertices)*(total_vertices-1) > total_edges){

    if(total_edges < 0){
      break;
    }
    
    min = n;
    min_vertex = 0;
    
    for(int i=0; i<n; i++){

      if(graph[i]->in_graph == 1){
	if(graph[i]->degree < min){
	  min_vertex = i;
	  min = graph[i]->degree;
	}
      }
      //  printf("min vertex is %d\n", min_vertex);
    }
  
    //remove min vertex
    graph[min_vertex]->in_graph = 0;

    removed_list[removed_list_index] = min_vertex;
    removed_list_index++;
    
    for(int i=0; i<n; i++){

      if(min_vertex != i){
	if(graph[i]->in_graph == 1){
	  if(graph[min_vertex]->neighbor[i] == 1){

	    //graph[min_vertex].neighbor[i] = 0;
	    //graph[i].neighbor[min_vertex] = 0;
	    graph[min_vertex]->degree--;
	    graph[i]->degree--;
	    total_edges -= 2;
	  }
	}
      }
    }

    total_vertices--;
    
    //  printf("%d is the total number of edges\n", total_edges);
    // printf("%d is the total number of vertices\n", total_vertices);
    // print_graph(graph);
  }

  for(int i=removed_list_index-1; i>=0; i--){
    //  printf("%d is removed %d\n", removed_list[i], i+1);
  }

  printf("%d is the number of vertices in the clique\n", total_vertices);
  printf("Lets start working on adding to the clique:\n");

  for(int i=removed_list_index-1; i>=0; i--){

    int v = removed_list[i];
    // printf("Trying to add %d\n", v);
    int flag = 1;
    for(int j=0; j<n; j++){

      if(graph[j].in_graph == 1){
	if(graph[v].neighbor[j] == 0){
	  //  printf("Vertex %d fails on vertex %d\n", v, j);
	  flag = 0;
	  break;
	}
      }
    }
    if(flag == 1){
      printf("Adding vertex %d to clique\n", v);
      total_vertices++;
      graph[v]->in_graph = 1;
    }
  } 
  
  
  return 0;
}
