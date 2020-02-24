#include "head.h"

/*
   Entradas:        un entero 'ancho', un entero 'alto'; de 'matriz'.
                    doble puntero de tipo entero 'matriz', doble puntero 'nuevaMatriz' de tipo float.
                    doble puntero de tipo entero 'pasabajo'.

   Funcionamiento:  -multiplica los elemento de una matriz 3x3 con los elementos 3x3 del pasabajo.
                    -evalua si uno de los elementos son igual o menor a cero de la matriz o el pasabajo.
                    -el resultado de la multiplicación o cuyo caso elementos iguales a cero son:
                        --guardados en una variable correspondiente a su espacio matricial de 3x3 |a,b,c| |d,e,f| |g,h,i|.
                    *su función principal es guardar en nuevaMatriz  los valores de operación convolución. siendo de los elementos de la 'matriz' y
                    'pasabjo' o bien aplicado el filtro correspondiente.

   Salidas:         Tipo float de valor modificado para la nuevaMatriz con fin de comprobación.
                    Función principal es ejecutada a nivel de memoria, podria perfectamente funcionar como tipo void.    
*/
float pixelmodificado(int ancho, int alto, int** matriz, float** nuevaMatriz, int** pasabajo){
    int a,b,c,d,e,f,g,h,i;
    int n=-1;
    int m=-1;
    float valor;

    //matriz 0,0
    if((matriz[alto-1][ancho-1])<=0 || (pasabajo[0][0])==0){
        a=0;
    }else{
            a=((matriz[alto-1][ancho-1])*(pasabajo[0][0]));
        }
    
    //matriz 0,1
    if((matriz[alto-1][ancho])<=0 || (pasabajo[0][1])==0){
        b=0;
    }else{
            a=((matriz[alto-1][ancho])*(pasabajo[0][1]));
    }

    //matriz 0,2
    if((matriz[alto-1][ancho+1])<=0 || (pasabajo[0][2])==0){
        c=0;
    }else{
        c=((matriz[alto-1][ancho+1])*(pasabajo[0][2]));
    }

    //matriz 1,0
    if((matriz[alto][ancho-1])<=0 || (pasabajo[1][0])==0){
        d=0;
    }else{
            d=((matriz[alto][ancho-1])*(pasabajo[1][0]));
    }

    //matriz 1,1
    if((matriz[alto][ancho])<=0 || (pasabajo[1][1])==0){
        e=0;
    }else{
            e=((matriz[alto][ancho])*(pasabajo[1][1]));
    }

    //matriz 1,2
    if((matriz[alto][ancho+1])<=0 || (pasabajo[1][2])==0){
        f=0;
    }else{
            f=((matriz[alto][ancho+1])*(pasabajo[1][2]));
    }

    //matriz 2,0
    if((matriz[alto+1][ancho-1])<=0 || (pasabajo[2][0])==0){
        g=0;
    }else{
            g=((matriz[alto+1][ancho-1])*(pasabajo[2][0]));
    }

    //matriz 2,1
    if((matriz[alto+1][ancho])<=0 || (pasabajo[2][1])==0){
        h=0;
    }else{
            h=((matriz[alto+1][ancho])*(pasabajo[2][1]));
    }

    //matriz 2,2
    if((matriz[alto+1][ancho+1])<=0 || (pasabajo[2][2])==0){
        i=0;
    }else{
            i=((matriz[alto+1][ancho+1])*(pasabajo[2][2]));
    }


    valor=(a+b+c+d+e+f+g+h+i);
    valor=valor/9;
    nuevaMatriz[alto+n][ancho+m]=valor;
        
    
    return (nuevaMatriz[alto+n][ancho+m]);
}

/*
    Entradas:       doble puntero 'matriz' de tipo entero; contiene la imagen binarizada. 
                    doble puntero 'nuevaMatriz' de tipo float; donde será modificada por el resultante de la convolución.
                    doble puntero 'pasabajo' de tipo entero; matriz de 3x3 que será aplicado como filtro.
                    puntero 'anchoxalto' de tipo entero; contiene las dimensiones de puntero doble 'matriz'

    Funcionamiento: modifica la nuevaMatriz a partir del resultado de aplicar la 
                    convolución; resultado de la multiplicación de los elementos de igual posición matricial del pasabajo y matriz.

    Salidas:        retorna un entero, más bien un valor 0 para pruebas. no es requerido un retorno.
                    Las operaciones requeridas son efectuadas en memoria, especificamente a 'nuevaMatriz'.
*/
int convolucion(int** matriz,int limiteINFAlto,int alto ,int* anchoxalto, float** nuevaMatriz, int** pasabajo){
    int limiteInferiorAlto=limiteINFAlto;
    int limiteAlto = alto;
    if(limiteINFAlto==0){
    limiteInferiorAlto=1;
    }
    if(limiteAlto==anchoxalto[1]){
       limiteAlto=limiteAlto-2;
    }
    
        
    for(;limiteInferiorAlto<limiteAlto;limiteInferiorAlto++){
        for(int ancho=1;ancho<((anchoxalto[0])-2);ancho++){
            pixelmodificado( ancho,  limiteInferiorAlto, matriz, nuevaMatriz, pasabajo);
        //printf("[ancho %d alto %d] \n", ancho, limiteInferiorAlto);
        //printf("%f\n", ok);
        }
    }

    return 0;
}




