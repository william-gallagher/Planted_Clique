#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define n 4096

int total_edges;
int total_vertices;

struct{
  int degree;
  int in_graph;
  int neighbor[n];
} typedef vertex;

/*
Prints the vertices and associated adjency lists for debugging.
Not recommended for graphs of large size!
*/
void print_graph(vertex **graph){

  for(int i=0; i<n; i++){
    printf("row: [%d] [%d]\t", i, graph[i]->in_graph);
    printf("Degree %d:\t ", graph[i]->degree);
    for(int j=0; j<n; j++){

      if(i == j){
	printf("- ");
      }
      else if(graph[i]->in_graph == 0){
	printf("%d ", 0);
      }
      else if(graph[j]->in_graph == 0){
	printf("%d ", 0);
      }
      else{
	printf("%d ", graph[i]->neighbor[j]);
      }
    }
    printf("\n");
  }
}

/*
Assign edges with probability 1/2 to all vertices
*/
void fill_adjacency_matrix(vertex **graph){
  
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
}

/*
Fisher-Yates Shuffle
Accepts an array with vertices 0 to n-1
Returns the shuffled array
*/
void shuffle_vertices(int array[n]){

  int j;
  int temp;
  for(int i=0; i<n-1; i++){
    j = rand()%(n-i)+i;

    temp = array[j];
    array[j] = array[i];
    array[i] = temp;
  }
}

void plant_clique(vertex **graph, int k){

  int array[n];
  for(int i=0; i<n; i++){
    array[i] = i;
  }

  shuffle_vertices(array);
  
  int v;

  //Use the first k most element of shuffled array to determine the
  //vertices to include in the planted clique
  for(int i=0; i<k; i++){
    v = array[i];

    for(int j=i+1; j<k; j++){

      if(graph[v]->neighbor[array[j]] != 1){
	graph[v]->neighbor[array[j]] = 1;
	graph[array[j]]->neighbor[v] = 1;
	total_edges += 2;
	graph[v]->degree++;
	graph[array[j]]->degree++;
      }
    }
  }
}

/*
Search through the vertices to find the one with the lowest degree
*/
int find_min_degree(vertex **graph){
  
  int min = n;
  int min_vertex = 0;
    
  for(int i=0; i<n; i++){

    if(graph[i]->in_graph == 1){
      if(graph[i]->degree < min){
	min_vertex = i;
	min = graph[i]->degree;
      }
    }
  }
  return min_vertex;
}

/*
Remove the min_vertex from all the neighbor lists of the other
vertices
*/
void remove_from_neighbor_list(vertex **graph, int min_vertex){
  
  for(int i=0; i<n; i++){

    if(min_vertex != i){
      if(graph[i]->in_graph == 1){
	if(graph[min_vertex]->neighbor[i] == 1){
	  
	  graph[min_vertex]->degree--;
	  graph[i]->degree--;
	  total_edges -= 2;
	}
      }
    }
  }
}

void removal_phase(vertex **graph, int removed_list[n], int *index){

  int min_vertex = 0;
    
  while((total_vertices)*(total_vertices-1) > total_edges){

    min_vertex = find_min_degree(graph);

    graph[min_vertex]->in_graph = 0;

    removed_list[(*index)] = min_vertex;
    (*index)++;
    
    remove_from_neighbor_list(graph, min_vertex);

    total_vertices--;
  }
}

/*
Check to see if vertex v can be added to the clique
*/
void try_add_vertex(int v, vertex **graph){
  int flag = 1;
  for(int j=0; j<n; j++){
    if(graph[j]->in_graph == 1){
      if(graph[v]->neighbor[j] == 0){
	flag = 0;
	break;
      }
    }
  }
  if(flag == 1){
    total_vertices++;
    graph[v]->in_graph = 1;
  }
}

/*
Try to add the vertices back into the clique. Return 1 a clique of the
proper size is located. Otherwise return 0.
*/
int inclusion_phase(vertex **graph, int removed_list[n], int index,
		    int planted_clique_size){

  if(total_vertices >= planted_clique_size){
    return 1;
  }
  else{

    for(int i=index-1; i>=0; i--){

      int v = removed_list[i];
      try_add_vertex(v, graph);
    }
    if(total_vertices >= planted_clique_size){
      return 1;
    }
  }
  return 0;
}

  

int string_to_int(char *str){

  int value = 0;
  int i=0;
  while(str[i] != '\0'){
    
    value = value*10;
    value += (str[i]-'0')%10;
    i++;
  }
  return value;
}
  

int main(int argc, char **argv){

  if(argc < 3){
    printf("Usage: First Argument is number of iterations \n");
    printf("Second Argument is the size of the Planted Clique\n");
    exit(0);
  }
  
  int trials = string_to_int(argv[1]);
  int planted_clique_size = string_to_int(argv[2]);

  srand(time(NULL));
  
  vertex **graph = malloc(sizeof(vertex *) * n);

  for(int i=0; i<n; i++){
    graph[i] = malloc(sizeof(vertex));
  }

  int removed_list[n];
  int removed_list_index;
  int successes = 0;
  int result;

  for(int i=0; i<trials; i++){

    total_edges = 0;
    total_vertices = n;
    removed_list_index = 0;

    fill_adjacency_matrix(graph);
    
    plant_clique(graph, planted_clique_size);

    removal_phase(graph, removed_list, &removed_list_index);
    
    result = inclusion_phase(graph, removed_list, removed_list_index,
			     planted_clique_size);

    successes = successes + result;

  }

  printf("%d, %d, %d\n", planted_clique_size, successes, trials);
  
  //Cleanup 
  for(int i=0; i<n; i++){
    free(graph[i]);
  }
  free(graph);

  return 0;
}
