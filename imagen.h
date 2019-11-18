#ifndef __IMAGEN__
#define __IMAGEN__

#define BLANCO 0xFF
#define NEGRO  0x00

#define LECTURA   "rb"
#define ESCRITURA "wb"

typedef unsigned char Byte;

// Toma 2 bytes y una máscara. La máscara tambiénde debe ser un byte.
// Si la máscara es igual a NEGRO devuelve la primera imagen, sino la segunda.
Byte transformar_byte(Byte, Byte, Byte);

#endif
