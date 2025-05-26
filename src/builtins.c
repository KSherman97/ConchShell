/*
* @file   builtins.c
* @brief  Implements builtin shell functions
* @author Kyle Sherman
* @date   2025-05-22
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <dirent.h> // for directory handling
#include <sys/types.h>
#include <sys/stat.h>

#include "utilities.h"
#include "common.h"
#include "builtins.h"

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

static builtin_command_t builtins[] = {
    {"clear", conch_clear},
    {"oceanman", conch_oceanman},
    {"man", conch_oceanman},
    {"dir", conch_dir},
    {"ls", conch_dir},
    {"cd", conch_cd},
    {"ask", conch_ask},
    {"8ball", conch_ask},
    {NULL, NULL}
};

t_builtin_func get_builtin(const char *cmd) {
    for (int i = 0; builtins[i].name != NULL; ++i) {
        if (strcmp(builtins[i].name, cmd) == 0) {
            return builtins[i].func;
        }
    }
    return NULL;
}

/**
 * @brief oceanman function | conch replacement for man shell command
 * 
 * @param args An array of string arguments
 */
int conch_oceanman(char **args) {
   if (args[1] == NULL) {
    printf("\n🎶 Ocean man, take me by the hand, lead me to the land...\n");
    printf("That you understand...\n\n");
    printf("Try: oceanman ls\n");
    return 1;
  }

  // otherwise run the actual man command
  pid_t pid = fork();
  if(pid == 0) {
    execvp("man", args);
    perror("execvp failed");
    exit(EXIT_FAILURE);
  } else if (pid > 0) {
    int status;
    waitpid(pid, &status, 0);
  } else {
    perror("Error forking the process");
  }

  return 1;
}

/**
 * @brief clear screen function
 */
int conch_clear() {
  printf("\033[2J\033[H"); // clear the screen and move cursor to the top left
  fflush(stdout);

  return 1;
}

/**
 * @brief Conch implementation of the linux sysyem dir / ls command
 * 
 * @param args This is an array of string arguments
 */
int conch_dir(char **args) {
  // if args[1] exists, use this as the directory. Default to root "."
  const char *path = (args[1] != NULL) ? args[1] : ".";

  DIR *dir = opendir(path);
  if(dir == NULL) {
    perror("conch_dir");
    return 1;
  }

  struct dirent *entry;
  char **files = malloc(sizeof(char *) * 1);
  char **directories = malloc(sizeof(char *) * 1);

  int file_count = 0;
  int directory_count = 0;

  while((entry = readdir(dir)) != NULL) {
    // skip hidden files (starting with '.')
    if(entry->d_name[0] == '.') {
      continue;
    }

    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

    struct stat statbuf;
    if(stat(full_path, &statbuf) == -1) {
      continue;
    }

    if(S_ISDIR(statbuf.st_mode)) {
      // strncpy(directories[directory_count++], entry->d_name, 255);
      directories = add_to_list(directories, &directory_count, entry->d_name);
    } else {
      //strncpy(files[file_count++], entry->d_name, 255);
      files = add_to_list(files, &file_count, entry->d_name);
    }
  }

  closedir(dir);

  // print directories
  if(directory_count > 0) {
    printf("Directories:\n");
    for(int i = 0; i < directory_count; i++) {
      printf("%s ", directories[i]);
    }
    printf("\n");
  }

  // print files
  if(file_count > 0) {
    printf("Files:\n");

    for(int i = 0; i < file_count; i++) {
      printf("%s ", files[i]);
    }

    printf("\n");
  }

  for(int i = 0; i < file_count; i++) {
    free(files[i]);
  }

  for(int i = 0; i < directory_count; i++) {
    free(directories[i]);
  }

  free(files);
  free(directories);

  return 1;
}

int conch_cd(char **args) {
  const char *path = (args[1] != NULL) ? args[1] : "~";
  const char *home = getenv("HOME");


  if(args[1] == NULL || strcmp(args[1], "~") == 0) {
    if(home == NULL) {
      fprintf(stderr, "cd: HOME environment variable is not set\n");
      return 1;
    }
    path = home;
  } else {
    path = args[1];
  }

  if(chdir(path) != 0) {
    perror("cd failed");
  }

  return CONCH_SUCCESS;
}

int conch_ask(char **args) {
  srand(time(NULL));

  const char *answers = {
      "It is certain.",
      "It is decidedly so.",
      "Without a doubt.",
      "Yes, definitely.",
      "You may rely on it.",
      "As I see it, yes.",
      "Most likely.",
      "Outlook good.",
      "Yes.",
      "Signs point to yes.",
      "Reply hazy, try again.",
      "Ask again later.",
      "Better not tell you now.",
      "Cannot predict now.",
      "Concentrate and ask again.",
      "Don't count on it.",
      "My reply is no.",
      "My sources say no.",
      "Outlook not so good.",
      "Very doubtful."
  };

  int num_answers = sizeof(answers) / sizeof(answers[0]);

  if (args[1] == NULL) {
      printf("Ask the Magic 8-Ball a question!\n");
      printf("Example: ask Will I become a millionaire today?\n");
      return 1;
  }

  // Generate a random index
  int random_index = rand() % num_answers;

  // Print the selected answer
  printf("\nMagic 8-Ball says: %s\n\n", answers[random_index]);

  return 0; // Return 0 for success
}