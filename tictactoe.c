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

    // send intro messages
    char *msg = "Welcome to Tic Tac Toe, player 2!\n";
    if (send(connect_d, msg, strlen(msg), 0) == -1){
      error("Can't send");
    }
    
    srand(time(NULL)); 
    int i = rand() % 2;
    printf("%d\n", i);
    int curr_player;
    char *msg2;
    char *msg3;
    char *msg4 = "Please wait for Player 1 to finish their turn.\n";
    char *msg5 = "Your turn, Player 2. Please pick a remaining square [1-9]\n";

    int square_choice;
    char choice_str[1];
    char squares[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    int win = 0;
    
    if (i == 0){
        
        char *msg2 = "Player 1 will start. Please wait for them to pick a square\n";
        send(connect_d, msg2, strlen(msg2), 0);
        puts("Player 1 you go first! Please pick a square [1-9]");
        print_board_host(squares);
        scanf("%s", choice_str);
        square_choice = atoi(choice_str);
        squares[square_choice] = 'X';

        // if (check_valid_move(squares, square_choice) == 1){
        //     squares[square_choice] = 'X';
        // }
        // else {
        //     puts("Invalid Move");
        //     curr_player ++;
        // }
        curr_player = 0;
    }
             
    else {
        
        puts("Player 2 will start. Please wait for them to pick a square");

        char *msg3 = "Player 2 you go first! Please pick a square [1-9]\n";
        send(connect_d, msg3, strlen(msg3), 0);
        print_board_player(squares, connect_d);
        read_in(connect_d, choice_str, sizeof(choice_str));
        square_choice = atoi(choice_str);
        squares[square_choice] = 'O';

        // if (check_valid_move(squares, square_choice) == 1){
        //     squares[square_choice] = 'O';
        // }
        // else {
        //     puts("Invalid Move");
        //     curr_player ++;
        // }
        curr_player = 1;
    }
    
    while (win==0){
        print_board_host(squares);
        print_board_player(squares, connect_d);
        switch (curr_player){
            case 1:
                // GAME Player 1
                send(connect_d, msg4, strlen(msg4), 0);

                puts("Your turn, Player 1. Please pick a remaining square [1-9]");
                scanf("%s", choice_str);
                square_choice = atoi(choice_str);
                squares[square_choice] = 'X';

                // if (check_valid_move(squares, square_choice) == 1){
                //     squares[square_choice] = 'X';
                // }
                // else {
                //     puts("Invalid Move");
                //     curr_player ++;
                // }
            case 0:
                // GAME Player 2
                puts("Please wait for Player 2 to finish their turn.");

                send(connect_d, msg5, strlen(msg5), 0);
                read_in(connect_d, choice_str, sizeof(choice_str));
                square_choice = atoi(choice_str);
                squares[square_choice] = 'O';

                // if (check_valid_move(squares, square_choice) == 1){
                //     squares[square_choice] = 'O';
                // }
                // else {
                //     puts("Invalid Move");
                //     curr_player ++;
                // }
        }
        curr_player = (curr_player ++) % 2;
        win = check_win_cond(squares);
    }
    
    if (win==-1){
        puts("Tie Game!");
        char *msgTie = "Tie Game!\n";
        send(connect_d, msgTie, strlen(msgTie), 0);
    }

    else if (curr_player = 1 && win==1){
        puts("You Win!");
        char *msgLoss = "Player 1 wins, sorry!\n";
        send(connect_d, msgLoss, strlen(msgLoss), 0);
    }

    else if (curr_player = 0 && win==1){
        puts("Player 2 wins, sorry!");
        char *msgLoss = "You Win!\n";
        send(connect_d, msgLoss, strlen(msgLoss), 0);
    }
}

void print_board_host(char *squares){
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
        
    else if (squares[1] != '1' && squares[2] != '2' && squares[3] != '3' &&
        squares[4] != '4' && squares[5] != '5' && squares[6] != '6' && squares[7] 
        != '7' && squares[8] != '8' && squares[9] != '9')

        return -1;
    else
        return  0;
}

// int check_valid_move(char *squares, int square_choice){
//     if (square_choice == '1' && squares[1] == '1'){
//             return 1;
//         }
//         else if (square_choice == '2' && squares[2] == '2'){
//             return 1;
//         }
//         else if (square_choice == '3' && squares[3] == '3'){
//             return 1;
//         }
//         else if (square_choice == '4' && squares[4] == '4'){
//             return 1;
//         }
//         else if (square_choice == '5' && squares[5] == '5'){
//             return 1;
//         }
//         else if (square_choice == '6' && squares[6] == '6'){
//             return 1;
//         }
//         else if (square_choice == '7' && squares[7] == '7'){
//             return 1;
//         }
//         else if (square_choice == '8' && squares[8] == '8'){
//             return 1;
//         }
//         else if (square_choice == '9' && squares[9] == '9'){
//             return 1;
//         }
//         else {
//             return 0;
//         }
//     }
