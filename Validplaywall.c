#include <stdio.h>
#include "Header.h"
#include <stdlib.h>
#include <string.h>

// Pawn's position in board's cordinates. //

#define xlast ((2 * x) + 1)
#define ylast ((4 * y) + 2) 

// We search if a player can win.//
// ptr[x][y] == -1 if a pawn didn't pass from this cell, or ptr[x][y] == 0 if it passed.//

int check(char **table, int **ptr, int n, int x, int y, char color, char opp) {
	int flag = 0;
	

	if (x == 0 && color == 'W') { // Terminate condition.
		ptr[x][y] = 0;
		flag = 1;
		return flag;
    } 


	if (y == n - 1 && color == 'B') { // Terminate condition.
		ptr[x][y] = 0; 
		flag = 1;
		return flag;
    } 

	if (flag != 1 && x != 0 && ptr[x - 1][y] == -1 && table[xlast - 1][ylast] != '=' &&  table[xlast - 2][ylast] != opp) {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x - 1, y, color, opp);
	} // Condition A

	if (flag != 1 && x > 1 && ptr[x - 2][y] == -1 && table[xlast - 2][ylast] == opp && table[xlast - 1][ylast] != '=' && table[xlast - 3][ylast] != '=') {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x - 2, y, color, opp);
	} // Condition B

	if (flag != 1 && x != 0 && y != 0 && ptr[x - 1][y - 1] == -1 && table[xlast - 2][ylast] == opp &&  table[xlast - 3][ylast] == '=' && table[xlast - 3][ylast - 4] == '=' && (table[xlast - 2][ylast - 2] != 'H') && (table[xlast - 1][ylast] != '=')) {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x - 1, y - 1, color, opp);
	} // Condition C

	if (flag != 1 && x != 0 && y != n - 1 && ptr[x - 1][y + 1] == -1 && table[xlast - 2][ylast] == opp &&  table[xlast - 3][ylast] == '=' && table[xlast - 3][ylast + 4] == '=' && (table[xlast - 2][ylast + 2] != 'H') && (table[xlast - 1][ylast] != '=')) {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x - 1, y + 1, color, opp);
	} // Condition D


	if (flag != 1 && y != 0 && ptr[x][y - 1] == -1 && table[xlast][ylast - 2] != 'H' &&  table[xlast][ylast - 4] != opp) {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x, y - 1, color, opp);
	} // Condition E

	if (flag != 1 && y > 1 && ptr[x][y - 2] == -1 && table[xlast][ylast - 4] == opp && table[xlast][ylast - 2] != 'H' && table[xlast][ylast - 6] != 'H') {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x, y - 2, color, opp);
	} // Condition F

	if (flag != 1 && x != 0 && y != 0 && ptr[x - 1][y - 1] == -1 && table[xlast][ylast - 4] == opp &&  table[xlast][ylast - 6] == 'H' && table[xlast - 2][ylast - 6] == 'H' && table[xlast - 1][ylast - 4] != '=' && table[xlast][ylast - 2] != 'H') {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x - 1, y - 1, color, opp);
	} // Condition G

	if (flag != 1 && x != n - 1 && y != 0 && ptr[x + 1][y - 1] == -1 && table[xlast][ylast - 4] == opp && table[xlast][ylast - 6] == 'H' && table[xlast + 2][ylast - 6] == 'H' && table[xlast + 1][ylast - 4] != '=' && table[xlast][ylast - 2] != 'H') {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x + 1, y - 1, color, opp);
	} // Condition H

	if (flag != 1 && y != n - 1 && ptr[x][y + 1] == -1 && table[xlast][ylast + 2] != 'H' && table[xlast][ylast + 4] != opp) {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x, y + 1, color, opp);
	} // Condition I

	if (flag != 1 && y < n - 2 && ptr[x][y + 2] == -1 && table[xlast][ylast + 4] == opp && table[xlast][ylast + 2] != 'H' &&   table[xlast][ylast + 6] != 'H') {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x, y + 2, color, opp);
	} // Condition J

	if (flag != 1 && x != 0 && y != n - 1 && ptr[x - 1][y + 1] == -1 && table[xlast][ylast + 4] == opp &&   table[xlast][ylast + 6] == 'H' && table[xlast - 2][ylast + 6] == 'H' && table[xlast][ylast + 2] != 'H' && table[xlast - 1][ylast + 4] != '=') {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x - 1, y + 1, color, opp);
	} // Condition K

	if (flag != 1 && x != n - 1 && y != n - 1 && ptr[x + 1][y + 1] == -1 && table[xlast][ylast + 4] == opp && table[xlast][ylast + 6] == 'H' && table[xlast + 2][ylast + 6] == 'H' && table[xlast + 1][ylast + 4] != '=' && table[xlast][ylast + 2] != 'H') {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x + 1, y + 1, color, opp);
	} // Condition L

	if (flag != 1 && x != n - 1 && table[xlast + 1][ylast] != '=' && ptr[x + 1][y] == -1 && table[xlast + 2][ylast] != opp) {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x + 1, y, color, opp);
	} // Condition M

	if (flag != 1 && x < n - 2 && ptr[x + 2][y] == -1 && table[xlast + 2][ylast] == opp && table[xlast + 1][ylast] != '=' &&  table[xlast + 3][ylast] != '=') {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x + 2, y, color, opp);
	} // Condition N

	if (flag != 1 && x != n - 1 && y != 0 && ptr[x + 1][y - 1] == -1 && table[xlast + 2][ylast] == opp &&  table[xlast + 3][ylast] == '=' && table[xlast + 3][ylast - 4] == '=' && (table[xlast + 2][ylast - 2] != 'H') && (table[xlast + 1][ylast] != '=')) {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x + 1, y - 1, color, opp);
	} // Condition O

	if (flag != 1 && x != n - 1 && y != n - 1 && ptr[x + 1][y + 1] == -1 && table[xlast + 2][ylast] == opp &&  table[xlast + 3][ylast] == '=' && table[xlast + 3][ylast + 4] == '=' && (table[xlast + 2][ylast + 2] != 'H') && (table[xlast + 1][ylast] != '=')) {
		ptr[x][y] = 0;
		flag = check(table, ptr, n, x + 1, y + 1, color, opp);
	} // Condition P
	
    return flag;
}
// Editors:
// sdi1500129.
// sdi1500195.
