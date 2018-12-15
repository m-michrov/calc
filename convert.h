#pragma once

#ifndef LAB4_4_CONVERT_H
#define LAB4_4_CONVERT_H

#include <ctype.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

#define SYNTAX_ERROR {printf("syntax error\n"); exit(EXIT_SUCCESS);}
#define MEMORY_ERROR {printf("memory error\n"); exit(EXIT_SUCCESS);}

typedef enum ItemType {
    LAST_START_FILE,
    LAST_NUMBER,
    LAST_OPEN_BRACKET,
    LAST_CLOSE_BRACKET,
    LAST_OPERATOR

} ItemType;

static bool is_operator(
        char c);

static int priority(
        char operator);

static bool associativity(
        char operator);

Token * convertToPostfix(
        char *string);

#endif
