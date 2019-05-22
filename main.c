#include <stdio.h>


#include "definitions.h"
#include "convert.h"
#include "calculate.h"


static void pprint(
        double value,
        double precision) {
    if (fabs(value - round(value)) < precision)
    {
        printf("%d\n", (int) round(value));
    }
    else
    {
        printf("%.*lf\n", (int) fabs(log10(precision)), value);
    }
}


int main(
        void)
{
    char input[BLOCK_SIZE];
    Token * postfix;
    double result;

    while (true)
    {
        fgets(input, BLOCK_SIZE, stdin);

        if (feof(stdin))
        {
            return 0;
        }

        postfix = convertToPostfix(input);

        result = calculatePostfix(postfix);

        free(postfix);

        pprint(result, 0.001);
    }
}