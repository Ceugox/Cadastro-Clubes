#include <stdio.h>
#include <stdlib.h>




    typedef struct TipoClubes {
    int codigoClube;//5 dígitos
    char nomeClube;
    char maiorJogador;
    int anoFund;
    }Clube;
    typedef struct TipoCompeticoes{
    int codigoCompeticao;//4 dígitos
    char nomeCompeticao;
    char paisSede;
    char artilheiro;
    int qtdtimes;
    } Competicoes;

     void cadastrarClube (Clube)
{
        Clube *newClube = (Clube *) malloc(sizeof(Clube));
        if (!newClube)
        {
                printf("ERRO DE ALOCACAO DE MEMORIA!!!\n");
                exit(-1);
        }
        else
        {
                printf("\n--- PRENCHA OS DADOS DE CADASTRO DO SEU CLUBE ---\n\n");
                printf("Digite o nome do clube: ");
                scanf(" %[^\n]", newClube->nomeClube);
                fflush(stdin);
                do{
                printf("Digite o codigo do clube com 5 digitos, sendo o primeiro digito diferente de 0: ");
               scanf(" %d", &newClube->codigoClube);}while(newClube->codigoClube>99999 || newClube->codigoClube<10000);
                printf("Digite o ano de fundacao do clube: ");
                scanf(" %d", newClube->anoFund);
                printf("Digite o maior jogador do seu clube: ");
                scanf(" %c", newClube->maiorJogador);

        return;
}
void cadastrarCompeticao (Competicoes) {
    char resposta;
Competicoes *newCompeticoes= (Competicoes *)malloc(sizeof(Competicoes));

if(!newCompeticoes){

    printf("ERRO DE ALOCACAO DE MEMORIA!!!\n");
    exit(-1);
}

else {
    printf("-- PREENCHA OS CAMPOS DE CADASTRO DAS COMPETIÇÕES NAS QUAIS SEU CLUBE PARTICIPA --\n\n");
    do{
        printf("Digite o nome da competicao: ");
                scanf(" %[^\n]", newCompeticoes->nomeCompeticao);
                fflush(stdin);
                do{
                printf("Digite o codigo da competicao com 4 digitos, sendo o primeiro digito diferente de 0: ");
               scanf(" %d", &newCompeticoes->codigoCompeticao);}while(codigoCompeticao>9999 || codigoCompeticao<1000);
                printf("Digite o pais sede da competicao:");
                scanf(" %[^\n]", newCompeticoes->paisSede);
                printf("Digite o artilheiro da competicao: ");
                scanf(" %c", newCompeticoes->artilheiro);
                printf("Digite o numero de times participantes:")
                scanf(" %d" newCompeticoes->qtdtimes);
                do{
                printf("Deseja cadastrar mais uma competicao:s-Sim n-Não:");
                scanf("%c",%resposta);
                }while(resposta!='s' || resposta!='n');

    }while(resposta='s');
    return;
}
}
int main (){

    printf("Bem-vindo ao BrasfootTIME:O melhor Gerenciador de Clubes do Brasil\n");
    printf("Vamos iniciar o cadastro do seu time");
    cadastrarClube(Clube);
    cadastrarCompeticao(Competicoes);

return 0;
}
