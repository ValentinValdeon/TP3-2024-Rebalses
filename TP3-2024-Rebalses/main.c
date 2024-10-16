#include <stdio.h>
#include <stdlib.h>
#include "Prestadores.h"
#include "RAL.h"
#include "RAC.h"
#include "RS.h"

//Analisis de resultados

// Rebalse Abierto Linal
// Costos maximos ->    Evocacion Exitosa= 55         Evocacion Fracaso= 62
// Costos Medios  ->    Evocacion Exitosa= 2.68       Evocacion Fracaso= 24.77

// Rebalse Abierto Cuadratico
// Costos maximos ->    Evocacion Exitosa= 26         Evocacion Fracaso= 131
// Costos Medios  ->    Evocacion Exitosa= 2.00       Evocacion Fracaso= 14.35

// Rebalse Separado
// Costos maximos ->    Evocacion Exitosa= 7          Evocacion Fracaso= 4
// Costos Medios  ->    Evocacion Exitosa= 1.55       Evocacion Fracaso= 1.18
/*
Rebalse Abierto Linal

En t�rminos de costos m�ximos, el rebalse abierto lineal es la que m�s baldes consulta (evocacion exitosa y que fracasa).
En t�rminos de costos medios, es relativamente costosa en caso de evocaci�n fallida (24.77 baldes como media). Pero, para evocaci�n exitosa, el costo medio es moderado (2.68 baldes).
Es la peor estructura para evocaciones fracasadas debido a sus altos costos tanto m�ximos como medios. En evocaciones exitosas, es decente pero pueden ser mejores los costos si utilizamos una mejor estructura.


Rebalse Abierto Cuadr�tico
En costos m�ximos, es mucho m�s eficiente en evocaciones exitosas (26 frente a 55 del Rebalse Abierto Linal), pero tiene un costo m�ximo muy alto en evocaciones fracasadas (131).
En costos medios, es mejor que el Rebalse Abierto Linal en ambos casos, especialmente en evocaciones fracasadas (14.35 comparado con 24.77).
Es una buena estructura para evocaciones exitosas debido a su bajo costo medio y su costo m�ximo moderado. Para evocaciones fracasadas, es mejor que el Rebalse Abierto Linal pero sigue siendo muy costosa.


Rebalse Separado
En costos m�ximos, es la estructura m�s eficiente en ambos casos, con valores muy bajos tanto en evocaciones exitosas (7) como en fracasadas (4).
En costos medios, tambien es la m�s eficiente en ambos casos. La evocaci�n exitosa tiene un costo promedio de 1.55 baldes, y la fallida apenas cuesta 1.18 de media.
Esta es claramente la mejor estructura en t�rminos de costo general para evocaciones exitosas y fracasadas. Tiene los costos m�ximos y medios m�s bajos en ambos casos.

*/


void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}

int compararEstructuras(Prestador RAL[], Prestador RAC[], Lista RS[],int *cantRAC, int *cantRAL)
{

    FILE* fp = fopen("Operaciones-Prestadores.txt", "r");
    Prestador aux, p;
    int dniX=0;
    int op, i;

    *cantRAL=0;
    *cantRAC=0;
    initRAL(RAL);
    initRAC(RAC);
    initRS(RS);
    limpiarRS(RS);

    // Alta - Baja - Evocacion - SumaAlta - SumaBaja - SumaEvo - Maximo

    int  evoRAL=0,maxEvoERAL=0, maxEvoFRAL=0;
    float sumaEvoERAL=0, sumaEvoFRAL=0;

    int evoRAC=0,maxEvoERAC=0, maxEvoFRAC=0;
    float sumaEvoERAC=0, sumaEvoFRAC=0;

    int evoRS=0, maxEvoERS=0, maxEvoFRS=0;
    float sumaEvoERS=0, sumaEvoFRS=0;

    int cantEvoERAL=0,cantEvoERAC=0, cantEvoERS=0;
    int cantEvoFRAL=0,cantEvoFRAC=0, cantEvoFRS=0;

    if(fp==NULL)
    {
        printf("No se encontro el archivo");
        return -1;
    }
    else
    {
        rewind(fp);

        while(!feof(fp))
        {

            fscanf(fp, "%d", &op);
            if(op==1 || op==2)
            {
                fscanf(fp," %d", (&aux.dni));
                fscanf(fp," %[^\n]", aux.nombre_y_apellido);
                fscanf(fp," %[^\n]", aux.servicios);
                fscanf(fp," %[^\n]", aux.domicilio);
                fscanf(fp," %[^\n]", aux.mail);
                fscanf(fp," %[^\n]", aux.telefono);

                for(i=0; i<80; i++)
                {
                    aux.nombre_y_apellido[i] = toupper(aux.nombre_y_apellido[i]);
                }
                for(i=0; i<120; i++)
                {
                    aux.servicios[i] = toupper(aux.servicios[i]);
                }
                for(i=0; i<80; i++)
                {
                    aux.domicilio[i] = toupper(aux.domicilio[i]);
                }
                for(i=0; i<50; i++)
                {
                    aux.mail[i] = toupper(aux.mail[i]);
                }
                  for(i=0; i<50; i++)


                if(op==1)
                {

                    altaRAL(RAL,aux,cantRAL);
                    altaRAC(RAC,aux,cantRAC);
                    altaRS(RS,aux);

                }
                else
                {

                    bajaRAL(RAL,aux,cantRAL);
                    bajaRAC(RAC,aux,cantRAC);
                    bajaRS(RS,aux);

                }

            }
            else
            {
                fscanf(fp, "%d", (&dniX));

                if(evocarRAL( RAL,&p,dniX, &evoRAL)==1)
                {
                    // Suma para sacar la media
                    sumaEvoERAL = sumaEvoERAL + evoRAL;

                    // Calcular el maximo costo
                    if(evoRAL>maxEvoERAL) maxEvoERAL = evoRAL;

                    cantEvoERAL++;
                }
                else
                {
                    // Suma para sacar la media
                    sumaEvoFRAL = sumaEvoFRAL + evoRAL;

                    // Calcular el maximo costo
                    if(evoRAL>maxEvoFRAL) maxEvoFRAL = evoRAL;

                    cantEvoFRAL++;
                }

                if(evocarRAC(RAC, &p,dniX, &evoRAC )==1)
                {
                    // Suma para sacar la media
                    sumaEvoERAC = sumaEvoERAC + evoRAC;

                    // Calcular el maximo costo
                    if(evoRAC>maxEvoERAC) maxEvoERAC = evoRAC;

                    cantEvoERAC++;
                }
                else
                {
                    // Suma para sacar la media
                    sumaEvoFRAC = sumaEvoFRAC + evoRAC;

                    // Calcular el maximo costo
                    if(evoRAC>maxEvoFRAC) maxEvoFRAC = evoRAC;

                    cantEvoFRAC++;
                }
                //EVOCACIONES LI
                if(evocarRS(RS, dniX, &p, &evoRS)==1)
                {
                    // Suma para sacar la media
                    sumaEvoERS = sumaEvoERS + evoRS;

                    // Calcular el maximo costo
                    if(evoRS>maxEvoERS) maxEvoERS = evoRS;

                    cantEvoERS++;
                }
                else
                {
                    // Suma para sacar la media
                    sumaEvoFRS = sumaEvoFRS + evoRS;

                    // Calcular el maximo costo
                    if(evoRS>maxEvoFRS) maxEvoFRS = evoRS;

                    cantEvoFRS++;
                }

                //Inicializar nuevamente
                evoRAL=0;
                evoRAC=0;
                evoRS=0;
            }
        }

        fclose(fp);
        printf("// Rebalse Abierto Linal\n");
        gotoxy(0,2);
        printf("// Costos maximos ->");
        gotoxy(25,2);
        printf("Evocacion Exitosa= %d", maxEvoERAL);
        gotoxy(55,2);
        printf("Evocacion Fracaso= %d", maxEvoFRAL);
        gotoxy(0,3);
        printf("// Costos Medios  ->");

        gotoxy(25,3);
        if(cantEvoERAL!=0) printf("Evocacion Exitosa= %.2f", sumaEvoERAL/cantEvoERAL);
        else printf("Evocacion Exitosa= 0");

        gotoxy(55,3);
        if(cantEvoFRAL!=0) printf("Evocacion Fracaso= %.2f", sumaEvoFRAL/cantEvoFRAL);
        else printf("Evocacion Fracaso= 0");

        gotoxy(0,5);
        printf("// Rebalse Abierto Cuadratico");
        gotoxy(0,6);
        printf("// Costos maximos ->");
        gotoxy(25,6);
        printf("Evocacion Exitosa= %d", maxEvoERAC);
        gotoxy(55,6);
        printf("Evocacion Fracaso= %d", maxEvoFRAC);
        gotoxy(0,7);
        printf("// Costos Medios  ->");
        gotoxy(25,7);

        if(cantEvoERAC!=0) printf("Evocacion Exitosa= %.2f", sumaEvoERAC/cantEvoERAC);
        else printf("Evocacion Exitosa= 0");

        gotoxy(55,7);
        if(cantEvoFRAC!=0) printf("Evocacion Fracaso= %.2f", sumaEvoFRAC/cantEvoFRAC);
        else printf("Evocacion Fracaso= 0");


        gotoxy(0,9);

        printf("// Rebalse Separado");
        gotoxy(0,10);
        printf("// Costos maximos ->");
        gotoxy(25,10);
        printf("Evocacion Exitosa= %d", maxEvoERS);
        gotoxy(55,10);
        printf("Evocacion Fracaso= %d", maxEvoFRS);
        gotoxy(0,11);

        printf("// Costos Medios  ->");
        gotoxy(25,11);
        if(cantEvoERS!=0) printf("Evocacion Exitosa= %.2f", sumaEvoERS/cantEvoERS);
        else printf("Evocacion Exitosa= 0");

        gotoxy(55,11);
        if(cantEvoFRS!=0) printf("Evocacion Fracaso= %.2f", sumaEvoFRS/cantEvoFRS);
        else printf("Evocacion Fracaso= 0");

        gotoxy(0,13);
    }

    return 1;
}

int main()
{
    Prestador RAL[RAL_FACTOR];
    Prestador RAC[RAC_FACTOR];
    Lista RS[RS_FACTOR];

    initRAL(RAL);
    initRAC(RAC);
    initRS(RS);

    limpiarRS(RS);
    int cantRAC=0,cantRAL=0;
    int i=0;
    int vacio=0,respRS=0;
    int opcion;
    Nodo* pos = NULL;

    do
    {
        printf("Seleccione una opcion\n");
        printf("1- Comparar estructuras\n");
        printf("2- Mostrar Rebalse Abierto Linal\n");
        printf("3- Mostrar Rebalse Abierto Cuadratico\n");
        printf("4- Mostrar Rebalse Separado\n");
        printf("5- Salir\n");
        printf("Opcion: ");
        scanf("%d",&opcion);
        fflush(stdin);

        system("cls");
        switch (opcion)
        {
        case 1:
            vacio=0;
            compararEstructuras(RAL,RAC,RS,&cantRAC,&cantRAL);
            system("pause");
            system("cls");
            break;
        case 2:
            vacio=0;
            for(i=0; i<RAL_FACTOR; i++)
            {
                if(RAL[i].dni==VIRGEN || RAL[i].dni==LIBRE)
                {
                    vacio++;
                }
            }
            if(vacio == RAL_FACTOR)
            {
                printf("No existen prestadores cargados\n");
            }
            else
            {
                for(i=0; i<RAL_FACTOR; i++)
                {
                    if(RAL[i].dni==VIRGEN)
                    {
                        printf("\n---------------------------------------------------------------");
                        printf("\n%d",i);
                        printf("\nCelda virgen");
                        printf("\nPresione ENTER para continuar");
                        getchar();
                    }
                    else if(RAL[i].dni==LIBRE)
                    {
                        printf("\n---------------------------------------------------------------");
                        printf("\n%d",i);
                        printf("\nCelda libre");
                        printf("\nPresione ENTER para continuar");
                        getchar();
                    }
                    else
                    {
                        printf("\n---------------------------------------------------------------");
                        printf("\n%d\n",i);
                        MostrarPrestador(RAL[i]);
                        printf("\nPresione ENTER para continuar");
                        getchar();
                    }
                }
            }
            system("pause");
            system("cls");
            break;
        case 3:
            for(i=0; i<RAC_FACTOR; i++)
            {
                if(RAC[i].dni == VIRGEN || RAC[i].dni == LIBRE)
                {
                    vacio++;
                }
            }
            if(vacio == RAC_FACTOR)
            {
                printf("No existen prestadores cargados\n");
            }
            else
            {
                for(i=0; i<RAC_FACTOR; i++)
                {
                    if(RAC[i].dni==VIRGEN)
                    {
                        printf("\n---------------------------------------------------------------");
                        printf("\n%d",i);
                        printf("\nCelda virgen");
                        printf("\nPresione ENTER para continuar");
                        getchar();
                    }
                    else if(RAC[i].dni == LIBRE)
                    {
                        printf("\n---------------------------------------------------------------");
                        printf("\n%d",i);
                        printf("\nCelda libre");
                        printf("\nPresione ENTER para continuar");
                        getchar();
                    }
                    else
                    {
                        printf("\n---------------------------------------------------------------");
                        printf("\n%d\n",i);
                        MostrarPrestador(RAC[i]);
                        printf("\nPresione ENTER para continuar");
                        getchar();
                    }
                }
            }
            system("pause");
            system("cls");
            break;
        case 4:
            printf("Seleccione una opcion\n");
            printf("1- Mostrar datos completos\n");
            printf("2- Mostrar rebalse grafico (solo dni)\n");
            printf("Opcion: ");
            scanf("%d",&respRS);
            vacio = 0;
            for(i=0; i<RS_FACTOR; i++)
            {
                if(RS[i].acc == NULL)
                {
                    vacio++;
                }
            }
            if(respRS==1){
                if(vacio == RS_FACTOR)
                {
                    printf("No existen prestadores cargados\n");

                }
                else
                {
                    for(i=0; i<RS_FACTOR; i++)
                    {
                        if(RS[i].acc == NULL)
                        {
                            printf("\n---------------------------------------------------------------");
                            printf("\n%d",i);
                            printf("\nLista vacia");
                            printf("\nPresione ENTER para continuar");
                            getchar();
                        }
                        else
                        {
                            pos = RS[i].acc;

                            while(pos!=NULL)
                            {
                                printf("\n---------------------------------------------------------------");
                                printf("\n%d\n",i);
                                MostrarPrestador(pos->dato);
                                printf("\nPresione ENTER para continuar");

                                getchar();
                                pos = pos->sig;
                            }
                        }
                    }
                }
            }else{
                for(i=0; i<RS_FACTOR; i++)
                {
                    pos = RS[i].acc;
                    printf("Cabecera %d ===> ",i);
                    while(pos !=NULL){
                        printf("|%d|-->",pos->dato.dni);
                        pos = pos->sig;
                    }
                    if(pos==NULL) printf("//");
                    printf("\n");
                }
            }
            system("pause");
            system("cls");
            respRS=0;
            break;
        }
    }

    while (opcion!=5);
    return 0;
}
