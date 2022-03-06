/* Testing 20 questions
Feb. 2022

To connect:
[in another terminal while socket_test is running]
$ telnet 127.0.0.1 3000

To find your ip address:
hostname -i
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

// Function declarations
void play_20q(int connect_d);

void error(char* msg) {
  printf("%s\n", msg);
  exit(2);
}

int read_in(int socket, char *buf, int len) {
  char *s = buf;
  int slen = len;
  int c = recv(socket, s, slen, 0);
  while ((c > 0) && (s[c-1] != '\n')) {
    s += c; slen -= c;
    c = recv(socket, s, slen, 0);
  }
  if (c < 0)
    return c;
  else if (c == 0)
    buf[0] = '\0';
  else
    s[c-1]='\0';
  return len - slen;
}

int main() {
  int listener_d = socket(PF_INET, SOCK_STREAM, 0);
  if (listener_d == -1) error("Can't open socket");
  // printf("Listener_d: %d\n", listener_d);

  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(3000);
  name.sin_addr.s_addr = htonl(INADDR_ANY);

  printf("Trying to connect to socket... will exit after 30 seconds of failure...\n");
  int c = -1;
  int start_time = time(0);
  while (c==-1) {
    c = bind(listener_d, (struct sockaddr *) &name, sizeof(name));
    if ((start_time + 30) < time(0))
      error("Can't bind to socket");
  }
  puts("Connected.");


  if (listen(listener_d, 10) == -1)
    error("Can't listen");

  puts("Waiting for a player to join...");

  while(1) {

    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
    if (connect_d == -1)
      error("Can't open secondary socket");
    // printf("connect_d: %d\n", connect_d);

    // Play games!
    play_20q(connect_d);
    c = close(connect_d);
    // printf("c: %d\n", c);
    if (c==-1) {
      error("Could not close socket");
    }

    printf("Waiting for next player... press ctrl+C to quit\n");

  }

  return 0;
}

void print_ints(char* s) {
  if (*s == '\0') {
    printf("slash0\n");
    return;
  }
  printf("%d ", *s);
  print_ints(s+1);
}

/* Alternate form of strcmp that ignores carriage returns towards inequality
since carriage returns are appended on local strings but not ones sent through
telnet.
Returns 1 for "same" and 0 for "different"
*/
int strcmp_CRignore(char* s1, char* s2) {
  while (1) {
    if ((*s1=='\r' && *s2=='\0') ||
        (*s1=='\0' && *s2=='\r') ||
        (*s1=='\r' && *s2=='\r') ||
        (*s1=='\0' && *s2=='\0')) {
           return 1;
    }

    if (*s1 != *s2) {
      return 0;
    }

    s1++; s2++;
  }
}

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
        printf("%s\n", guess_array);

        // check for correct guess
        int res = strcmp_CRignore(answer_str, guess);
        if (res) {
          printf("Player 2 guessed the answer: \"%s\"!  Guessed in %i questions.\n", answer_str, i);
          char *end_msg = "You guessed it! Goodbye.\n";
          send(connect_d, end_msg, strlen(msg2), 0);
          break;
        }

        // Player 1 answers Y/N
        printf("Player 1: answer yes or no: ");
        scanf("%s", buf);
        char *response = strcat(buf, "\n");
        send(connect_d, response, strlen(response), 0);
    }
}
