#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include "helpers.h"
#include "games.h"

void play_20q(int connect_d) {
    char *msg = "Welcome to 20 questions!\n";
    if (send(connect_d, msg, strlen(msg), 0) == -1)
      error("Can't send");

    printf("Welcome to 20 questions!\n");
    char answer_array[80];
    char *answer_str = answer_array;
    puts("Player 1: What are you thinking of? ");
    scanf("%s", answer_str);

    char buf[255];

    for (int i = 1; i < 21; i++) {
        // Player 1 asks a question, which is saved
        char *msg2 = "Player 2: Ask a yes or no question: \n";
        send(connect_d, msg2, strlen(msg2), 0);
        char guess_array[80];
        read_in(connect_d, guess_array, sizeof(buf));
        char* guess = guess_array;
        printf("%s\n", guess_array);

        // check for correct guess
        printf("guess: %s\n", guess);
        printf("answer_str: %s\n", answer_str);
        printf("len guess: %zu\n", strlen(guess));
        printf("len answer_str: %zu\n", strlen(answer_str));
        int res = strcmp(answer_str, guess);
        printf("res: %d\n", res);
        if (!res) {
          printf("All done!!!!");
        }

        // Player 2 answers Y/N
        puts("Player 1: Enter Y or N, or C if it is the correct answer: ");
        scanf("%s", buf);
        char *response = strcat(buf, "\n");
        send(connect_d, response, strlen(response), 0);

        // Check for correct guess
        if (response[0] == 'C') {
            printf("Correct - Player 1 was thinking of \"%s\"! Guessed in %i questions.\n", answer_str, i);
            break;
        }
    }
}