#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define WHT "\e[0;37m"
#define YEL "\e[0;33m"
#define MAG "\e[0;35m"
#define BLU "\e[0;34m"
#define CYN "\e[0;36m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"
#define BYEL "\e[33;1m"
#define BGRN "\e[32;1m"
#define BBLU "\e[34;1m"

struct TCarro {
  char ModeloDoCarro[30];
  int AnoDoCarro;
  char NomeProprietario[30];
  char Placa[30];
};
///Menus
float inicio(float Precogasolina);
int menu(int op);
int menurelatorio(int op);
int menuabastecer(int op);
///Funções
void imprimeUmCarro(struct TCarro c);
void addCarro(int Ctotal, int *fila);
struct TCarro criaCarro();
void addCarro(int Ctotal, int *fila);
void flush_in();

void copiarPrincipalParaAtendidos(struct TCarro principal,
                                  struct TCarro atendidos);
void reorganizarVetor(struct TCarro vetor[], int tamanho);
void AbastecerAlem(float *Somavendida, float *Somagasolina, float *Tgasolina, float *Precogasolina, float *SomaTotal, int *CAbastecido, int *CFila);
void Abastecer(float *Somavendida, float *Somagasolina, float *Tgasolina,
                   float *Precogasolina, float *SomaTotal, int *CAbastecido,
                   int *CFila, int gasto);


///Apresentação de Tabelas
void FilaEspera(int *CFila, struct TCarro vetorCarro[]);
void FilaAtendido(int *CAbastecido, struct TCarro VetorAbastecido[]);
void Tabela(float preco, float *gasolina, int *CFila);
void TabelaGasoDisp(float *gasolina);
void TabelaComCarro(float *Somavendida, float *SomaTotal, int *CAbastecido, float *Tgasolina);
void TabelaGasoResto(float Tgasolina);
