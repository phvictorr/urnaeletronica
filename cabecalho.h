#ifndef CABECALHO_H_INCLUDED
#define CABECALHO_H_INCLUDED
#include "arvore.h"

*criaNo(Info *x);
void FAVazia(No **ppRaiz);
int insereTitulo(No **ppRaiz, Info *x);
int insereVoto(No **ppRaiz, Info *x);
void cadastraEleitor(No **arvoreTitulos);
void sucessor (No *q, No **r);
int retiraTitulo(No **ppRaiz, Info *x);
void descadastrarEleitor(No **arvoreTitulos);
void descadastrarEleitorVoto(No **arvoreVotos);
void imprimeEleitorVotados(Info eleitor);
void imprimirParciais(No *pRaiz);
void imprimeEleitor(Info);
void imprimir(No *arvoreVotos, Info eleitor);
void iniciarVotacao(No **arvoreVotos);
int pesquisaPeloTitulo(No *pRaiz, Info **pX);
int pesquisaPeloVoto(No *pRaiz, Info **pX);
int pesquisaSeVotou(No **arvoreTitulos);
void removeTodosElementosArvore(No **ppRaiz);
int numNos (No *pRaiz);

#endif
