/*
 * common.h
 *
 * Common definitions file
 *
 * Provides all of the global definitions to be used in multiple places
 * 
 * Author: Kyle Sherman
 * Created: 2025-05-22
 */

#ifndef COMMON_H
#define COMMON_H

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64

// define shared typedefs
typedef int (*builtin_func_t)(char **args);

// options: shared status code
#define CONCH_SUCCESS 0
#define CONCH_ERROR 1

#endif // COMON_H