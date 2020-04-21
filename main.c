#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define n 12

struct{
  int degree;
  int neighbor[n];
} typedef vertex;

void print_graph(vertex graph[n]){

  for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){

	if(i == j){
	  printf("- ");
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
    printf("%d is j and %d is n-i and %d is i\n", j, n-i, i);
    temp = array[j];
    array[j] = array[i];
    array[i] = temp;

    for(int g=0; g<n; g++){
      //  printf("%d ", array[g]);
    }
    //printf("\n");
	  
  }
  int v;

  //Use the first k most element of shuffled array to determine the vertices to include in the planted clique
  for(int i=0; i<k; i++){
    v = array[i];
    printf("%d is part of planted clique\n", v);
    for(int j=0; j<n; j++){

      graph[v].neighbor[j] = 1;
      graph[j].neighbor[v] = 1;
    }
  }
}

  

int main(){

  srand(0);
  vertex graph[n];

  for(int i=0; i<n; i++){
    for(int j=i; j<n; j++){

      int r = rand()%2;
      graph[i].neighbor[j] = r;
      graph[j].neighbor[i] = r;
    }
  }
  
  print_graph(graph);

  plant_clique(graph, 4);

  print_graph(graph);
  
  return 0;
}
