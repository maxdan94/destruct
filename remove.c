/*
Maximilien Danisch
November 2018
http://bit.ly/danisch
maximilien.danisch@gmail.com

Info:
This program iteratively removes a randomly chosen edge.

To compile:
"gcc remove.c -O9 -o remove".

To execute:
"./remove ng no net0.txt"
- "net0.txt" should contain the graph: one edge on each line (two unsigned long (nodes' ID)) separated by a space.
- "no" is the number of remove operation to perform before printing the resulting graph
- "ng" is the number of graphs to generate
- The resulting graphs will be printed in the files "net1.txt", "net2.txt", ..., "netng.txt". "neti.txt" is thus obtaind by performing i*no remove operations on the input graph.

Performance:
Up to 500 million edges on my laptop with 8G of RAM.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>//to estimate the runing time

#define NLINKS 100000000 //maximum number of edges for memory allocation, will increase if needed

typedef struct {
	unsigned long s;
	unsigned long t;
} edge;

//edge list structure:
typedef struct {
	unsigned long n;//number of nodes
	unsigned long e;//number of edges
	edge *edges;//list of edges
} edgelist;

//compute the maximum of three unsigned long
inline unsigned long max3(unsigned long a,unsigned long b,unsigned long c){
	a=(a>b) ? a : b;
	return (a>c) ? a : c;
}

//reading the edgelist from file
edgelist* readedgelist(char* input){
	unsigned long e1=NLINKS;
	unsigned long s,t;
	edgelist *g=malloc(sizeof(edgelist));
	FILE *file;

	g->n=0;
	g->e=0;
	file=fopen(input,"r");
	g->edges=malloc(e1*sizeof(edge));
	while (fscanf(file,"%lu %lu", &s, &t)==2) {
		g->n=max3(g->n,s,t);
		g->edges[g->e].s=s;
		g->edges[g->e].t=t;
		if (g->e++==e1) {//increase allocated memory of needed
			e1+=NLINKS;
			g->edges=realloc(g->edges,e1*sizeof(edge));
		}
	}
	fclose(file);
	g->n++;

	g->edges=realloc(g->edges,g->e*sizeof(edge));

	return g;
}

void free_edgelist(edgelist *g){
	free(g->edges);
	free(g);
}

//printing the edgelist to file
void printgraph(edgelist* g,char* output){
	unsigned i;
	FILE *file;
	file=fopen(output,"w");
	for (i=0;i<g->e;i++) {
		fprintf(file,"%lu %lu\n", g->edges[i].s, g->edges[i].t);
	}
}

int main(int argc,char** argv){
	edgelist* g;
	unsigned long i,j,ng,no;
	char str[20],str2[15];
	time_t t1,t2;

	t1=time(NULL);

	printf("Number of graphs: %s\n",argv[1]);
	ng=atoi(argv[1]);
	printf("Number of move operations: %s\n",argv[2]);
	no=atoi(argv[2]);

	printf("Reading edgelist from file %s\n",argv[3]);
	g=readedgelist(argv[3]);

	printf("Number of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n",g->e);

	srand(time(NULL));

	for (i=1;i<=ng;i++){
		for (j=0;j<no;j++){
			//printf("%lu %lu\n",i,j);
			if (g->e==0){
				printf("All edges have been removed\n");
				free_edgelist(g);
				t2=time(NULL);
				printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
				return 0;
			}
			g->edges[rand() % g->e]=g->edges[--g->e];
		}
		strcpy(str,"net");
		sprintf(str2,"%lu",i);
		strcat(str,str2);
		strcat(str,".txt");
		printf("Printing resulting graph in file %s\n",str);
		printgraph(g,str);
	}

	free_edgelist(g);
	t2=time(NULL);
	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	return 0;
}


