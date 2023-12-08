#include "tLesao.h"

struct tLesao {
    char rotulo[TAM_MAX_ROTULO];
    char diagnostico[TAM_MAX_DIAGNOSTICO];
    char regiao_corpo [TAM_MAX_REGIAO_CORPO];
    int tamanho;
    int enviar_cirurgia;
    int enviar_crioterapia;
}; 

tLesao* CriaLesao () {

    tLesao* lesao = (tLesao*) malloc(sizeof(tLesao));
    if (lesao == NULL) {
        printf("Falha na Alocacao da Lesao\n");
        exit(EXIT_FAILURE);
    }

    memset(lesao->diagnostico, '\0', TAM_MAX_DIAGNOSTICO);
    memset(lesao->regiao_corpo, '\0', TAM_MAX_REGIAO_CORPO);


    return lesao;
}


tLesao* CadastraLesao (int numRotulo) {

    tLesao* lesao = CriaLesao();

    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CADASTRO DE LESAO:\n");

    sprintf(lesao->rotulo, "L%d", numRotulo);

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

tLesao* ClonaLesao (tLesao* l) {

    // Cria um clone
    tLesao* lesao = CriaLesao();

    strcpy(lesao->diagnostico, l->diagnostico);
    strcpy(lesao->regiao_corpo, l->regiao_corpo);
    strcpy(lesao->rotulo, l->rotulo);    

    lesao->tamanho = l->tamanho;
    lesao->enviar_cirurgia = l->enviar_cirurgia;
    lesao->enviar_crioterapia = l->enviar_crioterapia;

    return lesao;
}

char* ObtemDiagnosticoLesao (tLesao* l) {
    return l->diagnostico;
}

int ObtemTamanhoLesao (tLesao* l) {
    return l->tamanho;
}

char* ObtemRegiaoCorpoLesao (tLesao* l) {
    return l->regiao_corpo;
}


bool LesaoFoiEncaminhadaPraCirurgia (tLesao* l) {
    return (l->enviar_cirurgia == 1);
}

char* ObtemRotuloLesao (tLesao* l) {
    return l->rotulo;
}


void DesalocaLesao (tLesao* l) {
    if (l) free(l);
}

