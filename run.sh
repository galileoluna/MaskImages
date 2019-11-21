#!/bin/bash
#nasm -f elf32 enmascarar_asm.s -o enmascarar_asm.o
#gcc -m32 main.c enmascarar_c.c enmascarar_asm.o -o ejec
gcc -m32 main.c enmascarar_c.c -o ejec
./ejec img/desierto800x600.rgb img/peces800x600.rgb img/mascara800x600.rgb 800 600
./ejec img/cielo1920x1080.rgb img/tiburon1920x1080.rgb img/mascara1920x1080.rgb 1920 1080
./ejec img/atardecer3840x2160.rgb img/iceberg3840x2160.rgb img/mascara3840x2160.rgb 3840 2160
