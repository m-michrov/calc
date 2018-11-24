#pragma once

#ifndef LAB4_4_STACK_H
#define LAB4_4_STACK_H

#include <stdbool.h>

typedef struct TElement {
    int value;
    bool is_operator;
} TElement;

unsigned int push(
        TElement *list,
        unsigned int stack_pos,
        int value,
        bool is_operator);

#endif //LAB4_4_STACK_H
