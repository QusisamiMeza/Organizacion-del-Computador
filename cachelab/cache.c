#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CAMPOS 5
#define MAX_PARAM 7
#define MODO_ESCRITURA 1
#define MODO_LECTURA 0
#define MODO_HIT "1"
#define MODO_CLEAN_MISS "2a"
#define MODO_DIRTY_MISS "2b"
#define CLEAN 0
#define DIRTY 1
#define MAX_CHAR 100


const char* FORMATO_TXT = ".txt";
const int ERROR = 1;
const int PENALTY = 100;
const int TIEMPO_CICLO= 1;
const int ARG_SIN_MODO_V = 4;
const int ARG_CON_MODO_V = 7;
const int IDX_FILE = 0;
const int IDX_SIZE_CACHE = 1;
const int IDX_E = 2;
const int IDX_SETS = 3;
const int IDX_N = 5;
const int IDX_M = 6;
const bool VERBOSO_ACTIVADO = true;
const bool VERBOSO_DESACTIVADO = true;
const int MIN_VALUE = 0;
const int SIZE_CACHE_VALIDA = 0;
const int CANT_INICIAL_BYTES = 0;
const int CANT_INICIAL_COUNT = 0;
const int CANT_INICIAL_D_MISSES = 0;
const int CANT_INICIAL_MISS = 0;
const int CANT_INICIAL_TIME = 0;
const float CANT_INICIAL_M_RATE = 0;
const int CANT_INICIAL_TOTAL_ACCESS = 0;
const int CANT_INICIAL_TOTAL_MISS = 0;
const bool BIT_SUCIO = 0;
const int SIN_USAR = -1;
const bool BIT_INVALIDO = 0;
const bool BIT_VALIDO = 1;
const int TAG_INVALIDO = -1;
const int SET_INVALIDO = -1;
const int TIEMPO_INICIAL_LRU = 0;
const int ES_POTENCIA = 0;
const int UNA_LINEA =1;
const int BYTES_KB= 1024;
const int ACCESOS_DIRTY_MISS = 2;
const int ES_ESCRITURA = 0;
const int IDX_INST_POINTER = 0;
const int IDX_MODO = 1;
const int IDX_DIRECCION = 2;
const int IDX_CANT_BYTES = 3;
const int IDX_OP_DATA = 4;
const int RESTAR_UNO = -1;

/*
 * Pre condiciones: -
 * Post condiciones: Retorna true si ` x ` es potencia de dos, false en caso contrario
 */
bool es_potencia_de_dos(int x) {
    return (x > MIN_VALUE && (x & (x + RESTAR_UNO)) == ES_POTENCIA);
}

/*
 * Pre condiciones: -
 * Post condiciones: Verifica que ` cant_args ` sea 4 o 7 (valido). En caso que no sea valido, imprime un error con stderr y termina el programa
 */
void verificar_cantidad_args (int cant_args) {
    if (cant_args != ARG_SIN_MODO_V && cant_args != ARG_CON_MODO_V){ 
        fprintf(stderr, "Error: cantidad de argumentos inválida\n");
        exit(ERROR);
    }
}

/*
 * Pre condiciones: -
 * Post condiciones: Verifica que ` n ` y ` m ` esten en un rango valido [0,n,m). En caso que no sea valido, imprime un error con stderr y termina el programa
 */
void verificar_rango(int n, int m){
    if (n < MIN_VALUE || n > m || m < MIN_VALUE){
        fprintf(stderr, "Error: n y m es un rango inválido\n");
        exit(ERROR);
    }
}

/*
 * Pre condiciones: -
 * Post condiciones: Inicializa los campos relacionados a modo verboso de ` parametros `
 */
void activar_modo_verboso(Params_t* parametros, int valor_N, int valor_M){
    parametros->is_verbose = VERBOSO_ACTIVADO;
    parametros->n = valor_N;
    parametros->m = valor_M;
}

/*
 * Pre condiciones: -
 * Post condiciones: Verifica que todos los parametros sean potencia de dos. En caso que no cumpla, imprime un error con stderr y termina el programa
 */
void verificar_potencia_de_dos (int size_cache, int E, int sets){
    if (!es_potencia_de_dos(size_cache) || !es_potencia_de_dos(E) || !es_potencia_de_dos(sets)){
        fprintf(stderr, "Error: C, E y S deben ser potencias de dos\n");
        exit(ERROR);
    }
}

/*
 * Pre condiciones: -
 * Post condiciones: Verifica que la combinacion de los parametros sea valida. En caso que no sea valido, imprime un error con stderr y termina el programa
 */
void verificar_combinacion (int size_cache, int E, int sets){
    int aux = sets * E;
    if (!((aux > MIN_VALUE) && (size_cache > aux) && size_cache % aux == SIZE_CACHE_VALIDA)){
        fprintf(stderr, "Error: Combinacion de parametros C, E y S invalida\n");
        exit(ERROR);
    }
}

/*
 * Pre condiciones: -
 * Post condiciones: Inicializa todos los campos de ` parametros ` excepto los relacionados a modo verboso 
 */
void rellenar_parametros (Params_t* parametros, char* file, int size_cache, int E, int sets){
    parametros->file= file;
    parametros->size_cache = size_cache;
    parametros->E = E;
    parametros->sets = sets;
}

/*
 * Precondiciones:
 *   - `argv` debe contener los argumentos correctamente ordenados:
 *       - [1] ruta del archivo de trazas
 *       - [2] tamaño de caché (en bytes)
 *       - [3] asociatividad (E)
 *       - [4] cantidad de conjuntos (sets)
 *       - (opcional) [5] índice n de modo verboso
 *       - (opcional) [6] índice m de modo verboso
 *   - `params` debe ser un puntero válido a una estructura `Params_t` ya reservada
 * Postcondiciones:
 *   - Valida la cantidad de argumentos y la validez de los parámetros
 *   - Verifica que tamaño de caché, E y sets sean potencias de dos
 *   - Verifica que la combinación de esos tres parámetros sea coherente
 *   - Llena la estructura `params` con los valores obtenidos de los argumentos
 *   - Si se reciben los índices `n` y `m`, activa el modo verboso en `params`
 *   - En caso de error, termina la ejecución con stderr
 */
void procesar_entrada(int cant_args, char *argv[], Params_t* params) {
    verificar_cantidad_args(cant_args);

    char* parametros[MAX_PARAM];
    int i = 1;
    int j = 0;
    while (j < cant_args){
        parametros[j] = argv[i];
        i++;
        j++;
    }
    char* file =parametros[IDX_FILE];
    int size_cache = atoi(parametros[IDX_SIZE_CACHE]);
    int E =atoi(parametros[IDX_E]);
    int sets = atoi(parametros[IDX_SETS]);

    verificar_potencia_de_dos(size_cache,E,sets);
    verificar_combinacion(size_cache,E,sets);
    rellenar_parametros (params,file,size_cache,E,sets);

    if (cant_args == ARG_CON_MODO_V){
        int n = atoi(parametros[IDX_N]);
        int m = atoi(parametros[IDX_M]);
        verificar_rango (n,m);
        activar_modo_verboso(params, n, m);
    } else {
        params->is_verbose = VERBOSO_DESACTIVADO;
    }
}

/*
 * Pre condiciones: -
 * Post condiciones: Inicializa cada campo de ` action `
 */
void inicializar_action (Action_t* action){
    action->bytes=CANT_INICIAL_BYTES;
    action->count=CANT_INICIAL_COUNT;
    action->dirty_misses=CANT_INICIAL_D_MISSES;
    action->miss=CANT_INICIAL_MISS;
    action->time=CANT_INICIAL_TIME;
}

/*
 * Pre condiciones: -
 * Post condiciones:  Inicializa cada campo de ` stats `
 */
void inicializar_stats (Stat_t* stat){
    stat->miss_rate = CANT_INICIAL_M_RATE;
    stat->total_access = CANT_INICIAL_TOTAL_ACCESS;
    stat->total_miss = CANT_INICIAL_TOTAL_MISS;
    inicializar_action (&stat->read);
    inicializar_action (&stat->write);
}

/*
 * Pre condiciones: ` lines ` debe apuntar a un bloque de memoria valido, previamente reservado para al menos ` cant_lines ` elementos
 * Post condiciones:  Inicializa cada campo de las `cant_lines ` lineas
 */
void inicializar_lines (Line_t* lines, int cant_lines){
    for (int i = 0; i < cant_lines; i++){
        lines[i].data=-1;
        lines[i].dirty_bit=BIT_SUCIO;
        lines[i].least_recently_used=SIN_USAR;
        lines[i].valid_bit=BIT_INVALIDO;
        lines[i].tag=TAG_INVALIDO; 
        lines[i].last_used_op_index=0;
    }
}

/*
 * Pre condiciones: ` set ` debe apuntar a un bloque de memoria valido, previamente reservado para al menos ` total_sets ` elementos
 * Post condiciones: Inicializa cada campo de las ` total_sets ` sets
 */
void inicializar_sets (Set_t* set, int total_sets, int cant_lines){
    for (int i = 0; i < total_sets ; i++){
        set[i].index = SET_INVALIDO;
        set[i].lines=malloc(sizeof(Line_t)*cant_lines);
        inicializar_lines (set[i].lines, cant_lines);
    }
}

/*
 * Pre condiciones: el campo ` params ` de ` cache ` debe estar previamente inicializado.
 * Post condiciones: Inicializa el resto de los campos ` cache ` 
 */
void inicializar_cache (CacheSim_t* cache){
    cache->block_size = cache->params.size_cache / (cache->params.sets * cache->params.E);
    cache->lru_counter = TIEMPO_INICIAL_LRU;
    inicializar_stats(&cache->stats);
    cache->sets = malloc (sizeof(Set_t)*cache->params.sets);
    inicializar_sets (cache->sets, cache->params.sets, cache->params.E);
}

/*
 * Pre condiciones: -
 * Post condiciones: Copia cada caracter de ` linea ` exceptuando ':' y '\n' en ` salida `  
 */
void eliminar_caracteres(char* linea, char* salida) {
    int j = 0;
    for (int i = 0; linea[i] != '\0'; i++) {
        if (linea[i] != ':' && linea[i] != '\n') {
            salida[j++] = linea[i];
        }
    }
    salida[j] = '\0';
}

/*
 * Pre condiciones: ` archivo ` debe ser una ruta válida y ` modo ` debe ser un string válido ('r' o 'w')
 * Post condiciones: 
 *      - Lo abre dependiendo del ` modo ` (lectura o escritura)
 *      - Si falla al abrir el archivo, tira error con stderr y termina la ejecución
 */
FILE* abrir_archivo(char archivo[MAX_CHAR], const char* modo){
    FILE* arch = fopen(archivo, modo);
    if (arch == NULL){
        fprintf(stderr, "Error: en abrir el archivo\n");
        exit (ERROR);
    }
    return arch;
}

/*
 * Precondiciones: `file`, `name_out` y `params` deben estar bien inicializados
 * Postcondiciones: Genera un nombre de archivo de salida en `name_out`, basado en el nombre base de `file`, agregando los parámetros de la caché y la extensión `.txt`
 */
void formar_nombre_salida (char* file, Params_t params, char* name_out){
    int i = 0;
    while (file[i] != '.' && file[i] != '\0'){
        name_out[i] = file[i];
        i++;
    }
    name_out[i] = '\0';
    sprintf(name_out + i, "_%i-%i-%i%s", params.size_cache,params.E,params.sets,FORMATO_TXT);
}

/*
 * Precondiciones: -
 * Postcondiciones: Si el archivo no es NULL, lo cierra con `fclose`
 */
void cerrar_archivo (FILE* archivo){
    if (archivo) {
        fclose(archivo);
    }
}

/*
 * Pre condiciones: n > 0
 * Post condiciones: calcula ⌈log₂(n)⌉
 */
int log2_int(int n) {
    int bits = 0;
    while ((1 << bits) < n){
        bits++;
    }
    return bits;
}

/*
 * Pre condiciones: ` params ` debe estar previamente inicializado
 * Post condiciones: Reserva memoria para un ` MemoryAddress_t ` e inicializa sus campos según ` direccion ` y  ` params `
 */
MemoryAddress_t* crear_direccion_memoria(int direccion, Params_t params){
    MemoryAddress_t *address = malloc(sizeof(MemoryAddress_t));

    int block_size = params.size_cache / (params.E * params.sets);
    int offset_bits = log2_int(block_size);
    int set_bits = log2_int(params.sets);
    address->offset = direccion & ((1 << offset_bits)-1);
    int set_mask = ((1<< set_bits)-1)<< offset_bits;
    address->set = (direccion & set_mask) >> offset_bits;
    address->tag = ((unsigned int)direccion) >> (offset_bits + set_bits);
    return address;
}

/*
 * Pre condiciones: ` traza ` debe estar previamente inicializada
 * Post condiciones: Libera la memoria dinamica de ` traza `
 */
void destruir_direccion_memoria(Operation_t* traza){
    free(traza->memory_address);
}

/*
 * Pre condiciones: ` params ` debe estar inicializado, ` campos ` debe ser valido
 * Post condiciones: Inicializa todos los campos de ` traza ` segun ` campos ` y ` params `
 */
void crear_operacion(Operation_t* traza, char** campos, Params_t params){
    traza->inst_pointer = atoi(campos[IDX_INST_POINTER]);
    if (strcmp(campos[IDX_MODO], "W") == ES_ESCRITURA) {
        traza->mode = MODO_ESCRITURA; 
    } else {
        traza->mode = MODO_LECTURA; 
    }
    int direccion = (int)strtol(campos[IDX_DIRECCION], NULL, 0);
    traza->memory_address = crear_direccion_memoria(direccion, params);
    traza->cant_bytes = atoi(campos[IDX_CANT_BYTES]);
    traza->op_data = atoi(campos[IDX_OP_DATA]);
}

/*
 * Pre condiciones: ` linea ` debe ser valida, ` cache ` debe estar previamente inicializado
 * Post condiciones: Decodifica ` linea ` y crea una traza con sus campos llenados
 */
Operation_t procesar_traza (char* linea, CacheSim_t cache){
    Operation_t traza;
    char limpia[100];
    eliminar_caracteres(linea, limpia);
    char *campos[MAX_CAMPOS];
    char* token = strtok(limpia, " ");
    int i = 0;
    while (token != NULL && i < MAX_CAMPOS){
        campos[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    crear_operacion(&traza, campos, cache.params);
    return traza;
}

/*
 * Pre condiciones: ` set ` debe estar previamente inicializado con ` E ` lineas
 * Post condiciones: Busca el indice de la linea que tenga el menos reciente uso
 */
int buscar_ind_linea_LRU(int E, Set_t* set){
    int lru_index = 0;
    int min_lru = set->lines[0].least_recently_used;
    for (int i = 0; i < E; i++){
        if (set->lines[i].least_recently_used < min_lru){
            min_lru = set->lines[i].least_recently_used;
            lru_index = i;
        }
    }
    return lru_index;
}

/*
 * Pre condiciones: ` action `, ` time_inicial ` y ` time_final ` deben estar inicializados
 * Post condiciones: Aumenta los campos ` count ` y ` time ` segun los parametros.
 */
void actualizar_stats(Action_t* action, int time_inicial, int time_final) {
    action->count++;
    action->time += time_final - time_inicial;
}

/*
 * Pre condiciones: ` cache `, ` linea ` y ` op ` deben estar inicializados
 * Post condiciones: Se actualiza:
*     - El contador de ciclos (` lru_counter `) por el tiempo de acceso.
*     - El índice de la última operación que usó la línea (` last_used_op_index `).
*     - Las estadísticas de lectura o escritura (` read ` o ` write `).
*     - El bit ` dirty_bit ` si fue una escritura sobre una línea limpia.
*     - El contador total de accesos (`total_access `).
 */
void actualizar_cache_hit(Operation_t op, CacheSim_t* cache, Line_t* linea, int index_op) {
    int time_inicial = cache->lru_counter;
    cache->lru_counter += TIEMPO_CICLO;
    int estado_linea = linea->dirty_bit;
    linea->last_used_op_index = index_op;
    if (op.mode == MODO_LECTURA) {
        actualizar_stats(&cache->stats.read, time_inicial, cache->lru_counter);
    } else {
        actualizar_stats(&cache->stats.write, time_inicial, cache->lru_counter);
        if (estado_linea == CLEAN) {
            linea->dirty_bit = DIRTY;
        }
    }
    linea->least_recently_used = cache->lru_counter;
    cache->stats.total_access = cache->stats.read.count + cache->stats.write.count;
}

/*
 * Pre condiciones: `linea` debe estar inicializada
 * Post condiciones: Asigna valores a todos los campos de ` linea ` exceptuando ` dirty_bit ` y ` last_used_op_index`.
 */
void cargar_linea (Line_t* linea, int tag, int least_recently, int data){
    linea->tag = tag;
    linea->least_recently_used=least_recently;
    linea->valid_bit = BIT_VALIDO;
    linea->data=data;
}

/*
 * Pre condiciones: ` cache ` y ` op ` debem estar inicializados
 * Post condiciones: 
 *  - Se actualiza `lru_counter` sumando el tiempo de acceso + doble penalidad por dirty miss.
 *  - Se actualizan las estadísticas correspondientes (read/write), incluyendo:
 *       - bytes transferidos
 *       - cantidad de misses
 *       - cantidad de dirty misses
 *       - tiempo total
 *  - Se actualiza `dirty_bit` de la línea:
 *       - a `CLEAN` si fue una lectura
 *       - a `DIRTY` si fue una escritura
 *  - Se incrementa `total_access`
 */
void actualizar_dirty_miss (CacheSim_t* cache, Operation_t op, int time_inicial, Line_t* linea){
    cache->lru_counter += (TIEMPO_CICLO + (2*PENALTY));
    cache->stats.read.bytes += cache->block_size;
    cache->stats.write.bytes += cache->block_size;
        if (op.mode == MODO_LECTURA) {
            cache->stats.read.miss++;
            actualizar_stats(&cache->stats.read, time_inicial, cache->lru_counter);
            cache->stats.read.dirty_misses++;
            linea->dirty_bit = CLEAN;
        } else {
            actualizar_stats(&cache->stats.write, time_inicial,cache->lru_counter);
            linea->dirty_bit = DIRTY;
            cache->stats.write.dirty_misses++;
            cache->stats.write.miss++;
            linea->dirty_bit = DIRTY;
        }
        cache->stats.total_access++;
}

/*
 * Pre condiciones: ` cache ` y ` op ` debem estar inicializados
 * Post condiciones: 
 *  - Se actualiza `lru_counter` con el tiempo de acceso más la penalidad por fallo de caché.
 *  - Se actualizan las estadísticas (read/write) según el tipo de operación:
 *       - cantidad de misses
 *       - tiempo total de acceso
 *  - Si es lectura, suma bytes leídos y actualiza stats de `read`
 *  - Si es escritura, suma bytes leídos (por write-allocate), actualiza `write` y se marca la línea como `DIRTY`.
 *  - Se incrementa `total_access`.
 */
void actualizar_clean_miss(CacheSim_t* cache, Operation_t op, int time_inicial, Line_t* linea){
    cache->lru_counter += (TIEMPO_CICLO + PENALTY);
    cache->stats.read.bytes += cache->block_size;
    if (op.mode == MODO_LECTURA) {
        actualizar_stats(&cache->stats.read, time_inicial, cache->lru_counter);
        cache->stats.read.miss++;
    } else {
        actualizar_stats(&cache->stats.write, time_inicial,cache->lru_counter);
        linea->dirty_bit = DIRTY;
        cache->stats.write.miss++;
    }
    cache->stats.total_access++;
}

/*
 * Pre condiciones: ` cache ` y ` op ` debem estar inicializados
 * Post condiciones: 
 *  - Se actualiza `lru_counter` en la caché según el tipo de miss:
 *       - `TIEMPO_CICLO + PENALTY` si es un clean miss.
 *       - `TIEMPO_CICLO + 2 * PENALTY` si es un dirty miss.
 *  - Se actualizan las estadísticas correspondientes (read/write, dirty_miss si aplica).
 *  - Se actualiza `linea->last_used_op_index` con el índice de la operación.
 *  - Se carga en `linea` el nuevo dato (`op.op_data`) con su `tag` y tiempo de uso.
 *  - Se incrementa el contador global de fallos (`total_miss`).
 */
void actualizar_cache_miss(Operation_t op, CacheSim_t* cache, Line_t* linea, int index_op, bool es_dirty_miss) {
    int time_inicial = cache->lru_counter;
    linea->last_used_op_index = index_op;   

    if (!es_dirty_miss) {
        actualizar_clean_miss(cache,op,time_inicial,linea);
    } else {
        actualizar_dirty_miss(cache,op,time_inicial,linea);
    }
    cargar_linea(linea,op.memory_address->tag,cache->lru_counter, op.op_data);
    cache->stats.total_miss++;
}

/*
 * Pre condiciones: `modo_verboso_data` debe estar inicializado
 * Post condiciones: Actualiza los campos ` line_ tag `, ` dirty_bit `, ` valid_bit ` e ` identifier ` de ` modo_verboso_data `
 */
void actualizar_modo_verboso (VerboseMode_t* modo_verboso_data, int tag, int d_bit, int v_bit, char * ident){
    modo_verboso_data->line_tag = tag;
    modo_verboso_data->dirty_bit = d_bit;
    modo_verboso_data->valid_bit = v_bit;
    modo_verboso_data->identifier = ident;
}

/*
 * Pre condiciones: ` linea `, ` set ` y ` modo_verboso ` deben estar inicializados
 * Post condiciones: Asigna a ` linea ` una linea de ` set ` si esa linea tiene el tag buscado y la data es valida
 */
void buscar_linea (Line_t** linea,Set_t* set,VerboseMode_t*  modo_verboso, int lru_counter, int E, unsigned int tag_buscado){
    for (int i = 0; i < E; i++) {
        if (set->lines[i].tag == tag_buscado && set->lines[i].valid_bit == BIT_VALIDO) {
            *linea = &set->lines[i];
            (*linea)->least_recently_used = lru_counter;
            modo_verboso->cache_line = i;
            break;
        }
    }
}

/*
 * Pre condiciones: ` set `, ` modo_verboso ` y ` linea ` deben estar inicializados
 * Post condiciones: Busca una linea invalida de ` set ` y la asigna a `*linea `. Actualiza ` modo_verboso `
 */
void asignar_linea_vacia (Line_t** linea, Set_t* set, VerboseMode_t*  modo_verboso, int lru_counter, int E){
    for (int i = 0; i < E; i++) {
        if (set->lines[i].valid_bit == BIT_INVALIDO) {
            *linea = &set->lines[i];
            modo_verboso->last_used = (*linea)->last_used_op_index;
            (*linea)->least_recently_used = lru_counter;
            modo_verboso->cache_line = i;
            break;
        }
    }
}

/*
 * Pre condiciones:  ` set `, ` modo_verboso ` y ` linea ` deben estar inicializados
 * Post condiciones: Busca la linea de ` set ` que tenga el menor ` last_used ` y la reemplaza
 */
void reemplazar_linea (Set_t* set, VerboseMode_t* modo_verboso_data, Line_t** linea, int lru_counter, int index_op, Params_t params){
    int lru_ind = buscar_ind_linea_LRU(params.E, set);
    *linea = &set->lines[lru_ind];
    modo_verboso_data->last_used = (*linea)->last_used_op_index;
    (*linea)->last_used_op_index = index_op;
    modo_verboso_data->cache_line = lru_ind;
}

/*
 * Pre condiciones: ` cache ` y ` modo_verboso_data ` deben estar inicializados y ` op ` debe ser valida
 * Post condiciones: .
 *   - Se accede o carga una línea de caché según corresponda (hit, clean miss o dirty miss).
 *   - Se actualizan los campos de la línea 
 *   - Se modifican las estadísticas de acceso 
 *   - Se incrementa `lru_counter` según el tipo de acceso.
 *   - Se actualiza la estructura de modo verboso si está activa.
 *   - Se actualizan los contadores LRU del conjunto.
 */
void actualizar_cache(Operation_t op, CacheSim_t* cache, int index_op, VerboseMode_t* modo_verboso_data) {
    Params_t params = cache->params;
    Set_t* set = &cache->sets[op.memory_address->set];
    Line_t* linea = NULL;
    int lru_counter = cache->lru_counter;

    buscar_linea (&linea,set,modo_verboso_data,lru_counter,params.E,op.memory_address->tag);
    if (linea == NULL) {
        asignar_linea_vacia(&linea,set,modo_verboso_data,lru_counter,params.E);
        if (linea != NULL) {
            actualizar_modo_verboso(modo_verboso_data, TAG_INVALIDO, linea->dirty_bit, BIT_INVALIDO, MODO_CLEAN_MISS);
            actualizar_cache_miss(op, cache, linea, index_op, false);
        } else {
            reemplazar_linea(set,modo_verboso_data,&linea,lru_counter,index_op,params);
            bool es_dirty_miss = (linea->valid_bit == BIT_VALIDO && linea->dirty_bit == DIRTY && linea->tag != op.memory_address->tag);
            if (es_dirty_miss){
                actualizar_modo_verboso(modo_verboso_data, linea->tag, linea->dirty_bit, BIT_VALIDO, MODO_DIRTY_MISS);
            } else {
                actualizar_modo_verboso(modo_verboso_data, linea->tag, linea->dirty_bit, BIT_VALIDO, MODO_CLEAN_MISS);
            }
            actualizar_cache_miss(op, cache, linea, index_op, es_dirty_miss); 
        }
    } else {
        modo_verboso_data->last_used = linea->last_used_op_index;
        linea->last_used_op_index = index_op;
        linea->least_recently_used = lru_counter;
        actualizar_modo_verboso(modo_verboso_data, linea->tag, linea->dirty_bit, BIT_VALIDO, MODO_HIT);
        actualizar_cache_hit(op, cache, linea, index_op);
    }
}

/*
 * Pre condiciones: ` archivo ` debe estar abierto en modo escritura('w'), ` data ` y ` addr ` deben estar inicializados
 * Post condiciones: Escribe el modo verboso en el archivo
 */
void modo_verboso(FILE* archivo, MemoryAddress_t* addr, VerboseMode_t* data, int E){
    int index = data->index;
    char* identifier= data->identifier;
    int set=addr->set;
    int tag=addr->tag;
    int line= data->cache_line;
    int line_tag= data->line_tag;
    bool valid_bit=data->valid_bit;
    bool dirty_bit=data->dirty_bit;
    char line_tag_str[20];
    if (line_tag == SIN_USAR){
        sprintf(line_tag_str, "%i", SIN_USAR);
    }else sprintf(line_tag_str, "%x", line_tag);
    
    if (E <= 1){
        fprintf(archivo, "%d %s %x %x %d %s %d %d\n",
        index, identifier, set,tag, line,line_tag_str, valid_bit, dirty_bit);
    } else {
        fprintf(archivo, "%d %s %x %x %d %s %d %d %d\n",
        index, identifier, set, tag, line, line_tag_str, valid_bit, dirty_bit, data->last_used);
    }
}

/*
 * Pre condiciones: -
 * Post condiciones: Retorna true si ` is_verbose ` está activado y ` n ` y ` m ` son validos
 */
bool es_modo_verboso_activado (bool is_verbose, int n, int m, int index_op){
    return (is_verbose && n <= index_op && index_op <= m);
}

/*
 * Pre condiciones: ` cache ` debe estar inicializada
 * Post condiciones: calcula total_miss / total access
 */
void calcular_miss_rate(CacheSim_t* cache){
    cache->stats.miss_rate = (float)cache->stats.total_miss / (float)cache->stats.total_access;
}

/*
 * Precondiciones: `cache`, `arch_trazas` y `arch_out` deben estar correctamente inicializados y abiertos
 * Postcondiciones:
 *   - Procesa todas las trazas del archivo `arch_trazas`
 *   - Actualiza la estructura `cache` según las operaciones
 *   - Si el modo verboso está activado y el índice corresponde, imprime información detallada en `arch_out` dentro del rango [n, m]
 *   - Al finalizar, calcula y actualiza el `miss_rate`
 */
void simular_cache (CacheSim_t* cache, FILE* arch_trazas, FILE* arch_out){
    char linea[MAX_CHAR];
    int index_op = 0;
    while (fgets(linea, sizeof(linea), arch_trazas)){
        Operation_t traza = procesar_traza (linea, *cache);
        VerboseMode_t modo_verboso_data;
        actualizar_cache(traza, cache, index_op, &modo_verboso_data);
        modo_verboso_data.index = index_op;
        if (es_modo_verboso_activado(cache->params.is_verbose,cache->params.n,cache->params.m,index_op)) {
            modo_verboso(arch_out, traza.memory_address, &modo_verboso_data, cache->params.E);
        }
        destruir_direccion_memoria(&traza);
        index_op++;
    }
    calcular_miss_rate(cache);
}

/*
 * Precondiciones: `cache` debe haber sido correctamente inicializada con memoria dinámica.
 * Postcondiciones: Libera toda la memoria dinámica asociada a los conjuntos (`sets`) y líneas de caché.
 */
void destruir_cache(CacheSim_t* cache){
    for (int i = 0; i < cache->params.sets; i++){
        free(cache->sets[i].lines);
    }
    free(cache->sets);
}

/*
 * Precondiciones: `cache` debe estar inicializada, y`archivo` debe estar abierto en modo escritura.
 * Postcondiciones: Escribe en `archivo` un resumen de estadísticas de la simulación de caché, incluyendo accesos, misses, tiempos, y tasa de fallos.
 */
void agregar_estadisticas (CacheSim_t* cache, FILE* archivo){
    int size_KB = cache->params.size_cache / BYTES_KB;
    if (cache->params.E == UNA_LINEA){
        fprintf(archivo, "direct-mapped, %d sets, size = %dKB\n", cache->params.sets, size_KB);
    } else {
        fprintf(archivo, "%d-way, %d sets, size = %dKB\n", cache->params.E, cache->params.sets, size_KB);
    }
    fprintf(archivo, "loads %d stores %d total %d\n", cache->stats.read.count, cache->stats.write.count, cache->stats.total_access);
    fprintf(archivo, "rmiss %d wmiss %d total %d\n", cache->stats.read.miss, cache->stats.write.miss, cache->stats.total_miss);
    fprintf(archivo,"dirty rmiss %d dirty wmiss %d\n", cache->stats.read.dirty_misses, cache->stats.write.dirty_misses);
    fprintf(archivo,"bytes read %d bytes written %d\n", cache->stats.read.bytes, cache->stats.write.bytes);
    fprintf(archivo, "read time %d write time %d\n", cache->stats.read.time, cache->stats.write.time);
    fprintf(archivo, "miss rate %f\n", cache->stats.miss_rate);
}
