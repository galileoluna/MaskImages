#include <stdio.h>
#include <stdlib.h>
#include "imagen.h"

void enmascarar_c(Byte*, Byte*, Byte*, int);

/* Recibe 3 argumentos del usuario desde la línea de comandos:
   arg1: imagen1
   arg2: imagen2
   arg3: mascara
*/
int main( int argc, char *argv[] ) {
  if( argc != 4 ) {
    fprintf(stderr, "Cantidad de argumentos incorrecta.\n");
    exit(1);
  }

  FILE *imagen1;
  FILE *imagen2;
  FILE *mascara;
  
  imagen1 = fopen(argv[1], LECTURA);
  imagen2 = fopen(argv[2], LECTURA);
  mascara = fopen(argv[3], LECTURA);
  
  if( imagen1 == NULL ) {
    fprintf(stderr, "Imagen 1 no encontrada.\n");
    exit(1);
  }

  if( imagen2 == NULL ) {
    fprintf(stderr, "Imagen 2 no encontrada.\n");
    exit(1);
  }

  if( mascara == NULL ) {
    fprintf(stderr, "Máscara no encontrada.\n");
    exit(1);
  }

  fseek(imagen1, 0, SEEK_END);
  long int size = ftell(imagen1);
  fseek(imagen1, 0, SEEK_SET);

  /* TODO: verificar que todas las imágenes sean del mismo tamaño */

  Byte buff_imagen1[size];
  Byte buff_imagen2[size];
  Byte buff_mascara[size];
  
  size_t total = fread(buff_imagen1, 1, size, imagen1);
  fclose(imagen1);

  size_t totalI2 = fread(buff_imagen2, 1, size, imagen2);
  fclose(imagen2);

  size_t totalMascara = fread(buff_mascara, 1, size, mascara);
  fclose(mascara);

  /* TODO: medir tiempo que tarda la siguiente función en ejecutarse */
  enmascarar_c(buff_imagen1, buff_imagen2, buff_mascara, (int) size);

  /* Acá estaría el llamado a la otra función:
  enmascarar_asm(buff_imagen1, buff_imagen2, buff_mascara, (int) size);
  */

  // tamaño, tiempo_c, tiempo_asm
  fprintf(stdout, "%d, %d, %d\n", size, 0, 0);

}
