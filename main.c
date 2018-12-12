#include <stdio.h>

#include "definitions.h"
#include "convert.h"
#include "calculate.h"

int main(void) {

    char input[BLOCK_SIZE];

    fgets(input, BLOCK_SIZE, stdin);

    Element * postfix = convertToPostfix(input);

    double result = calculatePostfix(postfix);

    if (fabs(result - round(result)) < 0.00001)
        printf("%d", (int)round(result));
    else
        printf("%.5lf", result);

    return 0;
}