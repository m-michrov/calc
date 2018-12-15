#include "stack.h"

unsigned int push(
        Token *list,
        unsigned int stack_pos,
        unsigned long value,
        bool type)
{

    list[stack_pos].value = value;
    list[stack_pos].type = type;

    stack_pos++;

    return stack_pos;
}
