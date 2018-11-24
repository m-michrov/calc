#pragma once

#ifndef LAB4_4_CALCULATE_H
#define LAB4_4_CALCULATE_H

#include <stdlib.h>
#include <math.h>

#include "stack.h"
#include "convert.h"
#include "definitions.h"

#define DIVISION_ERROR {printf("division by zero error\n"); free(list); exit(EXIT_SUCCESS);}

double calculatePostfix(
        TElement * list);

#endif //LAB4_4_CALCULATE_H
