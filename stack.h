#pragma once

#ifndef LAB4_4_STACK_H
#define LAB4_4_STACK_H

#include <stdbool.h>

typedef struct TElement {
    int value;
    bool type;
} TElement;

unsigned int push(
        TElement *list,
        unsigned int stack_pos,
        int value,
        bool type);

#endif //LAB4_4_STACK_H
