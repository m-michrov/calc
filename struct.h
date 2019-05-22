#pragma once

#ifndef LAB4_4_STRUCT_H
#define LAB4_4_STRUCT_H


#include <stdbool.h>


typedef enum ItemType
{
    LAST_START_FILE,
    LAST_NUMBER,
    LAST_OPEN_BRACKET,
    LAST_CLOSE_BRACKET,
    LAST_OPERATOR

} ItemType;


typedef struct st_Token
{
    unsigned long value;
    bool type;
} Token;


typedef struct st_Buff
{
    unsigned int list_position;
    unsigned int operator_stack_len;

    ItemType last_item;

    Token * result_array;
    char * operator_stack;
} TBuffer;


unsigned int push(
        Token *list,
        unsigned int stack_pos,
        unsigned long value,
        bool type);


#endif
