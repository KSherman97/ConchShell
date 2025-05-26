#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dispatcher.h"
#include "builtins.h"

#include "executor.h"

void command_dispatcher(char **args) {


  t_builtin_func is_builtin = get_builtin(args[0]);

  if(is_builtin) {
    is_builtin(args);
  } else {
    execute_external(args);
  }
}