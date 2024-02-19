#ifndef _DATA_STRUCTURES_VECTOR_H_
#define _DATA_STRUCTURES_VECTOR_H_


typedef struct Vector Vector;


/// @brief Cria um vetor vazio
/// @return Vector inicializado
Vector *VectorConstruct();


/// @brief Adiciona um elemento na posicao final do vetor
/// @param v (ponteiro para o vetor)
/// @param val (valor a ser adicionado)
void VectorPushBack(Vector *v, void* val);


/// @brief Remove o primeiro elemento do vetor e organiza os demais
/// @param v ponteiro para o vetor
/// @return elemento removido
void* VectorPopFront(Vector *v);


/// @brief Retorna o i-esimo elemento do vetor
/// @param v ponteiro para o vetor
/// @param i indice do elemento
/// @return void* elemento do vetor
void* VectorGet(Vector *v, int i);


/// @brief Retorna o tamanho do vetor
/// @param v ponteiro para o vetor
/// @return tamanho do vetor
int VectorSize(Vector *v);

/// @brief Desaloca memoria de um vetor
/// @param v ponteiro para o vetor
/// @param destroy funcao que desaloca memoria de cada elemento do vetor
void VectorDestroy(Vector *v, void (*destroy)(void*));


#endif
