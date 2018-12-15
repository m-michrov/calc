#pragma once

#ifndef LAB4_4_STACK_H
#define LAB4_4_STACK_H

#include <stdbool.h>

typedef struct st_Token {
    unsigned long value;
    bool type;
} Token;

unsigned int push(
        Token *list,
        unsigned int stack_pos,
        unsigned long value,
        bool type);

#endif
