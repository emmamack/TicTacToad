#pragma once

// Declarations for helper functions.
void error(char*);
int read_in(int, char*, int);
void print_ints(char*);

/* 
Alternate form of strcmp that ignores carriage returns towards inequality
since carriage returns are appended on local strings but not ones sent through
telnet.

Returns 1 for "same" and 0 for "different"
*/
int strcmp_CRignore(char*, char*);