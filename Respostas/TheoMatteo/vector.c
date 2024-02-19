#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

struct Vector {
    void** data;
    int size;
};

Vector *VectorConstruct() {

    Vector* v = malloc(sizeof(Vector));
    if (v == NULL) exit(EXIT_FAILURE);

    v->size = 0;
    v->data = NULL;

    return v;
}

void VectorPushBack(Vector *v, void* val) {
    v->data = realloc(v->data, sizeof(void*) * ++v->size);
    v->data[v->size - 1] = val;
}

void* VectorPopFront(Vector *v) {

    void* val = v->data[0];

    for (int i = 1; i < v->size; i++) {
        v->data[i - 1] = v->data[i];
    }

    // Diminui o tamanho da lista
    v->size--;

    // Cria um novo vetor com um tamanho menor e atribui ao novo
    void** new_data = calloc(v->size, sizeof(void*));
    for (int i = 0; i < VectorSize(v); i++) {
        new_data[i] = v->data[i];
    }

    free(v->data);
    v->data = new_data;

    return val;
}

void* VectorGet(Vector *v, int i) {
    return v->data[i];
}

int VectorSize(Vector *v) {
    return v->size;
}

void VectorDestroy(Vector *v, void (*destroy)(void*)) {
    
    if (v->data) {
        for (int i = 0; i < VectorSize(v); i++) {
            destroy(v->data[i]);
        }
        free(v->data);
    }

    free(v);
}