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

/**
 * @brief oceanman function | conch replacement for man shell command
 * 
 * @param args An array of string arguments
 */
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