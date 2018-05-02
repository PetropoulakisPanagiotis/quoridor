#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

int genmove(char **table, int n, struct player **play) {
	char cplayer[50]; // cplayer: Color of player.
	char color, current_let, opp; // Current_let: current position of pawn.
	int walls, current_num, x, y, flag = 0; // x,y: to have access in main board.
	int ch; 
	struct player *tmp;

	
	tmp = (*play);
	
	scanf("%s", cplayer);
	
	
	if (!strcmp(cplayer, "black")) color = 'B';  
	else if (!strcmp(cplayer, "white")) color = 'W'; 

	else { // If genmove xxxx given, xxxx means wrong arguments.

		while ((ch = getchar()) != '\n');  
		printf("\n? invalid syntax");
		printf("\n\n");

		return -1;
	}


	if (color == 'B') opp = 'W';
	else opp = 'B';

	while (tmp) { 

		if (tmp->color == color && flag == 0) {
			walls = tmp->r_walls;
			flag = -1;
		} // We use flag to find the remaining walls of pawn.

		if (tmp->color == color && tmp->wall_let == 0) { // We search last position of pawn. 
			current_num = tmp->position_num;
			current_let = tmp->position_let;

			break;
		}
		else tmp = tmp->next;
	}
	y = (4 * (current_let - 65)) + 2; 
	x = (2 * n) - (2 * current_num) + 1;

	if (color == 'W') {

		if (flag != 1 && x > 3 && table[x - 2][y] == opp && table[x - 1][y] != '=' && table[x - 3][y] != '=') {
			table[x - 4][y] = color;
			table[x][y] = ' ';
			current_num += 2;
			flag = 1;
		} // Move A

		if (flag != 1 && x != 0 && table[x - 1][y] != '=' &&  table[x - 2][y] != opp) {
			table[x - 2][y] = color;
			table[x][y] = ' ';
			current_num++;
			flag = 1;
		} // Move B

		if (flag != 1 && x != 0 && y != 0 && table[x - 2][y] == opp &&  table[x - 3][y] == '=' && table[x - 3][y - 4] == '=' && (table[x - 2][y - 2] != 'H') && (table[x - 1][y] != '=')) {
			table[x - 2][y - 4] = color;
			table[x][y] = ' ';
			current_num++;
			current_let--;
			flag = 1;
		} // Move C

		if (flag != 1 && x != 0 && y != 0 && table[x][y - 4] == opp && table[x][y - 6] == 'H' && table[x - 2][y - 6] == 'H' && table[x - 1][y - 4] != '=' && table[x][y - 2] != 'H') {
			table[x - 2][y - 4] = color;
			table[x][y] = ' ';
			current_num++;
			current_let--;
			flag = 1;
		} // Move D

		if (flag != 1 && x != 0 && y != n - 1 && table[x - 2][y] == opp && table[x - 3][y] == '=' && table[x - 3][y + 4] == '=' && (table[x - 2][y + 2] != 'H') && (table[x - 1][y] != '=')) {
			table[x - 2][y + 4] = color;
			table[x][y] = ' ';
			current_num++;
			current_let++;
			flag = 1;
		} // Move E

		if (flag != 1 && x != 0 && y != n - 1 && table[x][y + 4] == opp && table[x][y + 6] == 'H' && table[x - 2][y + 6] == 'H' && table[x][y + 2] != 'H' && table[x - 1][y + 4] != '=') {
			table[x - 2][y + 4] = color;
			table[x][y] = ' ';
			current_let++;
			current_num++;
			flag = 1;
		} // Move F

		if (flag != 1 && y != 0 && table[x][y - 2] != 'H' && table[x][y - 4] != opp) {
			table[x][y - 4] = color;
			table[x][y] = ' ';
			current_let--;
			flag = 1;
		} // Move G

		if (flag != 1 && y > 1 && table[x][y - 4] == opp && table[x][y - 2] != 'H' && table[x][y - 6] != 'H') {
			table[x][y - 8] = color;
			table[x][y] = ' ';
			current_let -= 2;
			flag = 1;
		} // Move H

		if (flag != 1 && y != n - 1 && table[x][y + 2] != 'H' && table[x][y + 4] != opp) {
			table[x][y + 4] = color;
			table[x][y] = ' ';
			current_let++;
			flag = 1;
		} // Move I

		if (flag != 1 && y < n - 2 && table[x][y + 4] == opp && table[x][y + 2] != 'H' && table[x][y + 6] != 'H') {
			table[x][y + 8] = color;
			table[x][y] = ' ';
		    current_let += 2;
			flag = 1;
		} // Move J

		if (flag != 1 && x != n - 1 && table[x + 1][y] != '=' && table[x + 2][y] != opp) {
			table[x + 2][y] = color;
			table[x][y] = ' ';
			current_num--;
			flag = 1;
		} // Move K

		if (flag != 1 && x != n - 1 && y != 0 && table[x][y - 4] == opp && table[x][y - 6] == 'H' && table[x + 2][y - 6] == 'H' && table[x + 1][y - 4] != '=' && table[x][y - 2] != 'H') {
			table[x + 2][y - 4] = color;
			table[x][y] = ' ';
			current_num--;
			current_let--;
			flag = 1;
		} // Move L

		if (flag != 1 && x != n - 1 && y != 0 && table[x + 2][y] == opp &&  table[x + 3][y] == '=' && table[x + 3][y - 4] == '=' && (table[x + 2][y - 2] != 'H') && (table[x + 1][y] != '=')) {
			table[x + 2][y - 4] = color;
			table[x][y] = ' ';
			current_num--;
			current_let--;
			flag = 1;
		} // Move M

		if (flag != 1 && x != n - 1 && y != n - 1 && table[x + 2][y] == opp &&  table[x + 3][y] == '=' && table[x + 3][y + 4] == '=' && (table[x + 2][y + 2] != 'H') && (table[x + 1][y] != '=')) {
			table[x + 2][y + 4] = color;
			table[x][y] = ' ';
			current_num--;
			current_let++;
			flag = 1;
		} // Move N

		if (flag != 1 && x != n - 1 && y != n - 1 && table[x][y + 4] == opp && table[x][y + 6] == 'H' && table[x + 2][y + 6] == 'H' && table[x + 1][y + 4] != '=' && table[x][y + 2] != 'H') {
			table[x + 2][y + 4] = color;
			table[x][y] = ' ';
			current_let++;
			current_num--;
			flag = 1;
		} // Move O

		if (flag != 1 && x < n - 2 && table[x + 2][y] == opp && table[x + 1][y] != '=' &&  table[x + 3][y] != '=') {
			table[x + 4][y] = color;
			table[x][y] = ' ';
			current_num -= 2;
			flag = 1;
		} // Move P

	}
	else
	{
		if (flag != 1 && x < n - 2 && table[x + 2][y] == opp && table[x + 1][y] != '=' &&  table[x + 3][y] != '=') {
			table[x + 4][y] = color;
			table[x][y] = ' ';
			current_num -= 2;
			flag = 1;
		} // Move P

		if (flag != 1 && x != n - 1 && table[x + 1][y] != '=' && table[x + 2][y] != opp) {
			table[x + 2][y] = color;
			table[x][y] = ' ';
			current_num--;
			flag = 1;
		} // Move K

		if (flag != 1 && x != n - 1 && y != 0 && table[x + 2][y] == opp &&  table[x + 3][y] == '=' && table[x + 3][y - 4] == '=' && (table[x + 2][y - 2] != 'H') && (table[x + 1][y] != '=')) {
			table[x + 2][y - 4] = color;
			table[x][y] = ' ';
			current_num--;
			current_let--;
			flag = 1;
		} // Move M

		if (flag != 1 && x != n - 1 && y != 0 && table[x][y - 4] == opp && table[x][y - 6] == 'H' && table[x + 2][y - 6] == 'H' && table[x + 1][y - 4] != '=' && table[x][y - 2] != 'H') {
			table[x + 2][y - 4] = color;
			table[x][y] = ' ';
			current_num--;
			current_num--;
			flag = 1; 
		} // Move L

		if (flag != 1 && x != n - 1 && y != n - 1 && table[x + 2][y] == opp &&  table[x + 3][y] == '=' && table[x + 3][y + 4] == '=' && (table[x + 2][y + 2] != 'H') && (table[x + 1][y] != '=')) {
			table[x + 2][y + 4] = color;
			table[x][y] = ' ';
			current_num--;
			current_let++;
			flag = 1;
		} // Move N

		if (flag != 1 && x != n - 1 && y != n - 1 && table[x][y + 4] == opp && table[x][y + 6] == 'H' && table[x + 2][y + 6] == 'H' && table[x + 1][y + 4] != '=' && table[x][y + 2] != 'H') {
			table[x + 2][y + 4] = color;
			table[x][y] = ' ';
			current_let++;
			current_num--;
			flag = 1;
		} // Move O

		if (flag != 1 && y != 0 && table[x][y - 2] != 'H' && table[x][y - 4] != opp) {
			table[x][y - 4] = color;
			table[x][y] = ' ';
			current_let--;
			flag = 1;
		} // Move G

		if (flag != 1 && y > 1 && table[x][y - 4] == opp && table[x][y - 2] != 'H' && table[x][y - 6] != 'H') {
			table[x][y - 8] = color;
			table[x][y] = ' ';
			current_let -= 2;
			flag = 1;
		} // Move H

		if (flag != 1 && y != n - 1 && table[x][y + 2] != 'H' && table[x][y + 4] != opp) {
			table[x][y + 4] = color;
			table[x][y] = ' ';
			current_let++;
			flag = 1;
		} // Move I


		if (flag != 1 && y < n - 2 && table[x][y + 4] == opp && table[x][y + 2] != 'H' && table[x][y + 6] != 'H') {
			table[x][y + 8] = color;
			table[x][y] = ' ';
			current_let += 2;
			flag = 1;
		} // Move J

		if (flag != 1 && x != 0 && y != n - 1 && table[x][y + 4] == opp && table[x][y + 6] == 'H' && table[x - 2][y + 6] == 'H' && table[x][y + 2] != 'H' && table[x - 1][y + 4] != '=') {
			table[x - 2][y + 4] = color;
			table[x][y] = ' ';
			current_let++;
			current_num++;
			flag = 1;
		} // Move F

		if (flag != 1 && x != 0 && y != n - 1 && table[x - 2][y] == opp && table[x - 3][y] == '=' && table[x - 3][y + 4] == '=' && (table[x - 2][y + 2] != 'H') && (table[x - 1][y] != '=')) {
			table[x - 2][y + 4] = color;
			table[x][y] = ' ';
			current_num++;
			current_let++;
			flag = 1;
		} // Move E

		if (flag != 1 && x != 0 && y != 0 && table[x][y - 4] == opp && table[x][y - 6] == 'H' && table[x - 2][y - 6] == 'H' && table[x - 1][y - 4] != '=' && table[x][y - 2] != 'H') {
			table[x - 2][y - 4] = color;
			table[x][y] = ' ';
			current_num++;
			current_let--;
			flag = 1;
		} // Move D

		if (flag != 1 && x != 0 && y != 0 && table[x - 2][y] == opp &&  table[x - 3][y] == '=' && table[x - 3][y - 4] == '=' && (table[x - 2][y - 2] != 'H') && (table[x - 1][y] != '=')) {
			table[x - 2][y - 4] = color;
			table[x][y] = ' ';
			current_num++;
			current_let--;
			flag = 1;
		} // Move C

		if (flag != 1 && x != 0 && table[x - 1][y] != '=' &&  table[x - 2][y] != opp) {
			table[x - 2][y] = color;
			table[x][y] = ' ';
			current_num++;
			flag = 1;
		} // Move B

		if (flag != 1 && x > 1 && table[x - 2][y] == opp && table[x - 1][y] != '=' && table[x - 3][y] != '=') {
			table[x - 4][y] = color;
			table[x][y] = ' ';
			current_num += 2;
			flag = 1;
		} // Move A
	}



	struct player *help; // Save our move.


	total_plays++; 

	help =  malloc(sizeof(struct player));
	
    if (help == NULL){
        printf("Error in memory allocation\n\n");
        return -1;
    }

	help->color = color;
	help->position_let = current_let;
	help->position_num = current_num;
	help->wall_num= 0;
	help->wall_let = 0;
	help->r_walls = walls; 
	help->orient = 0;
	help->next = (*play);
	(*play) = help;

	printf("= %c%d\n\n", current_let, current_num);

	return 0;
}

// Editors:
// sdi1500129.
// sdi1500195.
