#include "head.h"

/*
   Entradas: un puntero de tipo char o bien string
   Funcionamiento: abre un fichero para extraer el valor de una matriz
   Salidas: una matriz de tipo entero de tamaño 3x3
*/

int** leerFichero(char* nombre){

    //char* suma=malloc(sizeof(char)*27);
    //char* name="../";

    //sprintf(suma,"%s%s", name, nombre);

    //abre el fichero con permisos de lectura
    FILE * fp= fopen(nombre, "r" );
    if(fp==NULL){
        printf("error en cargar el archivo\n");
        return NULL;
    }

    int i,j;
    int** pasabajo=malloc(sizeof(int*)*3);
    
    if(pasabajo==NULL){
        printf("error en asignacion de memoria a pasabajo**\n");
        return NULL;
    }

    for(i=0;i<3;i++){
        pasabajo[i]=malloc(sizeof(int)*3);
        if(pasabajo==NULL){
            printf("error en asignacion de memoria a pasabajo\n");
            return NULL;
        }
    } 

    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            fscanf(fp, "%d", &pasabajo[i][j]);
        }
    }

    fclose(fp);
    return pasabajo;
}