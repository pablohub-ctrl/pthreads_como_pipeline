Renderizar imágenes astronómicas de formato png para obtener por medio de los parámetros ingresados si dicha imágenes son nearly-black o no.

[IMPORTANTE!!]
PRIMERO ES REQUERIDO INSTALAR EN EL SISTEMA LO SIGUIENTE:   "sudo apt-get install libpng-dev pkg-config"

Función:

La función del programa se describe en el proyecto "uso_de_fork_comunicacion_bidireccional_de_procesos_por_pipeline"

Pthreads es propio de la Api de Linux y el programa trabaja con el uso de Hilos, Mutex y barreras.
Los Flag como parámetros de entradas se describen como:

-c: cantidad de imágenes.
-m: Máscara del filtro que se le aplicará a la imagen en la fase de convolución. Consiste en un archivo .txt
-n: UMBRAL para clasificación, se recibe como un entero.
-b: bandera que indica si se deben mostrar los resultados por pantalla, es decir, la conclusión obtenida al leer la imagen binarizada.
-h: cantidad de hebras que ejecutarán cada etapa del pipeline, por lo tanto, si se ingresa un número 10, se deben crear 10 hebras para ejecutar el pipeline además de una hebra productora que solo lea y "produzca" las imágenes de entrada.
-t: Tamaño del buffer para la lectura de las imágenes de entrada.


*Los resultados son guardados en la carpeta principal donde reside el Makefile.

*en la terminal del repositorio al llamar el Makefile con escribir "make" es suficiente para el funcionamiento del programa por completo.

-para limpiar existe el comando "make clean"











