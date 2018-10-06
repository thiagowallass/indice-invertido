#include <stdlib.h>
#include <stdio.h>
#include "inverted-list.h"
#include "dict.h"
#include "lista.h"

void printDouble(void * d_p){
    int *d;
    /* Certifica-se de que nenhum ponteiro é nulo */
    if(d_p!=NULL){
        d = (int*)d_p;
        printf("<%d , %d>",d[0], d[1]);
    }
}

void printSll(void* l_p){
    sll * l;
    /* Certifica-se de que nenhum ponteiro é nulo */
    if(l_p!=NULL){
        l = (sll*)l_p;
        sllPrint(l , printDouble);
    }
}

void ilPrint(inv_list * invl){
    if(invl!=NULL){
        printf("====== Inverted List ======\n");
        dictPrint(invl->elms , printSll);
        printf("\n");
    }
}

int ilInsert(inv_list * invl, char * key , void * v){
    sll * l;
    void * l_p;
    if(invl==NULL || key == NULL) return FALSE;

    /* recupera a lista de duplas do dict*/
    l_p = dictQuery(invl->elms , key);

    if(l_p == NULL){//Caso a palavra ainda não tenha sido registrada
    
        /* Cria a lista de duplas */
        l = sllCreate();
        /* Insere a dupla na lista de duplas */
        if(sllInsert(l , v)!=TRUE) return FALSE;
        /* Insere a lista de duplas no dicionário */
        return dictInsert(invl->elms , key  , (void*)l);

    }else{
        /* converte a lista */
        l = (sll*)l_p;

        /* Insere a dupla na lista de duplas */
        return sllInsert(l , v);
    }
}

inv_list * ilCreate(void){
    inv_list * invl;

    /* Aloca um novo elemento do tipo inv_list */
    invl = (inv_list*)malloc(sizeof(inv_list));

    /* Checa se realmente foi alocado */
    if(invl!=NULL){
        /* Aloca um novo elemento do tipo dict */
        invl->elms = dictCreate();

        /* Checa se realmente foi alocado */
        if(invl->elms!=NULL){
            return invl;
        }else{
            free(invl);
        }
    }
    return NULL;
}