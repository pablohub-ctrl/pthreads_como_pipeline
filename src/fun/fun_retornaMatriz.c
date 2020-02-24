#include "head.h"
#include "estructura_png.c"


int** returnMatrizIMG(char* nombreImg){
     //se crea una estructura tipo MatrizPNG y es cargada a esta la imagen png
    MatrizPNG* matrizPng = readImage(nombreImg);
                   
    //reservo espacio en memoria para guardar las dimensiones de la imagen cargada
    int* dimensiones= (int*)malloc(sizeof(int*)*2);
    dimensiones[0]=matrizPng->width; //ancho 0
    dimensiones[1]=matrizPng->height;//alto 1

    //printf("EL ancho es: %d\n",dimensiones[0]);
    //printf("EL alto es: %d\n",dimensiones[1]);

    //se crea una variable doble puntero para albergar la dirección de la matriz o imagen png
    int** matrixPNG;
    matrixPNG = matrizPng->image;

    return matrixPNG;

}

int* returndimensionesIMG(char* nombreImg){
     //se crea una estructura tipo MatrizPNG y es cargada a esta la imagen png
    MatrizPNG* matrizPng = readImage(nombreImg);
                   
    //reservo espacio en memoria para guardar las dimensiones de la imagen cargada
    int* dimensiones= (int*)malloc(sizeof(int*)*2);
    dimensiones[0]=matrizPng->width; //ancho 0
    dimensiones[1]=matrizPng->height;//alto 1

    return dimensiones;
}

int* returndimensionesPooling(int* dimensiones){

    int* dimensionPooling=malloc(2*sizeof(int));

    dimensionPooling[0]=((dimensiones[0]-3)/3);
    dimensionPooling[1]=((dimensiones[1]-3)/3);

    return dimensionPooling;
}


void printfMAtrices(int** matriz, int* dimensiones){
    for(int i=0;i<dimensiones[1];i++){
        for(int j=0;j<dimensiones[0];j++){
            printf("%d ",matriz[i][j]);
        }
    printf("\n");
    }
}


float** reservaEspacioMatrizConvolucion(int* dimensiones){
    //reserva de espacio para el contenedor de la etapa convolucion
    float** nuevaMatriz=malloc(((dimensiones[1])-2)*(sizeof(float*)));


    for(int i=0;i<((dimensiones[1])-2);i++){
        
        nuevaMatriz[i]=malloc(((dimensiones[0])-2)*(sizeof(float*)));

    }

    return nuevaMatriz;
}



float** reservaSpaceMAtrizPooling(int* dimensiones){
    
    float** matrizpooling=malloc(((dimensiones[1])/3)*(sizeof(float*)));

    for(int i=0;i<((dimensiones[1])/3);i++){
        matrizpooling[i]=malloc(((dimensiones[0])/3)*(sizeof(float*)));
    }

    return matrizpooling;
}



void rectificar(float** MatrizConvolucion, int* dimensiones, int inicio, int fin){
    int limiteInferiorAlto=inicio;
    int limiteAlto = fin;
  //  if(inicio==0){
//        limiteInferiorAlto=limiteInferiorAlto-3;
  //  }
    if(limiteAlto==dimensiones[1]){
       limiteAlto=limiteAlto-3;
    }
    for(;limiteInferiorAlto<limiteAlto;limiteInferiorAlto++){
        for(int ancho=0;ancho<((dimensiones[0])-3);ancho++){
            if((MatrizConvolucion[limiteInferiorAlto][ancho])<0){
               MatrizConvolucion[limiteInferiorAlto][ancho]=0;
            }

        }   
    }
}    
