#include "tDocumento.h"
#include <stdio.h>
#include <stdlib.h>

struct tDocumento {
    void* dado;
    func_ptr_imprimeNaTela imprimeNaTela;
    func_ptr_imprimeEmArquivo ImprimeEmArquivo;
    func_ptr_desaloca desaloca;
};

tDocumento *criaDocumento(void *dado, func_ptr_imprimeNaTela imprimeNaTela, func_ptr_imprimeEmArquivo ImprimeEmArquivo, func_ptr_desaloca desaloca) {

    tDocumento* doc = (tDocumento *) malloc(sizeof(tDocumento));
    if (doc == NULL) {
        printf("Erro na Alocacao do Documento\n");
        exit(EXIT_FAILURE);
    }

    doc->dado = dado;
    doc->imprimeNaTela = imprimeNaTela;
    doc->ImprimeEmArquivo = ImprimeEmArquivo;
    doc->desaloca = desaloca;

    return doc;
}   

void desalocaDocumento(tDocumento *doc) {
    doc->desaloca(doc->dado);
    free(doc);
}

void imprimeNaTelaDocumento(tDocumento *doc) {
    doc->imprimeNaTela(doc->dado);
}

void imprimeEmArquivoDocumento(tDocumento *doc, char *path) {
    doc->ImprimeEmArquivo(doc->dado, path);
}