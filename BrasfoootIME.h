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
char Competition[50];
char clube;
} Temporada;

int lerInt();

void cadastrarClube(CadastroClube **clubes, int *tamanhoClube, CadastroCompeticoes *competicoes, int tamanhoCompeticoes);
void cadastrarCompeticao(CadastroCompeticoes **competicoes, int *tamanhoCompeticoes);
void gerarRelatorio(CadastroClube *clubes, CadastroCompeticoes *competicoes, int TamanhoClube, int TamanhoCompeticoes);
void salvarDados(CadastroClube *clubes, CadastroCompeticoes *competicoes, int TamanhoClube, int TamanhoCompeticoes);
void carregarDados(CadastroClube **clubes, CadastroCompeticoes **competicoes, int *TamanhoClube, int *TamanhoCompeticoes, int codigoClubeTirar,int i, int j);
void removerClube( CadastroClube **clubes, CadastroCompeticoes **competicoes, int codigoClubeTirar);
void removerCompeticao (CadastroCompeticoes *competicoes, int tamanhoCompeticoes, int codigoCompeticaoTirar );
















