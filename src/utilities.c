#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "utilities.h"

/**
 * @brief Adds a new item to an existing list and resizes the list
 * 
 * @param list The existing list to expand and add to
 * @param count The size of the existing list
 * @param item The string to append to the list
 * 
 * @return The newly expanded list
 */
char **add_to_list(char **list, int *count, const char *item) {
  char **new_list = realloc(list, (*count + 1) * sizeof(char *));
  
  if(new_list == NULL) {
    perror("realloc");
    exit(EXIT_FAILURE);
  }

  new_list[*count] = strdup(item); // duplicate string
  if(new_list[*count] == NULL) {
    perror("strdup");
    exit(EXIT_FAILURE);
  }

  (*count)++;
  return new_list;
}