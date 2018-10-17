#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dict.h"

/*
* Implementação das operações possíveis sobre o TAD dicionario, utilizando uma hashtable.
* Por : Arthur Guilherme
*/

int dictResize(dict * d){
    int i , new_size;
    dnode ** new_elms;

    if(d == NULL) return FALSE;

    /*define o novo tamanho do vetor*/
    new_size = d->size + INITVAL;

    /*aloca o novo vetor de elementos*/
    new_elms = (dnode**)malloc(sizeof(dnode*)*new_size);

    /*Certifica-se de que foi alocado*/
    if(new_elms == NULL) return FALSE;

    for(i = 0  ; i < new_size; i++){
        new_elms[i] = (dnode*)malloc(sizeof(dnode));
        /* Caso ocorra falha na alocação, desaloca os nodes anteriores */
        if(new_elms[i]==NULL){
            i--;
            while(i>=0){
                free(new_elms[i]);
                i--;
            }
            free(new_elms);
            return FALSE;
        }
    }

    /* Copia os elementos de d->elms para o novo vetor*/
    for(i = 0 ; i < d->size; i++){
        strcpy(new_elms[i]->key,d->elms[i]->key);
        new_elms[i]-> data = d->elms[i]->data;
    }

    /*Preenche o restante do vetor com casas vazias*/
    for(; i < new_size;i++){
        strcpy(new_elms[i]->key, "");
    }

    /*Desaloca o vetor antigo*/
    for(i = 0 ; i  <d->size; i++){
        free(d->elms[i]);
    }

    /*Atribui o novo vetore à estrutura*/
    d->elms = new_elms;
    d->size = new_size;

    return TRUE;
}

void dictPrint(dict *d , void(*print)(void*)){
    int i , empty;
    /*
    * Certifica-se de que nenhum ponteiro é nulo
    */
    if(d!=NULL){
        printf("tamanho : %d\n",d->size);
        /* Itera por cada elemento da hashtable, e aplica a função print passada */
        
        for(i = 0 ; i < d->size; i++){
            empty = strcmp(d->elms[i]->key  , "")==0 || strcmp(d->elms[i]->key  , "_")==0;
            if(empty!=TRUE){
                printf("%s : ", d->elms[i]->key);
                print(d->elms[i]->data);
                printf("\n");
            }
        }
    }
}

int hash(char * key){
    int i , x , n;
    /* Itera sobre cada letra de key, retirando seu valor ascii e somando com a sua multiplicação por um peso aleatorio */
    n = strlen(key);
    x = 0;
    for(i = 0 ; i < n ; i++){
        printf("Key = %d\n", (int)key[i]);
        x+=((int) key[i]) * (128^(n-i));
    }
    return x;
}

void * dictQuery(dict * d, char * key){
    int i, empty , equals , hash_key;

    /*
    * Certifica-se de que nenhum ponteiro é nulo
    */
    if(d==NULL || key ==NULL) return NULL;
    if(strcmp(key , "")==0 ||strcmp(key , "_")==0 ) return NULL;
    
    hash_key = hash(key)%d->size; //Calcula o índice
    printf("%d\n", hash_key);
    /* Busca a primeira casa vazia, ou que a chave seja igual a key, por tentativa linear*/
    empty = strcmp(d->elms[hash_key]->key  , "") == 0;
    equals = strcmp(d->elms[hash_key]->key , key) == 0;
    while(empty!=TRUE && equals!=TRUE && hash_key<d->size-1){
        /* incrementa e compara novamente */
        hash_key++;
        empty = strcmp(d->elms[hash_key]->key  , "") == 0;
        equals = strcmp(d->elms[hash_key]->key , key) == 0;
    }
    /* Caso tenha encontrado a chave */
    if(equals==TRUE){
        return d->elms[hash_key]->data;
    }
    return NULL;
}

void * dictRemove(dict *d, char * key){
    int i, empty , equals , hash_key;

    /*
    * Certifica-se de que nenhum ponteiro é nulo
    */
    if(d == NULL || key == NULL) return NULL;
    if(strcmp(key , "")==0 || strcmp(key , "_")==0) return NULL;

    hash_key = hash(key)%d->size; //Calcula o índice

    /* Busca a primeira casa vazia, ou que a chave seja igual a key, por tentativa linear*/
    empty = strcmp(d->elms[hash_key]->key  , "") == 0;
    equals = strcmp(d->elms[hash_key]->key , key) == 0;
    while(empty!=TRUE && equals!=TRUE && hash_key<d->size-1){
        /* incrementa e compara novamente */
        hash_key++;
        empty = strcmp(d->elms[hash_key]->key  , "") == 0;
        equals = strcmp(d->elms[hash_key]->key , key) == 0;
    }
    /* Caso tenha encontrado a chave */
    if(equals==TRUE){
        strcpy(d->elms[hash_key]->key , "_");
        return d->elms[hash_key]->data;
    }
    return NULL;
}

int dictInsert(dict * d , char * key ,void* elm){

    int hash_key;
    int i, empty , equals;

    /*
    * Certifica-se de que nenhum ponteiro é nulo
    */
    if(d == NULL || elm == NULL || key == NULL) return FALSE;
    if(strcmp(key , "")==0 || strcmp(key , "_")==0) return FALSE;

    hash_key =  hash(key) % d->size; //calcula a hash_key do elemento

    /* Busca a primeira casa vazia, ou que a chave seja igual a key*/
    empty = strcmp(d->elms[hash_key]->key  , "")==0 || strcmp(d->elms[hash_key]->key  , "_")==0;
    equals = strcmp(d->elms[hash_key]->key , key) == 0;
    while(empty!=TRUE && equals!=TRUE && hash_key<d->size-1){
        /* incrementa e compara novamente */
        hash_key++;
        empty = strcmp(d->elms[hash_key]->key  , "")==0 || strcmp(d->elms[hash_key]->key  , "_")==0;
        equals = strcmp(d->elms[hash_key]->key , key) == 0;
    }

    if(empty==TRUE || equals == TRUE){//Caso exista alguma casa disponível ou com a mesma chave

        if(empty==TRUE){
            strcpy(d->elms[hash_key]->key , key);
        }
        d->elms[hash_key]->data = elm;
        return TRUE;

    }else if(hash_key == d->size-1){ //Caso o vetor esteja cheio

        /* Tenta executar um resize e reinserir o elemento */
        if(dictResize(d)){
            return dictInsert(d , key , elm);
        }else{
            return FALSE;
        }

    }
    return -1;
}

void dictDestroy(dict * d){
    int i;
    /*
    * Certifica-se de que nenhum ponteiro é nulo
    */
   if(d!=NULL){
        
        /* Itera por cada elemento da hashtable, e aplica a função dealoc passada */
        for(i = 0 ; i < d->size ; i++){
            free(d->elms[i]);
        }

        /* Libeara o espaço alocado previamente na estrutura */
        free(d->elms);
        free(d);
    }
}

dict * dictCreate(void){
    dict * d;
    int i;

    /*Aloca um elemento do tipo dict*/
    d = (dict*)malloc(sizeof(dict));

    /* Verifica se foi realmente alocado */
    if(d!=NULL){

        /*Aloca o vetor de elementos do tamanho de INITVAL*/
        d->elms = (dnode**)malloc(sizeof(dnode*)*INITVAL);

        /* Verifica se foi realmente alocado */
        if(d->elms!=NULL){
            d->size = INITVAL; //Armazena o tamanho inicial

            /*Inicializa todas as key com a string vazia*/
            for(i = 0 ; i < d->size; i++){

                d->elms[i] = (dnode*)malloc(sizeof(dnode));

                /* Caso ocorra falha na alocação, desaloca os nodes anteriores */
                if(d->elms[i]==NULL){
                    i--;
                    while(i>=0){
                        free(d->elms[i]);
                        i--;
                    }
                    free(d->elms);
                    free(d);
                    return NULL;
                }
                strcpy(d->elms[i]->key , "");
                d->elms[i]->data = NULL;
            }
            return d;
        }
    }
    return NULL;
}
