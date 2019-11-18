#include <stdio.h>
#include <stdlib.h>
#include "imagen.h"

#define NOMBRE_SALIDA "salida_c.rgb"

void enmascarar_c(Byte *a, Byte *b, Byte *mask, int cant) {

  FILE *output = fopen(NOMBRE_SALIDA, ESCRITURA);
  
  for( int i = 0; i < cant; i++ )
    *(a + i) = transformar_byte(*(a + i), *(b + i), *(mask + i));

  fwrite(a, 1, cant, output);
  fclose(output);

}

Byte transformar_byte(Byte a, Byte b, Byte mascara) {
  return (a & ~mascara) | (b & mascara);
}
