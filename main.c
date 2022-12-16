#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main()
{
	FAVazia(&arvoreTitulos);
    printf("**** SISTEMA DE VOTACAO ****\n\n");
    int opcao, i, nos;
    do{
        printf("\n1 - Cadastrar um titulo\n2 - Descadastrar um titulo\n3 - Iniciar nova votacao\n4 - Votar\n5 - Retirar voto\n6 - Mostrar parcial\n7 - Listar titulos e nomes de quem ja votou\n8 - Encerrar\n\n");
        printf("\nDigite uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                cadastraEleitor(&arvoreTitulos);
                break;
            case 2:
                descadastrarEleitor(&arvoreTitulos);
                break;
            case 3:
                iniciarVotacao(&arvoreVotos);
                break;
            case 4:
                pesquisaSeVotou(&arvoreTitulos, &arvoreVotos);
                break;
            case 5:
                descadastrarEleitorVoto(&arvoreVotos);
                break;
            case 6:
                imprimirParciais(arvoreVotos);
                break;
            case 7:
                imprimir(arvoreTitulos);
                break;
            case 8:
                removeTodosElementosArvore(&arvoreTitulos);
				removeTodosElementosArvore(&arvoreVotos);
				FAVazia(&arvoreTitulos);
				FAVazia(&arvoreVotos);
                break;
            case 9:
                nos = numNos(arvoreTitulos);
                printf("\nNumero de nos arvore Titulos: %d\n", nos);
                nos = numNos(arvoreVotos);
                printf("Numero de nos arvore Votos: %d\n", nos);
                break;
            default:
                printf("Erro: Digite uma opcao valida.\n\n");
        }

    }while(opcao != 8);
    return 0;
}
