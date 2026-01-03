#include <stdbool.h>
#include <stdio.h>
#define MAX_CHAR 100

typedef struct {
    char* file;
    int size_cache;
    int E;
    int sets;
    bool is_verbose;
    int n;
    int m;
} Params_t;

typedef struct{
    int index;
    char* identifier;
    int cache_index;
    int cache_tag;
    int cache_line;
    int line_tag;
    bool valid_bit;
    bool dirty_bit;
    int last_used;
} VerboseMode_t;

typedef struct{
    int count;
    int miss;
    int dirty_misses;
    int bytes;
    int time;
} Action_t;

typedef struct{
    Action_t read;
    Action_t write;
    int total_access;
    int total_miss;
    float miss_rate;
} Stat_t;

typedef struct{
    unsigned int tag;
    unsigned int data;
    bool dirty_bit;
    bool valid_bit;
    int least_recently_used;
    int last_used_op_index;
} Line_t;

typedef struct{
    int index;
    Line_t* lines;
} Set_t;

typedef struct{
    unsigned int tag;
    int set;
    int offset;
} MemoryAddress_t;

typedef struct{
    int inst_pointer;
    int mode;
    MemoryAddress_t* memory_address;
    int cant_bytes;
    unsigned int op_data;
} Operation_t;

typedef struct{
    Set_t* sets;
    Params_t params;
    int block_size;
    int lru_counter;
    Stat_t stats;
} CacheSim_t;

/*
 * Pre condiciones: La linea de comando debe seguir es siguiente formato:
 *                   ` $ ./cachesim tracefile.xex C E S [ -v n m ] `
 *                  Los cuatro primeros argumentos son:
 *                   1. el archivo de traza a simular
 *                   2. el tamaño de la caché C, en bytes
 *                   3. la asociatividad de la caché, E
 *                   4. el número de sets de la caché, S
 *                  El parametro -v es opcional. Si está presente, n y m representan el rango de operaciones que se desea ver.
 * Post condiciones: Verifica que los argumentos sean validos, rellena ` params ` con dichos argumentos validados.
 */
void procesar_entrada(int cant_args, char *argv[], Params_t* params);

/*
 * Pre condiciones: Tener inicializada el campo ` params ` de la cache con datos validos.
 * Post condiciones: Inicializara la cache cargando toda la informacion inicial de cada campo.
 */
void inicializar_cache (CacheSim_t* cache);

/*
 * Pre condiciones: -
 * Post condiciones: retorna el archivo abierto
 */
FILE* abrir_archivo(char archivo[MAX_CHAR], const char* modo);

/*
 * Pre condiciones: ` file ` debe tener un unico `.` ademas los parametros deben estar inicializados 
 * Post condiciones: rellena ` name_out `, el resultado tiene el siguiente formato:
 *                  ` file_(size_cache)-(E)-(sets).txt `   
 */
void formar_nombre_salida (char* file, Params_t params, char* name_out);

/*
 * Pre condiciones: ` arch_trazas ` y ` arch_out ` deben ser archivos previamente abiertos. ` cache ` debe estar 
 *                   previamente inicializada
 * Post condiciones: Decodifica cada traza de ` arch_trazas `, las procesa en la cache, actualiza la cache y 
 *                   se imprime en ` arch_out ` si es que está el modo verboso activado.
 */
void simular_cache(CacheSim_t* cache, FILE* arch_trazas, FILE* arch_out);

/*
 * Pre condiciones: ` cache `  debe estar previamente inicializada, ` archivo ` debe estar previamente abierto. 
 * Post condiciones: Imprime la informacion del campo ` stats ` tenida en ` cache ` en ` archivo `
 */
void agregar_estadisticas (CacheSim_t* cache, FILE* archivo);

/*
 * Pre condiciones: ` archivo ` debe estar previamente abierto.
 * Post condiciones: Cierra ` archivo `
 */
void cerrar_archivo (FILE* archivo);

/*
 * Pre condiciones: El campo ` sets ` de ` cache ` y ` lines ` de cada ` sets` deben estar inicializados
 * Post condiciones: Se libera la memoria dinamica reservada para cache
 */
void destruir_cache (CacheSim_t* cache);

