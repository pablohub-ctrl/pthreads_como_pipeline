#include "src/fun/head.h"
#include "src/fun/fun_retornaMatriz.c"
#include "src/fun/pasabajo.c"
#include "src/fun/convolucion.c"
#include "src/fun/newStruct.c"
#include "src/fun/arregloFila.c"
#include "src/fun/crearnombre.c"
#include "src/fun/pooling.c"
#include "src/fun/clasificacion.c"
#include "src/fun/saveImagen.c"



//Estructura de datos necesaria para cada hebra 
typedef struct str_limite{
    int tid;	//Identifica el id del thread
    int init;	//Posición inicial del vector
    int end;	//Posición final del vector
    pthread_mutex_t *mutexArray;
}limite;


//pthread_mutex_t mutexs, mutex2;
pthread_mutex_t mutex2;
pthread_mutex_t mutex3;
pthread_mutex_t mutexs3;

pthread_mutex_t bufferFULL, bufferEmpty;
pthread_cond_t finish, start, finish2;
pthread_cond_t FULL, EMPTY;
pthread_barrier_t barrier;
pthread_barrier_t barrier2;


//pthread_mutex_t mutexs[nthreads];
pthread_mutex_t *mutexs;
pthread_mutex_t *mutexsClasificacion;
//int nthreads = 12;
int** matrixPNG;
int** matrixPNG2;
int** matrixPNGpipe=NULL;
int* sumaBlackForHILO;

int* dimensiones;
int* dimensionPooling;
char* m;
int buff=0;
int h=0;
int black=0;
float umbral;
int thi;
int** pasabajo;
pila* buffer=NULL;
int c=0;
float** MatrizConvolucion;
float** matrizpooling;
float porcentaje=0;
int n=0;
int opt;
int b;
//void thread_fun(void *arg)

//// PRODUCTOR
void thread_fun(void *arg)
{
    int l=1;
    buff=0;
    
    //int i = (__intptr_t)arg;
    while(l<c+1){

    //printf("paso por el while N:%d\n",l);
    buffer=NULL;
    buff=0;
    umbral=0;
    black=0;
    int starti=0;
  
    matrixPNG=returnMatrizIMG(nombre_imagen(l));
    dimensiones=returndimensionesIMG(nombre_imagen(l));

    
    MatrizConvolucion = matrizConvuluciandadaRealy(dimensiones);
    
    dimensionPooling=returndimensionesPooling(dimensiones);
    
    matrizpooling= matrizPoolingRealy(dimensionPooling);
             
    pasabajo=leerFichero(m);     //es cargada la matriz
    
    for(int j=0; j<dimensiones[1]; j++){

            if(buff<thi){
                buffer=push(buffer,j,getFilaMatriz(matrixPNG, dimensiones[0],  j));
                buff=buff+1;
            }
            else{
                if(starti==0){
                //SEÑAL A LOS HILOS CONSUMIDORES A CONTINUAR CON EL CONSUMO POR PRIMERA VEZ
                pthread_cond_broadcast(&start);
                //ESPERA UNA SEÑAL A QUE EL BUFFER SE VACIE POR PARTE DE LOS HILOS CONSUMIDORES PARA CONTINUAR CON LA PRODUCCIÓN DE FILAS A CONSUMIR
                pthread_cond_wait(&FULL, &bufferFULL);
                starti=starti+1;
                j=j-1;
                }
                else{
                    //ENVÍA UNA SEÑAL A LAS HEBRAS CONSUMIDORAS A QUE EL BUFFER SE ENCUENTRA LLENO Y LISTO A SER CONSUMIDO
                    pthread_cond_signal(&EMPTY);
                    //ESPERA UNA SEÑAL A QUE EL BUFFER SE VACIE POR PARTE DE LOS HILOS CONSUMIDORES PARA CONTINUAR CON LA PRODUCCIÓN DE FILAS A CONSUMIR
                    pthread_cond_wait(&FULL, &bufferFULL);
                    j=j-1;               
                }
            }
    }
    //ENVÍA UNA SEÑAL A LAS HEBRAS CONSUMIDORAS A QUE EL BUFFER SE ENCUENTRA LLENO Y LISTO A SER CONSUMIDO 
    //ESTO PARA LAS ÚLTIMAS FILAS DE LA IMAGEN QUE DEBEN SER CONSUMIDAS
    pthread_cond_signal(&EMPTY);
 



    //CARGA LA VARIABLE GLOBAL EN +1 PARA CARGAR LA SIGUIENTE IMAGEN
    l = l + 1;    
    
    if(l==7){
        //ESPERA A QUE LAS HEBRAS CONSUMIDORAS TERMINEN SU PIPELINE PARA CARGAR LA SIGUIENTE IMAGEN
        pthread_cond_wait(&finish2,&mutex3);    
    }
    else{
        //ESPERA A QUE LAS HEBRAS CONSUMIDORAS TERMINEN SU PIPELINE PARA CARGAR LA SIGUIENTE IMAGEN
        pthread_cond_wait(&finish,&mutex2);
    }
    

  }//while

    
    printf("Padre ha terminado\n");
}  




// CONSUMIDOR
void recorreHilos(void *arg)
{
    int img=1;
    limite *hilo = (limite *) arg;	
    
    while(img<c+1){
    
    int p=1;
    
    //ESPERA A QUE LA HEBRA PRODUCTORA CARGUE LOS PARAMETROS NECESARIOS DE LA IMAGEN A PROCESAR
    pthread_cond_wait(&start,hilo->mutexArray);
    
    if(hilo->tid==0){
       matrixPNGpipe=matrizConvuluciandada(dimensiones);
    }
    
        hilo->init = hilo->tid*(dimensiones[1]/h);
        hilo->end = (hilo->tid+1)*(dimensiones[1]/h);
        

    
    int mm = (dimensiones[1]/h);
    if((h-1)==hilo->tid){
        float nopar=(dimensiones[1]/h);
       
        if(nopar>mm){
            mm=mm+1;
        }
        
    }
    //PERMITE QUE ACCEDA EL HILO 0 EN PRIMER LUGAR Y LOS DEMÁS SE BLOQUEEN
    pthread_mutex_lock(&mutexs[hilo->tid]);
    
    
    while(p<mm){
    

        if(buff>0 || buffer!=NULL){
                pila* dos;
                dos=pop(buffer);
    
                matrixPNGpipe[dos->Nfila]=dos->filaBuff;
                buffer=deleteFirstNodo(buffer);
                
                free(dos);

                p=p+1;
                
                buff=buff-1;
    
                
                if(h == hilo->tid+1){
                    if(p==mm){
                        //CASO BORDE CUANDO HILO ÚLTIMO TERMINA SU CANTIDAD DE FILAS A CONSUMIR
                        //PERMITE EL PASO AL SIGUIENTE HILO PARA CONSUMIR DEL BUFFER EN ESTE CASO EL PRIMER HILO 0
                        pthread_mutex_unlock(&mutexs[0]);
                    }
                    else{
                        //PERMITE EL PASO AL SIGUIENTE HILO PARA CONSUMIR DEL BUFFER
                        pthread_mutex_unlock(&mutexs[0]);
                        //EL HILO RESPECTIVO SE BLOUEA
                        pthread_mutex_lock(&mutexs[hilo->tid]);
                    }
                    
                }
                else{
                    
                    if(p==mm){
                        //CASO BORDE PARA EL HILO POR HABER CONSUMIDO LA TOTALIDAD, DONDE DESBLOQUEA EL HILO SIGUIENTE PARA CONSUMIR DEL BUFFER
                        pthread_mutex_unlock(&mutexs[hilo->tid+1]);    
                    }
                    else{
                        //CASO BORDE PARA EL HILO DONDE DESBLOQUEA EL HILO SIGUIENTE PARA CONSUMIR DEL BUFFER
                        pthread_mutex_unlock(&mutexs[hilo->tid+1]);
                        //EL HILO RESPECTIVO SE BLOQUEA
                        pthread_mutex_lock(&mutexs[hilo->tid]);
                    }
                    
                }
                        
        }
        else{
            //EL BUFFER SE ENCUENTRA VACIO
            //ACTIVA LA SEÑAL PARA CONTINUAR CON EL LLENADO DEL BUFFER
            pthread_cond_signal(&FULL);
            //ESPERA A QUE CUANDO LA HEBRA PRODUCTORA TERMINE DE LLENAR EL BUFFER ÉSTA ENVIARÁ LA SEÑAL PARA CONTINUAR SU CONSUMO.
            pthread_cond_wait(&EMPTY, &bufferEmpty);
            
        }

        
        
    }   

    //ESPERA A QUE LOS HILOS TERMINEN DE CONSUMIR SUS RESPECTIVAS FILAS 
    pthread_barrier_wait(&barrier);  
        
    //PARAMETROS DE TRABAJO EN LOS SEGMENTOS RESPECTIVO A TRABAJAR CADA HILO EN FILAS CORRESPONDIENTES    
    int inicio = hilo->init;
    int fin = hilo->end;
 
    convolucion(matrixPNG, inicio,fin ,dimensiones, MatrizConvolucion, pasabajo);  /*PASO 2 - CONVOLUCIÓN*/ 
        
        
    pthread_barrier_wait(&barrier);      
  
    
    rectificar(MatrizConvolucion, dimensiones, inicio, fin);  /*PASO 3 - NORMALIZAR/RECTIFICAR*/
        
    
        
    pthread_barrier_wait(&barrier);      

    /*PASO 4 - POOLING*/

    inicio= hilo->init/3;
    fin= hilo->end/3;
    

    if(hilo->tid==h-1){
        pooling(MatrizConvolucion, matrizpooling, dimensionPooling, inicio, dimensionPooling[1]);   
    }
    else{
        pooling(MatrizConvolucion, matrizpooling, dimensionPooling, inicio, fin);   
    }

    pthread_barrier_wait(&barrier);      
        
    
    /*PASO 5 - Clasificación*/
    //
    //VA SUMANDO LOS NEGROS DE CADA PIXEL CORRESPONDIENTE A LAS FILAS QUE LE CORRESPONDE A CADA HILO
    if(hilo->tid==h-1){
        sumaBlackForHILO[hilo->tid]=clasificacion(matrizpooling, dimensionPooling,inicio, dimensionPooling[1]); 
    }
    else{
        sumaBlackForHILO[hilo->tid]=clasificacion(matrizpooling, dimensionPooling,inicio, fin);
    }
    
    pthread_barrier_wait(&barrier);      
    
    //CONDICIÓN DE CARRERA SINCRONIZANDO EL ACCESO PRIMERO PASA EL HILO 0 
    pthread_mutex_lock(&mutexsClasificacion[hilo->tid]);
    //SECCIÓN CRÍTICA
    black= black + sumaBlackForHILO[hilo->tid];

    //EL ÚLTIMO HILO EJECUTA LA ESCRITURA Y LOS PARAMETROS POR PANTALLA EN CASO DE QUE ESTO ÚLTIMO SEA ESPRESADO POR EL FLAG -b
    if(hilo->tid==h-1){
            if(b==1){
            //DESBLOQUEA EL ÚLTIMO HILO PARA TERMINAR CON EL CICLO DE LA IMAGEN
            pthread_mutex_unlock(&mutexsClasificacion[0]);

            umbral=umbralDato(black, dimensionPooling);

            int** ultima_matriz=malloc((dimensionPooling[1])*(sizeof(int*)));  

            for(int i=0;i<dimensionPooling[1];i++){
                ultima_matriz[i]=malloc((dimensionPooling[0])*(sizeof(int*)));
            }
            
            for(int i=0;i<dimensionPooling[1];i++){
                for(int j=0;j<dimensionPooling[0];j++){
                    ultima_matriz[i][j] = matrizpooling[i][j];
                }
            }
            
            MatrizPNG* matrizPNG2;
            matrizPNG2 = (MatrizPNG*) malloc(sizeof(MatrizPNG));
            matrizPNG2->width = dimensionPooling[0];
            matrizPNG2->height = dimensionPooling[1];
            matrizPNG2->image = ultima_matriz;
            char* nombre = nombre_imagen_salida(img);
            
            //Se escribe la imagen en disco
            saveImage(matrizPNG2, nombre); 
            
                    char* nombrePrint=nombre_imagen_printf(img);    
                    
                    char* nearlyBlack=NULL;
                    if(clasifica(n, umbral)== 1){
                        nearlyBlack="yes";
                    }else{
                        nearlyBlack="no";
                    }
               
                    if(b==1){
                    printf("|\t%s\t|\t  %s\t      |\n",nombrePrint,nearlyBlack);    
                    }

            }
            else{
                    //DESBLOQUEA EL ÚLTIMO HILO PARA TERMINAR CON EL CICLO DE LA IMAGEN
                    pthread_mutex_unlock(&mutexsClasificacion[0]);
                    int** ultima_matriz=malloc((dimensionPooling[1])*(sizeof(int*)));  
                    //se asigna espacio en memoria
                    for(int i=0;i<dimensionPooling[1];i++){
                        ultima_matriz[i]=malloc((dimensionPooling[0])*(sizeof(int*)));
                    }
                    
                    for(int i=0;i<dimensionPooling[1];i++){
                        for(int j=0;j<dimensionPooling[0];j++){
                            ultima_matriz[i][j] = matrizpooling[i][j];
                        }
                    }
                    
                    MatrizPNG* matrizPNG2;
                    matrizPNG2 = (MatrizPNG*) malloc(sizeof(MatrizPNG));
                    matrizPNG2->width = dimensionPooling[0];
                    matrizPNG2->height = dimensionPooling[1];
                    matrizPNG2->image = ultima_matriz;
                    char* nombre = nombre_imagen_salida(img);
                    
                    saveImage(matrizPNG2, nombre); 
            }
      





    }
    else{
        //PERMITE EL PASO AL SIGUIENTE HILO PARA HACER LA SUMA DE NEGROS EN LA SECCIÓN CRÍTICA
        pthread_mutex_unlock(&mutexsClasificacion[hilo->tid+1]);
    }

    pthread_barrier_wait(&barrier);      

    img = img + 1; 

    if(hilo->tid==h-1){
        if(img==7){
        //LE DICE A LA HEBRA PRODUCTORA CONTINUAR CON LA SIGUIENTE IMAGEN
        pthread_cond_signal(&finish2);    
        }
        else{
        //LE DICE A LA HEBRA PRODUCTORA CONTINUAR CON LA SIGUIENTE IMAGEN
        pthread_cond_signal(&finish);
        }
    }   
}
    
  //  printf("listo tid: %d\n",hilo->tid);
} 

int main(int argc, char *argv[]){



while((opt=getopt(argc, argv, "c:m:n:h:t:b"))!= -1){
       switch (opt){
            case 'c':
                        c=atoi(optarg);
                        if(c<=0){
                            printf("Cantidad de las imagenes no pueden ser menor o igual a cero\n");
                            return 0;
                        }
                        c=atoi(optarg);
                        break;
            case 'm':
                        m= optarg;
                        int largoNombre;
                        largoNombre=strlen(m);
                        //printf("El largo de nombre: %d\n",largoNombre);
                        if(largoNombre<6){
                            printf("Nombre de longitud incorrecta\n");
                            return 0;
                        }
                        char t=m[largoNombre-1];
                        char x=m[largoNombre-2];
                        char t1=m[largoNombre-3];
                        char punto=m[largoNombre-4];
                        if(punto!='.' || t!='t' || x!='x' || t1!='t'){
                            printf("El achivo debe ser de extensión .txt\n");
                            return 0;                          
                        }
                        
                        break;
            case 'n':
                        n=atoi(optarg);
                        if(n>=1 && n<=100){
                             //printf("el valor de n es: %f\n",n);
                            n=atoi(optarg);
                            break;
                        }
                        else{
                            printf("%d\n",n);
                            printf("Valor incorrecto para umbral\n");
                            return 0;
                        }
            case 'h':
                        h=atoi(optarg);
                        if(h>=3 && h<20){  //tengo que permitir que sólo una hebra cubra todo lo solicitado
                            
                            h=atoi(optarg);
                            break;
                        }
                        else{
                            printf("%d\n",h);
                            printf("los valores de las hebras  han de ser entre 2 o hasta  20\n");
                            return 0;
                        }
            case 't':
                        thi=atoi(optarg);
                        if(thi>=2 && thi<80){  //tengo que permitir que sólo una hebra cubra todo lo solicitado
                            
                            thi=atoi(optarg);
                            break;
                        }
                        else{
                            printf("%d",thi);
                            printf("los valores para el tamano del buffer han de ser entre 2 o hasta  80\n");
                            return 0;
                        }
            case 'b':
                        b=1;
                        break;       
            case '?':
                    printf("Valor no reconocico\n");
                    printf("El formato a ingresar es: main.c -c N_imagenes -m filtro.txt -n umbral -p porciento_clasificacion -b\n");
                    return 0;
                        
       }
   }


//tengo que quitar el porcentaje de clasificación NO VA EN ESTE LAB. MODIFICAR O SIMPLIFICAR LA FUNCIÓN
if(b==1){
    printf("|  \timagen\t\t|\tnearly black\t|\n");
    printf("|-----------------------|-----------------------|\n");
}


//printf("desconozco que T:%d\n",thi);
mutexs = (pthread_mutex_t *)malloc(h*sizeof(pthread_mutex_t));
mutexsClasificacion = (pthread_mutex_t *)malloc(h*sizeof(pthread_mutex_t));

pthread_mutex_init(&mutex2, NULL);
pthread_mutex_init(&mutex3, NULL);
pthread_mutex_init(&bufferEmpty, NULL);
pthread_mutex_init(&bufferFULL, NULL);
pthread_cond_init(&finish,NULL);
pthread_cond_init(&start, NULL);
pthread_cond_init(&EMPTY, NULL);
pthread_cond_init(&FULL, NULL);
pthread_cond_init(&finish2,NULL);
pthread_barrier_init(&barrier,NULL,h);
pthread_barrier_init(&barrier2,NULL,h);


pthread_t* threads = (pthread_t*) malloc(h*sizeof(pthread_t));	//Se crea un arreglo de pthread, necesario para crear los thread    

limite * array = (limite*)malloc(sizeof(limite)*h);		//Vector de estructuras de datos necesaria para la creacion de los thread

sumaBlackForHILO = (int*)malloc(h*(sizeof(int)));
for(int i=0;i<h;i++){
    sumaBlackForHILO[i]=0;
}

pthread_t tid;
//pthread_create(&tid, NULL, (void*)thread_fun, (void *)(__intptr_t)(i));


for(int i=0; i< h; i++){
    //printf("el valor de t es:%d\n",t);
        array[i].tid = i;			
      
        array[i].mutexArray = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    
    
        pthread_mutex_init(array[i].mutexArray, NULL);
}

for(int i = 0; i < h; i++){
    
        pthread_mutex_init(&mutexs[i], NULL);
    
        if(i!=0)
        pthread_mutex_lock(&mutexs[i]);
    }

for(int i = 0; i < h; i++){
    
        pthread_mutex_init(&mutexsClasificacion[i], NULL);
    
        if(i!=0)
        pthread_mutex_lock(&mutexsClasificacion[i]);
}
    


pthread_mutex_init(&mutexs3, NULL);

for(int i=0;i<h;i++){
    pthread_create(&(threads[i]), NULL, (void *)recorreHilos,(void*) &(array[i]));
    
}



pthread_create(&tid, NULL, (void*)thread_fun, NULL);


for(int i=0;i<h;i++){
    
    pthread_join(threads[i], NULL);
    //printf("ha finalizado el %d\n",i);
}

pthread_cancel(tid);
pthread_join(tid, NULL);

pthread_barrier_destroy(&barrier);

}