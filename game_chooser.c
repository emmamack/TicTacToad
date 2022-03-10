#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include "helpers.h"
#include "games.h"

void game_chooser(int connect_d) {
    // send prompt
    char *msg = "----------------------------------------------------------\n|   Welcome to TicTacToad! Enter 1 for \"20 questions\",   |\n|                  2 for \"Tic-Tac-Toe\".                  |\n|         Made with <3 by Emma, Maya, and Berwin         |\n----------------------------------------------------------\n";
    if (send(connect_d, msg, strlen(msg), 0) == -1)
      error("Can't send");

    // get input and compare
    char answer_array[80];
    read_in(connect_d, answer_array, sizeof(answer_array));
    char *answer_str = answer_array;

    char *choice_a = "1";
    char *choice_b = "2";

    if (strcmp_CRignore(answer_str, choice_a))
        play_20q(connect_d);
    else if (strcmp_CRignore(answer_str, choice_b))
        play_tictactoe(connect_d);
}