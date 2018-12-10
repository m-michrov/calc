#pragma once

#ifndef LAB4_4_STACK_H
#define LAB4_4_STACK_H

#include <stdbool.h>

typedef struct TElement {
    unsigned long value;
    bool type;
} Element;

unsigned int push(
        Element *list,
        unsigned int stack_pos,
        unsigned long value,
        bool type);

#endif
