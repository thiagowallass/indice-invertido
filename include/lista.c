#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

void sllPrint(sll * l, void (*print)(void*)){
    node * aux;

    /*Itera por cada elemento aplicando a função print passada*/
    if(l->first!=NULL){
        aux = l->first;
        while(aux!=NULL){
            print(aux->data);
            printf("\t");
            aux = aux->next;
        }
    }
}

int sllInsertBefore(sll * l, void * data, void * key, int (*cmp)(void*,void*)){
    node * aux, * prev , * new;
    int stat;

    /* Certifica-se de que nenhum ponteiro é nulo */
    if(l!=NULL){
        if(l->first!=NULL){

            /* Itera por toda a lista procurando uma correspondência */
            aux = l->first;
            prev = NULL;
            stat = cmp(key, aux->data);
            while(stat != TRUE && aux->next!=NULL){
                prev = aux;
                aux = aux->next;
                stat = cmp(key,aux->data);
            }
            /* Aloca novo nó */
            new = (node*)malloc(sizeof(node));

            /* Checa se realmente alocou e preenche os dados */
            if(new!=NULL){
                    new->data = data;
            }

            /* Caso haja uma correspondência */
            if(stat == TRUE){
                /* 
                * Trata quando um elemento está no começo da lista,
                * ou em outra posição 
                */
                new->next = aux;
                if(prev!=NULL){
                    prev->next = new;
                }else{
                    l->first = new;
                }
                return TRUE;
            }else{
                aux->next = new;
                new->next = NULL;
                return TRUE;
            }
        }
    }
    return FALSE;
}

int sllInsertAfter(sll * l, void * data, void * key, int (*cmp)(void*,void*)){
    node * aux, * new;
    int stat;
    
    /* Certifica-se de que nenhum ponteiro é nulo */
    if(l!=NULL){
        if(l->first!=NULL){

            /* itera por todos os elementos procurando uma correspondência */
            aux = l->first;
            stat = cmp(key, aux->data);
            while(stat != TRUE && aux->next!=NULL){
                aux = aux->next;
                stat = cmp(key,aux->data);
            }
            /* Caso haja uma correspondência, aloca o novo nó e insere logo após */
            if(stat == TRUE){
                /* Aloca */
                new = (node*)malloc(sizeof(node));

                /* Checa se realmente alocou*/
                if(new!=NULL){
                    new->data = data;
                    new->next = aux->next;
                    aux->next = new;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

void * removeFirst(sll * l){
    node * aux; void* data;

    /* Certifica-se de que nenhum ponteiro é nulo */
    if(l!=NULL){
        if(l->first!=NULL){
            
            aux = l->first;
            data = aux->data;//Guarda o dado

            /* Faz o começo da lista apontar para o segundo elemento */
            l->first = aux->next;

            /*Desaloca*/
            free(aux);

            return data;
        }
    }
    return NULL;
}

int sllInsertFirst(sll * l , void * data){
    node * new;
    /* Certifica-se de que nenhum ponteiro é nulo*/
    if(l!=NULL){

        /*Aloca um novo nó*/
        new = (node*)malloc(sizeof(node));

        /*Checa se foi realmente alocado*/
        if(new!=NULL){

            /*Atribui o dado ao novo nó*/
            new->data = data;

            /*Transforma o nó em primeiro elemento da lista*/
            new->next = l->first;
            l->first = new;

            return TRUE;
        }
    }
    return FALSE;
}

int sllNumNodes(sll * l){
    int n;
    node * aux;
    n = 0;

    /* Certifica-se de que nenhum ponteiro é nulo */
    if(l!=NULL){
        if(l->first!=NULL){//Caso haja elementos na lista

            /* 
            * Itera por todos os elementos até encontrar um nulo
            * enquanto isso acumula +1 na variavel "n"
            */
            aux = l->first;
            while(aux != NULL){
                aux = aux->next;
                n++;
            }
            return n;
        }
        return 0;
    }
    return -1;
}

void * sllQuery(sll * l, void * key, int(*cmp)(void*,void*)){
    node * aux;
    int stat;
    
    /* Certifica-se de que nenhum ponteiro é nulo */
    if(l!=NULL){
        if(l->first!=NULL){
            /* Itera por cada elemento buscando uma correspondência de chave */
            aux = l->first;
            stat = cmp(key, aux->data);
            while(stat != TRUE && aux->next!=NULL){
                aux = aux->next;
                stat = cmp(key,aux->data);
            }

            /* Caso haja uma correspondência, retorna o dado */
            if(stat == TRUE){
                return aux->data;
            }
        }
    }
    return NULL;
}

void * sllremove(sll * l, void * key, int(*cmp)(void*,void*)){
    node * aux, * prev;
    void * data;
    int stat;

    /* Certifica-se de que nenhum ponteiro é nulo */
    if(l!=NULL){
        if(l->first!=NULL){//Checa se a lista está vazia

            /* Itera por todos os elementos buscando uma correspondência de key */
            aux = l->first;
            stat = cmp(key, aux->data);
            while(stat != TRUE && aux->next!=NULL){
                prev = aux;
                aux = aux->next;
                stat = cmp(key,aux->data);
            }

            if(stat == TRUE){
                /*Caso haja uma correspondência*/

                data = aux->data;//Guarda o dado

                /* 
                * Trata quando um elemento está no começo da lista,
                * ou em outra posição 
                */
                if(prev!=NULL){
                    prev->next = aux->next;
                }else{
                    l->first = aux->next;
                }
                free(aux);
                return data;
            }
        }
    }
    return NULL;
}

int sllInsert(sll * l, void * data){
    node * aux , * new;

    /* Certifica-se de que nenhum ponteiro é nulo*/
    if(l!=NULL){
        /* Aloca um novo nó na lista*/
        new = (node*)malloc(sizeof(node));

        /* Certifica-se de que foi alocado */
        if(new!=NULL){

            /* Define o novo nó como ultimo elemento da lista */
            new->next = NULL;
            new->data = data;

            if(l->first == NULL){//Caso a lista esteja vazia
                l->first = new;
                
            }else{//Caso haja elementos
                aux = l->first;
                while(aux->next !=NULL){
                    aux = aux->next;
                }
                aux->next = new;
            }
            return TRUE;
        }
    }
    return FALSE;
}


sll * sllCreate(){
    sll * l;
    /* Aloca um novo elemento do tipo sll */
    l = (sll*)malloc(sizeof(sll));

    /* Certifica-se de que foi alocado */
    if (l!=NULL){
        /* Inicializa a lista vazia */
        l->first = NULL;
        return l;
    }
    return NULL;
}

void sllDestroy(sll * l){
    node * aux, *next;

    /* Certifica-se de que nenhum ponteiro é nulo*/
    if(l!=NULL){

        /* Itera por todos os nós, desalocando cada um */
        aux = l->first;
        while(aux!=NULL){
            next = aux->next;
            free(aux);
            aux = next;
        }
    }
}