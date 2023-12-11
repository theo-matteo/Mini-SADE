#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Funcoes Auxiliares do Sistema */


/// @brief Calcula idade de uma pessoa a partir de uma data
/// @param data 
/// @return idade
int CalculaIdade(char* data);


/// @brief Imprime data na tela com a formatacao adequada 
/// @param data 
void ImprimeDataTela (char* data);


/// @brief Imprime a data em um arquivo com a formatacao adequada 
/// @param data 
/// @param file 
void ImprimeDataArquivo (char* data, FILE* file);


/// @brief Tela de impressao do menu principal do secretario ADMIN
void TelaImpressaoSecrADMIN();


/// @brief Tela de impressao do menu principal do secretario USER
void TelaImpressaoSecrUSER();


/// @brief Tela de impressao do menu principal do Medico
void TelaImpressaoMedico();


/// @brief Tela de busca de pacientes
void TelaImprBuscaPacientes1();


/// @brief Sub-menu da busca de pacientes
void TelaImprBuscaPacientes2 ();


/// @brief Imprime barra de consulta medica
void ImprimeBarraConsultaMedica();


/// @brief Imprime dados de um paciente apos busca por cpf
/// @param nome 
/// @param cpf 
/// @param dtNasc 
void ImprConsultaDadosPaciente (char* nome, char* cpf, char* dtNasc);


/// @brief Imprime mensagem de sucesso apos o cadastrado
void ImprimeSucessoCadastro();


/// @brief Imprime tela de consulta medica
void ImprTelaConsultaMedica();


/// @brief Imprime tela da fila de impressao
void ImprimeTelaFiladeImpressao();


/// @brief Imprime uma barra final do menu '####'
void ImprimeBarraFinalMenu();


#endif