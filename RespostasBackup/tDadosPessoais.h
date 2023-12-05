#ifndef _TDADOSPESSOAIS_H_
#define _TDADOSPESSOAIS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct tDadosPessoais tDadosPessoais;

/// @brief Le dados de uma DadosPessoais da entrada padrao (teclado)
/// @param  DadosPessoais
tDadosPessoais* LeDadosPessoais();


/// @brief Retorna um ponteiro do tipo dadospessoais com informacoes fornecidas por parametro
/// @param nome nome
/// @param cpf cpf
/// @param dtNasc data nascimento
/// @param tel telefone
/// @param genero genero
/// @return dados pessoais
tDadosPessoais* CriaDadosPessoais (char* nome, char* cpf, char* dtNasc, char* tel, char* genero);


/// @brief Desaloca DadosPessoais
/// @param  DadosPessoais
void DesalocaDadosPessoais(tDadosPessoais*);


/// @brief Salva dados pessoais em um arquivo binario
/// @param d dados pessoais
/// @param file arquivo
void SalvaDadosPessoaisArquivoBinario (tDadosPessoais* d, FILE* file);


/// @brief Le um arquivo binario contendo informacoes (dados pessoais) e retorna estrutura
/// @param  arquivo
/// @return dados pessoais
tDadosPessoais* ObtemDadosPessoaisArquivoBinario (FILE*);


bool CPFsaoIguais (char* cpf, tDadosPessoais* d);

/// @brief Obtem nome da pessoa
/// @param  dadosPessoais
/// @return retorna ponteiro do nome da pessoa
char* ObtemNomeDadosP(tDadosPessoais*);

/// @brief Obtem CPF da pessoa
/// @param  dadosPessoais
/// @return retorna ponteiro do CPF da pessoa
char* ObtemCPFDadosP(tDadosPessoais*);

/// @brief  Obtem Data de Nascimento da pessoa
/// @param  dadosPessoais
/// @return retorna ponteiro da Data de Nascimento da pessoa
char* ObtemDtNascDadosP(tDadosPessoais*);

/// @brief Obtem Telefone da pessoa
/// @param  dadosPessoais
/// @return retorna ponteiro do Telefone da pessoa
char* ObtemTelDadosP(tDadosPessoais*);

/// @brief Obtem genero da pessoa
/// @param  dadosPessoais
/// @return retorna ponteiro do genero da pessoa
char* ObtemGeneroDadosP(tDadosPessoais*);


#endif