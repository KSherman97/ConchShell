/*
* main.c
*
* Responsible for the main control loop of the conch shell
*
* Author: Kyle Sherman
* Created: 2025-05-22
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "parser.h"
#include "dispatcher.h"

int main() {

  char userString[MAX_INPUT_SIZE];
  char *args[MAX_TOKENS];

  /**
   * Structured
   * get input
   * parse input
   * dispatch command
   * execute builtin
   * launch program
   */


  system("clear");
	printf("Welcome to the Conch Shell 🐚\n");

  while (1) {
    printf("Conch> ");
    fflush(stdout);

    get_input(userString, sizeof(userString));
    parse_input(userString, args);

    if (args[0] == NULL) {
      continue; // empty input
    } else if(strcmp(args[0], "exit") == 0) {
      break;
    } else {
      command_dispatcher(args);
    }
  }

  printf("Goodby!\n");
  
  return 0;
}
