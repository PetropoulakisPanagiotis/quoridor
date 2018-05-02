#ifndef QUOR // Compile once.
#define QUOR

// We use these equations, to create the board. //

#define N(a) ((2 * a) + 1) 
#define M(a) ((4 * a) + 1)
	
extern int total_plays;

struct player { // Struct of each player's move.

	char color; // B or W.
	int r_walls; // Number of remaining walls.
	int position_num; // 1 up to n, position of pawn.
	char position_let; // A up to (A + n - 1), position of pawn.
	int wall_num; // Number of played wall in specific move.
	char wall_let; // Letter of played wall in specific move.
	char orient; // Orientation of played wall in specific move.
	struct player *next;

}; 

void protocol_version(void);

void name(void);

void version(void);

int known_command(void);

void list_commands(void);

void quit(char**, int, struct player **);

int boardsize(char ***, int);

int clear_board(char **, int, struct player **);

void showboard(char **, int, struct player *);

int wallsf(struct player **);

int playmove(char **, int, struct player **);

int save_playmove(char, char, int, struct player **, const int);

int playwall(char **, int, struct player **);

int check(char **, int **, int, int, int, char, char);

int winner(struct  player *, int);

int undo(char **, int, struct player **);

int genmove(char **, int, struct player **);

#endif

// Editors:
// sdi1500129
// sdi1500195
