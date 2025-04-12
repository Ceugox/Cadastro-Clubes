#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BrasfootIME.h"

#define MAX_COMPETICOES 10 // Definido no header, mas como não está, coloco aqui para referência

// Função para ler um inteiro com validação
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

// Função para cadastrar um clube
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

    // Associar competições ao clube
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
                    // Adicionar o clube à lista de participantes da competição
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

// Função para cadastrar uma competição
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

// Função para gerar relatórios
void gerarRelatorio(CadastroClube *clubes, CadastroCompeticoes *competicoes, int TamanhoClube, int TamanhoCompeticoes) {
    printf("\n--- Relatorio ---\n");

    // 1. Listar clubes inscritos em uma competição
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

    // 2. Listar competições de um clube em um período
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

// Função para salvar dados em arquivo
void salvarDados(CadastroClube *clubes, CadastroCompeticoes *competicoes, int TamanhoClube, int TamanhoCompeticoes) {
    FILE *file = fopen("dados.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    // Salvar clubes
    fprintf(file, "%d\n", TamanhoClube);
    for (int i = 0; i < TamanhoClube; i++) {
        fprintf(file, "%d\n%s\n%s\n%d\n%d\n", clubes[i].codigoClube, clubes[i].nomeClube,
                clubes[i].maiorJogador, clubes[i].anoFund, clubes[i].qtdCompeticoes);
        for (int j = 0; j < clubes[i].qtdCompeticoes; j++) {
            fprintf(file, "%s\n", clubes[i].competicoes[j]);
        }
    }

    // Salvar competições
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

// Função para carregar dados de arquivo
void carregarDados(CadastroClube **clubes, CadastroCompeticoes **competicoes, int *TamanhoClube, int *TamanhoCompeticoes) {
    FILE *file = fopen("dados.txt", "r");
    if (file == NULL) {
        printf("Nenhum arquivo de dados encontrado.\n");
        return;
    }

    // Liberar memória existente
    for (int i = 0; i < *TamanhoCompeticoes; i++) {
        free((*competicoes)[i].clubesParticipantes);
    }
    free(*clubes);
    free(*competicoes);
    *clubes = NULL;
    *competicoes = NULL;

    // Carregar clubes
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

    // Carregar competições
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

// Função para remover um clube
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

    // Remover o clube das competições
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

    // Remover o clube da lista de clubes
    for (int i = indice; i < *TamanhoClube - 1; i++) {
        (*clubes)[i] = (*clubes)[i + 1];
    }
    (*TamanhoClube)--;
    *clubes = (CadastroClube *)realloc(*clubes, (*TamanhoClube) * sizeof(CadastroClube));
    printf("Clube removido com sucesso!\n");
}

// Função para remover uma competição
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

    // Liberar a memória dos clubes participantes
    free((*competicoes)[indice].clubesParticipantes);

    // Remover a competição da lista
    for (int i = indice; i < *tamanhoCompeticoes - 1; i++) {
        (*competicoes)[i] = (*competicoes)[i + 1];
    }
    (*tamanhoCompeticoes)--;
    *competicoes = (CadastroCompeticoes *)realloc(*competicoes, (*tamanhoCompeticoes) * sizeof(CadastroCompeticoes));
    printf("Competição removida com sucesso!\n");
}
