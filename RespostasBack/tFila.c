#include "tFila.h"
#include <stdio.h>
#include <stdlib.h>

struct tFila {
    tDocumento** documentos;
    int qtdDocumentos;
};

tFila *criaFila() {

    tFila* fila = (tFila *) malloc(sizeof(tFila));
    if (fila == NULL) {
        printf("Falha na Alocacao da Fila de Documentos\n");
        exit(EXIT_FAILURE);
    }

    fila->documentos = NULL;
    fila->qtdDocumentos = 0;

    return fila;
}

void desalocaFila(tFila *f) {

    if (f == NULL) return;

    if (f->documentos) {
        for (int i = 0; i < quantidadeDocumentosNaFila(f); i++) {
            if (f->documentos[i]) desalocaDocumento(f->documentos[i]);
        }
        free(f->documentos);
    }

    free(f);
}

void insereDocumentoFila(tFila *f, void *dado, func_ptr_imprimeNaTela imprimeNaTela, func_ptr_imprimeEmArquivo ImprimeEmArquivo, func_ptr_desaloca desaloca) {
    f->qtdDocumentos++;
    f->documentos = realloc(f->documentos, f->qtdDocumentos * sizeof(tDocumento *));
    f->documentos[f->qtdDocumentos - 1] = criaDocumento(dado, imprimeNaTela, ImprimeEmArquivo, desaloca);
}

int quantidadeDocumentosNaFila(tFila *f) {
    return f->qtdDocumentos;
}

void imprimeFila(tFila *f, char *path) {
    for (int i = 0; i < quantidadeDocumentosNaFila(f); i++) {
        tDocumento* doc = f->documentos[i];
        imprimeNaTelaDocumento(doc);
        imprimeEmArquivoDocumento(doc, path);
    }
}