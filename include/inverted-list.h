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
* Incrementa uma dupla <n , doc_id> , atrelada à uma palavra
* Caso esta dupla não exista ainda, será criada uma nova dupla com n = 1
* Caso a palavra não esteja no dicionário ainda, será criada uma nova entrada no dicionário, com a chave key passada 
* e será criada a sua lista de duplas, com a dupla <1 , file> já inserida
*/
int ilInsert(inv_list * invl, char * key, int file);

/* Printa todos os elementos de invl */
void ilPrint(inv_list * invl);

/* Desaloca toda a estrutura invl */
void ilDestroy(inv_list * invl);

#endif