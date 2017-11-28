typedef enum
{
    START,
    KLIC_SLOVO,
    REZ_SLOVO,
    CHYBA,
    IDENTIFIK,
    INTEGER,
    DOUBLE_KONTR,
    DOUBLE,
    EXP_KONTR,
    EXP_KONTR02,
    EXP,
    STREDNIK,
    PRIRAZENI,
    LEVA_ZAVORKA,
    PRAVA_ZAVORKA,
    CARKA,
    PLUS,
    MINUS,
    KRAT,
    DELENO_DESET,
    DELENO_CELY,
    VETSI,
    MENSI,
    JE_ROVNO,
    VETSI_ROVNO,
    MENSI_ROVNO,
    NENI_ROVNO,
    ENDOFFILE,
    EOL,
    RADK_KOMENT,
    BLOK_KOMENT,
    BLOK_KOMENT02,
    RETEZEC,
    RETEZEC01,
} tStav;

int sloupec, error;

typedef struct
{
    tStav stav;
    char *data;
    int radek;
    int sloupec;
} tToken;


extern tToken token;


tToken getToken(void);

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define POCET_KLUCOVYCH_SLOV 22
#define POCET_REZERVOVANYCH_SLOV 13
#define POKRACUJ 0
#define STOP 1

static void rozsirToken(int znak, int *i);
static void vratZnak(int znak);
static tStav prejdiRezervovaneSlova(char *slovo);

char *klucoveSlova[POCET_KLUCOVYCH_SLOV] =
{
    "As\0, Asc\0, Declare\0, Dim\0, Do\0, Double\0, Else\0, End\0, Chr\0",
    "Function\0, If\0, Input\0, Integer\0, Length\0, Loop\0, Print\0, Return\0",
    "Scope\0, String\0, SubStr\0, Then\0, While\0"
};

char *rezervovaneSlova[POCET_REZERVOVANYCH_SLOV] =
{
    "And\0, Boolean\0, Continue\0, Elseif\0, Exit\0, False\0, For\0, Next\0",
    "Not\0, Or\0, Shared\0, Static\0, True\0"
};

static void rozsirToken(int znak, int *i)
{

    if ((token.data = (char *) advRealloc(token.data, (*i) + 2)))
    {
        token.data[(*i) + 1] = '\0';
        token.data[(*i)] = znak;
        (*i)++;
    }
    else
        error = 2;
}


static void vratZnak(int znak)
{

    if (!isspace(znak))
        ungetc(znak, soubor);


    if (isprint(znak))
        sloupec--;
}

static tStav prejdiRezervovaneSlova(char *slovo)
{
    int j;


    for (j = 0; j < POCET_KLUCOVYCH_SLOV; j++)
        if (!(strcmp(slovo, klucoveSlova[j])))
            return KLIC_SLOVO;


    for (j = 0; j < POCET_REZERVOVANYCH_SLOV; j++)
        if (!(strcmp(slovo, rezervovaneSlova[j])))
            return REZ_SLOVO;

    return IDENTIFIK;
}

tToken getToken()
{

tStav stav = START;
int pokracuj = 0;
int i = 0;
int c, znak, radek;

token.stav = START;
token.data = NULL;
token.radek = radek;
token.sloupec = sloupec;




while (pokracuj == 0)
{
    znak = getc(soubor);

    switch (stav)
    {
        case(START);
        {
            if ((isalpha(znak)) || (znak == '_'))  stav = IDENTIFIK;
            else if (isdigit(znak))                stav = INTEGER;
            else if (znak == '=')                  stav = PRIRAZENI;
            else if (znak == ';')                  stav = STREDNIK;
            else if (znak == '(')                  stav = LEVA_ZAVORKA;
            else if (znak == ')')                  stav = PRAVA_ZAVORKA;
            else if (znak == ',')                  stav = CARKA;
            else if (znak == '+')                  stav = PLUS;
            else if (znak == '-')                  stav = MINUS;
            else if (znak == '*')                  stav = KRAT;
            else if (znak == '/')                  stav = DELENO_DESET;
            else if (znak == 92)     /*   \  */    stav = DELENO_CELY;
            else if (znak == '>')                  stav = VETSI;
            else if (znak == '<')                  stav = MENSI;
            else if (znak == EOF)                  stav = ENDOFFILE;
            else if (znak == '\n')                 stav = EOL;
            else if (znak == 39)      //  '
            {
                stav = RADK_KOMENT;
                break;
            }
            else if (znak == '!')
            {
                stav = RETEZEC01;
                break;
            }
            else if (isspace(znak))
            {
                stav = START;
                break;
            }
            else
            {
                stav = CHYBA;
                break;
            }

            rozsirToken(znak, &i);
            break;

        }
        case IDENTIFIK:
        {

            if ((isalpha(znak) || isdigit(znak) || (znak == '_')))
            {
                stav = IDENTIFIK;
                if (znak>64 && znak<91)
                {
                    znak += ('a'-'A');
                }
                rozsirToken(znak, &i);
            }

            else
            {
                token.stav = prejdiRezervovaneSlova(token.data);
                pokracuj = 1;
                vratZnak((char) znak);
            }

            break;
        }


        case INTEGER:
        {
            if (isdigit(znak))
            {
                stav = INTEGER;
                rozsirToken(znak, &i);
            }
            else if (znak == '.')
            {
                stav = DOUBLE_KONTR;
                rozsirToken(znak, &i);
            }
            else if ((znak == 'e') || (znak == 'E'))
            {
                stav = EXP_KONTR;
                rozsirToken(znak, &i);
            }
            else
            {
                token.stav = stav;
                pokracuj = 1;
                vratZnak((char) znak);
            }

            break;
        }

        case DOUBLE_KONTR:
        {
            if (isdigit(znak))
            {
                stav = DOUBLE;
                rozsirToken(znak, &i);
            }
            else
            {
                token.stav = stav;
                stav = CHYBA;
                vratZnak((char) znak);
            }

            break;
        }

        case DOUBLE:
        {
            if (isdigit(znak))
            {
                stav = DOUBLE;
                rozsirToken(znak, &i);
            }
            else if ((znak == 'e') || (znak == 'E'))
            {
                stav = EXP_KONTR;
                rozsirToken(znak, &i);
            }
            else
            {
                token.stav = stav;
                pokracuj = 1;
                vratZnak((char) znak);
            }

            break;
        }

        case EXP_KONTR:
        {
            if ((znak == '-') || (znak == '+'))
            {
                stav = EXP_KONTR02;
                rozsirToken(znak, &i);
            }
            else if (isdigit(znak))
            {
                stav = EXP;
                rozsirToken(znak, &i);
            }
            else
            {
                token.stav = stav;
                stav = CHYBA;
                vratZnak((char) znak);
            }

            break;
        }

        case EXP_KONTR02:
        {
            if (isdigit(znak))
            {
                stav = EXP;
                rozsirToken(znak, &i);
            }
            else
            {
                token.stav = stav;
                stav = CHYBA;
                vratZnak((char) znak);
            }

            break;
        }

        case EXP:
        {
            if (isdigit(znak))
            {
                stav = EXP;
                rozsirToken(znak, &i);
            }

            else
            {
                token.stav = stav;
                pokracuj = 1;
                vratZnak((char) znak);
            }

            break;
        }

        case DELENO_DESET:
        {
            if (znak == 39)
            {
                stav = BLOK_KOMENT;
            }

            else
            {
                token.stav = stav;
                pokracuj = 1;
                vratZnak((char) znak);
            }

            break;
        }

        case PRIRAZENI:
        {
            if (znak == '=')
            {
                stav = JE_ROVNO;
                rozsirToken(znak, &i);
            }

            else
            {
                token.stav = stav;
                pokracuj = 1;
                vratZnak((char) znak);
            }

            break;
        }

        case VETSI:
        {
            if (znak == '=')
            {
                stav = VETSI_ROVNO;
                rozsirToken(znak, &i);
            }

            else
            {
                token.stav = stav;
                pokracuj = 1;
                vratZnak((char) znak);
            }

            break;
        }

        case MENSI:
        {
            if (znak == '=')
            {
                stav = MENSI_ROVNO;
                rozsirToken(znak, &i);
            }

            else if (znak == '>')
            {
                stav = NENI_ROVNO;
                rozsirToken(znak, &i);
            }

            else
            {
                token.stav = stav;
                pokracuj = 1;
                vratZnak((char) znak);
            }

            break;
        }

        case KLIC_SLOVO:
        case REZ_SLOVO:
        case PLUS:
        case MINUS:
        case KRAT:
        case DELENO_CELY:
        case VETSI_ROVNO:
        case MENSI_ROVNO:
        case NENI_ROVNO:
        case JE_ROVNO:
        case LEVA_ZAVORKA:
        case PRAVA_ZAVORKA:
        case CARKA:
        case ENDOFFILE:
        case EOL:
        case STREDNIK:
        {
            token.stav = stav;
            pokracuj = 1;
            vratZnak((char) znak);
            break;
        }

        case RADK_KOMENT:
        {
            if (znak == '\n')
            {
                stav = START;
                i = 0;
            }

            else if (znak == EOF)
            {
                stav = ENDOFFILE;
            }

            else
            {
                stav = RADK_KOMENT;
            }
            break;
        }

        case BLOK_KOMENT:
        {
            if (znak == 39)
            {
                stav = BLOK_KOMENT02;
            }

            else
            {
                stav = BLOK_KOMENT;
            }

            break;
        }

        case BLOK_KOMENT02:
        {
            if (c == '/')
            {
                stav = START;
                i = 0;
            }

            else if (c == 39)
            {
                stav = BLOK_KOMENT02;
            }

            else
            {
                stav = BLOK_KOMENT;
            }

            break;
        }

        case RETEZEC01:
        {
            if (c == '"')
            {
                stav = RETEZEC;
            }

            else
            {
                token.stav = stav;
                stav = CHYBA;
                vratZnak((char) znak);
            }

            break;
        }

        case RETEZEC:
        {
            if (c == '"')
            {
                token.stav = RETEZEC;
                pokracuj = 1;
            }

            else
            {
                stav = RETEZEC;
                rozsirToken(c, &i);
            }

            break;
        }

        case CHYBA:
        {
            error = 1;
            pokracuj = 1;
            break;
        }

       /* case KONEC:
        {
            vratZnak((char) znak);
            pokracuj = 1;
            break;
        }*/


        if (error)
            break;

        if (znak == '\n')
        {
            radek++;
            sloupec = 1;
        }
        else if (isprint(znak))
            sloupec++;

    }
}
return token;
}
