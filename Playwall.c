#include <stdio.h>
#include "Header.h"
#include <stdlib.h>
#include <string.h>

int playwall(char **table, int n, struct player **play) {
	char cplayer[50]; // cplayer: Color of player. 
	char keep_or[50]; // Keep_or : horizontal or vertical.
	char dest_let, color, orientation, opp, ch; // dest_let: destination letter , orientation: Horizontal or vertical, opp: color of opponent.
	int dest_num; // dest_num: destination number.
	struct player *head;
	int x,y,w = 0; // x,y: to have access in our main board,w: Check if player has any walls left.

	head = (*play);

	scanf("%s", cplayer); // Read who plays.

	if (!strcmp(cplayer, "black")) {
		color = 'B';
		opp = 'W';  	
	} 
	else if (!strcmp(cplayer, "white")) {
		color = 'W';  
		opp = 'B';
	}
	else { 
		while ((ch = getchar()) != '\n'); // Read the whole "wrong" syntax line and ignore it.
		printf("\n? invalid syntax");
		printf("\n\n");
		return -1;
	}

	getchar(); // Ignore space.
	scanf("%c%d", &dest_let, &dest_num);
	
    if (dest_let < 65 || dest_let > (65 + n - 1) || dest_num > n || dest_num < 1) { 
		
        while ((ch = getchar()) != '\n'); // Read the whole "wrong" syntax line and discard it.
		printf("\n? invalid syntax");
		printf("\n\n");
		
        return -1;
	} 
	

	getchar();
	scanf("%s", keep_or);

	if (!strcmp(keep_or, "horizontal")) orientation = 'H';
	else if (!strcmp(keep_or, "vertical")) orientation = 'V';
	else { 
		while ((ch = getchar()) != '\n'); // Read the whole "wrong" syntax line and discard it.
		printf("\n? invalid syntax");
		printf("\n\n");
		return -1;
	} 
	
	while (head) { // Find number of remaining walls.
		if (head->color == color) {
			w = head->r_walls;
			break;
		}
		else head = head->next;
	}

	if (w == 0) { // No walls.
		printf("? illegal move\n\n");
		return 1;
	} // A mistake.

	if ((dest_num > n) || (dest_num <= 1) || (dest_let < 65) || (dest_let > 65 + (n - 2))) {
		printf("? illegal move\n\n");
		return 1;
	} // B mistake.


	x = (2 * n) - (2 * dest_num) + 2; // Lines
	y = (4 * (dest_let - 65)) + 1; // Columns.


	// First put wall on board and then check if it is valid.//

	if (orientation == 'H') { // Put horizontal.
		int i = 0;

		while (i != 7) {
			if (table[x][y + i] == '=' || table[x][y + i] == 'H') { 
				printf("? illegal move\n\n");
				return 0;
			} // C mistake.
			i++;
		}
		i = 0;

		while (i != 7) { // Place wall on board.
			table[x][y + i] = '=';
			i++;
		}
	}
	if (orientation == 'V') { // Put vertical.
		int i = 0;
		y += 3; 
		x -= 1;

		while (i != 3) {
			if (table[x + i][y] == 'H' || table[x + i][y] == '=') {
				printf("? illegal move\n\n");
				return 0;
			} // C mistake.
			i++;
		}
		i = 0;

		while (i != 3) { // Place wall on board.
			table[x + i][y] = 'H';
			i++;
		}
	}

	// Check if playwall is valid.//


	int current_num;
	char  current_let; // Find where is the pawn.
	
	head = (*play);

	while (head) {
		if (head->color == color && (head->position_let != 0)) { // Find last position of the pawn.
			current_let = head->position_let;
			current_num = head->position_num;
			break;
		}
		else
			head = head->next;
	}

	int **ptr; // 'Help' array for recursion check.
	int a, b, status = 0;


	ptr = malloc(n * sizeof(int *));

	if (ptr == NULL) {
		printf("Error in memory allocation\n\n");
		return -1;
	}

	for (a = 0; a < n; a++) {
		
        *(ptr + a) = malloc(n * sizeof(int));
		
        if (*(ptr + a) == NULL) {
			printf("Error in memory allocation\n\n");
			return -1;
		}
	}

	for (a = 0; a < n; a++) // Fill the 'help' array with -1 , then will know if already checked a path.
		for (b = 0; b < n; b++)
			ptr[a][b] = -1;

	ptr[n - current_num][current_let - 65] = 1;

	status = check(table, ptr, n, n - current_num, current_let - 65, color, opp);
	
	head = (*play);

	while (head) {
		if (head->color == opp && (head->position_let != 0)) { // Check if emeny can win.
			current_let = head->position_let;
			current_num = head->position_num;
			break;
		}
		else
			head = head->next;
	}
	
	for (a = 0; a < n; a++)
		for (b = 0; b < n; b++)
			ptr[a][b] = -1;

	ptr[n - current_num][current_let - 65] = 1;
	
	// If status == 1 means that our color player can win so we check for opponent.//
	
	if (status == 1) status = check(table, ptr, n, n - current_num, current_let - 65, opp, color); // If status remains 1, then both player can win.
	
	if (status == 1) { // If both players can win we save playwall.
		struct player *tmp;
		
		printf("=\n\n");

		total_plays++; // We increase total plays.

		tmp =  malloc(sizeof(struct player));

        if(tmp == NULL){
            printf("Error in memory allocation\n\n");
            return -1;
        }

		tmp->color = color;
		tmp->position_let = 0;
		tmp->position_num = 0;
		tmp->wall_let = dest_let;
		tmp->wall_num = dest_num;
		tmp->r_walls = (--w); // Decrease player's walls.
		tmp->orient = orientation;
		tmp->next = (*play);
		(*play) = tmp;
		return 0;
	}
	else { // Not valid move, so must remove the placed walls.
		int i = 0;
	
        printf("? illegal move\n\n");
	
		if (orientation == 'H') { 
			while (i != 7) { 
				if (i == 3) table[x][y + i] = '+';
				else table[x][y + i] = '-';
				i++;
			}
		}
		else if (orientation == 'V') {
			while (i != 3) { 
				if (i % 2 == 0)
					table[x + i][y] = '|';
				else
					table[x + i][y] = '+';
				i++;
			}
		}
	}

	return 0;
}

// Editors:
// sdi1500129.
// sdi1500195.
