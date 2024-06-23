/*
 * In this file, you'll implement Dijkstra's algorithm to find the least
 * expensive paths in the graph defined in `airports.dat`.  Don't forget to
 * include your name and @oregonstate.edu email address below.
 *
 * Name: Troy Diaz
 * Email: diaztr@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"

#define DATA_FILE "airports.dat"
#define START_NODE 0
#define INF_COST 999

struct path{ // Represet path taken
	int node; 
	int prev;
	int cost;
};

int main(int argc, char const *argv[]) {
	/*
	 * Open file and read the first two int: num of nodes, num of edges
	 */
	int n_nodes, n_edges;
	FILE* file = fopen(DATA_FILE, "r");
	// First two lines are number of nodes and number of edges
	fscanf(file, " %d %d ", &n_nodes, &n_edges);
	
	/*
	 * Write your code here to find the
	 * least-cost paths from node 0 to all other nodes in the graph.  Make sure
	 * to print out the least-cost paths you find at the end.
	 *
 	 */

	// Create matrix 
	int matrix[n_nodes][n_nodes];

	for(int i = 0; i < n_nodes; i++){
		for(int j = 0; j < n_nodes; j++){
			matrix[i][j] = INF_COST;
		}
	}

	// Store costs of each node edge
	int node_i = 0, node_j = 0, cost_i_j = 0;

	for (int i = 0; i < n_edges; i++){
		fscanf(file, " %d %d %d ", &node_i, &node_j, &cost_i_j);
		matrix[node_i][node_j] = cost_i_j;
	}

	// Close file for reading
	fclose(file);

	// Initialize nodes
	struct path* paths[n_nodes];

	for (int i = 0; i < n_nodes; i++){
		// Allocate memory to each path
		paths[i] = malloc(sizeof(struct path));

		// Initialize every path
		paths[i]->node = i;
		paths[i]->cost = INF_COST;
		paths[i]->prev = 0;
	}

	// Initialize start node to have cost 0 and undefined previous
	paths[START_NODE]->cost = 0; 

	// Create new priority queue
	struct pq* pq = pq_create();

	// Insert starting ndoe with priority 0
	pq_insert(pq, paths[START_NODE], 0);

	while(!pq_isempty(pq)){

		// Store the path that has the least cost from pq
		struct path* current_path = pq_remove_first(pq);

		if (current_path->cost != INF_COST){

			// Update costs and previous nodes in current path
			paths[current_path->node]->cost = current_path->cost;
			paths[current_path->node]->prev = current_path->prev;

			// Neighboring nodes
			for (int neighbor = 0; neighbor < n_nodes; neighbor++){
				
				// Store total cost it takes to get to neighboring node
				int total_cost = matrix[current_path->node][neighbor] + current_path->cost;

				// If total cost is less than current cost, insert path into pq
				if (total_cost < paths[neighbor]->cost){
					struct path* new_path = malloc(sizeof(struct path));

					new_path->node = neighbor;
					new_path->cost = total_cost;
					new_path->prev = current_path->node;

					pq_insert(pq, new_path, total_cost);
				}
			}
		}
		else{
			// Can free the path indicating we already visited
			free(current_path);
		}
	}

	// Print least cost paths
    for (int i = 0; i < n_nodes; i++){
		printf("Cost to node %d: %d -- Previous node: %d\n", i, paths[i]->cost, paths[i]->prev);
	}

	// Free paths
	for (int i = 0; i < n_nodes; i++){
		free(paths[i]);
	}

	// Free pq
	pq_free(pq);
	 
  return 0;
}