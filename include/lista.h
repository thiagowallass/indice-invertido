#ifndef LISTA_H
#define LISTA_H
#define TRUE 1
#define FALSE 0
#define NULL 0

typedef struct _node_{
    void * data;
    struct _node_ *next;
}node;

typedef struct _sll_{
    node * first;
}sll;

sll * sllCreate();
int sllDestroy(sll*);
int sllInsertFirst(sll * l , void * data);
void * sllRemoveFirst(sll*l);
int sllNumNodes(sll * l);
int sllInsertLast(sll * l, void * data);
void * sllQuery(sll * l, void * key, int(*cmp)(void *,void*));
int insertAfter(sll * l, void * data, void * key, int (*cmp)(void*,void*));
int insertBefore(sll * l, void * data, void * key, int (*cmp)(void*,void*));
void * sllremove(sll * l, void * key, int(*cmp)(void*,void*));
void sllPrint(sll * l, void (*print)(void*));

#endif
