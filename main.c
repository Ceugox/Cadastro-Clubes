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
        printf("6. Remover Clube\n");
        printf("7. Remover Competicao\n");
        printf("8. Sair\n");
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
                if (TamanhoClube > 0) {
                    printf("Digite o código do clube a remover: ");
                    int codigoClube = lerInt();
                    removerClube(&clubes, &competicoes, &TamanhoClube, &TamanhoCompeticoes, codigoClube);
                } else {
                    printf("Nenhum clube cadastrado.\n");
                }
                break;
            case 7:
                if (TamanhoCompeticoes > 0) {
                    printf("Digite o código da competição a remover: ");
                    int codigoComp = lerInt();
                    removerCompeticao(&competicoes, &TamanhoCompeticoes, codigoComp);
                } else {
                    printf("Nenhuma competição cadastrada.\n");
                }
                break;
            case 8:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
        if (opcao != 8) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }
    } while (opcao != 8);

    // Liberar memória
    for (int i = 0; i < TamanhoCompeticoes; i++) {
        free(competicoes[i].clubesParticipantes);
    }
    free(clubes);
    free(competicoes);

    return 0;
}
