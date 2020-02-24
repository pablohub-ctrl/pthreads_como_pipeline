#include "head.h"

/*
   Entradas:        un valor 'n' de tipo entero, información respecto al ciclo de la imagen a cargar o bien, binarizar. 
   Funcionamiento:  formular el nombre correcto para cada ciclo de las imagenes a procesar para ser posible cargar imágenes .png de forma dinámica en conteo.
   Salidas:         un puntero tipo char.
*/

char* nombre_imagen(int n){
    char* retorno=malloc(sizeof(char)*27);
    //char foto[]="imagen_";
    char foto[]="src/img/imagen_";
    
    sprintf(retorno,"%s%d.png", foto, n);

    return retorno;   
}


/*
   Entradas:        un valor 'n' de tipo entero, información respecto al ciclo de la imagen a cargar o bien, binarizar. 
   Funcionamiento:  formular el nombre correcto para cada ciclo de las imagenes a procesar para ser posible etiquetar un nombre a la imagen procesada .png de forma dinámica en conteo.
   Salidas:         un puntero tipo char.
*/
char* nombre_imagen_salida(int n){
    char* retorno=malloc(sizeof(char)*30);
    char foto[]="out_";
    sprintf(retorno,"%s%d.png", foto, n);
    
    return retorno;
}

/*
   Entradas:        un valor 'n' de tipo entero, información respecto al ciclo de la imagen a cargar o bien, binarizar. 
   Funcionamiento:  formular el nombre correcto para cada ciclo de las imagenes a imprimir por pantalla etiquetar un nombre de la imagen finalizada en proceso.
   Salidas:         un puntero tipo char.
*/
char* nombre_imagen_printf(int n){
    char* retorno=malloc(sizeof(char)*10);
    char foto[]="imagen_";
    sprintf(retorno,"%s%d", foto, n);
    
    return retorno;
}