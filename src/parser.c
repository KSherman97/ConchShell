/*
* parser.c
*
* Responsible for tokenizing user input into argument aray
*
* Author: Kyle Sherman
* Created: 2025-05-22
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "parser.h"


void parse_input(char *input, char **args) {
  int i = 0;

  char *token = strtok(input, " \t\n");

  while(token != NULL && i < MAX_TOKENS - 1) {
    args[i++] = token;
    token = strtok(NULL, " \t\n");
  }

  args[i] = NULL;
}

// read a line from stdin and trim newline
void get_input(char *buffer, size_t size) {
  if(fgets(buffer, size, stdin) != NULL) {
    // remove the trailing newline
    buffer[strcspn(buffer, "\n")] = 0;
  } else {
    // handle ctrl-d [EOF]
    buffer[0] = '\0';
  }
}