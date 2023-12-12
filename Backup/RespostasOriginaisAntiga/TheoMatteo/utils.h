#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>



int CalculaIdade(char* data);
void ImprimeDataTela (char* data);
void ImprimeDataArquivo (char* data, FILE* file);


/// @brief Tela de impressao do menu principal do secretario ADMIN
void TelaImpressaoSecrADMIN();


/// @brief Tela de impressao do menu principal do secretario USER
void TelaImpressaoSecrUSER();


/// @brief Tela de impressao do menu principal do Medico
void TelaImpressaoMedico();


void TelaImprBuscaPacientes1();


void TelaImprBuscaPacientes2 ();

void ImprimeBarraConsultaMedica();

void ImprConsultaDadosPaciente (char* nome, char* cpf, char* dtNasc);

void ImprimeSucessoCadastro();

void ImprTelaConsultaMedica();

/// @brief Imprime uma barra final do menu '####'
void ImprimeBarraFinalMenu();


#endif