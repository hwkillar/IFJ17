#include "ial.h"
#include "vest_funkce.h"
#include "vyrazy.h"
#include "garbage_collector.h"

tBTSUzolPtr built_substr(tBTSUzolPtr input, tBTSUzolPtr node_start, tBTSUzolPtr node_end)
{
    if(error != EOK)
        return NULL;
    int len;
    int res;
    int start = 0;
    int end = 0;
    int index = 0;
    int limit;
    int goOn = 1;
    int isNil = 0;
    char *strPtr;


    // overit vstupni datove typy (char*, int, int)
    if(input == NULL || node_start == NULL || node_end == NULL) {
        isNil = 1;
    }

    if((isNil == 0) && (input->data.typ != tString))   // jestli se jedna opravdu o string, jinak chyba
    {
        goOn = 0;
        isNil = 1;
    }

    if((isNil == 0) && ((node_start->data.typ != tDouble) && (node_end->data.typ != tDouble)))   // jestli se jedna opravdu o string, jinak chyba
    {

        goOn = 0;
        isNil = 1;
    }


    if(goOn == 0 || isNil == 1) {
        char* str = advMalloc(sizeof(char)*25);
        sprintf(str,"@prom_%u",nameID++);

        tSymbol ptr;
        TSinitSymbol(&ptr);
        ptr.nazov = str;
        ptr.varFc = false;
        ptr.typ = tNil;

        if((TSreadSymbol(str)) != NULL) //pokud uz jmeno bylo v tabulce
            error = EINT;
        else TSvlozSymbol(ptr); //jinak vloz do tabulky

        tBTSUzolPtr node = TSreadSymbol(str);
        return node;
    }
      start = node_start->data.value.d;
        end = node_end->data.value.d;

    // dale jiz pracujeme jen s retezcem
    char* inString = input->data.value.s;
#ifdef DEBUG

#endif
    if(start - end == 0)
    {
        // pripad, kdy jsou zadana 2 stejna cisla => nulova delka retezce. 'emptyString' byl inicializovan na prazdny retezec
#ifdef DEBUG

#endif
        strPtr = "";
        goOn = 0;
    }

    // stara se specificke situace, ktere ale vraci nulovy retezce
    res = start*end;
    if(res > 0 && goOn == 1)
    {
        // zadany 2 zaporne nebo 2 kladno cisla
        if((start < 0) && (start > end))   //  abs(start) < abs(end)
        {
            // zaporne cisla; druhe je vetsi nez prvni => nulovy retezec
#ifdef DEBUG

#endif

            strPtr = "";
            goOn = 0;
        }
        if((start > 0) && (start > end))
        {
            // kladne cisla; prvni je vetsi nez druhe => nulovy retezec
#ifdef DEBUG

#endif

            strPtr = "";
            goOn = 0;
        }
    }

    if ((res == 0) && (end == 0)  && goOn == 1)
    {
        // end je nula => vzdy prazdny retezec
#ifdef DEBUG

#endif

        strPtr = "";
        goOn = 0;
    }
    else if (goOn == 1)
    {
        // jiz nejspis vypisuje podretezec
        // a proto take alokujeme pamet, kdyby nahodou predali nejaky extremne dlouhy retezec...
        len = strlen(inString);
        limit = abs(start - end + 1); // smazat - nepouziva se
        strPtr = (char*)advMalloc(len * sizeof(char)+1);

        if((start > 0) && (start > len))
        {
            // 'start' pozice se dostala za konec retezce => nulovy retezec
#ifdef DEBUG

#endif

            start = 0;
            end = 0;

            strPtr = "";
            goOn = 0;
        }

        if(goOn == 1)
        {
            if((start < 0) && (abs(start) > len))
            {
                // 'start' pozice se dostala za pocatek retezce => posunuti na zacatek
#ifdef DEBUG

#endif

                start = 0; // index v poli ! (ne pismeno)
            }

            // pøemìna poradi pismena (od jednicky) na index v poli (od nuly)
            if(start < 0)
                start = len - abs(start); // index v poli ! ne pismeno
            else if (start > 0)
                start = start - 1; // index v poli ! ne pismeno
            else
                start = 0; // index v poli ! ne pismeno

            if(end < 0)
                end = len - abs(end); // index v poli ! ne pismeno
            else if (end > 0)
                end = end - 1; // index v poli ! ne pismeno
            else
                end = 0; // index v poli ! ne pismeno

#ifdef DEBUG

#endif
            // pruchod retezcem a uprava indexu
            for(index = 0; (index <= end) && (start <= end) && (start < len); start++)
            {
                strPtr[index] = inString[start];
                index++;
#ifdef DEBUG

#endif
            }
            // append the End-of-string character
            strPtr[index] = inString[len]; // \0

#ifdef DEBUG

#endif
        }
    }
    // ulozeni struktury
#ifdef DEBUG

#endif
    char* str = advMalloc(sizeof(char)*25);
    sprintf(str,"@prom_%u",nameID++);

    tSymbol ptr;
    TSinitSymbol(&ptr);
    ptr.nazov = str;
    ptr.varFc = false;
    if(isNil == 0)
    {

        char* ret = advMalloc(sizeof(char)*strlen(strPtr)+1);
        strcpy(ret, strPtr);

        ptr.value.s = ret;
        ptr.typ = tString;
    }
    else
    {
        ptr.typ = tNil;
    }

    if((TSreadSymbol(str)) != NULL) //pokud uz jmeno bylo v tabulce
        error = EINT;
    else TSvlozSymbol(ptr); //jinak vloz do tabulky

    tBTSUzolPtr node = TSreadSymbol(str);
    return node;
}

tBTSUzolPtr Built_Length(tBTSuzolPtr input[1000])
{
    if(error != EOK)
        return NULL;
    int len = 0;

    if (!(input == NULL) || (input->data.typ != sString)))
    {
        int len = 0;
        while (input[len] != '\0')
        {
            len++;
        }
        TSvlozInt(input, len);
        tBTSUzolPtr node = len;
        return node;
    }
    else
    {
        TSvlozInt(input, len);
        tBTSUzolPtr node = len;
        return node;
    }
}

int Length (char *str)// vlastni funkce bez pomoci c knihovna
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}
/*int Length(char *str)
{
    return strlen(str);
}*/

int Asc(char *str, int i)
{
    int number = 0;
    number = str[i] - 'a' + 97;
    return number;
}

char Chr(int i)
{
    char z;
    z = i + 'a' - 97;
    return z;
}
char *substr (char *str, int i, int n)
{
    if (i < 0 || n < 0)
    {
        fprintf(stderr, "substr: index or length is negative value. \n");
        exit();// other error
    }
    char *newstr = (char*) malloc(sizeof(char));
    if (newstr == NULL)
        exit();// chyba alokace

    if (i > (Length(str)))
    {
        fprintf(stderr, "index is greater than length of string.\n");
        free(newstr);
        exit();// chyba doplnit typ chyby
    }

    if (n > (Length(str)))
    {
        fprintf(stderr, "length of searching string is longer than length of string.\n");
        free(newstr);
        exit();// chyba doplnit typ chyby
    }

    memcpy(newstr, s + i , n);// pomoci c funkce
    /*int d = 0;
    while ( i < n) // bez pomoci c funkce
    {
        newstr[d] = str[i];
        i++;
        d++;
    }*/
    newstr[n] = '\0';
    return newstr;
}
