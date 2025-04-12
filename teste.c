#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMPETICOES 10

// Estruturas (anteriormente em BrasfootIME.h)
typedef struct TipoClubes {
    int codigoClube; // 5 digitos
    char nomeClube[50];
    char maiorJogador[50];
    int anoFund;
    char competicoes[MAX_COMPETICOES][50]; // Lista de competicoes em que o clube participa
    int qtdCompeticoes; // Numero de competicoes que o clube participa
} CadastroClube;

typedef struct TipoCompeticoes {
    int codigoCompeticao; // 4 digitos
    char nomeCompeticao[50];
    char paisSede[50];
    char artilheiro[50];
    CadastroClube *clubesParticipantes; // Lista de clubes que participam da competicao
    int qtdClubes; // Numero de clubes participantes na competicao
} CadastroCompeticoes;

typedef struct Temporadas {
    int ano; // Ano da temporada (ex.: 2024)
    char competicao[50]; // Nome da competição
    char clube[50]; // Nome do clube
} Temporada;

// Protótipos das funções (anteriormente em BrasfootIME.h)
int lerInt();
void cadastrarClube(CadastroClube **clubes, int *tamanhoClube, CadastroCompeticoes *competicoes, int tamanhoCompeticoes);
void cadastrarCompeticao(CadastroCompeticoes **competicoes, int *tamanhoCompeticoes);
void gerarRelatorio(CadastroClube *clubes, CadastroCompeticoes *competicoes, int TamanhoClube, int TamanhoCompeticoes);
void salvarDados(CadastroClube *clubes, CadastroCompeticoes *competicoes, int TamanhoClube, int TamanhoCompeticoes);
void carregarDados(CadastroClube **clubes, CadastroCompeticoes **competicoes, int *TamanhoClube, int *TamanhoCompeticoes);
void removerClube(CadastroClube **clubes, CadastroCompeticoes **competicoes, int *TamanhoClube, int *TamanhoCompeticoes, int codigoClubeTirar);
void removerCompeticao(CadastroCompeticoes **competicoes, int *tamanhoCompeticoes, int codigoCompeticaoTirar);

// Implementação das funções (anteriormente em BrasfootIME.c)
int lerInt() {
    int valor;
    char buffer[100];
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &valor) == 1) {
                return valor;
            }
        }
        printf("Entrada invalida. Digite um numero inteiro: ");
    }
}

void cadastrarClube(CadastroClube **clubes, int *tamanhoClube, CadastroCompeticoes *competicoes, int tamanhoCompeticoes) {
    *clubes = (CadastroClube *)realloc(*clubes, (*tamanhoClube + 1) * sizeof(CadastroClube));
    if (*clubes == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }

    CadastroClube *novoClube = &(*clubes)[*tamanhoClube];

    printf("Digite o codigo do clube (5 digitos): ");
    novoClube->codigoClube = lerInt();
    while (novoClube->codigoClube < 10000 || novoClube->codigoClube > 99999) {
        printf("Codigo invalido! Deve ter 5 digitos: ");
        novoClube->codigoClube = lerInt();
    }

    printf("Digite o nome do clube: ");
    fgets(novoClube->nomeClube, 50, stdin);
    novoClube->nomeClube[strcspn(novoClube->nomeClube, "\n")] = '\0';

    printf("Digite o maior jogador do clube: ");
    fgets(novoClube->maiorJogador, 50, stdin);
    novoClube->maiorJogador[strcspn(novoClube->maiorJogador, "\n")] = '\0';

    printf("Digite o ano de fundacao: ");
    novoClube->anoFund = lerInt();

    novoClube->qtdCompeticoes = 0;
    if (tamanhoCompeticoes > 0) {
        printf("Competições disponíveis:\n");
        for (int i = 0; i < tamanhoCompeticoes; i++) {
            printf("%d - %s\n", competicoes[i].codigoCompeticao, competicoes[i].nomeCompeticao);
        }
        printf("Quantas competições o clube participa? (max %d): ", MAX_COMPETICOES);
        novoClube->qtdCompeticoes = lerInt();
        if (novoClube->qtdCompeticoes > MAX_COMPETICOES) novoClube->qtdCompeticoes = MAX_COMPETICOES;
        if (novoClube->qtdCompeticoes > tamanhoCompeticoes) novoClube->qtdCompeticoes = tamanhoCompeticoes;

        for (int i = 0; i < novoClube->qtdCompeticoes; i++) {
            printf("Digite o código da competição %d: ", i + 1);
            int codigoComp = lerInt();
            int found = 0;
            for (int j = 0; j < tamanhoCompeticoes; j++) {
                if (competicoes[j].codigoCompeticao == codigoComp) {
                    strcpy(novoClube->competicoes[i], competicoes[j].nomeCompeticao);
                    competicoes[j].clubesParticipantes = (CadastroClube *)realloc(
                        competicoes[j].clubesParticipantes,
                        (competicoes[j].qtdClubes + 1) * sizeof(CadastroClube)
                    );
                    competicoes[j].clubesParticipantes[competicoes[j].qtdClubes] = *novoClube;
                    competicoes[j].qtdClubes++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("Competição não encontrada! Ignorando...\n");
                i--;
                novoClube->qtdCompeticoes--;
            }
        }
    } else {
        printf("Nenhuma competição disponível para associar.\n");
    }

    (*tamanhoClube)++;
    printf("Clube cadastrado com sucesso!\n");
}

void cadastrarCompeticao(CadastroCompeticoes **competicoes, int *tamanhoCompeticoes) {
    *competicoes = (CadastroCompeticoes *)realloc(*competicoes, (*tamanhoCompeticoes + 1) * sizeof(CadastroCompeticoes));
    if (*competicoes == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }

    CadastroCompeticoes *novaCompeticao = &(*competicoes)[*tamanhoCompeticoes];

    printf("Digite o codigo da competicao (4 digitos): ");
    novaCompeticao->codigoCompeticao = lerInt();
    while (novaCompeticao->codigoCompeticao < 1000 || novaCompeticao->codigoCompeticao > 9999) {
        printf("Codigo invalido! Deve ter 4 digitos: ");
        novaCompeticao->codigoCompeticao = lerInt();
    }

    printf("Digite o nome da competicao: ");
    fgets(novaCompeticao->nomeCompeticao, 50, stdin);
    novaCompeticao->nomeCompeticao[strcspn(novaCompeticao->nomeCompeticao, "\n")] = '\0';

    printf("Digite o pais-sede: ");
    fgets(novaCompeticao->paisSede, 50, stdin);
    novaCompeticao->paisSede[strcspn(novaCompeticao->paisSede, "\n")] = '\0';

    printf("Digite o artilheiro da competicao: ");
    fgets(novaCompeticao->artilheiro, 50, stdin);
    novaCompeticao->artilheiro[strcspn(novaCompeticao->artilheiro, "\n")] = '\0';

    novaCompeticao->qtdClubes = 0;
    novaCompeticao->clubesParticipantes = NULL;

    (*tamanhoCompeticoes)++;
    printf("Competicao cadastrada com sucesso!\n");
}

void gerarRelatorio(CadastroClube *clubes, CadastroCompeticoes *competicoes, int TamanhoClube, int TamanhoCompeticoes) {
    printf("\n--- Relatorio ---\n");

    if (TamanhoCompeticoes > 0) {
        printf("\nCompetições disponíveis:\n");
        for (int i = 0; i < TamanhoCompeticoes; i++) {
            printf("%d - %s\n", competicoes[i].codigoCompeticao, competicoes[i].nomeCompeticao);
        }
        printf("Digite o código da competição para listar os clubes: ");
        int codigoComp = lerInt();
        for (int i = 0; i < TamanhoCompeticoes; i++) {
            if (competicoes[i].codigoCompeticao == codigoComp) {
                printf("\nClubes na competição %s:\n", competicoes[i].nomeCompeticao);
                for (int j = 0; j < competicoes[i].qtdClubes; j++) {
                    printf("- %s\n", competicoes[i].clubesParticipantes[j].nomeClube);
                }
                break;
            }
        }
    } else {
        printf("Nenhuma competição cadastrada.\n");
    }

    if (TamanhoClube > 0) {
        printf("\nClubes disponíveis:\n");
        for (int i = 0; i < TamanhoClube; i++) {
            printf("%d - %s\n", clubes[i].codigoClube, clubes[i].nomeClube);
        }
        printf("Digite o código do clube: ");
        int codigoClube = lerInt();
        printf("Digite o ano da temporada (ex.: 2024): ");
        int ano = lerInt();

        for (int i = 0; i < TamanhoClube; i++) {
            if (clubes[i].codigoClube == codigoClube) {
                printf("\nCompetições do clube %s no ano %d:\n", clubes[i].nomeClube, ano);
                for (int j = 0; j < clubes[i].qtdCompeticoes; j++) {
                    printf("- %s\n", clubes[i].competicoes[j]);
                }
                break;
            }
        }
    } else {
        printf("Nenhum clube cadastrado.\n");
    }
}

void salvarDados(CadastroClube *clubes, CadastroCompeticoes *competicoes, int TamanhoClube, int TamanhoCompeticoes) {
    FILE *file = fopen("dados.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    fprintf(file, "%d\n", TamanhoClube);
    for (int i = 0; i < TamanhoClube; i++) {
        fprintf(file, "%d\n%s\n%s\n%d\n%d\n", clubes[i].codigoClube, clubes[i].nomeClube,
                clubes[i].maiorJogador, clubes[i].anoFund, clubes[i].qtdCompeticoes);
        for (int j = 0; j < clubes[i].qtdCompeticoes; j++) {
            fprintf(file, "%s\n", clubes[i].competicoes[j]);
        }
    }

    fprintf(file, "%d\n", TamanhoCompeticoes);
    for (int i = 0; i < TamanhoCompeticoes; i++) {
        fprintf(file, "%d\n%s\n%s\n%s\n%d\n", competicoes[i].codigoCompeticao, competicoes[i].nomeCompeticao,
                competicoes[i].paisSede, competicoes[i].artilheiro, competicoes[i].qtdClubes);
        for (int j = 0; j < competicoes[i].qtdClubes; j++) {
            fprintf(file, "%s\n", competicoes[i].clubesParticipantes[j].nomeClube);
        }
    }

    fclose(file);
    printf("Dados salvos com sucesso!\n");
}

void carregarDados(CadastroClube **clubes, CadastroCompeticoes **competicoes, int *TamanhoClube, int *TamanhoCompeticoes) {
    FILE *file = fopen("dados.txt", "r");
    if (file == NULL) {
        printf("Nenhum arquivo de dados encontrado.\n");
        return;
    }

    for (int i = 0; i < *TamanhoCompeticoes; i++) {
        free((*competicoes)[i].clubesParticipantes);
    }
    free(*clubes);
    free(*competicoes);
    *clubes = NULL;
    *competicoes = NULL;

    fscanf(file, "%d\n", TamanhoClube);
    *clubes = (CadastroClube *)malloc(*TamanhoClube * sizeof(CadastroClube));
    for (int i = 0; i < *TamanhoClube; i++) {
        fscanf(file, "%d\n", &(*clubes)[i].codigoClube);
        fgets((*clubes)[i].nomeClube, 50, file);
        (*clubes)[i].nomeClube[strcspn((*clubes)[i].nomeClube, "\n")] = '\0';
        fgets((*clubes)[i].maiorJogador, 50, file);
        (*clubes)[i].maiorJogador[strcspn((*clubes)[i].maiorJogador, "\n")] = '\0';
        fscanf(file, "%d\n", &(*clubes)[i].anoFund);
        fscanf(file, "%d\n", &(*clubes)[i].qtdCompeticoes);
        for (int j = 0; j < (*clubes)[i].qtdCompeticoes; j++) {
            fgets((*clubes)[i].competicoes[j], 50, file);
            (*clubes)[i].competicoes[j][strcspn((*clubes)[i].competicoes[j], "\n")] = '\0';
        }
    }

    fscanf(file, "%d\n", TamanhoCompeticoes);
    *competicoes = (CadastroCompeticoes *)malloc(*TamanhoCompeticoes * sizeof(CadastroCompeticoes));
    for (int i = 0; i < *TamanhoCompeticoes; i++) {
        fscanf(file, "%d\n", &(*competicoes)[i].codigoCompeticao);
        fgets((*competicoes)[i].nomeCompeticao, 50, file);
        (*competicoes)[i].nomeCompeticao[strcspn((*competicoes)[i].nomeCompeticao, "\n")] = '\0';
        fgets((*competicoes)[i].paisSede, 50, file);
        (*competicoes)[i].paisSede[strcspn((*competicoes)[i].paisSede, "\n")] = '\0';
        fgets((*competicoes)[i].artilheiro, 50, file);
        (*competicoes)[i].artilheiro[strcspn((*competicoes)[i].artilheiro, "\n")] = '\0';
        fscanf(file, "%d\n", &(*competicoes)[i].qtdClubes);
        (*competicoes)[i].clubesParticipantes = (CadastroClube *)malloc((*competicoes)[i].qtdClubes * sizeof(CadastroClube));
        for (int j = 0; j < (*competicoes)[i].qtdClubes; j++) {
            fgets((*competicoes)[i].clubesParticipantes[j].nomeClube, 50, file);
            (*competicoes)[i].clubesParticipantes[j].nomeClube[strcspn((*competicoes)[i].clubesParticipantes[j].nomeClube, "\n")] = '\0';
        }
    }

    fclose(file);
    printf("Dados carregados com sucesso!\n");
}

void removerClube(CadastroClube **clubes, CadastroCompeticoes **competicoes, int *TamanhoClube, int *TamanhoCompeticoes, int codigoClubeTirar) {
    int indice = -1;
    for (int i = 0; i < *TamanhoClube; i++) {
        if ((*clubes)[i].codigoClube == codigoClubeTirar) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Clube não encontrado!\n");
        return;
    }

    for (int i = 0; i < *TamanhoCompeticoes; i++) {
        for (int j = 0; j < (*competicoes)[i].qtdClubes; j++) {
            if (strcmp((*competicoes)[i].clubesParticipantes[j].nomeClube, (*clubes)[indice].nomeClube) == 0) {
                for (int k = j; k < (*competicoes)[i].qtdClubes - 1; k++) {
                    (*competicoes)[i].clubesParticipantes[k] = (*competicoes)[i].clubesParticipantes[k + 1];
                }
                (*competicoes)[i].qtdClubes--;
                (*competicoes)[i].clubesParticipantes = (CadastroClube *)realloc(
                    (*competicoes)[i].clubesParticipantes,
                    (*competicoes)[i].qtdClubes * sizeof(CadastroClube)
                );
                break;
            }
        }
    }

    for (int i = indice; i < *TamanhoClube - 1; i++) {
        (*clubes)[i] = (*clubes)[i + 1];
    }
    (*TamanhoClube)--;
    *clubes = (CadastroClube *)realloc(*clubes, (*TamanhoClube) * sizeof(CadastroClube));
    printf("Clube removido com sucesso!\n");
}

void removerCompeticao(CadastroCompeticoes **competicoes, int *tamanhoCompeticoes, int codigoCompeticaoTirar) {
    int indice = -1;
    for (int i = 0; i < *tamanhoCompeticoes; i++) {
        if ((*competicoes)[i].codigoCompeticao == codigoCompeticaoTirar) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Competição não encontrada!\n");
        return;
    }

    free((*competicoes)[indice].clubesParticipantes);

    for (int i = indice; i < *tamanhoCompeticoes - 1; i++) {
        (*competicoes)[i] = (*competicoes)[i + 1];
    }
    (*tamanhoCompeticoes)--;
    *competicoes = (CadastroCompeticoes *)realloc(*competicoes, (*tamanhoCompeticoes) * sizeof(CadastroCompeticoes));
    printf("Competição removida com sucesso!\n");
}

// Função principal (anteriormente em main.c)
int main() {
    CadastroClube *clubes = NULL;
    CadastroCompeticoes *competicoes = NULL;
    int TamanhoClube = 0, TamanhoCompeticoes = 0;
    int opcao;

    do {
        system("clear || cls");

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

    for (int i = 0; i < TamanhoCompeticoes; i++) {
        free(competicoes[i].clubesParticipantes);
    }
    free(clubes);
    free(competicoes);

    return 0;
}
