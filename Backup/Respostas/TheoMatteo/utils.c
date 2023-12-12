#include "utils.h"



int CalculaIdade(char* data) {

    int diaRef = 9, mesRef = 11, anoRef = 2023;

    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    int idade = anoRef - ano;
    if (mes > mesRef) idade--;
    else if (mes == mesRef && dia > diaRef) idade--;

    return idade;
}

void ImprimeDataTela (char* data) {
    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    printf("%d/%d/%d\n", dia, mes, ano);
}

void ImprimeDataArquivo (char* data, FILE* file) {
    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    fprintf(file, "%d/%d/%d\n", dia, mes, ano);
}


void TelaImpressaoSecrADMIN() {
    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(1) CADASTRAR SECRETARIO\n");
    printf("\t(2) CADASTRAR MEDICO\n");
    printf("\t(3) CADASTRAR PACIENTE\n");
    printf("\t(4) REALIZAR CONSULTA\n");
    printf("\t(5) BUSCAR PACIENTES\n");
    printf("\t(6) RELATORIO GERAL\n");
    printf("\t(7) FILA DE IMPRESSAO\n");
    printf("\t(8) FINALIZAR O PROGRAMA\n");
    ImprimeBarraFinalMenu();
}


void TelaImpressaoSecrUSER() {
    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(2) CADASTRAR MEDICO\n");
    printf("\t(3) CADASTRAR PACIENTE\n");
    printf("\t(5) BUSCAR PACIENTES\n");
    printf("\t(6) RELATORIO GERAL\n");
    printf("\t(7) FILA DE IMPRESSAO\n");
    printf("\t(8) FINALIZAR O PROGRAMA\n");
    ImprimeBarraFinalMenu();
    
}


void TelaImpressaoMedico() {
    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(4) REALIZAR CONSULTA\n");
    printf("\t(5) BUSCAR PACIENTES\n");
    printf("\t(6) RELATORIO GERAL\n");
    printf("\t(7) FILA DE IMPRESSAO\n");
    printf("\t(8) FINALIZAR O PROGRAMA\n");
    ImprimeBarraFinalMenu();
}

void TelaImprBuscaPacientes1 () {
    printf("#################### BUSCAR PACIENTES #######################\n");
    printf("NOME DO PACIENTE: ");
}

void TelaImprBuscaPacientes2 () {
    printf("#################### BUSCAR PACIENTES #######################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(1) ENVIAR LISTA PARA IMPRESSAO\n");
    printf("\t(2) RETORNAR AO MENU PRINCIPAL\n");
}

void ImprimeBarraConsultaMedica() {
    printf("#################### CONSULTA MEDICA #######################\n");
}

void ImprConsultaDadosPaciente (char* nome, char* cpf, char* dtNasc) {
    ImprimeBarraConsultaMedica();
    printf("CPF DO PACIENTE: %s\n", cpf);
    printf("- - -\n");
    printf("- NOME: %s\n", nome);
    printf("- DATA DE NASCIMENTO: %s\n", dtNasc);
    printf("- - -\n");
}

void ImprTelaConsultaMedica() {
    ImprimeBarraConsultaMedica();
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(1) CADASTRAR LESAO\n");
    printf("\t(2) GERAR RECEITA MEDICA\n");
    printf("\t(3) SOLICITACAO DE BIOPSIA\n");
    printf("\t(4) ENCAMINHAMENTO\n");
    printf("\t(5) ENCERRAR CONSULTA\n");
}

void ImprimeSucessoCadastro() {
    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
}

void ImprimeBarraFinalMenu() {
    printf("###############################################################\n");
}

void ImprimeTelaFiladeImpressao() {
    printf("################### FILA DE IMPRESSAO MEDICA #####################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(1) EXECUTAR FILA DE IMPRESSAO\n");
    printf("\t(2) RETORNAR AO MENU ANTERIOR\n");
}