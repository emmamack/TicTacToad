/*Instructions:

$ gcc -o where cmd_line_test.c
$ sudo mv where /bin/
$ where

or if /bin isn't the right place...

$ echo $PATH | tr \: \\n

and use one of those locations

*/

#include <stdio.h>

int main() {
  printf("Anywhere!\n");
}
