#ifndef _TUSUARIO_H_
#define _TUSUARIO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tUsuario tUsuario;
typedef void (*telaImpressao)(void);
typedef void (*DesalocaUsuario)(void *);


typedef enum {
    M, // Medico
    S_ADMIN, // Secretario ADMIN
    S_USER // Secretario USER
} tipoUsuario;


/// @brief Cria novo usuario que ira utilizar o sistema
/// @param user ponteiro generico para o usuario
/// @param telaImpr tela de impressao do menu principal
/// @param desalocaUser desaloca memoria da estrutura do usuario
/// @param tipoUsuario tipo de usuario (medico ou secretario)
/// @return usuario alocado
tUsuario* CriaUsuarioSistema (void* user, telaImpressao telaImpr, DesalocaUsuario desalocaUser, tipoUsuario type);


/// @brief Desaloca memoria de um usuario 
/// @param  usuario
void DesalocaUsuarioSistema (tUsuario*);


/// @brief Obtem o tipo de usuario que esta utilizando o sistema
/// @param  usuario 
/// @return tipo do usuario
tipoUsuario ObtemTipoUsuarioSistema(tUsuario*);


/// @brief Imprime o menu principal baseado no tipo de usuario
/// @param  Usuario
void ImprimeMenuPrincipalUsuario (tUsuario*);


/// @brief Obtem o usuario que esta logado no sistema
/// @param  usuario
/// @return ponteiro desse usuario
void* ObtemUsuarioSistema (tUsuario*);


/// @brief Verifica se o usuario escolheu uma opcao valida
/// @param  usuario
/// @param  opcao
/// @return true or false
bool UsuarioEscolheuOpcaoValida (tUsuario*, int);

#endif