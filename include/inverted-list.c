#include <stdlib.h>
#include <stdio.h>
#include "inverted-list.h"
#include "dict.h"
#include "lista.h"
#include <dirent.h>
#include <string.h>



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
    }
}

int cmp_file_ptr(void * file_ptr , void * vet_ptr){
    int *file, *vet;
    if(file_ptr == NULL || vet_ptr == NULL) return -1;

    file = (int*)file_ptr;
    vet  = (int*)vet_ptr;

    if(*file == vet[1]){
        return TRUE;
    }
    return FALSE;
}

int ilInsert(inv_list * invl, char * key, int file){

    sll * l;
    void * l_p;
    void * vet_p;
    int * vet;

    if(invl==NULL || key == NULL) return FALSE;
    /* Armazena a lista de duplas da palavra passada, buscando-a no dicionário do índice invertido */
    l_p = dictQuery(invl->elms , key);
    
    if(l_p == NULL){//Caso a palavra ainda não tenha sido registrada
        /* Cria a lista de duplas */
        l = sllCreate();

        /* Aloca uma nova dupla e armazena na lista de duplas */
        vet = malloc(sizeof(int*)* 2);
        vet[0] = 1;
        vet[1] = file;

        if(sllInsert(l , (void*)vet)!=TRUE) return FALSE;

        /* Insere a lista de duplas no dicionário */
        return dictInsert(invl->elms , key  , (void*)l);

    }else{//Caso a palavra já tenha sido registrada
        /* converte a lista */
        l = (sll*)l_p;

        /* Busca pela dupla identificada por 'file' */
        vet_p = sllQuery(l , (void*)&file, cmp_file_ptr);
        
        if(vet_p!=NULL){//Caso a dupla já esteja na lista
            vet = (int*)vet_p;
            vet[0]++;//Incrementa o contador da dupla

        }else{// Caso a dupla ainda não esteja na lista

            /* Aloca uma nova dupla e armazena na lista de duplas */
            vet = malloc(sizeof(int*)* 2);
            vet[0] = 1;
            vet[1] = file;
            sllInsert(l , (void*)vet);
        }
    }
}

int isletter(char c){
    switch(c){
        case '\n':
        case '#':
        case '=':
        case '(':
        case ')':
        case '}':
        case '{':
        case '\'':
        case '\"':
        case '-':
        case ' ':
        case '.':
        case ',':
        case ';':
            return FALSE;
        default:
            return TRUE;
    }
}

void print_filename(void * file_ptr){
    char * file;
    if(file_ptr!=NULL){
        file = (char*)file_ptr;
        printf("%s", file);
    }
}

sll * get_files(char * PATH){

    /*
    * Retorna uma lista dos nomes de todos os arquivos localizados na pasta PATH
    */
    char * tmp_fname;
    node * aux;
    sll * l; //lista de nomes
    DIR * dir_pointer;
    struct dirent * dir_info;
    int i;

    /* Verifica se o ponteiro do caminho é nulo*/
    if(PATH == NULL) return FALSE;

    /* Aloca uma nova lista de Nomes */
    l = sllCreate();

    /* Checa se realmente foi alocada*/
    if(l!=NULL){

        /* Abre a pasta localizada em PATH */
        dir_pointer =  opendir(PATH);

        if(dir_pointer!=NULL){
            /* Itera por todos os arquivos na pasta PATH */
            while((dir_info = readdir(dir_pointer)) != NULL ){

                /* Ignora os arquivos . e .. */
                if(strcmp(dir_info->d_name, ".") != 0 && strcmp(dir_info->d_name, "..") != 0){
                    /* Insere o nome do arquivo na lista */
                    tmp_fname = malloc(sizeof(char) * strlen(dir_info->d_name));
                    for(i= 0; i < strlen(dir_info->d_name); i++){
                        tmp_fname[i] = dir_info->d_name[i];
                    }
                    sllInsert(l,(void *)tmp_fname);
                }
            }

        }

        /* fecha o diretório */
        closedir(dir_pointer);
        return l;
    }

    return NULL;
}

void read_file(inv_list * invl, char* PATH, char* fname, int fnumber){
    char buffer[200], temp_filepath[300] , tmp;
    FILE * f;
    int i;

    if(invl!=NULL){
        /* Abre o arquivo */
        strcpy(temp_filepath, PATH);
        strcat(temp_filepath, fname);
        f = fopen(temp_filepath, "r");
        
        if(f!=NULL){
            /*Itera por todos os caracteres, identificando palavras*/
            i = 0;
            while(!feof(f)){
                /*Itera por todas as letras de uma palavra até o fim da palavra*/
                tmp = fgetc(f);
                while(isletter(tmp) == TRUE && !feof(f)){
                    buffer[i] = tmp;
                    tmp = fgetc(f);
                    i++;
                }
                
                
                if(i!=0){//Se alguma letra já foi inserida como parte da palavra
                    /* Define o fim da palavra */
                    buffer[i] = '\0';
                    ilInsert(invl , buffer , fnumber);
                }
                i = 0;
            }
        }
    }
}

inv_list * ilCreate(char * PATH){

    int i;
    node * aux;
    sll * files_list;
    inv_list * invl;
    char * temp_name;

    /* Aloca um novo elemento do tipo inv_list */
    invl = (inv_list*)malloc(sizeof(inv_list));

    /* Checa se realmente foi alocado */
    if(invl == NULL) return NULL;

    /* Aloca um novo elemento do tipo sll */
    files_list = get_files(PATH);
    /* Checa se realmente foi alocado */
    if(files_list == NULL){
        free(invl);
        return NULL;
    } 

    /* Aloca um novo elemento do tipo dict */
    invl->elms = dictCreate();

    /* Checa se realmente foi alocado */
    if(invl->elms==NULL){
        free(invl);
        free(files_list);
        return NULL;
    }

    /* Após tudo alocado, preenche a lista invertida com as entradas passadas na pasta PATH */
    i = 1;
    aux = files_list->first;
    while(aux != NULL){
        temp_name = (char*)aux->data;
        read_file(invl, PATH, temp_name, i);
        aux = aux->next;
        i++;
    }

    ilPrint(invl);
}

void ilDestroy(inv_list * invl){
    if(invl!=NULL){
        dictDestroy(invl->elms);
        free(invl);
    }
}