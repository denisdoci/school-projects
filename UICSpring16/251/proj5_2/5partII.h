#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 20

typedef struct {
	double dist;
	int id;
} edg;

typedef struct {
	char * name;
	int id;
	edg * edgs;
	int visited;
	int * path;
	double currDist;
} vert;

typedef struct {
	vert * verts;
	int num_verts;
	int vertsVisited;
} Graph;

extern void printLocs(vert * verts, int numUsedVerts){
	printf("Locations:\n\n");
	int i;
	for(i=0; i<numUsedVerts; i++){
		printf("%s ", verts[i].name);
	}
	printf("\n\n");
}

static int addvert(Graph * r, char * v){
	int num_used = r->vertsVisited;
	int i;
	for(i=0; i<num_used; i++){
		if(strcmp(r->verts[i].name, v) == 0)
			return i;
	}
	strcpy(r->verts[i].name, v);
	r->verts[i].id = i;
	r->vertsVisited++;

	return r->verts[i].id;
}

static void push(edg * edgs, int numUsedVerts, int toID, double edgLen){
	int i = 0;
	while(i<numUsedVerts && edgs[i].id != -1){
		if(edgs[i].id == toID)
			return;
		i++;
	}
	edgs[i].id = toID;
	edgs[i].dist = edgLen;
}

static void addedg(vert * v, int numUsedVerts, int id1, int id2, double edgLen){
	push(v[id1].edgs, numUsedVerts, id2, edgLen);
	push(v[id2].edgs, numUsedVerts, id1, edgLen);
}

extern Graph * init_graph(char ** tokens, int numTokens, int numverts){
    
	Graph * gr = malloc (sizeof(Graph));
	gr->num_verts = numverts;
	gr->vertsVisited = 0;
	gr->verts = malloc(sizeof(vert) * numverts);
	int id1, id2, i, j;
	double dist;

	for(i=0; i<numverts; i++){
		gr->verts[i].name = (char *) malloc (LEN);
		gr->verts[i].id = -1;
		gr->verts[i].edgs = malloc(sizeof(edg) * numverts);
		gr->verts[i].path = (int *) malloc (sizeof(int) * numverts);
		for(j=0; j<numverts; j++){
			gr->verts[i].edgs[j].id = -1;
			gr->verts[i].path[j] = -1;
		}
	}

	for(i=1; i<numTokens; i+=3){
		id1 = addvert(gr, tokens[i]);
		id2 = addvert(gr, tokens[i+1]);
		dist = atof(tokens[i+2]);
		addedg(gr->verts, gr->vertsVisited, id1, id2, dist);
	}

	return gr;
}

extern void freeg(Graph * g){
	int i;
	for(i=0; i<g->num_verts; i++){
		free(g->verts[i].edgs);
		free(g->verts[i].path);
		free(g->verts[i].name);
	}
	free(g->verts);
	free(g);
}

extern int get_location(Graph * g, char * vert){
	int num_verts = g->vertsVisited;
	int i;
	for(i=0; i<num_verts; i++){
		if(strcmp(g->verts[i].name, vert) == 0)
			return g->verts[i].id;
	}

	return -1;
}

static void resetpth(Graph * g, int id){
    int i = 0;
    while(i < g->num_verts && g->verts[id].path[i] != -1)
        g->verts[id].path[i] = -1;
}

static void update_path(Graph * g, int from, int toID){
    int num_path_steps = 0;
    int i = 0;

    resetpth(g, toID);
    while(g->verts[from].path[i] != -1){
        g->verts[toID].path[i] = g->verts[from].path[i];
        i++;
    }
    g->verts[toID].path[i] = toID;
    
}

static int notqued(vert ** queue, int id){
    int i = 0;
    while(queue[i] != NULL){
        if(id == queue[i]->id)
            return 0;
        i++;
    }
    return 1;
}

static void resetgraph(Graph * g){
	int numVerts = g->vertsVisited;
	double np = 1.0/0.0;
	int i, j;

	for (i=0; i<numVerts; i++)
	{
		for(j=0; j<g->num_verts; j++)
			g->verts[i].path[j] = -1;
		g->verts[i].visited = 0;
		g->verts[i].currDist = np;
	}
}





extern double dijkstra(Graph * g, int from, int toID, int * optimalJourney){
    
    int numVerts = g->vertsVisited;
    int i = 0;
    int j = 0;
    int top = -1;
    int id;
    double dist;


	if(from == toID)
        return 0;
	else resetgraph(g);

	vert ** queue = malloc(sizeof(vert *) * numVerts);
	for(i=0; i<numVerts; i++)
		queue[i] = NULL;

	i = 0;
	queue[i] = &g->verts[from];
	queue[i]->currDist = 0;
	queue[i]->visited = 1;
	queue[i]->path[0] = from;
	while(top != i){
		if(i == 0) top = 1;
		id = queue[i]->edgs[j].id;
		while(id !=  -1){
			if(notqued(queue, id)){
                queue[top] = &g->verts[id];
				queue[top]->currDist = queue[i]->currDist + queue[i]->edgs[j].dist;
				queue[top]->visited = 1;
				update_path(g, queue[i]->id, id);
				top++;
			}
            else{
				dist = queue[i]->edgs[j].dist + queue[i]->currDist;
				if( dist < g->verts[id].currDist){
					g->verts[id].currDist = dist;
					update_path(g, queue[i]->id, id);
				}
			}
			j++;
			id = queue[i]->edgs[j].id;
		}
		i++;
	}
    i=0;
    while(g->verts[g->verts->path[i]].name != NULL){
        printf(" %s->\n", g->verts[g->verts->path[i]].name);
        i++;
    }
	dist = g->verts[toID].currDist;
	if(g->verts[toID].currDist != 0){
		*optimalJourney = g->verts[toID].path[1];
		free(queue);
		return g->verts[toID].currDist;
	}

	free(queue);
	return -1;
}

