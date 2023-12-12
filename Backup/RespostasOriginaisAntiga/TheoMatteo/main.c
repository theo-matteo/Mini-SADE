#include "tSistema.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {

    if (argc <= 1) {
        printf("O diretorio nao foi informado!\n");
        exit(EXIT_FAILURE);
    }

    tSistema* sistema = CriaSistema(argv[1]);
    ExecutaSistema(sistema);
    DesalocaSistema(sistema);


    return EXIT_SUCCESS;
}