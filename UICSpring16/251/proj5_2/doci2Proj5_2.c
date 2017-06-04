#include "5partII.h"

int main(int argc, char *argv[]){
    
    int i,j;
    char c;
    FILE * f;
    Graph * g;
    
    int optChoice;
    int usrChoice;
    int optID;
    double dist = 0;
    double currDist;
    double optDist;

    
    int strings = 100;
    int lengthStr = LEN;
    int numOfVerts;
    int numtoks=0;
    
    
    char * s;
    char * fromVert;
    char * toVert;
    char * tok;
    char ** toks;
    
    int id;
    int id1=-1;
    int id2=-1;
    
    printf("\nStarting program\n\n");
    
    s = (char *) malloc (lengthStr);
    fromVert = (char *) malloc (lengthStr);
    toVert = (char *) malloc (lengthStr);
    tok = NULL;
    toks = (char **) malloc (sizeof(char *) * strings);
    for(i=0; i<strings; i++) toks[i] = (char *) malloc (LEN);
    i=0;
    f = fopen(argv[1], "r");
    
    if (f) {
        c = fgetc(f);
        while (c != EOF){
            if(j >= lengthStr-1){
                lengthStr *= 2;
                s = realloc(s, lengthStr);
            }
            s[j] = c;
            c = fgetc(f);
            j++;
        }
        fclose(f);
    }
    
    
    tok = strtok(s, "\n");
    while(tok != NULL){
        strcpy(toks[numtoks], tok);
        toks[numtoks][strlen(toks[numtoks])] = '\0';
        numtoks++;
        tok = strtok(NULL, " ");
        
        if(tok == NULL) break;
        
        strcpy(toks[numtoks], tok);
        toks[numtoks][strlen(toks[numtoks])] = '\0';
        numtoks++;
        tok = strtok(NULL, " ");
        
        if(tok == NULL) break;
        
        strcpy(toks[numtoks], tok);
        toks[numtoks][strlen(toks[numtoks])] = '\0';
        numtoks++;
        tok = strtok(NULL, "\n");
        
    }
    
    numOfVerts = atoi(toks[0]);
    g = init_graph(toks, numtoks, numOfVerts);
    
    printLocs(g->verts, g->vertsVisited);
    
    while(id1 == -1){
        printf("Where would you like to begin: ");
        scanf("%s", fromVert);
        id1 = get_location(g, fromVert);
        if(id1 == -1)
	  printf("\nPosition not possible try again\n");
    }
    while(id2 == -1){
        printf("\nWhere would you like to go: ");
        scanf("%s", toVert);
        id2 = get_location(g, toVert);
        if(id2 == -1) 
	  printf("Position not possible try again\n");
    }
    
    currDist = dijkstra(g, id1, id2, &optID);
    printf("%s\n", g->verts[id2].name);
    optDist = currDist;
    
    if(currDist == -1){
        for(i=0; i<strings; i++)
            free(toks[i]);
        free(toks);
        free(s);
        free(fromVert);
        free(toVert);
        freeg(g);
        printf("\nCan't get to that location from yours\n");
        exit(1);
    }
    else{
        printf("\nThe distance from your location to your destination is %.1f.\n\n", currDist);
    }
    
    printf("\nMoving\n\n");
    
    while(id1 != id2){
        printf("You are at %s\n", fromVert);
        printf("You are going %s\n", toVert);
        printf("Which will take at least: %.1f\n\n", currDist);
        printf("Options\n\n");
        printf("0: Quit\n");
        i = 0;
        while(i < g->vertsVisited && g->verts[id1].edgs[i].id != -1){
            id = g->verts[id1].edgs[i].id;
            if(id == optID) optChoice = i+1;
            printf("%d. %s (%.1f units)\n", i+1, g->verts[id].name, g->verts[id1].edgs[i].dist);
            i++;
        }
        
        printf("\nChoice you should make: %d\n\n", optChoice);
        usrChoice = -1;
    
        while(usrChoice < 0 || usrChoice > i){
            printf("\nMake your choice: ");
            scanf("%d", &usrChoice);
        }
        
        if(usrChoice == 0){
            for(i=0; i<strings; i++)
                free(toks[i]);
            free(toks);
            free(toVert);
            freeg(g);
            exit(1);
        }
        
        if(dist == 0) free(fromVert);
        
        dist += g->verts[id1].edgs[usrChoice-1].dist;
        id1 = g->verts[id1].edgs[usrChoice-1].id;
        fromVert = g->verts[id1].name;
        printf("\nYour distance was %.2f\n\n", dist);
        currDist = dijkstra(g, id1, id2, &optID);
        printf("%s\n", g->verts[id2].name);

    }
    
    for(i=0; i<strings; i++) free(toks[i]);
    free(s);
    free(toks);
    free(toVert);
    freeg(g);
    
    printf("\nAt End\n");
    printf("\nThe shortest distance was: %.2f \nEnding now byebye\n", optDist);
    return 0;
}

