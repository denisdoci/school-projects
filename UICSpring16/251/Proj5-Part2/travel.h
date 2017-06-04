#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 20

typedef struct {
	double edge_len;
	int id;
} Edge;

typedef struct {
	char * name;
	int id;
	Edge * Edges;
	int visited;
	int * path;
	double distance_from_src;
} Vertex;

typedef struct {
	Vertex * Vertices;
	int num_verts;
	int num_used_verts;
} Graph;

extern void print_Vertices(Vertex * vertices, int numUsedVerts){
	printf("Vertices:\n\n  ");
	int i;
	for(i=0; i<numUsedVerts; i++){
		printf("%s ", vertices[i].name);
	}
	printf("\n\n");
}

extern void print_Vertices_debug(Vertex * vertices, int numUsedVerts){
	printf("\nVertices-DEBUG:\n");
	int i, j, id;
	for(i=0; i<numUsedVerts; i++){
		printf("  %s: ", vertices[i].name);
		j=0;
		while(j<numUsedVerts && vertices[i].Edges[j].id != -1){
			id = vertices[i].Edges[j].id;
			printf("<%d,%s> ", id, vertices[id].name);
			j++;
		}
		printf("\n");
	}
	printf("\n");
}

static int addVertex(Graph * r, char * v){
	int num_used = r->num_used_verts;
	int i;
	for(i=0; i<num_used; i++){
		if(strcmp(r->Vertices[i].name, v) == 0)
			return i;
	}
	strcpy(r->Vertices[i].name, v);
	r->Vertices[i].id = i;
	r->num_used_verts++;

	return r->Vertices[i].id;
}

static void push(Edge * Edges, int numUsedVerts, int dest_id, double edgeLen){
	int i = 0;
	while(i<numUsedVerts && Edges[i].id != -1){
		if(Edges[i].id == dest_id)
			return;
		i++;
	}
	Edges[i].id = dest_id;
	Edges[i].edge_len = edgeLen;
}

static void addEdge(Vertex * v, int numUsedVerts, int id1, int id2, double edgeLen){
	push(v[id1].Edges, numUsedVerts, id2, edgeLen);
	push(v[id2].Edges, numUsedVerts, id1, edgeLen);
}

extern Graph * init_graph(char ** tokens, int numTokens, int numVertices){
	Graph * new = malloc (sizeof(Graph));
	new->num_verts = numVertices;
	new->num_used_verts = 0;
	new->Vertices = malloc(sizeof(Vertex) * numVertices);
	int id1, id2, i, j;
	double edge_len;

	for(i=0; i<numVertices; i++){
		new->Vertices[i].name = (char *) malloc (MAX_STR_LEN);
		new->Vertices[i].id = -1;
		new->Vertices[i].Edges = malloc(sizeof(Edge) * numVertices);
		new->Vertices[i].path = (int *) malloc (sizeof(int) * numVertices);
		for(j=0; j<numVertices; j++){
			new->Vertices[i].Edges[j].id = -1;
			new->Vertices[i].path[j] = -1;
		}
	}

	for(i=1; i<numTokens; i+=3){
		id1 = addVertex(new, tokens[i]);
		id2 = addVertex(new, tokens[i+1]);
		edge_len = atof(tokens[i+2]);
		addEdge(new->Vertices, new->num_used_verts, id1, id2, edge_len);
	}

	return new;
}

extern void free_graph(Graph * g){
	int i;
	for(i=0; i<g->num_verts; i++){
		free(g->Vertices[i].Edges);
		free(g->Vertices[i].path);
		free(g->Vertices[i].name);
	}
	free(g->Vertices);
	free(g);
}

extern int find_vertex(Graph * g, char * vertex){
	int num_verts = g->num_used_verts;
	int i;
	for(i=0; i<num_verts; i++){
		if(strcmp(g->Vertices[i].name, vertex) == 0)
			return g->Vertices[i].id;
	}

	return -1;
}

static void reset_graph_paths(Graph * g){
	int numVerts = g->num_used_verts;
	double inf = 1.0/0.0;
	int i, j;

	for (i=0; i<numVerts; i++)
	{
		for(j=0; j<g->num_verts; j++)
			g->Vertices[i].path[j] = -1;
		g->Vertices[i].visited = 0;
		g->Vertices[i].distance_from_src = inf;
	}
}

static int not_in_queue(Vertex ** queue, int id){
	int i = 0;
	while(queue[i] != NULL){
		if(id == queue[i]->id)
			return 0;
		i++;
	}
	return 1;
}

static void clean_path(Graph * g, int id){
	int i = 0;
	while(i < g->num_verts && g->Vertices[id].path[i] != -1)
		g->Vertices[id].path[i] = -1;
}

static void update_path(Graph * g, int src_id, int dest_id){
	int num_path_steps = 0;
	int i = 0;
	clean_path(g, dest_id);
	while(g->Vertices[src_id].path[i] != -1){
		g->Vertices[dest_id].path[i] = g->Vertices[src_id].path[i];
		i++;
	}
	g->Vertices[dest_id].path[i] = dest_id;
}


//FOR DEBUGGING
static void print_solution(Graph * g, int id){
	int i = 0;
	printf("PATH: ");
	while(g->Vertices[id].path[i] != -1){
		printf("%d ", g->Vertices[id].path[i]);
		i++;
	}
	printf("\n");
}

extern double dijkstra(Graph * g, int src_id, int dest_id, int * rec_path){
	int numVerts = g->num_used_verts;
	int i = 0, j = 0;
	int top = -1, id, edge_i;
	double dist;

	if(src_id == dest_id) return 0;
	else reset_graph_paths(g);

	Vertex ** queue = malloc(sizeof(Vertex *) * numVerts);
	for(i=0; i<numVerts; i++)
		queue[i] = NULL;

	i = 0;
	queue[i] = &g->Vertices[src_id];
	queue[i]->distance_from_src = 0;
	queue[i]->visited = 1;
	queue[i]->path[0] = src_id;
	
	while(top != i){
		//used to enter loop
		if(i == 0) top = 1;

		j = 0; //Edge index
		id = queue[i]->Edges[j].id;
		while(id !=  -1){
			if(not_in_queue(queue, id)){
				queue[top] = &g->Vertices[id];
				queue[top]->distance_from_src = queue[i]->distance_from_src + queue[i]->Edges[j].edge_len;
				queue[top]->visited = 1;
				update_path(g, queue[i]->id, id);
				top++;
			}else{
				dist = queue[i]->Edges[j].edge_len + queue[i]->distance_from_src; 
				if( dist < g->Vertices[id].distance_from_src){
					g->Vertices[id].distance_from_src = dist;
					update_path(g, queue[i]->id, id);
				}
			}
			j++;
			id = queue[i]->Edges[j].id;
		}
		i++;
	}
    while(g->Vertices[g->Vertices->path[i]].name!=NULL){
        printf("  %s->\n", g->Vertices[g->Vertices->path[i]].name);
        i++;
    }

	dist = g->Vertices[dest_id].distance_from_src;
	if(g->Vertices[dest_id].distance_from_src != 0){
		*rec_path = g->Vertices[dest_id].path[1];
		//print_solution(g, dest_id); //DEBUG
		free(queue);
		return g->Vertices[dest_id].distance_from_src;
	}
	free(queue);
	return -1;
}
