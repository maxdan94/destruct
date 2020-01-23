/*
Maximilien Danisch
November 2018
http://bit.ly/danisch
maximilien.danisch@gmail.com

Info:
This program shuffle the edges of a graph by iteratively selecting two random edges and swaping their end-nodes while making sure not to create any self-loop or double edge.
The input graph should not contain any self-loop or double-edge and the resulting graphs will not contain any self-loop or double-edge.
Note that the degree of each node is conserved.


To compile:
"gcc swap.c -O9 -o swap".

To execute:
"./swap ng no net0.txt"
- "net0.txt" should contain the graph: one edge on each line (two unsigned long (nodes' ID)) separated by a space.
- "no" is the number of move operation to perform before printing the resulting graph
- "ng" is the number of graphs to generate
- The resulting graphs will be printed in the files "net1.txt", "net2.txt", ..., "netng.txt". "neti.txt" is thus obtaind by performing i*no swap operations on the input graph.

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

	unsigned long *ht;//hash table
	unsigned long *ll;//linked list 
} edgelisthash;

//compute the maximum of three unsigned long
inline unsigned long max3(unsigned long a,unsigned long b,unsigned long c){
	a=(a>b) ? a : b;
	return (a>c) ? a : c;
}

//reading the edgelist from file
edgelisthash* readedgelist(char* input){
	unsigned long e1=NLINKS;
	unsigned long s,t;
	edgelisthash *g=malloc(sizeof(edgelisthash));
	FILE *file;

	g->n=0;
	g->e=0;
	file=fopen(input,"r");
	g->edges=malloc(e1*sizeof(edge));
	while (fscanf(file,"%lu %lu", &s, &t)==2) {
		g->n=max3(g->n,s,t);
		if (s>t){//make sure that s<t
			g->edges[g->e].s=t;
			g->edges[g->e].t=s;
		}
		else{
			g->edges[g->e].s=s;
			g->edges[g->e].t=t;
		}
		if (++(g->e)==e1) {//increase allocated memory of needed
			e1+=NLINKS;
			g->edges=realloc(g->edges,e1*sizeof(edge));
		}
	}
	fclose(file);
	g->n++;

	g->edges=realloc(g->edges,g->e*sizeof(edge));

	return g;
}

void free_edgelisthash(edgelisthash *g){
	free(g->edges);
	free(g->ht);
	free(g->ll);
	free(g);
}

//simple hash function
unsigned long hash(edge ed, unsigned long s){
	return (ed.s*10009+ed.t*1009) % s;
}

//building hash table
void mkhash(edgelisthash* g){
	unsigned long i,j,h;

	g->ht=malloc(g->e*sizeof(unsigned long));//size of hashtable is g->e
	g->ll=malloc(g->e*sizeof(unsigned long));//using a single malloc for the linked lists
	for (i=0;i<g->e;i++){
		g->ht[i]=-1;
		g->ll[i]=-1;
	}
	for (i=0;i<g->e;i++){//filling the hash table
		h=hash(g->edges[i],g->e);
		if (g->ht[h]==-1){
			g->ht[h]=i;
		}
		else {
			j=g->ht[h];
			while (g->ll[j]!=-1){
				j=g->ll[j];
			}
			g->ll[j]=i;
		}
	}
}

//remove the kiest edge from the hash table
void rmedge(edgelisthash *g, unsigned long k){
	unsigned long h=hash(g->edges[k],g->e);
	unsigned long i;
	if (g->ht[h]==k){
		g->ht[h]=g->ll[k];
	}
	else {
		i=g->ht[h];
		while (g->ll[i]!=k){
			i=g->ll[i];
		}
		g->ll[i]=g->ll[k];
	}
	g->ll[k]=-1;
}

//check if edge ed is in edgelist
char isin(edgelisthash *g, edge ed){
	unsigned long h=hash(ed,g->e);
	unsigned long i=g->ht[h];
	while (i!=-1){
		if ((g->edges[i].s==ed.s) && (g->edges[i].t==ed.t)){
			return 1;
		}
		i=g->ll[i];
	}
	return 0;
}

//add edge ed at the kiest position and in the hash table
void addedge(edgelisthash *g, edge ed, unsigned long k){
	g->edges[k]=ed;
	unsigned long h=hash(ed,g->e);
	unsigned long i;
	if (g->ht[h]==-1){
		g->ht[h]=k;
	}
	else {
		i=g->ht[h];
		while (g->ll[i]!=-1){
			i=g->ll[i];
		}
		g->ll[i]=k;
	}
}

//swap the end nodes of two randomly chosen edges
void swap(edgelisthash* g){
	unsigned long k,l;
	edge ed1,ed2;
	unsigned long tmp;
	do{
		k=rand() % g->e;//chosing 2 random edge
		l=rand() % g->e;
		//given 2 edges there are 2 possible swaps. "k<l" is used to decide which one
		if (k<l){
			ed1.s=g->edges[k].s;
			ed1.t=g->edges[l].s;
			if (ed1.s>ed1.t){
				tmp=ed1.s;
				ed1.s=ed1.t;
				ed1.t=tmp;
			}
			ed2.s=g->edges[k].t;
			ed2.t=g->edges[l].t;
			if (ed2.s>ed2.t){
				tmp=ed2.s;
				ed2.s=ed2.t;
				ed2.t=tmp;
			}
		}
		else{
			ed1.s=g->edges[k].s;
			ed1.t=g->edges[l].t;
			if (ed1.s>ed1.t){
				tmp=ed1.s;
				ed1.s=ed1.t;
				ed1.t=tmp;
			}
			ed2.s=g->edges[l].s;
			ed2.t=g->edges[k].t;
			if (ed2.s>ed2.t){
				tmp=ed2.s;
				ed2.s=ed2.t;
				ed2.t=tmp;
			}
		}
	} while (ed1.s==ed1.t || ed2.s==ed2.t || isin(g,ed1) || isin(g,ed2) );
	rmedge(g,k);
	rmedge(g,l);
	addedge(g,ed1,k);
	addedge(g,ed2,l);
}

//printing the edgelist to file
void printgraph(edgelisthash* g,char* output){
	unsigned i;
	FILE *file;
	file=fopen(output,"w");
	for (i=0;i<g->e;i++) {
		fprintf(file,"%lu %lu\n", g->edges[i].s, g->edges[i].t);
	}
}

int main(int argc,char** argv){
	edgelisthash* g;
	unsigned long i,j,ng,no;
	char str[20],str2[15];
	time_t t1,t2;

	t1=time(NULL);

	printf("Number of graphs: %s\n",argv[1]);
	ng=atoi(argv[1]);
	printf("Number of swap operations: %s\n",argv[2]);
	no=atoi(argv[2]);

	printf("Reading edgelist from file %s\n",argv[3]);
	g=readedgelist(argv[3]);

	printf("Number of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n",g->e);

	printf("Building hash map\n");
	mkhash(g);

	srand(time(NULL));

	for (i=1;i<=ng;i++){
		for (j=0;j<no;j++){
			//printf("%lu %lu\n",i,j);
			swap(g);
		}
		strcpy(str,"net");
		sprintf(str2,"%lu",i);
		strcat(str,str2);
		strcat(str,".txt");
		printf("Printing resulting graph in file %s\n",str);
		printgraph(g,str);
	}

	free_edgelisthash(g);

	t2=time(NULL);

	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	return 0;
}


