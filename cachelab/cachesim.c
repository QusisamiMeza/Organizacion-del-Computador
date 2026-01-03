#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "cache.h"

const char* READ = "r";
const char* WRITE = "w";

int main (int argc, char *argv[]){  
    CacheSim_t cacheSim; 
    procesar_entrada(argc-1, argv, &cacheSim.params);
    inicializar_cache (&cacheSim);

    FILE* archivo_trazas = abrir_archivo(cacheSim.params.file, READ);

    char nombre_salida[100];
    formar_nombre_salida (cacheSim.params.file, cacheSim.params, nombre_salida);
    FILE* archivo_salida = abrir_archivo(nombre_salida, WRITE);

    simular_cache (&cacheSim, archivo_trazas, archivo_salida);
    agregar_estadisticas (&cacheSim, archivo_salida);
    
    cerrar_archivo (archivo_trazas);
    cerrar_archivo (archivo_salida);

    destruir_cache(&cacheSim);
    return 0;
}


