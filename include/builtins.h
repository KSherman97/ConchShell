#ifndef BUILTINS_H
#define BUILTINS_H

typedef int (*t_builtin_func)(char **args);

typedef struct {
    const char *name;
    t_builtin_func func;
} builtin_command_t;

int conch_oceanman(char **args);
int conch_clear();
int conch_dir();
int conch_cd();

t_builtin_func get_builtin(const char *command);

#endif // BUILTINS_H