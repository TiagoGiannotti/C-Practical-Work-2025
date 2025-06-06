#include "./Indice.h"
#include "./main.h"
#include <stdlib.h>
#include <string.h>



void index_create(t_index* idx) {
    idx->arr = malloc(INDEX_INITIAL_CAPACITY * sizeof(t_reg_index));
    idx->count = 0;
    idx->capacity = INDEX_INITIAL_CAPACITY;
}

int index_insert(t_index* idx, const t_reg_index* new_entry) {
    if (idx->count == idx->capacity) {
        size_t new_capacity = idx->capacity + (idx->capacity * INDEX_EXPAND_PERCENT / 100);
        t_reg_index* new_arr = realloc(idx->arr, new_capacity * sizeof(t_reg_index));
        if (!new_arr)
            return 0; // no hay memoria

        idx->arr = new_arr;
        idx->capacity = new_capacity;
    }

    t_reg_index* ptr = idx->arr + idx->count;
    while (ptr > idx->arr && (ptr - 1)->dni > new_entry->dni) {
        *ptr = *(ptr - 1);
        ptr--;
    }

    *ptr = *new_entry;
    idx->count++;
    return 1;
}
int index_load(t_index* idx, const char* path) {
    FILE* pf = fopen(path, "rb");
    if (!pf)
        return 0;

    t_partner partner;
    unsigned reg_num = 0;

    while (fread(&partner, sizeof(t_partner), 1, pf) == 1) {
        if (partner.status == 'A') {
            t_reg_index reg = { partner.dni, reg_num };
            index_insert(idx, &reg);
        }
        reg_num++;
    }

    fclose(pf);
    return 1;
}

int index_delete(t_index* idx, const t_reg_index* key) {
    t_reg_index* ptr = idx->arr;
    t_reg_index* end = idx->arr + idx->count;

    while (ptr < end && ptr->dni != key->dni)
        ptr++;

    if (ptr == end)
        return 0; // no encontrado

    while (ptr < end - 1) {
        *ptr = *(ptr + 1);
        ptr++;
    }

    idx->count--;
    return 1;
}

int index_find(const t_index* idx, t_reg_index* key_out) {
    int low = 0, high = (int)idx->count - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        t_reg_index* current = idx->arr + mid;

        if (current->dni == key_out->dni) {
            *key_out = *current;
            return 1;
        } else if (current->dni > key_out->dni) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return 0;
}

int index_empty(const t_index* idx) {
    return idx->count == 0;
}

int index_full(const t_index* idx) {
    return idx->count == idx->capacity;
}

void index_clear(t_index* idx) {
    free(idx->arr);
    idx->arr = NULL;
    idx->count = 0;
    idx->capacity = 0;
}
