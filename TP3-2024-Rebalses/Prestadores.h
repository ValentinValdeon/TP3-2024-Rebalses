#ifndef PRESTADORES_H_INCLUDED
#define PRESTADORES_H_INCLUDED
#define VIRGEN -1
#define LIBRE 0
#define RAL_FACTOR 133
#define RAC_FACTOR 127
#define RS_FACTOR 64

typedef struct {
    long dni;
    char nombre_y_apellido[80];
    char servicios[120];
    char domicilio[80];
    char mail[50];
    char telefono[30];
}Prestador;


void MostrarPrestador(Prestador prestador) {
    printf("DNI: %ld\n", prestador.dni);
    printf("Nombre y Apellido: %s\n", prestador.nombre_y_apellido);
    printf("Servicios: %s\n", prestador.servicios);
    printf("Domicilio: %s\n", prestador.domicilio);
    printf("Email: %s\n", prestador.mail);
    printf("Telefono: %s\n\n", prestador.telefono);

}


int compararPrestador(Prestador p1, Prestador p2) {
    if(strcmpi(p1.domicilio,p2.domicilio)==0 && strcmpi(p1.mail,p2.mail)==0 && strcmpi(p1.nombre_y_apellido,p2.nombre_y_apellido)==0 && strcmpi(p1.servicios,p2.servicios)==0 && strcmpi(p1.telefono,p2.telefono)==0){
        return 1;
    }
    return 0;
}

int hashing(long dni, int M) {
    char x[10];
    long longitud;
    int i, contenedor = 0;
    sprintf(x, "%ld", dni);
    longitud = strlen(x);
    for (i = 0; i < longitud; i++)
        contenedor += ((int)x[i]) * (i + 1);
    return (contenedor % M);
}

#endif // PRESTADORES_H_INCLUDED
