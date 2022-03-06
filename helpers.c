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

void print_ints(char* s) {
  if (*s == '\0') {
    printf("slash0\n");
    return;
  }
  printf("%d ", *s);
  print_ints(s+1);
}

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