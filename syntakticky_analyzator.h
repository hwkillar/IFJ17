#pragma once




#include "funkcie.h"
#include "lexikalny_analyzator.h"
#include "ial.h"
#include "vyrazy.h"
#include "tagenerator.h"

/**
 * Globalni promenna
 */
extern tSymbol name;
extern bool isWrite;
extern tBTSUzolPtr typPrirazeni;
extern tBTSUzolPtr volana_fce;
extern char * functionName;
extern TA_Item *ta;
extern int nazev_fce;
extern int *pole_back;
extern int index_pb;
extern bool isLocal;

extern tBTSUzolPtr cilovaAdresaFce;

/* 1=read;
 * 2=sort;
 *
 *
 * */
tError parser();
tError program();
tError funkce();
tError body();
tError params();
tError paramsNext();
tError varDeclar();
tError prirazeni();
tError list();
tError vest();
tError input();
tError print();
tError litExpr();
tError literal();
tError args();
tError argsNext();

/**
 * Funkce pro vyhledavani promennych ve stome
 */

void najdiKolize(tBTSUzolPtr uzel);