#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#include "Prestadores.h"

typedef struct {
    Envio dato;
    struct Nodo *sig;
}Nodo;

typedef struct {
    Nodo *acc;
}Lista;

void initRS(Lista l[]){
    int i;

    for(i=0 ; i<RS_FACTOR ; i++){
        l[i].acc = NULL;
    }
}

void limpiarRS(Lista l[]){
    int i;
    Nodo* pos = NULL;
    Nodo* aux = NULL;

    for(i=0 ; i<RS_FACTOR ; i++){
        pos = l[i].acc;
        aux = l[i].acc;
        while(pos != NULL){
            pos = aux->sig;
            free(aux);
            aux = pos;
             free((void*)aux);
        }
        l[i].acc = NULL;
    }
}

Nodo* crearNodo(Envio dato){
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));

    if(nuevoNodo!=NULL){
        nuevoNodo->sig = NULL;
        nuevoNodo->dato = dato;
    }

    return nuevoNodo;
}

int localizarRS(Lista lista[], char codigo[], int *i, int *celdas, Nodo **pos, Nodo **aux){
    *i = hashing(codigo, RS_FACTOR);

    (*pos) = lista[*i].acc;
    (*aux) = lista[*i].acc;

    while((*pos) != NULL && strcmp(codigo, (*pos)->dato.codigo)!=0){
        (*aux) = (*pos);
        (*pos) = (*aux)->sig;

        (*celdas)++;
    }

    if((*pos) != NULL){
        (*celdas)++;
        return 1;
    }
    else return 0;
}

int altaRS(Lista lista[], Envio dato){
    Nodo* nuevoNodo = crearNodo(dato);
    int celdas;

    if(nuevoNodo==NULL) return -1;
    else{
        Nodo* pos = NULL;
        Nodo* aux = NULL;
        int i;

        if(localizarRS(lista, dato.codigo, &i, &celdas, &pos, &aux)){
            free(nuevoNodo);
            return 0;
        }else{
            pos = lista[i].acc;
            lista[i].acc = nuevoNodo;
            nuevoNodo->sig = pos;
            return 1;
        }
    }
}

int bajaRS(Lista lista[], Envio dato){
    Nodo* pos = NULL;
    Nodo* aux = NULL;
    int i, celdas;

    if(localizarRS(lista, dato.codigo, &i, &celdas, &pos, &aux) && strcmp(pos->dato.direccion, dato.direccion) == 0 && pos->dato.dniRec == dato.dniRec && pos->dato.dniRem == dato.dniRem && strcmp(pos->dato.fechaE, dato.fechaE)==0 && strcmp(pos->dato.fechaR, dato.fechaR)==0 && strcmp(pos->dato.nombreRec, dato.nombreRec)==0 && strcmp(pos->dato.nombreRem, dato.nombreRem)==0){
        if(pos == aux){
            aux = pos->sig;
            lista[i].acc = aux;
            free(pos);
            pos = aux;
        }else{
            aux->sig = pos->sig;
            free(pos);
            pos = aux->sig;
        }

        return 1;
    }else{
        return 0;
    }
}

int evocarRS(Lista lista[], char cod[], Envio *dato, int *celdas){
    Nodo* pos = NULL;
    Nodo* aux = NULL;
    int i;

    if(localizarRS(lista, cod, &i, celdas, &pos, &aux)){
        *dato = pos->dato;
        return 1;
    }

    return 0;
}

#endif // RS_H_INCLUDED
