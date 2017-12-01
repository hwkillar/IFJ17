#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * Typ pre ukazatel na subor
 */
typedef FILE *tFile;

/**
 * Chybove kody.
 */ 
typedef enum Error
{
    EOK,        // 0 - vsetko ok
    ELEX,       // 1 - chyby v ramci lexikalnej analyzy
    ESYN,       // 2 - chyby v ramci syntaktickej analyzy
    ESEM,       // 3 - chyby v ramci semantickej analyzy
    EINT,       // 4 - chyby interpretace
    EINTERN,    // 5 - interne chyby interpretu
} tError;
 
/**
 * Globalne premenne
 */
tFile subor;
tError error;
int riadok;
int stlpec;