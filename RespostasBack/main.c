#include "tSistema.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {


    tSistema* sistema = CriaSistema(argv[1]);
    IniciaSistema(sistema);
    DesalocaSistema(sistema);

    return EXIT_SUCCESS;
} 