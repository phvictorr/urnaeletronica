#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

pos = 0;

// CRIAR NO
No *criaNo(Info *x){
	No *novo = (No*) malloc(sizeof(Info));
	// Define quantidade de votos como 0;
	x->quantidade_votos = 0;
	// Se recebeu voto, define como 0 para depois definir como 1
	x->recebeu_voto = 0;
	// Declara voto como 0
	novo->dir = NULL;
	novo->esq = NULL;
	novo->info = x;
}


// Definir arvore como vazia
void FAVazia(No **ppRaiz){
	*ppRaiz = NULL;
}

// Inserir Titulo
int insereTitulo(No **ppRaiz, Info *x){
	if (*ppRaiz == NULL){
		*ppRaiz = criaNo(x);
		return 1;
	}

	if (x->titulo_eleitor < (*ppRaiz)->info->titulo_eleitor){
		return insereTitulo(&((*ppRaiz)->esq), x);
	}

	if (x->titulo_eleitor > (*ppRaiz)->info->titulo_eleitor){
		return insereTitulo(&((*ppRaiz)->dir), x);
	}

	return 0;
}

// Inserir Voto
int insereVoto(No **ppRaiz, Info *x){

    if (*ppRaiz == NULL){
		*ppRaiz = criaNo(x);
		(*ppRaiz)->info->recebeu_voto = 1;
		return 1;
	}

	// Se a chave voto for igual ao elemento recebido, incrementar na quantidade de voto
	if((*ppRaiz)->info->voto == x->voto){
        (*ppRaiz)->info->quantidade_votos++;
        (*ppRaiz)->info->recebeu_voto = 1; // e, alem disso, definir "recebeu_voto" como 1, para entao imprimir
    }

    if (x->titulo_eleitor < (*ppRaiz)->info->titulo_eleitor){
		return insereVoto(&((*ppRaiz)->esq), x);
	}

	if (x->titulo_eleitor > (*ppRaiz)->info->titulo_eleitor){
		return insereVoto(&((*ppRaiz)->dir), x);
	}

	return 0;
}

// Cadastro de eleitor
void cadastraEleitor(No **arvoreTitulos){
    Info *eleitor = (Info*) malloc (sizeof(Info));
	int titulo;
	printf("\nDigite o nome do Eleitor: ");
	fflush(stdin);
	gets(eleitor->Nome);
	printf("Digite o Titulo do Eleitor: ");
	scanf("%d", &eleitor->titulo_eleitor);
	titulo = insereTitulo(arvoreTitulos, eleitor);

	if (titulo == 0){
        printf("\nErro: Esse titulo ja consta como cadastrado. Tente novamente!\n");
	}else {
		printf("\nO eleitor '%s' foi cadastrado. \n", eleitor->Nome);
	}
}

// Procurar sucessor
void sucessor (No *q, No **r){
	No *pAux;

	if ((*r)->esq != NULL)
	{
		sucessor(q, &(*r)->esq);
		return;
	}

	q->info = (*r)->info;
	pAux = *r;
	*r = (*r)->dir;
	free(pAux);
}

// Remover titulo de eleitor
int retiraTitulo(No **ppRaiz, Info *x){
    No *pAux;

	if (*ppRaiz == NULL){
		return 0;
	}

	if ((*x).titulo_eleitor < (*ppRaiz)->info->titulo_eleitor){
		return retiraTitulo(&(*ppRaiz)->esq, x);
	}

	if ((*x).titulo_eleitor > (*ppRaiz)->info->titulo_eleitor){
		return retiraTitulo(&(*ppRaiz)->dir, x);
	}


	if ((*ppRaiz)->dir == NULL){
		pAux = *ppRaiz;
		*ppRaiz = (*ppRaiz)->esq;
		*x = *(pAux->info);
		free(pAux);
		return 1;
	}

	if ((*ppRaiz)->esq == NULL){
		pAux = *ppRaiz;
		*ppRaiz = (*ppRaiz)->dir;
		*x = *(pAux->info);
		free(pAux);
		return 1;
	}

	sucessor(*ppRaiz, &(*ppRaiz)->dir);
	return 1;
}

// Descadastrar eleitor da arvore de Titulos
void descadastrarEleitor(No **arvoreTitulos){
    Info *eleitor = (Info*) malloc(sizeof(Info));
	int titulo;
	printf("\nDigite titulo que deseja remover: ");
	scanf("%d", &eleitor->titulo_eleitor);
	titulo = retiraTitulo(arvoreTitulos, eleitor);

	if (titulo == 1) {
		printf("\nTitulo %d foi removido com sucesso. \n", eleitor->titulo_eleitor);
	} else{
		printf("\nErro: Titulo %d nao encontrado! \n", eleitor->titulo_eleitor);
	}
}

// Descadastrar eleitor e Voto na Arvore de Votos
void descadastrarEleitorVoto(No **arvoreVotos){
    Info *eleitor = (Info*) malloc(sizeof(Info));
	int titulo;
	printf("\nDigite seu titulo para remover seu voto: ");
	scanf("%d", &eleitor->titulo_eleitor);
	titulo = retiraTitulo(arvoreVotos, eleitor);

	if (titulo == 1) {
		printf("\nVoto do titulo %d foi removido com sucesso. \n", eleitor->titulo_eleitor);
	} else{
		printf("\nErro: Titulo %d nao encontrado! \n", eleitor->titulo_eleitor);
	}
}

// Imprimir votados
void imprimeEleitorVotados(Info eleitor){
        if(eleitor.recebeu_voto == 1){
                printf("\n............................\n");
                printf("\nTitulo de eleitor: %d", eleitor.voto);
                printf("\nQuantidade de votos: %d\n............................", eleitor.quantidade_votos+1);
                printf("\n");
        }
}

// Procedimento para imprimir recursivamente
void imprimirParciais(No *pRaiz){
	if (pRaiz != NULL)
	{
	    imprimirParciais(pRaiz->esq);
	    imprimeEleitorVotados(*(pRaiz->info));
		imprimirParciais(pRaiz->dir);
	}
}

// Imprimir eleitores que ja votaram
void imprimeEleitor(Info eleitor){
        //Se o voto do eleitor estiver em "0", ele ainda nao votou, portanto, nao ira imprimir.
        printf("\n............................\n");
        printf("\nNome: %s", eleitor.Nome);
        printf("\nTitulo de Eleitor: %d\n............................", eleitor.titulo_eleitor);
        printf("\n");
}

// Procedimento para imprimir recursivamente eleitores que ja votaram
void imprimir(No *pRaiz){
	if (pRaiz != NULL)
	{
		imprimir(pRaiz->esq);
		imprimeEleitor(*(pRaiz->info));
		imprimir(pRaiz->dir);
	}
}

// Procedimento para iniciar votacao
void iniciarVotacao(No **arvoreVotos){
    FAVazia(&arvoreVotos);
    printf("\nINICIANDO URNA [...]\n");
    printf("VERIFICANDO SISTEMAS DE SEGURANCA [...]\n");
    if(arvoreVotos == NULL){
        printf("A urna foi iniciada e esta pronta para votar.\n");
    }else{
        printf("Ocorreu um erro ao iniciar a urna.");
    }
}

// Pesquisar pelo titulo
int pesquisaPeloTitulo(No *pRaiz, Info **pX){
	if (pRaiz == NULL){
		return 0;
	}

	if ((*pX)->titulo_eleitor < pRaiz->info->titulo_eleitor)
	{
		return pesquisaPeloTitulo(pRaiz->esq, pX);
	}

	if ((*pX)->titulo_eleitor > pRaiz->info->titulo_eleitor)
	{
		return pesquisaPeloTitulo(pRaiz->dir, pX);
	}

	*pX = pRaiz->info;
	return 1;
}

// Pesquisar pelo voto
int pesquisaPeloVoto(No *pRaiz, Info **pX){
	if (pRaiz == NULL){
		return 0;
	}

	if ((*pX)->titulo_eleitor < pRaiz->info->titulo_eleitor)
	{
		return pesquisaPeloVoto(pRaiz->esq, pX);
	}

	if ((*pX)->titulo_eleitor > pRaiz->info->titulo_eleitor)
	{
		return pesquisaPeloVoto(pRaiz->dir, pX);
	}

	*pX = pRaiz->info;
	return 1;
}

// Pesquisa se votou e inserir votos
void pesquisaSeVotou(No **arvoreTitulos, No **arvoreVotos){
	Info *eleitor = (Info*) malloc(sizeof(Info));
	Info *aux = (Info*) malloc(sizeof(Info));
	int i, insere, titulo, voto, numero;
    printf("\nDigite o seu titulo: ");
	scanf("%d", &eleitor->titulo_eleitor);
	printf("Digite seu voto: (titulo do votante): ");
    scanf("%d", &eleitor->voto);

    // Aux recebe voto e inverte para titulo de eleitor, para poder comparar e inserir a quantidade de votos posteriormente
    aux->titulo_eleitor = eleitor->voto;
    numero = eleitor->voto;

    //nome(&arvoreTitulos, voto);
    insere = insereVoto(arvoreVotos, eleitor);

    if(insere == 0){
        printf("\nErro: Titulo ja registrou um voto\n");
    }else{
        // Buscar se o titulo de eleitor existe na arvore de titulos
        titulo = pesquisaPeloTitulo(&arvoreTitulos, &eleitor);
        // Verificar se o titulo votado existe na base de dados
        voto = pesquisaPeloVoto(&arvoreTitulos, &aux);

        if(titulo == 1 && voto == 1){
            printf("\nO voto '%d' foi computado. \n", numero);
        }else if(titulo == 0 && voto == 1){
            retiraTitulo(arvoreVotos, eleitor);
            printf("\nErro: Titulo usado para votar esta invalido ou nao existe.\n");
        }else if(titulo == 1 && voto == 0){
            retiraTitulo(arvoreVotos, eleitor);
            printf("\nErro: Voto invalido. Digite um numero valido ou nao existe concorrente com esse titulo.\n");
        }else{
            retiraTitulo(arvoreVotos, eleitor);
            printf("\nErro: Titulo do voto e do votante estao invalidos.\n");
        }
    }
}

// Remover todos os elementos da arvore
void removeTodosElementosArvore(No **ppRaiz){
    if((*ppRaiz) == NULL){
        return;
    }

    if((*ppRaiz)->esq != NULL){
        removeTodosElementosArvore(&(*ppRaiz)->esq);
    }

    if((*ppRaiz)->dir != NULL ){
        removeTodosElementosArvore(&(*ppRaiz)->dir);
    }

    free((*ppRaiz));

    return;
}

// Contar os nos presentes na arvore (usado de forma oculta)
int numNos (No *pRaiz){
    if (pRaiz == NULL)
    {
        return 0;
    } else
    {
        return 1 + numNos(pRaiz->esq) + numNos(pRaiz->dir);
    }
}
