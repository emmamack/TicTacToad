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
    int square_choice;
    char choice_str[1];
    char mark = 'X';
    char square[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    
    if (i == 0){
        printf("P1 Loop\n");
        curr_player = 1;
        char *msg2 = "Player 1 will start. Please wait for them to pick a square\n";
        send(connect_d, msg2, strlen(msg2), 0);
        puts("Player 1 you go first! Please pick a square [1-9]\n");
        scanf("%s", choice_str);
        square_choice = atoi(choice_str);
    }
             
    else {
        curr_player = 2;
        puts("Player 2 will start. Please wait for them to pick a square\n");

        char *msg3 = "Player 2 you go first! Please pick a square [1-9]\n";
        send(connect_d, msg3, strlen(msg3), 0);
        read_in(connect_d, choice_str, sizeof(choice_str));
        square_choice = atoi(choice_str);
    }
    

    // char answer_array[80];
    // char *answer_str = answer_array;
    // puts("Welcome to 20 questions! Player 1, what word are you thinking of? ");
    // scanf("%s", answer_str);

    // char buf[255];

    // for (int i = 1; i < 21; i++) {
    //     char *msg4 = "Player 2: Ask a yes or no question, or enter a guess: \n";
    //     send(connect_d, msg2, strlen(msg2), 0);

    //     // read player 2 guess
    //     char guess_array[80];
    //     read_in(connect_d, guess_array, sizeof(guess_array));
    //     char* guess = guess_array;
    //     printf("%s\n", guess_array);

    //     // check for correct guess
    //     int res = strcmp_CRignore(answer_str, guess);
    //     if (res) {
    //       printf("Player 2 guessed the answer: \"%s\"!  Guessed in %i questions.\n", answer_str, i);
    //       char *end_msg = "You guessed it! Goodbye.\n";
    //       send(connect_d, end_msg, strlen(msg2), 0);
    //       break;
    //     }

    //     // Player 1 answers Y/N
    //     printf("Player 1: answer yes or no: ");
    //     scanf("%s", buf);
    //     char *response = strcat(buf, "\n");
    //     send(connect_d, response, strlen(response), 0);
    // }
}
