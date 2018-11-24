#include "stack.h"

unsigned int push(
        TElement *list,
        unsigned int stack_pos,
        int value,
        bool is_operator)
{

    TElement item = { value, is_operator };

    list[stack_pos] = item;

    stack_pos++;

    return stack_pos;
}
