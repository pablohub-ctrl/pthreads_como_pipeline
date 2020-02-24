#include<stdio.h>
#include<stdlib.h>


typedef struct pila{
    int Nfila;
    int* filaBuff;
    struct pila *siguiente;
    
}pila;

void liberarStructura(pila* estructura){
    free(estructura->filaBuff);
    free(estructura);
}

pila* crear(int fila, int* filaBuffer){
        pila *p=(pila*)malloc(sizeof(pila));
        
        if(p==NULL){
            printf("No fue posible asignar memoria a la pila\n");
            return NULL;
        }
        p->Nfila=fila;
        p->filaBuff=filaBuffer;
        p->siguiente=NULL;
        
    
    return p;
}

pila* trasladarUltimoNodo(pila* nodo){
    pila* clon=nodo;
    
    while(clon->siguiente != NULL){
        clon = clon->siguiente;
    }
    
    return clon;
}

pila* agregaNodoaPila(pila* grupo, pila* nueva){
    pila* clon=trasladarUltimoNodo(grupo);

    clon -> siguiente = nueva;
    
    return grupo;

}

pila* deleteFirstNodo(pila* buffer){
        pila *clon;

        clon=buffer;

        if(buffer == NULL){
            return NULL;
        }
        else if(clon->siguiente==NULL){

            return NULL;
        }
        else{
            clon = clon->siguiente;
            return clon;
        }        
}

pila* pop(pila* buffer){

        pila* clon;
        clon = buffer;
        if(buffer==NULL){
            return NULL;
        }
        else if(clon->siguiente==NULL){
            return clon;
        }
        else{
            //clon->siguiente=NULL;
            return clon;
        }
}


pila* push(pila* grupo, int fila, int* arreglo){
    pila* clon;
    if(grupo==NULL){
        clon=crear(fila, arreglo);
        return clon;
    }
    else{
        clon=crear(fila, arreglo);
        agregaNodoaPila(grupo, clon);
        return grupo;
    }
}


int* selectArreglo(pila* nodo){
    int* arreglo = nodo->filaBuff;
    free(nodo);
    return arreglo;
}

