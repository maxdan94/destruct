# destruct
C code to break the structure of a real-world graph

## Info:
move.c: This program shuffles the edges of a graph by iteratively removing a randomly chosen edge and putting it back between two randomly chosen nonadjacent nodes. The input graph should not contain any self-loop or double-edge and the resulting graphs will not contain any self-loop or double-edge.

swap.c: This program shuffles the edges of a graph by iteratively selecting two random edges and swapping their end-nodes while making sure not to create any self-loop or double edge. The input graph should not contain any self-loop or double-edge and the resulting graphs will not contain any self-loop or double-edge. Note that the degree of each node is conserved.

## To compile:
"gcc move.c -O9 -o move"  
"gcc swap.c -O9 -o swap"

## To execute:
"./move ng no net0.txt"  
"./swap ng no net0.txt"
- "net0.txt" should contain the graph: one edge on each line (two unsigned long (nodes' ID)) separated by a space.
- "no" is the number of move operation to perform before printing the resulting graph
- "ng" is the number of graphs to generate
- The resulting graphs will be printed in the files "net1.txt", "net2.txt", ..., "netng.txt". "neti.txt" is thus obtained by performing i*no move/swap operations on the input graph.

## Initial contributors:
Maximilien Danisch  
November 2018  
http://bit.ly/danisch  
maximilien.danisch@gmail.com
