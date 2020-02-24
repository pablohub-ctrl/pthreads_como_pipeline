#include "head.h"

/*
   Entradas:        3 valores 'a, b y c' de tipo float
   Funcionamiento:  retornar el valor más alto de los tres parámetros de entrada.
   Salidas:         un valor de tipo entero.
*/
float valormasAlto(float a, float b, float c){
    if(a>b || a==b){
        if(a>c || a==c){
            return a;
        }
        else{
            return c;
        }
    }
    else if(b>c || b==c){
                return b;
            }
    else{
        return c;
        } 

}

/*
   Entradas:  Un puntero doble de tipo float, dos enteros 'j' e 'i'.
   Funcionamiento:  mapea una porción de 3x3 de una imagen binarizada, su función es entregar el valor más alto del cuadrante 3x3
   Salidas: un valor de tipo float        
*/
float valorhighCuadrante(float** matrizrectificada, int i, int j){
    float a,b,c,d,e,f,g,h,I;
    
    if(i==0 && j==0){
    
            a=matrizrectificada[i][j+0];            
            b=matrizrectificada[i][j+1];
            c=matrizrectificada[i][j+2];
            d=matrizrectificada[i+1][j+0];
            e=matrizrectificada[i+1][j+1];
            f=matrizrectificada[i+1][j+2];
            g=matrizrectificada[i+2][j+0];
            h=matrizrectificada[i+2][j+1];
            I=matrizrectificada[i+2][j+2];
    
    }
    else if(i==0 && j!=0){
    
        j=j+(j*2);
            a=matrizrectificada[i][j+0];
            b=matrizrectificada[i][j+1];
            c=matrizrectificada[i][j+2];
            d=matrizrectificada[i+1][j+0];
            e=matrizrectificada[i+1][j+1];
            f=matrizrectificada[i+1][j+2];
            g=matrizrectificada[i+2][j+0];
            h=matrizrectificada[i+2][j+1];
            I=matrizrectificada[i+2][j+2];
    
    }


    else if(i!=0 && j==0){
        
        i=i+(2*i);
        
            a=matrizrectificada[i][j+0];
        
            b=matrizrectificada[i][j+1];
        
            c=matrizrectificada[i][j+2];
        
            d=matrizrectificada[i+1][j+0];
        
            e=matrizrectificada[i+1][j+1];
        
            f=matrizrectificada[i+1][j+2];
        
            g=matrizrectificada[i+2][j+0];
        
            h=matrizrectificada[i+2][j+1];
        
            I=matrizrectificada[i+2][j+2];
        
    }

    else{
        
        i=i+(2*i);
        j=j+(j*2);
            a=matrizrectificada[i][j+0];
            b=matrizrectificada[i][j+1];
            c=matrizrectificada[i][j+2];
            d=matrizrectificada[i+1][j+0];
            e=matrizrectificada[i+1][j+1];
            f=matrizrectificada[i+1][j+2];
            g=matrizrectificada[i+2][j+0];
            h=matrizrectificada[i+2][j+1];
            I=matrizrectificada[i+2][j+2];
    
    }

    

    float A=valormasAlto( a,  b,  c);
    
    float B=valormasAlto( d,  e,  f);
    
    float C=valormasAlto( g,  h,  I);
    
    return valormasAlto( A,  B,  C);
}

/*
   Entradas:        un puntero doble 'matrizrectificada' de tipo float, un doble puntero 'matrizpooling' de tipo float 
                    y un puntero 'dimensionPooling' de tipo entero.   
   Funcionamiento:  Crear una nueva matriz(matrizpooling) con los valores más altos por cada cuadrante de 3x3 de la matrizrectificada
   Salidas:         tipo void, modifica en espacio de memoria a matrizpooling
*/
void pooling(float** matrizrectificada, float** matrizpooling, int* dimensionPooling, int inicio, int fin){
    int j;
                for(;inicio<fin;inicio++){
                    for(j=0;j<dimensionPooling[0];j++){
                            matrizpooling[inicio][j]=valorhighCuadrante(matrizrectificada,  inicio,  j);
                    }
                }
                
}

