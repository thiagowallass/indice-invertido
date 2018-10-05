#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

sll * sllCreate(){
    sll * l;
    l = (sll*)malloc(sizeof(sll));

    if (l!=NULL){
        l->first = NULL;
        return l;
    }

    return NULL;
}

void sllPrint(sll * l, void (*print)(void*)){
    node * aux;

    aux = l->first;
    printf("== lista ==\n");

    while(aux!=NULL){
        print(aux->data);
        printf("\n");
        aux = aux->next;
    }
}

int insertBefore(sll * l, void * data, void * key, int (*cmp)(void*,void*)){
    node * aux, * prev;
    node * newNode;
    int stat;
    if(l!=NULL){
        if(l->first!=NULL){
            aux = l->first;
            prev = NULL;
            stat = cmp(key, aux->data);
            while(stat != TRUE && aux->next!=NULL){
                prev = aux;
                aux = aux->next;
                stat = cmp(key,aux->data);
            }
            if(stat == TRUE){
                newNode = (node*)malloc(sizeof(node));
                if(newNode!=NULL){
                    newNode->data = data;
                    newNode->next = aux;
                    if(prev!=NULL){
                        prev->next = newNode;
                    }else{
                        l->first = newNode;
                    }
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}


int insertAfter(sll * l, void * data, void * key, int (*cmp)(void*,void*)){
    node * aux;
    node * newNode;
    int stat;
    if(l!=NULL){
        if(l->first!=NULL){
            aux = l->first;
            stat = cmp(key, aux->data);
            while(stat != TRUE && aux->next!=NULL){
                aux = aux->next;
                stat = cmp(key,aux->data);
            }
            if(stat == TRUE){
                newNode = (node*)malloc(sizeof(node));
                if(newNode!=NULL){
                    newNode->data = data;
                    newNode->next = aux->next;
                    aux->next = newNode;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

void * sllremove(sll * l, void * key, int(*cmp)(void*,void*)){
    node * aux, * prev;
    void * data;
    int stat;
    if(l!=NULL){
        if(l->first!=NULL){
            aux = l->first;
            stat = cmp(key, aux->data);
            while(stat != TRUE && aux->next!=NULL){
                prev = aux;
                aux = aux->next;
                stat = cmp(key,aux->data);
            }
            if(stat == TRUE){
                data = aux->data;
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

void * sllQuery(sll * l, void * key, int(*cmp)(void*,void*)){
    node * aux;
    int stat;
    if(l!=NULL){
        if(l->first!=NULL){
            aux = l->first;
            stat = cmp(key, aux->data);
            while(stat != TRUE && aux->next!=NULL){
                aux = aux->next;
                stat = cmp(key,aux->data);
            }
            if(stat == TRUE){
                return aux->data;
            }
        }
    }
    return NULL;
}

int sllInsertLast(sll * l, void * data){
    node * aux;
    node * newNode;
    if(l!=NULL){
        newNode = (node*)malloc(sizeof(node));
        newNode->next = NULL;
        newNode->data = data;

        if(l->first !=NULL){
            aux = l->first;
            while(aux->next !=NULL){
                aux = aux->next;
            }
            aux->next = newNode;
        }else{
            l->first = newNode;
        }
        return TRUE;
    }
    return FALSE;
}

int sllNumNodes(sll * l){
    int n;
    node * aux;
    n = 0;
    if(l!=NULL){
        if(l->first!=NULL){
            aux = l->first;
            while(aux != NULL){
                aux = aux->next;
                n++;
            }
            return n;
        }
    }
    return 0;
}

int sllDestroy(sll * l){
    if(l!=NULL){
        if(l->first==NULL){
            free(l);
            return TRUE;
        }
    }
    return FALSE;
}

void * removeFirst(sll * l){
    node * aux; void* data;
    if(l!=NULL){
        if(l->first!=NULL){
            aux = l->first;
            data = aux->data;
            l->first = aux->next;
            free(aux);
            return data;
        }
    }
    return NULL;
}

int sllInsertFirst(sll * l , void * data){
    node * newNode;
    if(l!=NULL){
        newNode = (node*)malloc(sizeof(node));
        if(newNode!=NULL){
            newNode->data = data;
            newNode->next = l->first;
            l->first = newNode;
            return TRUE;
        }
    }
    return FALSE;
}
