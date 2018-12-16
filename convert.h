#pragma once

#ifndef LAB4_4_CONVERT_H
#define LAB4_4_CONVERT_H

#include <ctype.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "struct.h"

#define SYNTAX_ERROR {printf("syntax error\n"); exit(EXIT_SUCCESS);}
#define MEMORY_ERROR {printf("memory error\n"); exit(EXIT_SUCCESS);}

static bool is_operator(
        char c);

static int priority(
        char operator);

static bool associativity(
        char operator);

static unsigned int handleNumber(
        TBuffer * buffer,
        const char * string,
        unsigned int position);

static void handleOperator(
        TBuffer * buffer,
        char operator);

static void handleOpenBracket(
        TBuffer * buffer);

static void handleCloseBracket(
        TBuffer * buffer);

static void handleRest(
        TBuffer * buffer,
        unsigned int position);

Token * convertToPostfix(
        char *string);

#endif
