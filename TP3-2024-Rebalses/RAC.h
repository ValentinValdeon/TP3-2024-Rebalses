#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#include "Prestadores.h"

void initRAC(Prestador lista[]){
    int i;
    for(i=0; i<RAC_FACTOR ;i++){
        lista[i].dni = VIRGEN;
    }
}

int localizarRAC(Prestador lista[], long dniX, int *pos, int *celdas){
    int i = hashing(dniX, RAC_FACTOR);
    int primeraLibre = -1;
    int vistos = 0;

    while(vistos<RAC_FACTOR && lista[i].dni != VIRGEN && lista[i].dni != dniX){
        if(lista[i].dni == LIBRE && primeraLibre == -1) primeraLibre = i;

        vistos++;
        (*celdas)++;
        i = (i+vistos)%RAC_FACTOR;
    }

    if(lista[i].dni == VIRGEN)(*celdas)++;

    if(lista[i].dni == dniX){
        (*celdas)++;
        *pos = i;
        return 1;
    }else if(vistos==RAC_FACTOR && primeraLibre==-1){
        return -1;
    }else if((vistos==RAC_FACTOR && primeraLibre!=-1) || (lista[i].dni == VIRGEN && primeraLibre != -1)){
        *pos = primeraLibre;
    }
    else{
        *pos = i;
    }

    return 0;
}

int altaRAC(Prestador lista[], Prestador p,int *cant){
    int celdas;

    if(*cant == RAC_FACTOR) return -1;
    else{
        int pos;
        int resultado = localizarRAC(lista, p.dni, &pos, &celdas);

        if(resultado == 1 || resultado == -1 ) return 0;
        else{
            lista[pos] = p;
            (*cant)++;
            return 1;
        }
    }
}

int bajaRAC(Prestador lista[], Prestador p, int *cant){
    int pos, celdas;


    if(localizarRAC(lista, p.dni, &pos, &celdas)==1 && compararPrestador(lista[pos],p)){
        lista[pos].dni= LIBRE;
        (*cant)--;
        return 1;
    }else{
        return 0;
    }
}

int evocarRAC(Prestador lista[], Prestador *p, long dniX, int *celdas){
    int pos;

    if(localizarRAC(lista, dniX, &pos, celdas)==1){
        *p = lista[pos];
        return 1;
    }

    return 0;
}


#endif // RAC_H_INCLUDED
