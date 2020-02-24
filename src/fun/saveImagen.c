
#include "head.h"



int saveImage(MatrizPNG* matrizPNG, const char *fileName) {
    FILE* filePtr;
    png_structp pngPtr = NULL;
    png_infop infoPtr = NULL;
    int i, j;
    png_byte** rowPointers = NULL;

    int pixel_size = 1;
    int depth = 8;
    
    filePtr = fopen (fileName, "wb");
    if (!filePtr) {
        fprintf(stderr, "No se encontro el archivo con nombre \"%s\".\n", fileName);
        return -1;
    }

    pngPtr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    
    if (!pngPtr) {
        fprintf(stderr, "No se pudo crear \"pngPtr\".\n");
        return -2;
    }
    
    infoPtr = png_create_info_struct (pngPtr);
    
    if (!infoPtr) {
        fprintf(stderr, "No se pudo crear \"infoPtr\".\n");
        return -3;
    }
    

    
    if (setjmp(png_jmpbuf(pngPtr))) {
        fprintf(stderr, "Error png_read_image.\n");
        return -4;
    }
    
    // Se mantienen los valores por defecto

    png_set_IHDR (pngPtr,
                  infoPtr,
                  matrizPNG->width,
                  matrizPNG->height,
                  depth,
                  PNG_COLOR_TYPE_GRAY,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);

    rowPointers = png_malloc (pngPtr, sizeof(png_byte*) * matrizPNG->height);
    for (j = 0; j < matrizPNG->height; j++) {
        png_byte *row = png_malloc (pngPtr, sizeof(u_int8_t) * matrizPNG->width * pixel_size);
        rowPointers[j] = row;
        for (i = 0; i < matrizPNG->width; i++) {
            *row++ = matrizPNG->image[j][i];
        }
    }

    png_init_io (pngPtr, filePtr);
    png_set_rows (pngPtr, infoPtr, rowPointers);
    png_write_png (pngPtr, infoPtr, PNG_TRANSFORM_IDENTITY, NULL);

    for (j = 0; j < matrizPNG->height; j++) {
        png_free (pngPtr, rowPointers[j]);
    }
    png_free (pngPtr, rowPointers);

    fclose(filePtr);

    return 0;
}
