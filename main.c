#include <stdio.h>

#include "convert.h"
#include "calculate.h"
#include "definitions.h"

int main() {

    char input[BLOCK_SIZE];

    fgets(input, BLOCK_SIZE, stdin);

    TElement * postfix = convertToPostfix(input);

    double result = calculatePostfix(postfix);

    printf("%3.3lf", result);

    return 0;
}