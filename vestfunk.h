#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include "ial.h"
#pragma once

#define MAX 256

//define DEBUG 1


tBTSUzolPtr Substr(tBTSUzolPtr input, tBTSUzolPtr node_start, tBTSUzolPtr node_end);
tBTSUzolPtr Length(tBTSUzolPtr input);
tBTSUzolPtr Asc(tBTSUzolPtr input, tBTSUzolPtr index);
tBTSUzolPtr Chr(tBTSUzolPtr input);
//int Length(char *str);
//int Asc(char *str, int i);
//int Chr(int i);
//int substr(char* str, int i, int n);
