#ifndef RAL_H_INCLUDED
#define RAL_H_INCLUDED
#include "Prestadores.h"

void initRAL(Prestador lista[]){
    int i;

    for(i=0; i<RAL_FACTOR ;i++){
        lista[i].dni = VIRGEN;
    }
}

int localizarRAL(Prestador lista[], int dniX, int *pos, int *celdas){
    int i = hashing(dniX, RAL_FACTOR);
    int primerLibre = -1;
    int vistos = 0;

    while(vistos<RAL_FACTOR && lista[i].dni != VIRGEN && lista[i].dni != dniX){

        if(lista[i].dni == LIBRE && primerLibre == -1) primerLibre = i;

        vistos++;
        (*celdas)++;
        i = (i+1)%RAL_FACTOR;
    }

    if(lista[i].dni == VIRGEN) (*celdas)++;

    if(lista[i].dni == dniX){
        (*celdas)++;
        *pos = i;
        return 1;
    }
    else if(lista[i].dni == VIRGEN && primerLibre == -1) *pos = i;
    else if((vistos==RAL_FACTOR && primerLibre != -1) || (lista[i].dni == VIRGEN && primerLibre != -1)) *pos = primerLibre;

    return 0;
}

int altaRAL(Prestador lista[], Prestador p, int *cant){
    int celdas;

    if(*cant == RAL_FACTOR) return -1;
    else{
        int pos;

        if(localizarRAL(lista, p.dni, &pos, &celdas)) return 0;
        else{
            lista[pos] = p;
            (*cant)++;
            return 1;
        }
    }
}

int bajaRAL(Prestador lista[], Prestador p, int *cant){
    int pos, celdas;

    if(localizarRAL(lista, p.dni, &pos, &celdas) && compararPrestador(lista[pos],p)){
        lista[pos].dni=LIBRE;
        (*cant)--;
        return 1;
    }else{
        return 0;
    }
}

int evocarRAL(Prestador lista[], Prestador *p, int dniX,int *celdas){
    int pos;

    if(localizarRAL(lista, dniX, &pos, celdas)){
        *p = lista[pos];
        return 1;
    }

    return 0;
}


#endif // RAL_H_INCLUDED
