#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "imagen.h"

void enmascarar_c(Byte*, Byte*, Byte*, int);

static clock_t inicio_c, fin_c, inicio_asm, fin_asm;
static double total_c = 0, total_asm = 0;
static char SALIDA_C[] = "salida_c";
static char SALIDA_ASM[] = "salida_asm";
static char RGB[] = ".rgb";

/* Recibe 3 argumentos del usuario desde la línea de comandos:
   arg1: imagen1
   arg2: imagen2
   arg3: mascara
   arg4: ancho
   arg5: alto
*/
int main( int argc, char *argv[] ) {
  if( argc != 6 ) {
    fprintf(stderr, "Cantidad de argumentos incorrecta. arg1=imagen1, arg2=imagen2, arg3=mascara, arg4=ancho, arg5=alto.\n");
    exit(1);
  }

  FILE *imagen1;
  FILE *imagen2;
  FILE *mascara;
  FILE *output_c;
  FILE *output_asm;
  Byte *buff_imagen1;
  Byte *buff_imagen2;
  Byte *buff_mascara;
  long int imagen1_size;
  long int imagen2_size;
  long int mascara_size;
  char string_buff_c[30];
  char string_buff_asm[30];
  
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

  strcpy(string_buff_c, SALIDA_C);
  strcat(string_buff_c, argv[4]);
  strcat(string_buff_c, "x");
  strcat(string_buff_c, argv[5]);
  strcat(string_buff_c, RGB);  

  strcpy(string_buff_asm, SALIDA_ASM);
  strcat(string_buff_asm, argv[4]);
  strcat(string_buff_asm, "x");
  strcat(string_buff_asm, argv[5]);
  strcat(string_buff_asm, RGB);
  
  imagen1_size = fsize(imagen1);
  imagen2_size = fsize(imagen2);
  mascara_size = fsize(mascara);

  if( imagen1_size != imagen2_size | imagen1_size != mascara_size ) {
    fprintf(stderr, "Las imágenes no tienen el mismo tamaño.\n");
    exit(1);
  }
  
  buff_imagen1 = (Byte *) malloc(imagen1_size);
  buff_imagen2 = (Byte *) malloc(imagen2_size);
  buff_mascara = (Byte *) malloc(mascara_size);

  fread(buff_imagen1, 1, imagen1_size, imagen1);
  fread(buff_imagen2, 1, imagen2_size, imagen2);
  fread(buff_mascara, 1, mascara_size, mascara);

  fclose(imagen1);
  fclose(imagen2);
  fclose(mascara);

  output_c = fopen(string_buff_c, ESCRITURA);
  inicio_c = clock();
  enmascarar_c(buff_imagen1, buff_imagen2, buff_mascara, (int) imagen1_size);
  fin_c = clock();
  fwrite(buff_imagen1, 1, (int) imagen1_size, output_c);
  fclose(output_c);
  total_c = (double) (fin_c - inicio_c) / CLOCKS_PER_SEC;

  /* Acá estaría el llamado a la otra función:
  output_asm = fopen(string_buff_asm, ESCRITURA);
  inicio_asm = clock();
  enmascarar_asm(buff_imagen1, buff_imagen2, buff_mascara, (int) imagen1_size);
  fin_asm = clock();
  fwrite(buff_imagen1, 1, (int) imagen1_size, output_asm);
  fclose(output_asm);
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
