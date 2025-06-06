#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#define INDEX_INITIAL_CAPACITY 100
#define INDEX_EXPAND_PERCENT 30


typedef struct {
    long dni;
    unsigned num_reg;   // Posición del registro en el archivo
} t_reg_index;

typedef struct {
    t_reg_index * arr;  // Puntero a un arreglo dinamico de registros de índice
    size_t count;       // Cantidad actual de elementos en el arreglo
    size_t capacity;    // Capacidad total de elementos del arreglo
} t_index;

/**
 * @brief Inicializa el índice, reservando memoria y dejando el arreglo vacío.
 * @param idx Puntero al índice a inicializar.
 */
void index_create(t_index* idx);

/**
 * @brief Inserta un nuevo registro en el índice, manteniendo el orden por DNI.
 * @param idx Puntero al índice.
 * @param new_entry Puntero al registro a insertar.
 * @return 1 si se insertó correctamente, 0 si hubo error de memoria.
 */
int index_insert(t_index* idx, const t_reg_index* new_entry);

/**
 * @brief Elimina un registro del índice según el DNI.
 * @param idx Puntero al índice.
 * @param key Puntero al registro clave (DNI) a eliminar.
 * @return 1 si se eliminó, 0 si no se encontró.
 */
int index_delete(t_index* idx, const t_reg_index* key);

/**
 * @brief Libera la memoria utilizada por el índice y lo deja vacío.
 * @param idx Puntero al índice.
 */
void index_clear(t_index* idx);

/**
 * @brief Carga el índice desde un archivo de socios, agregando solo los activos.
 * @param idx Puntero al índice.
 * @param path Ruta del archivo binario de socios.
 * @return 1 si se cargó correctamente, 0 si hubo error de apertura.
 */
int index_load(t_index* idx, const char* path);

/**
 * @brief Indica si el índice está vacío.
 * @param idx Puntero al índice.
 * @return 1 si está vacío, 0 si tiene elementos.
 */
int index_empty(const t_index* idx);

/**
 * @brief Busca un registro en el índice por DNI.
 * @param idx Puntero al índice.
 * @param key_out Puntero al registro clave (DNI). Si se encuentra, se completa con la posición.
 * @return 1 si se encontró, 0 si no.
 */
int index_find(const t_index* idx, t_reg_index* key_out);

#endif // INDICE_H_INCLUDED
