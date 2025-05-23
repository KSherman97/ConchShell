#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dispatcher.h"
#include "builtins.h"

void command_dispatcher(char **args) {
    if (strcmp(args[0], "oceanman") == 0) {
      conch_oceanman(args);
    } else if (strcmp(args[0], "clear") == 0) {
      conch_clear();
    } else if ((strcmp(args[0], "ls") == 0) || (strcmp(args[0], "dir") == 0)) {
      conch_dir(args);
    } else {
      printf("You entered command: %s\n", args[0]);
    }
}