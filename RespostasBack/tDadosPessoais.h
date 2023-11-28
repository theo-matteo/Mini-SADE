#ifndef _TDADOSPESSOAIS_H_
#define _TDADOSPESSOAIS_H_

#define TAM_NOME 100
#define TAM_CPF 12
#define TAM_DATA 16
#define TAM_TELEFONE 16

typedef struct tDadosPessoais tDadosPessoais;


/// @brief Retorna um ponteiro da estrutura pessoa
/// @return pessoa
tDadosPessoais* CriaDadosPessoais ();


/// @brief Le dados de uma DadosPessoais da entrada padrao (teclado)
/// @param  DadosPessoais
void LeDadosPessoais(tDadosPessoais*);


/// @brief Desaloca DadosPessoais
/// @param  DadosPessoais
void DesalocaDadosPessoais(tDadosPessoais*);


#endif