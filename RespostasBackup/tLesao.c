#include "tLesao.h"

struct tLesao {
    char rotulo[TAM_MAX_ROTULO];
    char diagnostico[TAM_MAX_DIAGNOSTICO];
    char regiao_corpo [TAM_MAX_REGIAO_CORPO];
    int tamanho;
    int enviar_cirurgia;
    int enviar_crioterapia;
}; 

tLesao* CadastraLesao () {

    tLesao* lesao = (tLesao*) malloc(sizeof(tLesao));
    if (lesao == NULL) {
        printf("Falha na Alocacao da Lesao\n");
        exit(EXIT_FAILURE);
    }

    memset(lesao->rotulo, '\0', TAM_MAX_ROTULO);
    memset(lesao->diagnostico, '\0', TAM_MAX_DIAGNOSTICO);
    memset(lesao->regiao_corpo, '\0', TAM_MAX_REGIAO_CORPO);

    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CADASTRO DE LESAO:\n");

    printf("DIAGNOSTICO CLINICO: ");
    scanf("%s", lesao->diagnostico);

    printf("REGIAO DO CORPO: ");
    scanf("%s", lesao->regiao_corpo);

    printf("TAMANHO: ");
    scanf("%d", &lesao->tamanho);

    printf("ENVIAR PARA CIRURGIA: ");
    scanf("%d", &lesao->enviar_cirurgia);

    printf("ENVIAR PARA CRIOTERAPIA: ");
    scanf("%d", &lesao->enviar_crioterapia);

    printf("LESAO REGISTRADA COM SUCESSO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    char c; scanf("%c%*c", &c);
    printf("############################################################\n");

    return lesao;
}

void DesalocaLesao (tLesao* l) {
    if (l) free(l);
}

