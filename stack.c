#include "stack.h"

unsigned int push(
        Element *list,
        unsigned int stack_pos,
        unsigned long value,
        bool type)
{

    Element item = { value, type };

    list[stack_pos] = item;

    stack_pos++;

    return stack_pos;
}
