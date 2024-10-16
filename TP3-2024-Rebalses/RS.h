#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#include "Prestadores.h"


typedef struct Nodo {
    Prestador dato;
    struct Nodo *sig;
} Nodo;

typedef struct {
    Nodo *acc;
} Lista;

void initRS(Lista l[]){
    int i;

    for(i = 0; i < RS_FACTOR; i++){
        l[i].acc = NULL;
    }
}

void limpiarRS(Lista l[]) {
    int i;
    Nodo* actual;
    Nodo* siguiente;

    for(i = 0; i < RS_FACTOR; i++) {
        actual = l[i].acc;
        while (actual != NULL) {
            siguiente = actual->sig;
            free(actual);
            actual = siguiente;
        }
        l[i].acc = NULL;  // Dejar la cabecera en NULL
    }
}


Nodo* crearNodo(Prestador dato){
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));

    if(nuevoNodo!=NULL){
        nuevoNodo->sig = NULL;
        nuevoNodo->dato = dato;
    }

    return nuevoNodo;
}

int localizarRS(Lista lista[], int dni, int *i, int *celdas, Nodo **pos, Nodo **aux){
    (*i) = hashing(dni, RS_FACTOR);
    (*celdas)=0;
    (*pos) = lista[*i].acc;
    (*aux) = (*pos);

    (*celdas)++;
    if(lista[*i].acc == NULL) return 0;//revisa si la cabecera es NULL entonces da ese lugar

    while((*pos) != NULL && dni != (*pos)->dato.dni){
        (*aux) = (*pos);
        (*pos) = (*pos)->sig;
        if(*pos != NULL) (*celdas)++;
    }

    if((*pos) != NULL){

        return 1;
    }
    else return 0;
}

int altaRS(Lista lista[], Prestador dato) {
    Nodo* nuevoNodo = crearNodo(dato);
    int celdas;

    if (nuevoNodo == NULL) return -1;  // Error al crear nodo

    Nodo* pos = NULL;
    Nodo* aux = NULL;
    int i;


    if (localizarRS(lista, dato.dni, &i, &celdas, &pos, &aux)) {
        free(nuevoNodo);
        return 0;
    } else {

        if (lista[i].acc == NULL) {     // Si la cabecera está libre (acc == NULL)
            lista[i].acc = nuevoNodo;   //Inserta el nodo en la cabecera
        } else {
            nuevoNodo->sig = lista[i].acc->sig;
            lista[i].acc->sig = nuevoNodo;
        }
        return 1;
    }
}


int bajaRS(Lista lista[], Prestador dato) {
    Nodo* pos = NULL;
    Nodo* aux = NULL;
    int i, celdas;

    if (localizarRS(lista, dato.dni, &i, &celdas, &pos, &aux) && compararPrestador(pos->dato, dato)) {
        // Caso 1: Si el nodo a eliminar está en la cabecera
        if (pos == lista[i].acc) {
            Nodo* siguiente = pos->sig;
            lista[i].acc = siguiente;
            free(pos);
        }
        // Caso 2: Si el nodo a eliminar no está en la cabecera
        else {
            aux->sig = pos->sig;
            free(pos);
        }

        return 1;
    } else {
        return 0;
    }
}


int evocarRS(Lista lista[], int dni, Prestador *dato, int *celdas){
    Nodo* pos = NULL;
    Nodo* aux = NULL;
    int i;
    (*celdas)=0;
    if(localizarRS(lista, dni, &i, celdas, &pos, &aux)){
        *dato = pos->dato;
        return 1;
    }

    return 0;
}
#endif // RS_H_INCLUDED
