#ifndef INVLIST_H
#define INVLIST_H
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL (void*)0
#endif
#include "dict.h"
/*
* Este arquivo contém a definição do TAD Lista Invertida
* Por : Arthur Guilherme
*/

typedef struct inverted_list{
    dict elms;
}inv_list;

#endif