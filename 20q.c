#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include "helpers.h"
#include "games.h"

void play_20q(int connect_d) {

    // send intro messages
    char *msg = "Welcome to 20 questions, player 2! Player 1 is thinking of a secret word...\n";
    if (send(connect_d, msg, strlen(msg), 0) == -1)
      error("Can't send");
    char answer_array[80];
    char *answer_str = answer_array;
    puts("Welcome to 20 questions! Player 1, what word are you thinking of? ");
    scanf("%s", answer_str);

    char buf[255];

    for (int i = 1; i < 21; i++) {
        char *msg2 = "Player 2: Ask a yes or no question, or enter a guess: \n";
        send(connect_d, msg2, strlen(msg2), 0);

        // read player 2 guess
        char guess_array[80];
        read_in(connect_d, guess_array, sizeof(guess_array));
        char* guess = guess_array;

        // check for correct guess
        int res = strcmp_CRignore(answer_str, guess);
        if (res) {
          printf("Player 2 guessed the answer: \"%s\"!  Guessed in %i questions.\n", answer_str, i);
          char *end_msg = "You guessed it! Goodbye.\n";
          send(connect_d, end_msg, strlen(end_msg), 0);
          break;
        }

        // Player 1 answers Y/N
        printf("Player 1: answer yes or no: ");
        scanf("%s", buf);
        char *response = strcat(buf, "\n");
        send(connect_d, response, strlen(response), 0);
    }

    char *noqs_msg = "No more questions left, goodbye.\n";
    send(connect_d, noqs_msg, strlen(noqs_msg), 0);
    printf("No more questions left.\n");
}
