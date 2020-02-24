#include "head.h"

/*
   Entradas:        un puntero doble 'matriz' de tipo float. Un putero 'dimensiones' de tipo entero.
   Funcionamiento:  Encuentra el valor del umbral de oscuridad de la imagen.
   Salidas:         un valor de tipo float: 'umbral'.
*/
int clasificacion(float** matriz, int* dimensiones,int inicio, int fin){

        
        int black=0;

        for(;inicio<fin;inicio++){
            for(int j=0;j<dimensiones[0];j++){
                //por cada elemento de la mtriz pooling se evalua en si es igual a 0.
                //si el elemento es igual a cero, incremente el valor de la variable black
             //   printf("El valor de inicio es:%d y de fin es:%d ANCHO %d\n",inicio,fin,j);
               // printf("Y las dimensiones son Alto:%d y Ancho:%d\n",dimensiones[1],dimensiones[0]);
                if(matriz[inicio][j]==0){
                    black=black+1;
                }
            }
        }
        // valor umbral corresponde a la división de 'black' dividido por el área de la matriz poolinizada
        //float umbral=(float)black/((float)anchoxalto);
        
        return black;
}

float umbralDato(int black, int* dimensiones){
    int ancho=dimensiones[0];
    int alto=dimensiones[1];
    float anchoxalto=ancho*alto;
    float blackcasteado= black;
    //printf("El valor black es: %f\n",blackcasteado);
    //printf("El valor alto x ancho es %f\n",anchoxalto);
    //float umbral=(float)black/anchoxalto;
    float umbral=blackcasteado/anchoxalto;
    return umbral*100;
}



/*
   Entradas:        un valor 'n' de tipo float, un valor 'umbral' de tipo float y un valor 'porcentaje' de tipo entero. 
   Funcionamiento:  verifica si una imagen es nearly black mediante un 1 o 0, 1==true y 0==false.
   Salidas:         un valor de tipo entero.
*/
int clasifica(int n, float umbral){

    //int x= (100*umbral)/n;
    //x=x-100;
    
    //if(x>=porcentaje){
    if(umbral>=n){
        return 1;
    }else{
            return 0;
        }
}

