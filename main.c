#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BrasfootIME.h"


int main() {
    CadastroClube *clubes = NULL;
    CadastroCompeticoes *competicoes = NULL;
    int TamanhoClube = 0, TamanhoCompeticoes = 0;
    int opcao;

    do {
        system("clear || cls"); // Limpar a tela

        printf("\n---- MENU ----\n");
        printf("1. Cadastrar Clube\n");
        printf("2. Cadastrar Competicao\n");
        printf("3. Gerar Relatorio\n");
        printf("4. Salvar Dados\n");
        printf("5. Carregar Dados\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        opcao = lerInt();

        switch(opcao) {
            case 1:
                cadastrarClube(&clubes, &TamanhoClube, competicoes, TamanhoCompeticoes);
                break;
            case 2:
                cadastrarCompeticao(&competicoes, &TamanhoCompeticoes);
                break;
            case 3:
                gerarRelatorio(clubes, competicoes, TamanhoClube, TamanhoCompeticoes);
                break;
            case 4:
                salvarDados(clubes, competicoes, TamanhoClube, TamanhoCompeticoes);
                break;
            case 5:
                carregarDados(&clubes, &competicoes, &TamanhoClube, &TamanhoCompeticoes);
                break;
            case 6:
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
        printf("\nPressione Enter para continuar...");
        getchar();
    } while (opcao != 0);

    free(clubes);
    free(competicoes);

    return 0;
}
