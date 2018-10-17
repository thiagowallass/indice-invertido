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
#include "lista.h"

/*
* Este arquivo contém a definição do TAD Lista Invertida
* Por : Arthur Guilherme
*/

typedef struct inverted_list{
    dict * elms;
}inv_list;

/*
* Aloca um novo elemento do tipo inv_list
*/
inv_list * ilCreate(char * PATH);

/* 
* Insere uma nova dupla <n , doc_id> , atrelada à uma palavra 
*/
int ilInsert(inv_list * invl, char * key, int file);

/* Printa todos os elementos de invl */
void ilPrint(inv_list * invl);

/* Desaloca toda a estrutura invl */
void ilDestroy(inv_list * invl);

#endif