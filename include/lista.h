#ifndef LISTA_H
#define LISTA_H
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL (void*)0
#endif

/*
* Definição do TAD lista.
* Por : Arthur Guilherme
*/

typedef struct _node_{
    void * data;
    struct _node_ *next;
}node;

typedef struct _sll_{
    node * first;
}sll;

/* Aloca um novo elemento do tipo sll */
sll * sllCreate();

/* Insere um novo elemento no final da lista */
int sllInsert(sll * l, void * data);

/* 
* Realiza uma remoção por chave,
* caso a operação tenha sido bem sucedida: 
* retorna o elm identificado pela chave e remove o nó da lista
* caso não tenha sido encontrado ou tenha havido erro, retorna NULL
*/
void * sllRemove(sll * l, void * key, int(*cmp)(void*,void*));

/* 
* Realiza uma pesquisa por chave
* caso a operação tenha sido bem sucedida, retorna o elm identificado pela chave
* caso não tenha sido encontrado ou tenha havido erro, retorna NULL
*/
void * sllQuery(sll * l, void * key, int(*cmp)(void *,void*));

/* 
* Aplica a função print em todos os nós da lista
*/
void sllPrint(sll * l, void (*print)(void*));

/* 
* Desaloca todos os nós da lista
*/
void sllDestroy(sll*);

/* 
* Retorna o numero de nós em uma lista 
* em caso de erro, retorna -1
*/
int sllNumNodes(sll * l);

/* Insere um novo elemento na primeira posição da lista */
int sllInsertFirst(sll * l , void * data);

/* 
* Remove o primeiro elemento da lista
* caso a operação tenha sido bem sucedida, retorna o primeiro elm
* caso não tenha sido encontrado ou tenha havido erro, retorna NULL
*/
void * sllRemoveFirst(sll*l);

/* 
* Realiza uma pesquisa por chave
* caso a operação tenha sido bem sucedida:
* insere o elemento passado logo após o nó identificado pela chave
* caso não tenha sido encontrado ou tenha havido erro, retorna NULL
*/
int sllInsertAfter(sll * l, void * data, void * key, int (*cmp)(void*,void*));

/* 
* Realiza uma pesquisa por chave
* caso a operação tenha sido bem sucedida:
* insere o elemento passado logo antes do nó identificado pela chave
* caso não tenha sido encontrado ou tenha havido erro, retorna NULL
*/
int sllInsertBefore(sll * l, void * data, void * key, int (*cmp)(void*,void*));

#endif
