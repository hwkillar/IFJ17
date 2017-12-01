#pragma once

#include <math.h>
#include "tagenerator.h"
#include "ial.h"

void interpret(TA_Item **ta_table, tBTSUzolPtr root);
void destroy_labels(int *jump_array);
void find_labels(TA_Item **ta_table, int **jump_array);
