#include <stdio.h>
#include <stdlib.h>

// 20 Questions
// Two-player, one device (for now)
// Berwin Lan, Software Systems SP22
// Project 1 - TicTacToad

// TODOs & Known Bugs:
// - assumes the players don't go over INPUT_MAX length

// Maximum input length of string buffer
const int INPUT_MAX = 80;

int main() {
    // Initialize space for strings
    char answer_array[INPUT_MAX];
    char *answer_str = answer_array;

    char question_array[INPUT_MAX];
    char *question_str = question_array;

    char guess_array[INPUT_MAX];
    char *guess_str = guess_array;


    puts("Player 1: What are you thinking of? ");
    scanf("%s", answer_str);

    for (int i = 1; i < 21; i++) {
        // Player 1 asks a question, which is saved
        puts("Player 2: Ask a yes or no question: ");
        scanf("%s", question_str);

        // Player 2 answers Y/N
        puts("Player 1: Enter Y or N, or C if it is the correct answer: ");
        scanf("%s", guess_str);

        // Check for correct guess
        if (guess_str[0] == 'C') {
            printf("Correct - Player 1 was thinking of \"%s\"! Guessed in %i questions.\n", answer_str, i);
            break;
        }
    }

    return 0;
}