#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

int total_plays = 0; // Moves' counter, useful for undo command.

int main(void) {
	char command[100]; // Array that keeps current command name.
	char **table; // Game table.
	int  choose = 0, n = 0, flag = 0; // Choose: choosen command, n: size of board, flag: existance of board.
	int ch; // Helps discard invalid text given.
	struct player *play = NULL; // Pointer to list of moves.


	while (1) {

		scanf("%s", command);
		
		if (!(strncmp(command, "#", 1))) { // Text counts as comment.
			
			while ((ch = getchar()) != '\n'); 
			continue; // Read next command.
		}
    
        // Compare our string if it is the same with available commands.//

		if (!(strcmp(command, "protocol_version"))) choose = 1; 
        
        else if (!(strcmp(command, "name"))) choose = 2;

		else if (!(strcmp(command, "version"))) choose = 3;

		else if (!(strcmp(command, "known_command"))) choose = 4;

		else if (!(strcmp(command, "list_commands"))) choose = 5;

		else if (!(strcmp(command, "quit"))) choose = 6;

		else if (!(strcmp(command, "boardsize"))) choose = 7;

		else if (!(strcmp(command, "clear_board"))) choose = 8;

		else if (!(strcmp(command, "walls"))) choose = 9;

		else if (!(strcmp(command, "playmove"))) choose = 10;

		else if (!(strcmp(command, "playwall"))) choose = 11;

		else if (!(strcmp(command, "genmove"))) choose = 12;

		else if (!(strcmp(command, "undo"))) choose = 13;

		else if (!(strcmp(command, "winner"))) choose = 14;

		else if (!(strcmp(command, "showboard"))) choose = 15;

		else choose = 0; // In case of not acceptable command given.

        // Use command given through 'choose'.//

		switch (choose) {

		    case 1: // Command: protocol_version.

			    protocol_version();
		    	break;

	    	case 2: // Command: name.

		    	name();
			    break;

		    case 3: // Command: version.

			    version();
			    break;

		    case 4: // Command: known_command.

			    known_command();
			    break;

		    case 5: // Command: lists_commands.

			    list_commands();
			    break;

		    case 6: // Command: quit.
			    
                if (flag == 1) quit(table, n,&play); // Free dynamically allocated memory.
			    return 0;

			    break;

		    case 7: // Command: boardsize.

			    scanf("%d", &n); // Read size.

			    if (n < 3 || n > 25) { // Not accepted size.
				    printf("? unacceptable size\n\n");
				    break;
			    }

			    flag = 1; // We create array. If quit command given we must free it. 
			    boardsize(&table, n); 

			    break;

		    case 8: // Command: clear_board.

			    clear_board(table, n, &play);

			    /*The board is cleared, the two pawns return to their starting position,
			    the number of walls of each player become zero and the move history is reset to empty.*/

			    break;

		    case 9: // Command: walls.

			    wallsf(&play); // Set walls at the beggining.
			    break;

	    	case 10: // Command: playmove

		    	playmove(table, n, &play);
			    break;

		    case 11: // Command: playwall.

			    playwall(table, n, &play);
			    break;

		    case 12: // Command: genmove.

			    genmove(table, n, &play);
			    break;

    		case 13: // Command: undo.

	    		undo(table, n, &play);
			    break;

            case 14: // Command: winner.

			    winner(play, n);
			    break;

		    case 15: // Command: showboard.

			    showboard(table, n, play);
		    	break;

		    default: // Invalid command.

			    while ((ch = getchar()) != '\n'); // Read the whole "wrong" syntax line and discard it.
				printf("? unknown command\n\n");
			    break;
	
        } // End switch. 


		fflush(stdout);
	} // End while.

    return 0;
}

// Editors:
// sdi1500129.
// sdi1500195.
