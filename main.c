#include <stdio.h>

#include "definitions.h"
#include "convert.h"
#include "calculate.h"

static void pprint(
        double value,
        double precision)
{
    if (fabs(value - round(value)) < precision)
        printf("%d\n", (int)round(value));
    else
        printf("%.*lf\n", (int)fabs(log10(precision)), value);
}

int main(void) {

    char input[BLOCK_SIZE];

    fgets(input, BLOCK_SIZE, stdin);

    Token * postfix = convertToPostfix(input);

    double result = calculatePostfix(postfix);

    pprint(result, 0.001);

    return 0;
}