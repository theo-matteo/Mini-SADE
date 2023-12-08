#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


/// @brief Abre um arquivo binario (no modo append) dado um caminho e o nome do arquivo
/// @param path caminho onde o arquivo ficara
/// @param filename nome do arquivo
/// @return arquivo aberto
FILE* AbreArquivoBinario(char* path, char* filename);


/// @brief Verifica se um arquivo foi recem-criado (vazio)
/// @param file arquivo
/// @return verdadeiro ou falso
bool ArquivoEstaVazio (FILE* file);


/// @brief Tela de impressao do menu principal do secretario ADMIN
void TelaImpressaoSecrADMIN();


/// @brief Tela de impressao do menu principal do secretario USER
void TelaImpressaoSecrUSER();


/// @brief Tela de impressao do menu principal do Medico
void TelaImpressaoMedico();


#endif