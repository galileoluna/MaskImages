#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "imagen.h"

void enmascarar_c(Byte*, Byte*, Byte*, int);

static clock_t inicio_c, fin_c, inicio_asm, fin_asm;
static double total_c = 0, total_asm = 0;

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

  long int imagen1_size = fsize(imagen1);
  long int imagen2_size = fsize(imagen2);
  long int mascara_size = fsize(mascara);
  if( imagen1_size != imagen2_size | imagen1_size != mascara_size ) {
    fprintf(stderr, "Las imágenes no tienen el mismo tamaño.\n");
    exit(1);
  }

  Byte buff_imagen1[imagen1_size];
  Byte buff_imagen2[imagen1_size];
  Byte buff_mascara[imagen1_size];
  
  fread(buff_imagen1, 1, imagen1_size, imagen1);
  fclose(imagen1);

  fread(buff_imagen2, 1, imagen1_size, imagen2);
  fclose(imagen2);

  fread(buff_mascara, 1, imagen1_size, mascara);
  fclose(mascara);


  inicio_c = clock();
  enmascarar_c(buff_imagen1, buff_imagen2, buff_mascara, (int) imagen1_size);
  fin_c = clock();
  total_c = (double) (fin_c - inicio_c) / CLOCKS_PER_SEC;

  /* Acá estaría el llamado a la otra función:
  inicio_asm = clock();
  enmascarar_asm(buff_imagen1, buff_imagen2, buff_mascara, (int) size);
  fin_asm = clock();
  total_asm = (double) (fin_asm - inicio_asm) / CLOCKS_PER_SEC;
  */

  // tamaño, tiempo_c, tiempo_asm
  fprintf(stdout, "%d, %f, %f\n", imagen1_size, total_c, total_asm);

}

long int fsize(FILE *p) {
  fseek(p, 0, SEEK_END);
  long int size = ftell(p);
  fseek(p, 0, SEEK_SET);
  return size;
}
