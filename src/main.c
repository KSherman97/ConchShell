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
#include <unistd.h>
#include <limits.h>

#include "common.h"
#include "parser.h"
#include "dispatcher.h"

void print_prompt() {
  char *cwd = getcwd(NULL, 0);
  
}

int main() {

  char *current_working_directory = NULL;

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
    if(current_working_directory != NULL) {
      free(current_working_directory);
      current_working_directory = NULL;
    }

    current_working_directory = getcwd(NULL, 0);

    if(current_working_directory != NULL) {
      printf("%s > Conch: ", current_working_directory);
      fflush(stdout);
    } else {
      perror("getcwd");
      printf("Conch: ");
      fflush(stdout);
    }

    get_input(userString, sizeof(userString));
    parse_input(userString, args);

    if (args[0] == NULL) {
      continue; // empty input
    } else if(strcmp(args[0], "exit") == 0) {
      free(current_working_directory);
      break;
    } else {
      command_dispatcher(args);
    }
  }

  printf("Goodbye!\n");
  
  return 0;
}
