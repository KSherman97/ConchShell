#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64

void parse_input(char *input, char **args) {
  int i = 0;

  char *token = strtok(input, " \t\n");

  while(token != NULL && i < MAX_TOKENS - 1) {
    args[i++] = token;
    token = strtok(NULL, " \t\n");
  }

  args[i] = NULL;
}

void command_dispatcher(char **args) {
    if (strcmp(args[0], "oceanman") == 0) {
      conch_oceanman(args);
    } else if (strcmp(args[0], "clear") == 0) {
      conch_clear(args);
    } else {
      printf("You entered command: %s\n", args[0]);
    }

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

int conch_oceanman(char **args) {
  printf("\n🎶 Ocean man, take me by the hand, lead me to the land...\n");
  printf("That you understand...\n\n");

  if(args[1] != NULL) {
    printf("You asked about '%s', but the ocean has no answers. Only mysteries.\n", args[1]);
  } else {
    printf("Try: oceanman ls\n");
  }

  return 1;
}

int conch_clear(char **args) {
  printf("\033[2J\033[H"); // clear the screen and move cursor to the top left
  fflush(stdout);

  return 1;
}

int main() {

  char userString[1024];
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
