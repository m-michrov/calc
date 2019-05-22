#include "calculate.h"

double calculatePostfix(
        Token * list)
{
    if (list == NULL)
    {
        return -1.0;
    }

    double operand_stack[BLOCK_SIZE] = { 0.0 };

    unsigned int operand_stack_len = 0;
    unsigned int stack_position = 0;

    double first_operand;
    double second_operand;

    while (list[stack_position].type != OPERATOR || list[stack_position].value != 0)
    {
        if (list[stack_position].type == NUMBER)
        {
            operand_stack[operand_stack_len] = list[stack_position].value;
            operand_stack_len++;
        }
        else
        {
            second_operand = operand_stack[operand_stack_len - 1];
            operand_stack_len--;
            first_operand = operand_stack[operand_stack_len - 1];

            switch (list[stack_position].value)
            {
                case ADD:
                {
                    operand_stack[operand_stack_len - 1] = first_operand + second_operand;
                    break;
                }
                case SUB:
                {
                    operand_stack[operand_stack_len - 1] = first_operand - second_operand;
                    break;
                }
                case DIV:
                {
                    if (!second_operand)
                    {
                        printf("Division by zero\n");
                        return -1.0;
                    }

                    operand_stack[operand_stack_len - 1] = first_operand / second_operand;
                    break;
                }
                case MUL:
                {
                    operand_stack[operand_stack_len - 1] = first_operand * second_operand;
                    break;
                }
                case POW:
                {
                    operand_stack[operand_stack_len - 1] = pow(first_operand, second_operand);
                    break;
                }
                default:
                {
                    printf("Syntax error\n");
                    return -1.0;
                }
            }
        }

        stack_position++;
    }

    return operand_stack[0];
}