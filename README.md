### Planted Clique Assignment

For Professor Daniel Reichman's CS 525 Randomized Algorithms Class

ldr.c implements the lowest degree removal algorithm found in this [paper](Feige.pdf).

In general terms this 

### Usage

In `test.sh` set the following variables for the number of trials to run, the starting clique size and the final clique size.

 ```C
TRIALS=1000
START_CLIQUE_SIZE=28
END_CLIQUE_SIZE=128
```

Then run:

```Console
.\test.sh
```