#pragma once

#ifndef LAB4_4_CALCULATE_H
#define LAB4_4_CALCULATE_H

#include <stdlib.h>
#include <math.h>

#include "struct.h"
#include "convert.h"
#include "definitions.h"

#define DIVISION_ERROR {printf("division by zero\n"); exit(EXIT_SUCCESS);}

double calculatePostfix(
        Token * list);

#endif
