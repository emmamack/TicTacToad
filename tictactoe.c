#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "helpers.h"
#include "games.h"


void play_tictactoe(int connect_d) {

    // Send intro message
    char *msg = "Welcome to Tic Tac Toe, Player 2!\n";
    if (send(connect_d, msg, strlen(msg), 0) == -1){
      error("Can't send");
    }
    
    // Randomize which player starts
    srand(time(NULL)); 
    int i = rand() % 2;
    int curr_player;

    // Messages to send Player 2 during the game
    char *msg2 = "Player 1 will start. Please wait for them to pick a "
                 "square\n";
    char *msg3 = "Player 2 you go first! Please pick a square [1-9]\n";;
    char *msg4 = "Please wait for Player 1 to finish their turn.\n";
    char *msg5 = "Your turn, Player 2. Please pick a remaining square [1-9]\n";

    int square_choice;
    char choice_str[2];

    // Array to store the current game board
    char squares[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    // Integer to represent the game state
    int win = 0;
    
    // First round tells players who is going first
    if (i == 0){
        send(connect_d, msg2, strlen(msg2), 0);
        puts("Player 1 you go first! Please pick a square [1-9]");
        print_board_host(squares);

        // Take in host input as a string, convert to integer, and update the
        // respective board square.
        scanf("%s", choice_str);
        square_choice = atoi(choice_str);
        squares[square_choice] = 'X';
        print_board_host(squares);

        // Update current player counter
        curr_player = 0;
    }
             
    else {
        
        puts("Player 2 will start. Please wait for them to pick a square");
        send(connect_d, msg3, strlen(msg3), 0);
        print_board_player(squares, connect_d);

        // Take in player input as a string, convert to integer, and update the
        // respective board square.
        char plyr_choice_str[3];
        read_in(connect_d, plyr_choice_str, sizeof(plyr_choice_str));
        char* guess = plyr_choice_str;
        square_choice = atoi(plyr_choice_str);
        squares[square_choice] = 'O';
        print_board_player(squares, connect_d);

        // Update current player counter
        curr_player = 1;
    }
    
    while (win==0){
        
        
        if (curr_player%2 == 1){
                // Player 1 Turn
                send(connect_d, msg4, strlen(msg4), 0);

                print_board_host(squares);
                puts("Your turn, Player 1. Please pick a remaining square "
                     "[1-9]");
                scanf("%s", choice_str);
                square_choice = atoi(choice_str);
                squares[square_choice] = 'X';
                print_board_host(squares);
        }
        else {
                // Player 2 Turn
                puts("Please wait for Player 2 to finish their turn.");

                print_board_player(squares, connect_d);
                send(connect_d, msg5, strlen(msg5), 0);

                char plyr_choice_str[3];
                read_in(connect_d, plyr_choice_str, sizeof(plyr_choice_str));
                char* guess = plyr_choice_str;
                
                square_choice = atoi(plyr_choice_str);
                squares[square_choice] = 'O';
                print_board_player(squares, connect_d);
        }
        // Update current player counter
        curr_player ++;
        
        // Check if the game has ended
        win = check_win_cond(squares);
    }
    
    // Print the outcome of the game to host and client
    if (win==-1){
        puts("Tie Game!");
        char *msgTie = "Tie Game!\n";
        send(connect_d, msgTie, strlen(msgTie), 0);
    }

    else if ((win == 1) && (curr_player %2 == 0)){
        puts("You Win!");
        char *msgLoss = "Player 1 wins, sorry!\n";
        send(connect_d, msgLoss, strlen(msgLoss), 0);
    }

    else if ((win == 1) && (curr_player %2 == 1)){
        puts("Player 2 wins, sorry!");
        char *msgLoss = "You Win!\n";
        send(connect_d, msgLoss, strlen(msgLoss), 0);
    }
}

void print_board_host(char *squares){
    /*

    Print the current board state as a visual tic-tac-toe to the host

    Input
    - squares, a pointer to a character array that represents the game board

    */
    
    printf("   |   |   \n");
    printf(" %c | %c | %c\n", squares[1], squares[2], squares[3]);
    printf("___|___|___\n");
    printf("   |   |   \n");
    printf(" %c | %c | %c\n", squares[4], squares[5], squares[6]);
    printf("___|___|___\n");
    printf("   |   |   \n");
    printf(" %c | %c | %c\n", squares[7], squares[8], squares[9]);
    printf("   |   |   \n");
}

void print_board_player(char *squares, int connect_d){
    /*
    
    Print the current board state as a visual tic-tac-toe to the client

    Inputs
    - squares: a pointer to a character array that represents the game board
    - connect_d: an integer of the client's address

    */
    
    char *msg_vert = "   |   |   \n";
    char *msg_horiz = "___|___|___\n";
    char msg_row1[12];
    sprintf(msg_row1, " %c | %c | %c\n", squares[1], squares[2], squares[3]);

    char msg_row2[12];
    sprintf(msg_row2, " %c | %c | %c\n", squares[4], squares[5], squares[6]);

    char msg_row3[12];
    sprintf(msg_row3, " %c | %c | %c\n", squares[7], squares[8], squares[9]);
    
    send(connect_d, msg_vert, strlen(msg_vert), 0);
    send(connect_d, msg_row1, strlen(msg_row1), 0);
    send(connect_d, msg_horiz, strlen(msg_horiz), 0);
    send(connect_d, msg_vert, strlen(msg_vert), 0);
    send(connect_d, msg_row2, strlen(msg_row2), 0);
    send(connect_d, msg_vert, strlen(msg_vert), 0);
    send(connect_d, msg_horiz, strlen(msg_horiz), 0);
    send(connect_d, msg_vert, strlen(msg_vert), 0);
    send(connect_d, msg_row3, strlen(msg_row3), 0);
    send(connect_d, msg_vert, strlen(msg_vert), 0);

};

int check_win_cond(char *squares){
    /*
    
    Check if the game of tic-tac-toe has ended

    Input
    - squares, a pointer to a character array that represents the game board

    Return
    - 1 if the game is won
    - -1 if the game is tied
    - 0 if the game has not ended yet
    */
    
    // Return 1 if any player has 3 marks in a row (horizontally, vertically,
    // or diagonally)
    if (squares[1] == squares[2] && squares[2] == squares[3])
        return 1;
        
    else if (squares[4] == squares[5] && squares[5] == squares[6])
        return 1;
        
    else if (squares[7] == squares[8] && squares[8] == squares[9])
        return 1;
        
    else if (squares[1] == squares[4] && squares[4] == squares[7])
        return 1;
        
    else if (squares[2] == squares[5] && squares[5] == squares[8])
        return 1;
        
    else if (squares[3] == squares[6] && squares[6] == squares[9])
        return 1;
        
    else if (squares[1] == squares[5] && squares[5] == squares[9])
        return 1;
        
    else if (squares[3] == squares[5] && squares[5] == squares[7])
        return 1;
        
    // Return -1 if the board is full, but no player has 3 marks in a row 
    else if (squares[1] != '1' && squares[2] != '2' && squares[3] != '3' &&
        squares[4] != '4' && squares[5] != '5' && squares[6] != '6' && 
        squares[7] != '7' && squares[8] != '8' && squares[9] != '9')

        return -1;
    // Return 0 if the game has not ended
    else
        return  0;
}
