#include "head.h"

int* getFilaMatriz(int** matriz, int ancho, int fila){
    int* tamanoSize = (int*)malloc(ancho*sizeof(int));
    //int* tamanoSize;
    for(int i=0; i<ancho; i++){
        tamanoSize[i]=matriz[fila][i];
    }
    return tamanoSize;
}

int** matrizConvuluciandada(int* dimensiones){
    int** matriz=(int**)malloc(dimensiones[1]*sizeof(int *));
    for(int i=0;i<dimensiones[1];i++){
        matriz[i]=(int*)malloc(dimensiones[0]*sizeof(int *));
    }

    return matriz;
}

float** matrizConvuluciandadaRealy(int* dimensiones){
    float** matriz=(float**)malloc((dimensiones[1]-3)*sizeof(float *));
    for(int i=0;i<(dimensiones[1]-3);i++){
        matriz[i]=(float*)malloc((dimensiones[0]-3)*sizeof(float *));
    }
    
    return matriz;
}
float** matrizPoolingRealy(int* dimensiones){
    float** matriz=(float**)malloc((dimensiones[1])*sizeof(float *));
    for(int i=0;i<(dimensiones[1]);i++){
        matriz[i]=(float*)malloc((dimensiones[0])*sizeof(float *));
    }
    
    return matriz;
}