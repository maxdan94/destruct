# destruct
C code to break the structure of a real-world graph

## Info:
move.c: This program shuffles the edges of a graph by iteratively removing an edge chosen uniformly at random and putting it back between two nonadjacent nodes chosen uniformly at random. The input graph should not contain any self-loop or double-edge and the resulting graphs will not contain any self-loop or double-edge.

swap.c: This program shuffles the edges of a graph by iteratively selecting two edges chosen uniformly at random and swapping their end-nodes while making sure not to create any self-loop or double edge. The input graph should not contain any self-loop or double-edge and the resulting graphs will not contain any self-loop or double-edge. Note that the degree of each node is conserved.

add.c: This program iteratively adds an edge between two non-adjacent nodes chosen uniformly at random. The input graph should not contain any self-loop or double-edge and the resulting graphs will not contain any self-loop or double-edge. The code is efficient only if the final number of edges is small in front of "n*(n-1)/2" the number of possible edges.

remove.c: This program iteratively removes an edge chosen uniformly at random.

## To compile:
"gcc move.c -O9 -o move"  
"gcc swap.c -O9 -o swap"  
"gcc add.c -O9 -o add"  
"gcc remove.c -O9 -o remove"

## To execute:
"./move ng no net0.txt"  
"./swap ng no net0.txt"  
"./add ng no net0.txt"  
"./remove ng no net0.txt"
- "net0.txt" should contain the graph: one edge on each line (two unsigned long (nodes' ID)) separated by a space.
- "no" is the number of move operation to perform before printing the resulting graph
- "ng" is the number of graphs to generate
- The resulting graphs will be printed in the files "net1.txt", "net2.txt", ..., "netng.txt". "neti.txt" is thus obtained by performing i*no move/swap/add/remove operations on the input graph.

## Initial contributors:
Maximilien Danisch  
November 2018  
http://bit.ly/danisch  
maximilien.danisch@gmail.com
