### Planted Clique Assignment

For Professor Daniel Reichman's CS 525 Randomized Algorithms Class

ldr.c implements the lowest degree removal algorithm found in this [paper](Feige.pdf) for finding a hidden clique.

In general terms this algorithm works as follows:
1. Initialize the adjacency lists for each vertex with probability 1/2.
2. Chose k (for this assignment k ranges from 28 to 128) vertices and make a clique of them.
3. Remove vertices from the graph until the vertices that remain form a clique. Update the adjacency lists of each vertex as the lowest degree vertex is removed.
4. Attempt to add the removed vertices to the clique in the reverse order that they were removed. Only add if their addition preserves the clique property. 
5. Return the graph. It must be a clique. Compare to the planted clique. Return success if it is greater than or equal to the planted clique. Otherwise return failure


### Usage

Build the project.
```Console
make
```

In `test.sh` set the following variables for the number of trials to run, the starting clique size and the final clique size. For example, the setting shown below will run 1000 iterations for every clique size between 28 and 128.

 ```C
TRIALS=1000
START_CLIQUE_SIZE=28
END_CLIQUE_SIZE=128
```

Then run:

```Console
.\test.sh
```