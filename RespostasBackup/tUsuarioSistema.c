#include "tUsuarioSistema.h"


struct tUsuarioSistema {
    void* userPtr; 
    telaImpressao telaImp;
    DesalocaUsuario desalocaUserFunc;
    userType tipoUser; 
};

tUsuarioSistema* CriaUsuarioSistema (void* user, telaImpressao telaImpr, DesalocaUsuario desalocaUser, userType tipoUsuario) {

    tUsuarioSistema* usuario = (tUsuarioSistema*) malloc(sizeof(tUsuarioSistema));
    if (usuario == NULL) {
        printf("Falha na alocacao do usuario\n");
        exit(EXIT_FAILURE);
    }

    usuario->userPtr = user;
    usuario->telaImp = telaImpr;
    usuario->desalocaUserFunc = desalocaUser;
    usuario->tipoUser = tipoUsuario;

    return usuario;
}

void DesalocaUsuarioSistema (tUsuarioSistema* user) {
    if (!user) return;
    user->desalocaUserFunc(user->userPtr);
    free(user);
}

userType ObtemTipoUsuarioSistema(tUsuarioSistema* user) {
    return user->tipoUser;
}

void ImprimeMenuPrincipalUsuario (tUsuarioSistema* user) {
    user->telaImp();
}

bool UsuarioEscolheuOpcaoValida (tUsuarioSistema* user, int opcao) {

    if (ObtemTipoUsuarioSistema(user) == S_USER) {
        if (opcao == 1 || opcao == 4) return false;
    }
    else if (ObtemTipoUsuarioSistema(user) == MEDICO) {
        if (opcao < 4) return false;
    }

    return true;
}