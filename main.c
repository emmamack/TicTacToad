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
#include "helpers.h"
#include "games.h"

int strcmp_CRignore(char* s1, char* s2);

int main() {
  int listener_d = socket(PF_INET, SOCK_STREAM, 0);
  
  if (listener_d == -1)
    error("Can't open socket");
  // printf("Listener_d: %d\n", listener_d);

  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(3000);
  name.sin_addr.s_addr = htonl(INADDR_ANY);

  int c = bind(listener_d, (struct sockaddr *) &name, sizeof(name));
  if (c == -1)
    error("Can't bind to socket");

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
