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

void index_create(t_index*);

int index_insert(t_index*, const t_reg_index*);

int index_delete(t_index*, const t_reg_index*);

void index_clear(t_index*);

int index_load(t_index*, const char*);

int index_empty(const t_index*);

int index_find(const t_index*, t_reg_index*);


#endif // INDICE_H_INCLUDED
