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
#include "helpers.h"
#include "games.h"

int main() {
  
  int listener_d = socket(PF_INET, SOCK_STREAM, 0);

  if (listener_d == -1)
    error("Can't open socket");
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
    game_chooser(connect_d);
    c = close(connect_d);
    // printf("c: %d\n", c);
    if (c==-1) {
      error("Could not close socket");
    }

    printf("Waiting for next player... press ctrl+C to quit\n");

  }

  return 0;
}
