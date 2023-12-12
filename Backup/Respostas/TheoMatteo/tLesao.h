#ifndef _TLESAO_H_
#define _TLESAO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tMedico.h"
#include "utils.h"


#define TAM_MAX_DIAGNOSTICO 50
#define TAM_MAX_REGIAO_CORPO 25
#define TAM_MAX_ROTULO 5

typedef struct tLesao tLesao;


/// @brief Cadastra uma nova lesao e copia informacoes passadas
/// @param numRotulo 
/// @param cpfPaciente 
/// @param cpfMedico 
/// @param CRM 
/// @param data 
/// @return lesao
tLesao* CadastraLesao (int numRotulo, char* cpfPaciente, char* cpfMedico, char* CRM, char* data);


/// @brief Salva lesao em um arquivo binario
/// @param l 
/// @param file 
void SalvaLesaoArquivoBinario (tLesao* l, FILE* file);


/// @brief Obtem lesao de um arquivo binario 
/// @param file 
/// @return lesao
tLesao* ObtemLesaoArquivoBinario (FILE* file);


/// @brief Verifica se uma lesao foi encaminhada para cirurgia
/// @param l 
/// @return true or false
bool LesaoFoiEncaminhadaPraCirurgia (tLesao* l);


/// @brief Verifica se uma lesao foi encaminhada para a crioterapia
/// @param l 
/// @return true or false
bool LesaoFoiEncaminhaCrioterapia (tLesao* l);


/// @brief Clona todas informacoes de uma lesao
/// @param l 
/// @return lesao clonada
tLesao* ClonaLesao (tLesao* l);


/// @brief Obtem diagnostico da lesao
/// @param l 
/// @return diagnostico lesao
char* ObtemDiagnosticoLesao (tLesao* l);


/// @brief Obtem tamanho da lesao
/// @param l 
/// @return tamanho lesao
int ObtemTamanhoLesao (tLesao* l);


/// @brief Obtem regiao do corpo lesao
/// @param l 
/// @return regiao do corpo
char* ObtemRegiaoCorpoLesao (tLesao* l);


/// @brief Obtem rotulo da lesao
/// @param l 
/// @return rotulo da lesao
char* ObtemRotuloLesao (tLesao* l);


/// @brief Desaloca memoria de uma lesao 
void DesalocaLesao (tLesao*);

#endif