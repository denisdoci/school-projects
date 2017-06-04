#include "travel.h"

int main(int argc, char *argv[]){

	int num_strings = 100;
	int str_len = MAX_STR_LEN;
	int numOfVerts, numTokens=0;
	char * s = (char *) malloc (str_len);
	char * src_vertex = (char *) malloc (MAX_STR_LEN);
	char * dest_vertex = (char *) malloc (MAX_STR_LEN);
	char * token = NULL;
	int id, id1=-1, id2=-1;
	int rec_move, input_move;
	int recommended_id;
	double total_distance = 0;
	double path_len, optimal_len;
	int i,j;
	char c;	
	FILE * fp;
	Graph * g;

	char ** tokens = (char **) malloc (sizeof(char *) * num_strings);
	for(i=0; i<num_strings; i++)
		tokens[i] = (char *) malloc (MAX_STR_LEN);

	i=0;
	fp = fopen(argv[1], "r");
	//copy expresion char by char
	if (fp) {
		c = fgetc(fp);
		while (c != EOF){
			if(i >= str_len-1){
				str_len *= 2;
				s = realloc(s, str_len);
			}
			s[i] = c;
			c = fgetc(fp);
			i++;
		}
		fclose(fp);
	}

	token = strtok(s, "\n");
	while(token != NULL){
		strcpy(tokens[numTokens], token);
        tokens[numTokens][strlen(tokens[numTokens])] = '\0';
		numTokens++;
		token = strtok(NULL, " ");
		if(token == NULL){ break; }
		strcpy(tokens[numTokens], token);
        tokens[numTokens][strlen(tokens[numTokens])] = '\0';
		numTokens++;
		token = strtok(NULL, " ");
		if(token == NULL){ break; }
		strcpy(tokens[numTokens], token);
        tokens[numTokens][strlen(tokens[numTokens])] = '\0';
		numTokens++;
		token = strtok(NULL, "\n");
	}

	numOfVerts = atoi(tokens[0]);
	g = init_graph(tokens, numTokens, numOfVerts);

	//START-DEBUGGING
	// printf("*******************DEBUG*******************\n");
	// print_Vertices_debug(g->Vertices, g->num_used_verts);
	// printf("*******************************************\n");
	//END-DEBUGGING

	printf("Welcome to travel planner.\n\n");
	print_Vertices(g->Vertices, g->num_used_verts);

	while(id1 == -1){
		printf("SELECT YOUR CURRENT LOCATION:    ");
		scanf("%s", src_vertex);
		id1 = find_vertex(g, src_vertex);
		if(id1 == -1) printf("  ERROR: invalid location\n");
	}
	while(id2 == -1){	
		printf("SELECT YOUR DESTINATION     :    ");
		scanf("%s", dest_vertex);	
		id2 = find_vertex(g, dest_vertex);
		if(id2 == -1) printf("  ERROR: invalid location\n");
	}	

	path_len = dijkstra(g, id1, id2, &recommended_id);
	optimal_len = path_len;

	if(path_len == -1){
		for(i=0; i<num_strings; i++)
			free(tokens[i]);
		free(tokens);
		free(s);
		free(src_vertex);
		free(dest_vertex);
		free_graph(g);
		printf("\n  No path found.\n");
		exit(1);
	}else{
		printf("\nYou can reach your destination in %.1f units.\n\n", path_len);
	}
    
	printf("TIME TO TRAVEL!\n\n");
	while(id1 != id2){
		printf("  CURRENT LOCATION:    %s\n", src_vertex);
		printf("  DESTINATION     :    %s\n", dest_vertex);
		printf("  MINIMUM DISTANCE TO DESTINATION:  %.1f\n\n", path_len);

		printf("  POSSIBLE MOVES:\n\n");

		printf("    0. I give up!\n");
		i = 0;
		while(i < g->num_used_verts && g->Vertices[id1].Edges[i].id != -1){
			id = g->Vertices[id1].Edges[i].id;
			if(id == recommended_id) rec_move = i+1;
			printf("    %d. %s  (%.1f units)\n", i+1, g->Vertices[id].name, g->Vertices[id1].Edges[i].edge_len);
			i++;
		}

		printf("\nRECOMMENDED MOVE: %d\n\n", rec_move);

		input_move = -1;
		printf("SELECT A MOVE (ENTER A NUMBER):  ");
		while(input_move < 0 || input_move > i){
			printf("SELECT A MOVE (ENTER A NUMBER):  ");
			scanf("%d", &input_move);
		}

		if(input_move == 0){
			for(i=0; i<num_strings; i++)
				free(tokens[i]);
			free(tokens);
			free(dest_vertex);
			free_graph(g);
			exit(1);
		}
        
        if(total_distance == 0) { free(src_vertex); }
        
		total_distance += g->Vertices[id1].Edges[input_move-1].edge_len;
        id1 = g->Vertices[id1].Edges[input_move-1].id;
        src_vertex = g->Vertices[id1].name;
		printf("TOTAL DISTANCE TRAVELED:          %.2f\n\n", total_distance);
		printf("-------------------------------\n\n");

		path_len = dijkstra(g, id1, id2, &recommended_id);
	}
	
	 for(i=0; i<num_strings; i++)
	 	free(tokens[i]);
	free(s);
	free(tokens);
	free(dest_vertex);
	free_graph(g);

	printf("YOU MADE IT.\n");
	printf("(OPTIMAL DISTANCE: %.2f)\n", optimal_len);
	printf("GOODBYE.\n");
	return 0;	
}
