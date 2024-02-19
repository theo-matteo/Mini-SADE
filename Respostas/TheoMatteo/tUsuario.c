#include "tUsuario.h"

struct tUsuario {
    void* userPtr; 
    telaImpressao telaImp;
    DesalocaUsuario desalocaUserFunc;
    tipoUsuario type; 
};

tUsuario* CriaUsuarioSistema (void* user, telaImpressao telaImpr, DesalocaUsuario desalocaUser, tipoUsuario type) {

    tUsuario* usuario = (tUsuario*) malloc(sizeof(tUsuario));
    if (usuario == NULL) {
        printf("Falha na alocacao do usuario\n");
        exit(EXIT_FAILURE);
    }

    usuario->userPtr = user;
    usuario->telaImp = telaImpr;
    usuario->desalocaUserFunc = desalocaUser;
    usuario->type = type;

    return usuario;
}

void DesalocaUsuarioSistema (tUsuario* user) {
    if (!user) return;
    user->desalocaUserFunc(user->userPtr);
    free(user);
}

tipoUsuario ObtemTipoUsuarioSistema(tUsuario* user) {
    return user->type;
}

void* ObtemUsuarioSistema (tUsuario* user) {
    return user->userPtr;
}

void ImprimeMenuPrincipalUsuario (tUsuario* user) {
    user->telaImp();
}