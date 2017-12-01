#pragma once

/**
 * Hlavickove soubory
 */
#include "ial.h"
#include "lexikalny_analyzator.h"
#include "funkcie.h"
#include "syntakticky_analyzator.h"
#include "tagenerator.h"
#include <stdlib.h>

//globalni promenna pro generovani unikatnich nazvu konstant
extern unsigned int nameID;
extern bool isExprWr;

/**
 * enumy pro vyplneni staticke precedencni tabulky
 */

typedef enum
{
    M,	//< mensi
    V,	//> vetsi
    R,	//= rovno
    E	//prazdne misto v tabulce -> synt. chyba
} tPrvkyindexu;

typedef enum
{
    PLUS,		//0 +
    MINUS,	//1 -
    KRAT,		//2 *
    DELENO,	//3 /
    MOCNINA,	//4 ^
    ROVNITKO,	//5 ==
    NEROVNITKO,	//6 <>
    MENSIROVNO,	//7 <=
    VETSIROVNO,	//8 >=
    VICE,		//9 >
    MENE,		//10 <
    LZAVORKA,	//11 (
    PZAVORKA,	//12 )
    ID,		//13 promenna a konstanta
    FCE,		//14 volani funkce
    CARKA,	//15 ,
    KDOLAR,	//16 $ konec vyrazu
    MENSITKO,	//17 oznaceni < na zasobniku
    NETERM,	//18 neterminalni znak napr. E->
    CHYBA		//19 jiny token do vyrazu nepripoustime
} tIndexy;

/**
 * zasobnik pro vyrazy
 */
//datova slozka na zasobniku se sklada z vicero prvku
typedef struct
{
    tSymbol data;		//polozka tabulky symbolu
    tIndexy p;	//pseudopolozky s kterymi budu operovat na zasobniku
} tData;

extern tData neterm; //globalni pro ukladani vysledku exp

typedef struct tZasPrvek
{
    struct tZasPrvek *ptr;
    tData item;
} *tZPrvekptr;

typedef struct
{
    tZPrvekptr vrchol;
} tVZasobnik;

/**
 * Prototypy funkci
 */
//pparser
tError pparser();	//main precedencni analyzy
// zasobnik
void VSinit(tVZasobnik *zasobnik);	//inicializace zasobniku
void VSpush(tVZasobnik *zasobnik, tData item);	//push
void VSpop(tVZasobnik *zasobnik);				//pop
void VStop(tVZasobnik *zasobnik, tData *item);
void VStoppop(tVZasobnik *zasobnik, tData *item);
bool VSempty(tVZasobnik *zasobnik);
