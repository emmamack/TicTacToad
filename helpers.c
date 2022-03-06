// Defining helper functions.

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "helpers.h"

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