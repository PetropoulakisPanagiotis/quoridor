#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"



int playmove(char **table, int n, struct player **play) {
	char cplayer[50]; // cplayer: Color of player. 
	char dest_let, current_let, color, opp; // dest_let: destination letter,current_let:current letter of pawn, opp : opponent
	int walls, dest_num, current_num, prev_x = 0, prev_y = 0, next_x = 0, next_y = 0; // dest_num: destination number,current_num: current number, prev-next: To have access in our board.
	struct player *head;
	int ch; 

	head = (*play);

	scanf("%s", cplayer);

	if (!strcmp(cplayer, "black")) {
		color = 'B';
		opp = 'W';
	}
	else if (!strcmp(cplayer, "white")) {
		color = 'W';
		opp = 'B';
	}
	else { // If playmove xxxx C5 or playmove xxxx xxxx given, xxxx means wrong arguments.

		while ((ch = getchar()) != '\n'); // Read the whole "wrong" syntax line and discard it.
		printf("\n? invalid syntax");
		printf("\n\n");

		return -1;
	}

	getchar(); // Ignore space.
	scanf("%c%d", &dest_let, &dest_num); // Scan Destination.

	if (dest_let < 65 || dest_let > (65 + n - 1) || dest_num > n || dest_num < 1) { // Check if cordinates given are valid
		printf("\n? illegal move");
		printf("\n\n");
		return -1;
	} 

	while (head) { // Find pawn's position
		if (head->color == color && head->wall_num == 0) {
			current_num = head->position_num;
			current_let = head->position_let;
			break;
		}
		else head = head->next;
	}

	head = (*play);

	while (head) { // Keep previous walls for the new node
		if (head->color == color) {
			walls = head->r_walls;
			break;
		}
		else head = head->next;
	}

	// Find cordinates of pawn in board  
	prev_x = (2 * n) - (2 * current_num) + 1;
	prev_y = (4 * (current_let - 65)) + 2;

	next_x = (2 * n) - (2 * dest_num) + 1; // Find cordinates of destination on board
	next_y = (4 * (dest_let - 65)) + 2;


	// Check if our move is valid ***Check text file***


	if ((current_let == dest_let) && (current_num) == dest_num) {
		printf("? illegal move\n\n");
		return 1;
	} // A mistake.


	if ((dest_num > n) || (dest_num <= 0) || (dest_let < 65) || (dest_let > 65 + (n - 1))) {
		printf("? illegal move\n\n");
		return 1;
	} // B mistake.


	if ((current_num - dest_num) > 2 || (dest_num - current_num >2) || (dest_let - current_let > 2) || (current_let - dest_let > 2)) {
		printf("? illegal move\n\n");
		return 1;
	} // C mistake. 


	if ((((current_num - dest_num == 2) && (table[prev_x + 2][prev_y] != opp)) || ((dest_num - current_num == 2) && (table[prev_x - 2][prev_y] != opp))) && (dest_let == current_let)) {
		printf("? illegal move\n\n");
		return 1;
	} // D mistake.


	if ((current_num == dest_num) && (table[prev_x][prev_y + 4] != opp) && (dest_let - current_let == 2)) {
		printf("? illegal move\n\n");
		return 1;
	} // E mistake.


	if ((current_num == dest_num) && (table[prev_x][prev_y - 4] != opp)   && (current_let - dest_let == 2)) {
		printf("? illegal move\n\n");
		return 1;
	} // F mistake.

	if ((current_num - dest_num == 1) && (table[prev_x + 2][prev_y] == opp) && (dest_let == current_let)) {
		printf("? illegal move\n\n");
		return 1;
	} // G mistake.

	if ((dest_num -current_num == 1) && (table[prev_x - 2][prev_y] == opp) && (dest_let == current_let)) {
		printf("? illegal move\n\n");
		return 1;
	} // H mistake.

	if ((dest_num == current_num) && (table[prev_x][prev_y - 4] == opp) && (current_let - dest_let == 1)) {
		printf("? illegal move\n\n");
		return 1;
	} // I mistake.

	if ((dest_num == current_num) && (table[prev_x][prev_y + 4] == opp) && (dest_let - current_let == 1)) {
		printf("? illegal move\n\n");
		return 1;
	} // J mistake.

	if ((current_num - dest_num >= 1) && (dest_let == current_let) && (table[prev_x + 1][prev_y] == '=')) {
		printf("? illegal move\n\n");
		return 1;
	} // K mistake.

	if ((dest_num - current_num >= 1) && (dest_let == current_let) && (table[prev_x - 1][prev_y] == '=')) {
		printf("? illegal move\n\n");
		return 1;
	} // L mistake.

	if ((current_num == dest_num) && (dest_let - current_let >= 1) && (table[prev_x][prev_y + 2] == 'H')) {
		printf("? illegal move\n\n");
		return 1;
	} // M mistake.

	if ((current_num == dest_num) && (current_let - dest_let >= 1) && (table[prev_x][prev_y - 2] == 'H')) {
		printf("? illegal move\n\n");
		return 1;
	} // N mistake.

	if ((current_num - dest_num == 2) && (table[prev_x + 2][prev_y] == opp) && (dest_let == current_let) && (table[prev_x + 3][prev_y] == '=')) {
		printf("? illegal move\n\n");
		return 1;
	} // O mistake.


	if ((dest_num - current_num == 2) && (table[prev_x - 2][prev_y] == opp) && (dest_let == current_let) && (table[prev_x - 3][prev_y] == '=')) {
		printf("? illegal move\n\n");
		return 1;
	} // P mistake.

	if ((dest_num == current_num) && (table[prev_x][prev_y + 4] == opp) && (dest_let - current_let == 2) && (table[prev_x][prev_y + 6] == 'H')) {
		printf("? illegal move\n\n");
		return 1;
	} // Q mistake.

	if ((dest_num == current_num) && (table[prev_x][prev_y - 4] == opp) && (current_let - dest_let == 2) && (table[prev_x][prev_y - 6] == 'H')) {
		printf("? illegal move\n\n");
		return 1;
	} // R mistake.

	if ((current_num - dest_num == 1) && (current_let - dest_let == 1)) {
		if (((table[prev_x][prev_y - 4] != opp) || (table[prev_x][prev_y - 6] != 'H') || (table[prev_x + 2][prev_y - 6] != 'H') || (table[prev_x + 1][prev_y - 4] == '=') || (table[prev_x][prev_y - 2] == 'H')) && ((table[prev_x + 2][prev_y] != opp) || (table[prev_x + 3][prev_y] != '=') || (table[prev_x + 3][prev_y - 4] != '=') || (table[prev_x + 2][prev_y - 2] == 'H') || (table[prev_x][prev_y - 2] == 'H') || (table[prev_x + 1][prev_y] == '='))) {
			printf("? illegal move\n\n");
			return 1;
		}
	} // S mistake.

	if ((current_num - dest_num == 1) && (dest_let - current_let == 1)) {
		if (((table[prev_x][prev_y + 4] != opp) || (table[prev_x][prev_y + 6] != 'H') || (table[prev_x + 2][prev_y + 6] != 'H') || (table[prev_x + 1][prev_y + 4] == '=') || (table[prev_x][prev_y + 2] == 'H')) && ((table[prev_x + 2][prev_y] != opp) || (table[prev_x + 3][prev_y] != '=') || (table[prev_x + 3][prev_y + 4] != '=') || (table[prev_x + 2][prev_y + 2] == 'H') || (table[prev_x][prev_y + 2] == 'H') || (table[prev_x + 1][prev_y] == '='))) {
			printf("? illegal move\n\n");
			return 1;
		}
	} // T mistake.


	if ((dest_num - current_num == 1) && (current_let - dest_let == 1)) {
		if (((table[prev_x][prev_y - 4] != opp) || (table[prev_x][prev_y - 6] != 'H') || (table[prev_x - 2][prev_y - 6] != 'H') || (table[prev_x - 1][prev_y - 4] == '=') || (table[prev_x][prev_y - 2] == 'H')) && ((table[prev_x - 2][prev_y] != opp)  || (table[prev_x - 3][prev_y] != '=') || (table[prev_x - 3][prev_y - 4] != '=') || (table[prev_x - 2][prev_y - 2] == 'H') || (table[prev_x][prev_y - 2] == 'H') || (table[prev_x - 1][prev_y] == '='))) {
			printf("? illegal move\n\n");
			return 1;
		}
	} // U mistake.

	if ((dest_num - current_num == 1) && (dest_let - current_let == 1)) {
		if (((table[prev_x][prev_y + 4] != opp) || (table[prev_x][prev_y + 6] != 'H') || (table[prev_x - 2][prev_y + 6] != 'H') || (table[prev_x - 1][prev_y + 4] == '=') || (table[prev_x][prev_y + 2] == 'H')) && ((table[prev_x - 2][prev_y] != opp) || (table[prev_x - 3][prev_y] != '=') || (table[prev_x - 3][prev_y + 4] != '=') || (table[prev_x - 2][prev_y + 2] == 'H') || (table[prev_x][prev_y + 2] == 'H') || (table[prev_x - 1][prev_y] == '='))) {
			printf("? illegal move\n\n");
			return 1;
		} 
	} // V mistake.


	// We save our move to our list and our board, only if it's valid.//

	table[prev_x][prev_y] = ' ';
	table[next_x][next_y] = color; 

	save_playmove(color, dest_let, dest_num, play, walls);

	printf("=\n\n");

	return 0;
}

// Editors:
// sdi1500129.
// sdi1500195.
