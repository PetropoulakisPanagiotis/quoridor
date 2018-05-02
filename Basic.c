#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"


void protocol_version(void) { // Version of protocol.

	printf("= ");
	printf("2.0");
	printf("\n\n");
}

void name(void) { // Name of engine.

	printf("= ");
	printf("PP-AC");
	printf("\n\n");
}

void version(void) { // Version.

	printf("= ");
	printf("1.2");
	printf("\n\n");
}

int known_command() { // Existance of command.
	char command[50]; // For command name.

	scanf("%s", command);

	// Check if it's known command.//
	
    if (!(strcmp(command, "protocol_version"))) {
		printf("= ");
		printf("true");
	}

	else if (!(strcmp(command, "name"))) {
		printf("= ");
		printf("true");
	}

	else if (!(strcmp(command, "version"))) {
		printf("= ");
		printf("true");
	}

	else if (!(strcmp(command, "known_command"))) {
		printf("= ");
		printf("true");
	}

	else if (!(strcmp(command, "list_commands"))) {
		printf("= ");
		printf("true");
	}

	else if (!(strcmp(command, "quit"))) {
		printf("= ");
		printf("true");
	}

	else if (!(strcmp(command, "boardsize"))) {
		printf("= ");
		printf("true");
	}

	else if (!(strcmp(command, "clear_board"))) {
		printf("= ");
		printf("true");
	}

	else if (!(strcmp(command, "walls"))) {
		printf("= ");
		printf("true");
	}

	else if (!(strcmp(command, "playmove"))) {
		printf("= ");
		printf("true");
	}

	else if (!(strcmp(command, "playwall"))) {
		printf("= ");
		printf("true");
	}

	else if (!(strcmp(command, "genmove"))) {
		printf("= ");
		printf("true");
    }

	else if (!(strcmp(command, "undo"))) {
		printf("= ");
		printf("true");
	}

	else if (!(strcmp(command, "winner"))) {
		printf("= ");
		printf("true");
	}

	else if (!(strcmp(command, "showboard"))) {
		printf("= ");
		printf("true");
	}

	else {
		printf("? false");
		printf("\n\n");
		return -1;
	}

	printf("\n\n");

	return 0;
}

void list_commands(void) { // List of commands.

	printf("=");
	printf("\n");

	printf("protocol_version\n");
	printf("name\n");
	printf("version\n");
	printf("known_command\n");
	printf("list_commands\n");
	printf("quit\n");
	printf("boardsize\n");
	printf("clear_board\n");
	printf("walls\n");
	printf("playmove\n");
	printf("playwall\n");
	printf("genmove\n");
	printf("undo\n");
	printf("winner\n");
	printf("showboard");

	printf("\n\n");
}

void quit(char** table, int n,struct player **play) { // Free array and list.
	int i;
    struct player *tmp;
    
	for (i = 0; i < N(n); i++) free( *(table + i) );
	free(table);

    while(*play){ // Free list.
        tmp = (*play);
        *play = tmp->next;
        free(tmp);
    }

}

int boardsize(char*** table, int n) { // Create array.
	int i;

	*table = malloc(N(n) * sizeof(char*));
	
    if ((*table) == NULL){
		printf("Error in memory allocation\n\n");
		return -1;
	}
	
    for (i = 0; i < N(n); i++) {

		*(*table + i) = malloc(M(n) * sizeof(char));
		
        if (*(*table + i) == NULL) {
			printf("Error in memory allocation\n\n");
			return -1;
		}
	}
	
    printf("=\n\n");
    return 0;
}

int clear_board(char **table, int n, struct player **play) { // Set new array.
	int i, j;
	struct player *B, *W; // Create new nodes. 

	for (i = 0; i < N(n); i++) {
		for (j = 0; j < M(n); j++) {
			if ((i % 2 == 0) && (j % 4 == 0)) table[i][j] = '+';
			if ((i % 2 == 0) && (j % 4 != 0)) table[i][j] = '-';
			if ((i % 2 != 0) && (j % 4 == 0)) table[i][j] = '|';
			if ((i % 2 != 0) && (j % 4 != 0)) table[i][j] = ' ';
			table[(2 * n) - 1][(2 * n)] = 'W';
			table[1][(2 * n)] = 'B';
		}
	}

	// Save the "2 first conditions" of black and white pawn.//
		
    B = malloc(sizeof(struct player)); // For black.
		
    if (B == NULL) {
		printf("Error in memory allocation\n\n");
		return -1;
	}

	B->color = 'B';
	B->position_let = ('A' + (n / 2));
	B->position_num = n;
	B->r_walls = 0;
	B->wall_let = 0;
	B->wall_num = 0;
	B->orient = 0;

	W = malloc(sizeof(struct player)); // For white.
	
    if (W == NULL) {
		printf("Error in memory allocation\n\n");
		return -1;
	}
	
    W->color = 'W';		
    W->position_let = ('A' + (n / 2));
	W->position_num = 1;
	W->r_walls = 0;
	W->wall_let = 0;
	W->wall_num = 0;
	W->orient = 0;

	// Each time we insert new move at start(last move-first node).//
	
    B->next = (*play); // Rearrange list with B as last node...
	(*play) = B;
	W->next = (*play);  // ...and W as the node before the last.
	(*play) = W;


	printf("=\n\n");
	return 0;
}

int wallsf(struct player **play) { // Set walls.
	int walls;

	getchar(); // Ignore space.
	scanf("%d", &walls);

	(*play)->r_walls = walls; // Walls of white.
	(*play)->next->r_walls = walls; // Walls of black.

	printf("=\n\n");

	return 0;
}

int undo(char **table, int n, struct player **play) {
	int times = 0; // Times to undo.
	int x, y, i; // x,y: cordinates of pawns. 

	getchar(); // Ignore space.
	scanf("%d", &times);

	if (times > total_plays) {
		printf("? cannot undo\n\n");
		return 0;
	}

	while (*play) {

		if (times == 0) break; // Terminate condition.
		
        i = 0;

		if ((*play)->position_num == 0) { // If true,last move was playwall.

			x = (2 * n) - (2 * ((*play)->wall_num)) + 2; // Line of last wall played.
			y = (4 * (((*play)->wall_let) - 65)) + 1; // Collumn.

			if ((*play)->orient == 'V') { // Wall was placed vertically. 
				
                y += 3;
				x -= 1;
				
                while (i != 3) { // Remove wall-restore array. 

					if (i % 2 == 0) table[x + i][y] = '|';
					else table[x + i][y] = '+';
					i++;
				}

			}
			else if ((*play)->orient == 'H') {	// Wall was placed horizontally.

				while (i != 7) { // Remove wall-Restore array.

					if (i == 3) table[x][y + i] = '+';
					else table[x][y + i] = '-';
					i++;
				}
			}
		} 
	    else { // If none of the above,then last move was playmove.
			int last_x, last_y; // Cordinates of previous position.
			int color;

			x = (2 * n) - (2 * (*play)->position_num) + 1;
			y = (4 * ((*play)->position_let - 65)) + 2; 

			color = (*play)->color; // Save color of player.
			table[x][y] = ' '; // Remove character from array.

			struct player *help;
			help = (*play)->next;

			while (help) { // Find previous move to restore it.

				if (help->position_let != 0 && help->color == color) {
					last_x = (2 * n) - (2 * (help)->position_num) + 1;
					last_y = (4 * ((help)->position_let - 65)) + 2;
					table[last_x][last_y] = color; // Save character color to array.
					break;
				}
				else help = help->next;
			}
		}

		struct player *tmp;
        
        // Delete last move from list.//	
		
        tmp = (*play); 
		(*play) = tmp->next;
		free(tmp);

        // Reduce times of total_plays and times of undo. //

		times--; 			
        total_plays--;
	}

	printf("=\n\n");

	return 0;
}

int winner(struct player *head, int n) {
	char color;

	// Check if W is on top line or B on bottom line.//

	if (head->color == 'W' && head->position_num == n) printf("= true white\n\n");
	else if (head->color == 'B' && head->position_num == 1) printf("= true black\n\n");
	else printf("= false\n\n");

	return 0;
}

void showboard(char **table, int n, struct player *play) { // Print current array.
	int i, j, number = n;
	int walls_white, walls_black;
	struct player *tmp;

	tmp = play;

	while (tmp) { // Find white's number of walls.
		if (tmp->color == 'W') {
			walls_white = tmp->r_walls;
			break;
		}
		else tmp = tmp->next;
	}

	tmp = play;

	while (tmp) { // Find black's number of walls.
		if (tmp->color == 'B') {
			walls_black = tmp->r_walls;
			break;
		}
		else tmp = tmp->next;
	} 

	printf("=");
	printf("\n");
	printf("   ");

	for (i = 0; i < n; i++) { // Print upper letters of array(A to Z).
		putchar(65 + i);
		printf("   ");
	}

	printf("\n"); 

	for (i = 0; i < N(n); i++) {

		if (i % 2 == 1) printf("%d", number); // Print left side numbers of the array.
		else printf(" ");
		
        for (j = 0; j < M(n); j++) {

			printf("%c", table[i][j]);
			
            if (j == M(n) - 1) {

				if (i % 2 == 1) {
					
                    printf("%d", number); // Print right side numbers of the array.
					number--;
					
                    if (i == 1) { // Print number of walls of black.
						printf(" ");
						printf(" black walls:%d ", walls_black);
					}
					if (i == 3) { // Print number of walls of white.
						printf(" ");
						printf(" white walls:%d ", walls_white);
					}
				}
				else {
					printf(" ");
				}
			}
		}
		
		printf("\n");
	}

	printf("   ");

	for (i = 0; i < n; i++) { // Print lower letters of array.
		putchar(65 + i);
		printf("   ");
	}



	printf("\n\n");
}


int save_playmove(char color, char dest_let, int dest_num, struct player ** play, const int  walls) { // Creation of new node(move) with it's details.
	struct player *tmp;

	total_plays++; // We increase number of total_plays.

	tmp = malloc(sizeof(struct player));
		
    if(tmp == NULL){
        printf("Error in memory allocation\n\n");
        return -1;
    }
        
    tmp->color = color;
	tmp->position_let = dest_let;
	tmp->position_num = dest_num;
	tmp->wall_num = 0;  // Because no walls played(Basically 0 here indicates that this move is a playmove).
	tmp->wall_let = 0;
	tmp->r_walls = walls; 
	tmp->orient = 0;
	tmp->next = (*play);
		
    (*play) = tmp;

    return 0;
}

// Editors:
// sdi1500129.
// sdi1500195.
