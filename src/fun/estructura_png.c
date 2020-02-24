#include "head.h"


typedef struct matrizPNG{
	int height;
	int width;
	int** image;	
} MatrizPNG;

//Entrada: fileName <tipo: char*> (nombre del archivo a leer)
//Lee una imagen .png 
MatrizPNG* readImage(char* fileName) {

    png_structp	pngPtr;
    png_infop infoPtr;
    FILE* filePtr;
    png_uint_32 width;
    png_uint_32 height;
    int bitDepth;
    int colorType;
    int interlaceMethod;
    int compressionMethod;
    int filterMethod;
    int i, j;
    png_bytepp rows;
	

	
    filePtr = fopen (fileName, "rb");
    if (!filePtr) {
		fprintf(stderr, "No pudo leer el archivo; %s .\n", fileName);
		return NULL;
	}

    // Creando punteros necesarios para el uso de libpng

	pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!pngPtr) {
		fprintf(stderr, "No se pudo crear \"pngPtr\".\n");
		return NULL;
	}

	infoPtr = png_create_info_struct(pngPtr);

	if (!infoPtr) {
		fprintf(stderr, "No se pudo crear \"infoPtr\".\n");
		return NULL;
	}

	if (setjmp(png_jmpbuf(pngPtr))) {
		fprintf(stderr, "Error durante png_init_io.\n");
		return NULL;
	}

    png_init_io (pngPtr, filePtr);
    png_read_png (pngPtr, infoPtr, 0, 0);
    png_get_IHDR (pngPtr, infoPtr, & width, & height, & bitDepth,
		  & colorType, & interlaceMethod, & compressionMethod,
		  & filterMethod);

    // Iniciando lectura de pixeles

	// Si existe un problema con el archivo posterior a su metadata
	if (setjmp(png_jmpbuf(pngPtr))) {
		fprintf(stderr, "Error durante png_read_image.\n");
		return NULL;
	}

    rows = png_get_rows (pngPtr, infoPtr);
    int rowbytes;
    rowbytes = png_get_rowbytes (pngPtr, infoPtr);

    MatrizPNG* matrizPNG;
    matrizPNG = (MatrizPNG*) malloc(sizeof(MatrizPNG));
	matrizPNG->height = height;
	matrizPNG->width = width;
	matrizPNG->image = (int**) malloc(sizeof(int*) * matrizPNG->height);

	for (i = 0; i < matrizPNG->height; i++) {
		matrizPNG->image[i] = (int*) malloc(sizeof(int) * matrizPNG->width);
	}

    for (j = 0; j < height; j++) {
		png_bytep row;
		row = rows[j];
		if (rowbytes > width) {
			int multiplier = rowbytes/width;
			for (i = 0; i < width; i++) {
			    matrizPNG->image[j][i] = row[i*multiplier];
			}
		}

		else {
			int accumulated = 0;
			for (i = 0; i < rowbytes; i++) {
				int k = width/rowbytes;
				while (k > 0) {
					matrizPNG->image[j][i + accumulated] = row[i];
					accumulated++;
					k--;
				}
				accumulated--;
			}
		}
    }

    if (pngPtr && infoPtr) {
		png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
		pngPtr = NULL;
		infoPtr = NULL;
	}

    fclose(filePtr);

    return matrizPNG;
}
