#include "calculate.h"

double calculatePostfix(
        TElement * list)
{

    if (list == NULL)
        MEMORY_ERROR;

    puts("");

    double operand_stack[BLOCK_SIZE];

    unsigned int operand_stack_len = 0;
    unsigned int stack_position = 0;
    double operand_uno;
    double operand_duo;

    while (!(list[stack_position].is_operator == OPERATOR && list[stack_position].value == 0)) {


        if (list[stack_position].is_operator == NUMBER) {
            operand_stack[operand_stack_len] = list[stack_position].value;
            operand_stack_len++;

        }

        else {
            operand_duo = operand_stack[operand_stack_len - 1];

            operand_stack_len--;

            operand_uno = operand_stack[operand_stack_len - 1];

            switch (list[stack_position].value)
            {
                case ADD: {
                    operand_stack[operand_stack_len - 1] = operand_uno + operand_duo;
                    break;
                }

                case SUB: {
                    operand_stack[operand_stack_len - 1] = operand_uno - operand_duo;
                    break;
                }

                case DIV: {
                    if (!operand_duo)
                    DIVISION_ERROR;

                    operand_stack[operand_stack_len - 1] = operand_uno / operand_duo;
                    break;
                }

                case MUL: {
                    operand_stack[operand_stack_len - 1] = operand_uno * operand_duo;
                    break;
                }

                case POW: {
                    operand_stack[operand_stack_len - 1] = pow(operand_uno, operand_duo);
                    break;
                }

                default:
                    SYNTAX_ERROR;
            }
        }

        stack_position++;
    }

    free(list);

    return operand_stack[0];
}