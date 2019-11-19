#!/bin/bash
gcc main.c enmascarar_c.c -o ejec
./ejec img/desierto800x600.rgb img/peces800x600.rgb img/mascara800x600.rgb
./ejec img/cielo1920x1080.rgb img/tiburon1920x1080.rgb img/mascara1920x1080.rgb
./ejec img/atardecer3840x2160.rgb img/iceberg3840x2160.rgb img/mascara3840x2160.rgb
