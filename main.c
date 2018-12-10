#include <stdio.h>

#include "definitions.h"
#include "convert.h"
#include "calculate.h"

int main(void) {

    char input[BLOCK_SIZE];

    fgets(input, BLOCK_SIZE, stdin);

    Element * postfix = convertToPostfix(input);

    double result = calculatePostfix(postfix);

    if (fabs(result) - (int)fabs(result) < 0.001)
        printf("%d", (int)result);
    else
        printf("%3.3lf", result);

    return 0;
}