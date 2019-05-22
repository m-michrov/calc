#include "convert.h"
#include "definitions.h"

static bool is_operator(
        char c)
{
    return (c == ADD) || (c == SUB) || (c == MUL) || (c == DIV) || (c == POW);
}

static int priority(
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

static bool associativity(
        char operator)
{
    switch (operator) {
        case POW:
            return RIGHT;
        default:
            return LEFT;
    }
}

static unsigned int handleNumber(
        TBuffer * buffer,
        const char * string,
        unsigned int position)
{
    if (buffer->last_item == LAST_NUMBER || buffer->last_item == LAST_CLOSE_BRACKET)
    SYNTAX_ERROR;

    unsigned long number = 0;


    while (isdigit(string[position])) {

        number *= 10;
        number += string[position] - '0';

        position++;
    }

    if (string[position] == DOT) {
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

        //  a / 10^k -> a 10 k ^ /

        buffer->list_position = push(buffer->result_array, buffer->list_position, number, NUMBER);

        buffer->list_position = push(buffer->result_array, buffer->list_position, 10, NUMBER);

        buffer->list_position = push(buffer->result_array, buffer->list_position, decimal_count, NUMBER);

        buffer->list_position = push(buffer->result_array, buffer->list_position, POW, OPERATOR);

        buffer->list_position = push(buffer->result_array, buffer->list_position, DIV, OPERATOR);

    }
    else {

        buffer->list_position = push(buffer->result_array, buffer->list_position, number, NUMBER);

    }

    position--;

    buffer->last_item = LAST_NUMBER;

    return position;
}

static void handleOperator(
        TBuffer * buffer,
        const char operator)
{
    if (buffer->last_item == LAST_START_FILE || buffer->last_item == LAST_OPEN_BRACKET) {

        if (operator == ADD || operator == SUB) {

            buffer->list_position = push(buffer->result_array, buffer->list_position, 0, NUMBER);

        }
        else
        SYNTAX_ERROR;
    }

    if (buffer->last_item == LAST_OPERATOR)
    SYNTAX_ERROR;

    while (priority(operator) < priority(buffer->operator_stack[buffer->operator_stack_len - 1]) ||
           (priority(operator) == priority(buffer->operator_stack[buffer->operator_stack_len - 1]) &&
            associativity(buffer->operator_stack[buffer->operator_stack_len - 1]) == LEFT)) {

        buffer->operator_stack_len--;

        buffer->list_position = push(buffer->result_array, buffer->list_position, (unsigned char)buffer->operator_stack[buffer->operator_stack_len], OPERATOR);
    }

    buffer->operator_stack[buffer->operator_stack_len] = operator;

    buffer->operator_stack_len++;

    buffer->last_item = LAST_OPERATOR;
}

static void handleOpenBracket(
        TBuffer * buffer)
{
    if (buffer->last_item == LAST_NUMBER)
    SYNTAX_ERROR;

    buffer->operator_stack[buffer->operator_stack_len] = OPEN_BRACKET;

    buffer->operator_stack_len++;

    buffer->last_item = LAST_OPEN_BRACKET;
}

static void handleCloseBracket(
        TBuffer * buffer)
{
    if (buffer->last_item == LAST_OPEN_BRACKET)
    SYNTAX_ERROR;

    if (buffer->last_item == LAST_OPERATOR)
    SYNTAX_ERROR;

    bool found = false;

    while (buffer->operator_stack_len > 0) {

        if (buffer->operator_stack[buffer->operator_stack_len - 1] == OPEN_BRACKET) {
            found = true;
            break;
        }

        buffer->list_position = push(buffer->result_array, buffer->list_position, (unsigned char)buffer->operator_stack[buffer->operator_stack_len - 1], OPERATOR);

        buffer->operator_stack_len--;
    }

    if (!found)
    SYNTAX_ERROR;

    buffer->operator_stack_len--;

    buffer->last_item = LAST_CLOSE_BRACKET;
}

static void handleRest(
        TBuffer * buffer,
        unsigned int position)
{
    if (buffer->last_item == LAST_OPERATOR || !position)
    SYNTAX_ERROR;

    while (buffer->operator_stack_len > 1) {

        if (buffer->operator_stack[buffer->operator_stack_len - 1] == OPEN_BRACKET)
        SYNTAX_ERROR;

        buffer->operator_stack_len--;

        buffer->list_position = push(buffer->result_array, buffer->list_position, (unsigned char)buffer->operator_stack[buffer->operator_stack_len], OPERATOR);
    }

    push(buffer->result_array, buffer->list_position, 0, OPERATOR);
}

Token * convertToPostfix(
        char *string)
{
    char operator_stack[BLOCK_SIZE] = { 0 };

    unsigned int position = 0;

    Token * result_array = malloc(BLOCK_SIZE * sizeof(Token));

    if (result_array == NULL)
    {
        return NULL;
    }

    TBuffer buffer = {0, 1, LAST_START_FILE, result_array, operator_stack};

    while (string[position] != '\0' && string[position] != '\n')
    {

        if (isdigit(string[position]))
        {
            position = handleNumber(&buffer, string, position);
        }
        else if (is_operator(string[position]))
        {
            handleOperator(&buffer, string[position]);
        }
        else if (string[position] == OPEN_BRACKET)
        {
            handleOpenBracket(&buffer);
        }
        else if (string[position] == CLOSE_BRACKET)
        {
            handleCloseBracket(&buffer);
        }
        else if (string[position] == SPACE)
        {
            ;
        }
        else
        {
            SYNTAX_ERROR;
        }

        position++;
    }

    handleRest(&buffer, position);

    return result_array;

}