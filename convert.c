#include "convert.h"
#include "definitions.h"

bool is_operator(
        char c)
{
    return (c == ADD) || (c == SUB) || (c == MUL) || (c == DIV) || (c == POW);
}

int priority(
        char operator)
{
    switch (operator) {
        case POW:
            return 2;
        case MUL:
        case DIV:
            return 1;
        case ADD:
        case SUB:
            return 0;
        default:
            return -1;
    }
}

bool associativity(
        char operator)
{
    switch (operator) {
        case POW:
            return RIGHT;
        default:
            return LEFT;
    }
}

TElement * convertToPostfix(
        char *string)
{
    TElement *list = malloc(BLOCK_SIZE * sizeof(TElement));

    if (list == NULL)
        MEMORY_ERROR;

    char operator_stack[BLOCK_SIZE] = { 0 };

    unsigned int list_position = 0;
    unsigned int position = 0;
    unsigned int operator_stack_len = 1;

    ItemType last_item = LAST_START_FILE;

    while (string[position] != '\n') {

        if (isdigit(string[position])) { // handling numbers

            if (last_item == LAST_NUMBER || last_item == LAST_CLOSE_BRACKET)
                SYNTAX_ERROR;

            unsigned int number = 0;


            while (isdigit(string[position])) {

                number *= 10;
                number += string[position] - '0';

                position++;
            }

            if (string[position] == DOT) { // handling rational number
                position++;

                unsigned int decimal_count = 0;

                while (isdigit(string[position])) {

                    number *= 10;
                    number += string[position] - '0';

                    decimal_count++;

                    position++;
                }

                if (decimal_count == 0)
                    SYNTAX_ERROR;

                // writing rational number in the Scientific notation ( a / 10^k ) in Postfix notation ( a 10 k ^ / )

                list_position = push(list, list_position, number, NUMBER);

                list_position = push(list, list_position, 10, NUMBER);

                list_position = push(list, list_position, decimal_count, NUMBER);

                list_position = push(list, list_position, POW, OPERATOR);

                list_position = push(list, list_position, DIV, OPERATOR);

            }
            else {

                list_position = push(list, list_position, number, NUMBER);

            }

            position--;

            last_item = LAST_NUMBER;

        }

        else if (is_operator(string[position])) {

            if (last_item == LAST_START_FILE || last_item == LAST_OPEN_BRACKET) {

                if (string[position] == '+' || string[position] == '-') {

                    list_position = push(list, list_position, 0, NUMBER);

                }
                else
                    SYNTAX_ERROR;
            }

            if (last_item == LAST_OPERATOR)
                SYNTAX_ERROR;

            while (priority(string[position]) < priority(operator_stack[operator_stack_len - 1]) ||
                   (priority(string[position]) == priority(operator_stack[operator_stack_len - 1]) &&
                    associativity(operator_stack[operator_stack_len - 1]) == LEFT)) {

                operator_stack_len--;

                list_position = push(list, list_position, operator_stack[operator_stack_len], OPERATOR);
            }

            operator_stack[operator_stack_len] = string[position];

            operator_stack_len++;

            last_item = LAST_OPERATOR;
        }

        else if (string[position] == OPEN_BRACKET) {

            if (last_item == LAST_NUMBER)
                SYNTAX_ERROR;

            operator_stack[operator_stack_len] = string[position];

            operator_stack_len++;

            last_item = LAST_OPEN_BRACKET;

        }

        else if (string[position] == CLOSE_BRACKET) {

            if (last_item == LAST_OPEN_BRACKET)
                SYNTAX_ERROR;

            if (last_item == LAST_OPERATOR)
                SYNTAX_ERROR;

            bool found = false;

            while (operator_stack_len > 0) {

                if (operator_stack[operator_stack_len - 1] == OPEN_BRACKET) {
                    found = true;
                    break;
                }

                list_position = push(list, list_position, operator_stack[operator_stack_len - 1], OPERATOR);

                operator_stack_len--;
            }

            if (!found)
                SYNTAX_ERROR;

            operator_stack_len--;

            last_item = LAST_CLOSE_BRACKET;

        }

        else if (string[position] == SPACE)
            ;

        else
            SYNTAX_ERROR;

        position++;
    }

    if (last_item == LAST_OPERATOR || !position)
        SYNTAX_ERROR;

    while (operator_stack_len > 1) {

        if (operator_stack[operator_stack_len - 1] == OPEN_BRACKET)
            SYNTAX_ERROR;

        operator_stack_len--;

        list_position = push(list, list_position, operator_stack[operator_stack_len], OPERATOR);
    }

    push(list, list_position, 0, OPERATOR);

    return list;

}