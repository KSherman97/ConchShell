#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

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

int main() {

  char userString[1024];

	printf("Conch> ");
  fflush(stdout);

  get_input(userString, sizeof(userString));

  /**
  if(strcmp(userString, "exit") == 0) {
    break;
  }
  **/

  printf("%s", userString);
	
  return 0;
}
