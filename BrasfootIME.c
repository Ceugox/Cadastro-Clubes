#include <stdio.h>
#include <stdlib.h>
#include "BrasfootIME.h"

// Funcao para cadastrar um clube
void cadastrarClube(CadastroClube **clubes, int *tamanhoClube, CadastroCompeticoes *competicoes, int tamanhoCompeticoes) {
    system("clear || cls"); // Limpar a tela

    CadastroClube *newClube = (CadastroClube *)malloc(sizeof(CadastroClube));
    if (!newClube) {
        printf("ERRO DE ALOCACAO DE MEMORIA!!!\n");
        exit(-1);
    }

    printf("\n--- PREENCHA OS DADOS DE CADASTRO DO SEU CLUBE ---\n\n");
    printf("Digite o nome do clube: ");
    scanf(" %[^\n]", newClube->nomeClube);
    setbuf(stdin, NULL);

    do {
        printf("\nDigite o codigo do clube com 5 digitos, sendo o primeiro diferente de 0: ");
        newClube->codigoClube = lerInt(); // Verificação de entrada
    } while (newClube->codigoClube > 99999 || newClube->codigoClube < 10000);

    printf("\nDigite o ano de fundacao do clube: ");
    newClube->anoFund = lerInt(); // Verifica se o usuario realmente digitou um int

    printf("\nDigite o maior jogador do seu clube: ");
    scanf(" %[^\n]", newClube->maiorJogador);

    newClube->qtdCompeticoes = 0;

    // Cadastro das competicoes em que o clube participa
    printf("\nDigite o numero de competicoes que o clube participa (maximo %d): ", MAX_COMPETICOES);
    newClube->qtdCompeticoes = lerInt();

    for (int i = 0; i < newClube->qtdCompeticoes; i++) {
        printf("Digite o nome da competicao %d: ", i + 1);
        scanf(" %[^\n]", newClube->competicoes[i]);
    }

    (*clubes) = (CadastroClube *)realloc(*clubes, (*tamanhoClube + 1) * sizeof(CadastroClube));
    (*clubes)[*tamanhoClube] = *newClube;
    (*tamanhoClube)++;
    free(newClube);

    // Atualizar os clubes participantes nas competicoes
    for (int i = 0; i < newClube->qtdCompeticoes; i++) {
        for (int j = 0; j < tamanhoCompeticoes; j++) {
            if (strcmp(competicoes[j].nomeCompeticao, newClube->competicoes[i]) == 0) {
                competicoes[j].clubesParticipantes = (CadastroClube *)realloc(competicoes[j].clubesParticipantes,
                                                                              (competicoes[j].qtdClubes + 1) * sizeof(CadastroClube));
                competicoes[j].clubesParticipantes[competicoes[j].qtdClubes] = (*clubes)[*tamanhoClube - 1];
                competicoes[j].qtdClubes++;
            }
        }
    }
}

// Funcao para cadastrar uma competicao
void cadastrarCompeticao(CadastroCompeticoes **competicoes, int *tamanhoCompeticoes) {
    system("clear || cls"); // Limpar a tela

    CadastroCompeticoes *newCompeticoes = (CadastroCompeticoes *)malloc(sizeof(CadastroCompeticoes));
    if (!newCompeticoes) {
        printf("ERRO DE ALOCACAO DE MEMORIA!!!\n");
        exit(-1);
    }

    printf("\n-- PREENCHA OS CAMPOS DE CADASTRO DAS COMPETICOES --\n\n");

    printf("Digite o nome da competicao: ");
    scanf(" %[^\n]", newCompeticoes->nomeCompeticao);
    setbuf(stdin, NULL);

    do {
        printf("\nDigite o codigo da competicao com 4 digitos, sendo o primeiro diferente de 0: ");
        newCompeticoes->codigoCompeticao = lerInt();
    } while (newCompeticoes->codigoCompeticao > 9999 || newCompeticoes->codigoCompeticao < 1000);

    printf("Digite o pais sede da competicao: ");
    scanf(" %[^\n]", newCompeticoes->paisSede);
    setbuf(stdin, NULL);

    printf("Digite o artilheiro da competicao: ");
    scanf(" %[^\n]", newCompeticoes->artilheiro);
    setbuf(stdin, NULL);

    printf("Digite o numero de times participantes: ");
    newCompeticoes->qtdClubes = lerInt();

    newCompeticoes->qtdClubes = 0;
    newCompeticoes->clubesParticipantes = NULL;

    (*competicoes) = (CadastroCompeticoes *)realloc(*competicoes, (*tamanhoCompeticoes + 1) * sizeof(CadastroCompeticoes));
    (*competicoes)[*tamanhoCompeticoes] = *newCompeticoes;
    (*tamanhoCompeticoes)++;
    free(newCompeticoes);
}

// Funcao para gerar um relatorio
void gerarRelatorio(CadastroClube *clubes, CadastroCompeticoes *competicoes, int TamanhoClube, int TamanhoCompeticoes) {
    system("clear || cls"); // Limpar a tela

    FILE *fileRelatorio = fopen("relatorio_temporada.txt", "w");
    if (fileRelatorio == NULL) {
        printf("Erro ao abrir arquivo de relatorio!\n");
        return;
    }

    fprintf(fileRelatorio, "--- Relatorio de Temporada ---\n\n");

    // Relatorio de Clubes
    fprintf(fileRelatorio, "--- Clubes ---\n");
    for (int i = 0; i < TamanhoClube; i++) {
        fprintf(fileRelatorio, "Nome: %s\n", clubes[i].nomeClube);
        fprintf(fileRelatorio, "Codigo: %d\n", clubes[i].codigoClube);
        fprintf(fileRelatorio, "Ano de Fundacao: %d\n", clubes[i].anoFund);
        fprintf(fileRelatorio, "Maior Jogador: %s\n", clubes[i].maiorJogador);
        fprintf(fileRelatorio, "Competicoes Participando:");
        for (int j = 0; j < clubes[i].qtdCompeticoes; j++) {
            fprintf(fileRelatorio, "%s", clubes[i].competicoes[j]);
            if (j < clubes[i].qtdCompeticoes - 1) {
                fprintf(fileRelatorio, ", ");
            }
        }
        fprintf(fileRelatorio, "\n\n");
    }

    // Relatorio de Competicoes e seus clubes
    fprintf(fileRelatorio, "--- Competicoes ---\n");
    for (int i = 0; i < TamanhoCompeticoes; i++) {
        fprintf(fileRelatorio, "Nome: %s\n", competicoes[i].nomeCompeticao);
        fprintf(fileRelatorio, "Codigo: %d\n", competicoes[i].codigoCompeticao);
        fprintf(fileRelatorio, "Pais Sede: %s\n", competicoes[i].paisSede);
        fprintf(fileRelatorio, "Artilheiro: %s\n", competicoes[i].artilheiro);
        fprintf(fileRelatorio, "Quantidade de Times: %d\n", competicoes[i].qtdClubes);
        fprintf(fileRelatorio, "Clubes Participantes: ");

        if (competicoes[i].qtdClubes > 0) {
            for (int j = 0; j < competicoes[i].qtdClubes; j++) {
                fprintf(fileRelatorio, "%s (Codigo: %d)", competicoes[i].clubesParticipantes[j].nomeClube, competicoes[i].clubesParticipantes[j].codigoClube);
                if (j < competicoes[i].qtdClubes - 1) {
                    fprintf(fileRelatorio, ", ");
                }
            }
        } else {
            fprintf(fileRelatorio, "Nenhum clube registrado.\n");
        }
        fprintf(fileRelatorio, "\n\n");
    }

    fclose(fileRelatorio);

    printf("Relatorio gerado com sucesso!\n");
}

// Funcao para salvar os dados no arquivo
void salvarDados(CadastroClube *clubes, CadastroCompeticoes *competicoes, int TamanhoClube, int TamanhoCompeticoes) {
    FILE *fileClube = fopen("clubes.dat", "wb");
    if (fileClube == NULL) {
        printf("Erro ao abrir arquivo de clubes!\n");
        return;
    }
    fwrite(clubes, sizeof(CadastroClube), TamanhoClube, fileClube);
    fclose(fileClube);

    FILE *fileCompeticoes = fopen("competicoes.dat", "wb");
    if (fileCompeticoes == NULL) {
        printf("Erro ao abrir arquivo de competicoes!\n");
        return;
    }
    fwrite(competicoes, sizeof(CadastroCompeticoes), TamanhoCompeticoes, fileCompeticoes);
    fclose(fileCompeticoes);

    printf("Dados salvos com sucesso!\n");
}

// Funcao para carregar os dados dos arquivos
void carregarDados(CadastroClube **clubes, CadastroCompeticoes **competicoes, int *TamanhoClube, int *TamanhoCompeticoes, int codigoClubeTirar,int i, int j) {
    FILE *fileClube = fopen("clubes.dat", "rb");
    if (fileClube != NULL) {
        fread(*clubes, sizeof(CadastroClube), *TamanhoClube, fileClube);
        fclose(fileClube);
    }

    FILE *fileCompeticoes = fopen("competicoes.dat", "rb");
    if (fileCompeticoes != NULL) {
        fread(*competicoes, sizeof(CadastroCompeticoes), *TamanhoCompeticoes, fileCompeticoes);
        fclose(fileCompeticoes);
    }
}
void removerClube( CadastroClube **clubes, CadastroCompeticoes **competicoes, int codigoClubeTirar) {
FILE *fileRelatorio=fopen("relatorio_temporada.txt","w");

if(fileRelatorio==NULL){
    printf("ERRO AO ABRIR O ARQUIVO!!!");
    return;
}
printf("Vamos remover os dados sobre seu clube");
printf("Digite o codigo do clube que deseja remover do relatorio:");
scanf("%d",&codigoClubeTirar);
for(i=0;i<*tamanhoClube;i++){
if((*clubes)[i].codigoClube==codigoClubeTirar){
   encontrado=1; //Ou seja, a sentença é verdadeira
//A partir de agora devemos deslocar os clubes restantes para a posição removida

 for(j=i;j<*tamanhoClube-1;j++){
(*clubes)[j]=(*clubes)[j+1];
}
  *clubes=(CadastroClube *)realloc(*clubes,(*tamanhoClube-1)*sizeof(CadastroClube));
    (*tamanhoClube)--;
 printf("Clube removido!/n");
 return;
}
 if(!encontrado) {
  printf("Codigo do clube nao encontrado na base de dados!");
}
}
void removerCompeticao(CadastroCompeticoes **competicoes, int *tamanhoCompeticoes, int codigoCompeticaoTirar) {
    int encontrado = 0;
    
    printf("Vamos remover os dados sobre sua competicao\n");
    printf("Digite o codigo da competicao: ");
    scanf("%d", &codigoCompeticaoTirar);

    for (int i = 0; i < *tamanhoCompeticoes; i++) {
        if ((*competicoes)[i].codigoCompeticao == codigoCompeticaoTirar) {
            encontrado = 1;

            // Analogamente a remoção de clubes, dando um shift em todos os elementos após o removido
            for (int j = i; j < tamanhoCompeticoes - 1; j++) {
                competicoes[j] = competicoes[j + 1];
            }
        
  *competicoes=(CadastroCompeticoes *)realloc(*competicoes,(*tamanhoCompeticoes-1)*sizeof(CadastroCompeticoes)); 
            tamanhoCompeticoes--;
            printf("Competição removida!\n");
            return;
        }
    }
    if (!encontrado) {
        printf("Codigo da competicao nao encontrado na base de dados!\n");
    }
}
