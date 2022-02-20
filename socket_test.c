/* Testing boilerplate code to open a connection between machines.
Emma Mack, Feb. 2022

To connect:
[in another terminal while socket_test is running]
$ telnet 127.0.0.1 3000

TODOs:
- Test on multiple machines
- read from client (pg 478)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

void error(char* msg) {
  printf("%s\n", msg);
  exit(2);
}

int main() {
  int listener_d = socket(PF_INET, SOCK_STREAM, 0);
  if (listener_d == -1) error("Can't open socket");
  printf("Listener_d: %d\n", listener_d);

  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(3000);
  name.sin_addr.s_addr = htonl(INADDR_ANY);

  int c = bind(listener_d, (struct sockaddr *) &name, sizeof(name));
  if (c==-1)
    error("Can't bind to socket");
  printf("c: %d\n", c);

  if (listen(listener_d, 10) == -1)
    error("Can't listen");

  puts("Waiting...");

  while(1) {

    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
    if (connect_d == -1)
      error("Can't open secondary socket");
    printf("connect_d: %d\n", connect_d);

    char *msg = "Hello world!\n";
    if (send(connect_d, msg, strlen(msg), 0) == -1)
      error("Can't send");

    close(connect_d);

  }

  return 0;
}
