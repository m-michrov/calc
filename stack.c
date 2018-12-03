#include "stack.h"

unsigned int push(
        TElement *list,
        unsigned int stack_pos,
        int value,
        bool type)
{

    TElement item = { value, type };

    list[stack_pos] = item;

    stack_pos++;

    return stack_pos;
}
