#ifndef DICT_H
#define DICT_H
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL (void*)0
#endif
#define INITVAL 2
#define KEYVAL 80

/*
* Definição do TAD dicionario, utilizando uma hashtable
* Por : Arthur Guilherme
*/

typedef struct _dictionary_node_{
    char key[KEYVAL];
    void * data;
}dnode;

typedef struct _dictionary_{

    /* vetor de dnode's, cada elemento do vetor possui uma key e um campo data*/
    dnode ** elms;

    /* 
    * Contador de tamanho, serve para alocar uma hashtable com esta quantidade de espaço
    * e para fins de redimensionamento da estrutura
    */
    int size;
}dict;



/*
* Retorna um elemento do tipo dict com vetores do tamanho INITVAL alocados
*/
dict * dictCreate(void);

/*
* Insere um elemento na hashtable
* retorna 1 quando não houver erro
* retorna 0 quando não houver espaço
* retorna -1 quando houver erro
* Não é possível inserir um elemento com a chave string vazia
* Não é possível inserir um elemento com a chave "_"
*/
int dictInsert(dict * d , char * key ,void* elm);

/* 
* Remove o elemento identificado pela chave key
* retorna o elm armazenado no dicionário caso a operação tenha sido bem sucedida
* retorna NULL caso não seja encontrada nenhuma correspondência para a chave *key*
*/
void * dictRemove(dict *d, char * key);

/*
* Aplica a função "dealoc" (passada como arg) em todos os elementos do dicionário
* ao final desaloca o dicionário
*/
void dictDestroy(dict * d );

/*
* Aplica a função print para todos os elementos do dicionário
*/
void dictPrint(dict *d , void(*print)(void*));


/*
* Redimensiona o vetor do dicionário, alocando um novo vetor e copiando os elementos do velho para o novo.
* esta operação mantém os índices originais.
* retorna FALSE em caso de falha na alocação
* retorna TRUE caso a operação tenha sido bem sucedida
*/
int dictResize();

#endif