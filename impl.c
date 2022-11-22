#include "header.h"
#include <stdio.h>
#include <string.h>

////Menus
float inicio(float Precogasolina) {
  printf(BLU
         "=-= Bem vindo ao Posto da Esquina! =-= \n\n=-=Projeto de Mohamed Ali "
         "Awale=-=\n\n=-=Este programa irá organizar o funcionamento de um "
         "Posto de Gasolina com uma bomba de combustível=-=" WHT);

  printf("\n\nQual é o valor da gasolina hoje?\n(Por favor insira ponto (.) "
         "no lugar da vírgula (,)).\nDigite: ");
  scanf("%f", &Precogasolina);
  while (Precogasolina <= 0) {
    printf(RED
           "\n\nValor inválido (número negativo ou Zero).\nQual é o valor da "
           "gasolina hoje?\n(Por favor insira ponto (.) no lugar da vírgula "
           "(,))\nDigite: " WHT);
    scanf("%f", &Precogasolina);
  }
  return Precogasolina;
}
int menu(int op) {
  printf(YEL
         "\n==-== " BGRN " Menu " YEL " ==-==\n" BLU "(" BGRN "1" BLU ")" GRN
         " Adicione um veículo para a fila.\n" BLU "(" BGRN "2" BLU ")" BBLU " "
         "Abasteça o veículo.\n" BLU "(" BGRN "3" BLU ")" YEL
         " Fila de Espera.  \n" BLU "(" BGRN "4" BLU ")" MAG
         " Abrir o menu do relatório."
         "\n" BLU "(" BGRN "5" BLU ")" RED " Fechar menu.\n" YEL "==-== " BGRN
         " Menu " YEL " ==-==" WHT);
  printf("\nDigite: ");
  scanf("%d", &op);
  return op;
}
int menurelatorio(int op) {
  printf(MAG "\n==-== " BYEL "Menu do Relatório " MAG "==-== \n\n" BLU "(" MAG
             "1" BLU ")" GRN " Quantidade de litros"
             "vendida;\n" BLU "(" MAG "2" BLU ")" YEL
             " Valor total arrecadado com as vendas;\n" BLU "(" MAG "3" BLU
             ")" CYN " "
             "Quantidade de veículos atendidos; \n" BLU "(" MAG "4" BLU ")" GRN
             " Quantidade de combustível "
             "restante no tanque;\n" BLU "(" MAG "5" BLU ")" YEL
             " Gerar arquivo para impressão (com "
             "todas "
             "as informações de 1, 2, 3 e 4); \n" BLU "(" MAG "6" BLU ")" RED
             " Voltar ao menu."
             "anterior.\n\n" MAG "==-== " BYEL " Menu do Relatório " MAG
             "==-==" WHT);
  printf("\nDigite: ");
  scanf("%d", &op);
  return op;
}
int menuabastecer(int op) {
  printf(RED "\nNão temos a gasolina suficiente que você está pedindo.\n"
             "" GRN "Por favor, escolha uma das opções\n" BLU "(" YEL "1" BLU
             ")" GRN " Pedir outra "
             "quantidade de combustível.\n" BLU "(" YEL "2" BLU ")" YEL ""
             " Abastecer com o combustível "
             "restante.\n" BLU "(" YEL "3" BLU ")" RED " Sair da fila\n" CYN
             "Digite: " WHT);
  scanf("%d", &op);
  return op;
}

// funções
void imprimeUmCarro(struct TCarro c) {
  printf(GRN "\nProprietário: " BLU "%s" WHT, c.NomeProprietario);
  printf(GRN "\nModelo do Carro: " BLU "%s" WHT, c.ModeloDoCarro);
  printf(GRN "\nAno do Carro: " BLU "%d" WHT, c.AnoDoCarro);
  printf(GRN "\nPlaca do Carro: " BLU "%s\n" WHT, c.Placa);
}
struct TCarro criaCarro() {
  struct TCarro auxiliar;
  fgets(auxiliar.NomeProprietario, 30, stdin);
  auxiliar.NomeProprietario[strcspn(auxiliar.NomeProprietario, "\n")] = 0;
  printf(BLU "\nDigite seu nome:" WHT " ");
  fgets(auxiliar.NomeProprietario, 30, stdin);
  auxiliar.NomeProprietario[strcspn(auxiliar.NomeProprietario, "\n")] = 0;
  printf(BLU "\nDigite o Modelo do Carro:" WHT " ");
  fgets(auxiliar.ModeloDoCarro, 30, stdin);
  auxiliar.ModeloDoCarro[strcspn(auxiliar.ModeloDoCarro, "\n")] = 0;
  printf(BLU "\nDigite o Ano de fabricação do Carro:" WHT " ");
  scanf("%d", &auxiliar.AnoDoCarro);
  flush_in();
  printf(BLU "\nDigite a Placa do Carro:" WHT " ");
  fgets(auxiliar.Placa, 30, stdin);
  auxiliar.Placa[strcspn(auxiliar.Placa, "\n")] = 0;
  return auxiliar;
}
void flush_in() {
  int ch;
  while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
  }
}
void copiarPrincipalParaAtendidos(struct TCarro principal,
                                  struct TCarro atendidos) {
  strcpy(atendidos.Placa, principal.Placa);
  strcpy(atendidos.ModeloDoCarro, principal.ModeloDoCarro);
  strcpy(atendidos.NomeProprietario, principal.NomeProprietario);
  // strcpy(atendidos.AnoDoCarro, principal.AnoDoCarro);
}

void reorganizarVetor(struct TCarro vetor[], int tamanho) {
  for (int cont = 0; cont < tamanho; cont++) {
    vetor[cont] = vetor[cont + 1];
  }
}

void AbastecerAlem(float *Somavendida, float *Somagasolina, float *Tgasolina,
                   float *Precogasolina, float *SomaTotal, int *CAbastecido,
                   int *CFila) {
  *Somavendida += *Tgasolina;
  *Somagasolina = *Tgasolina * *Precogasolina;
  *SomaTotal += *Tgasolina;
  *Tgasolina = 0;
  *CAbastecido = *CAbastecido + 1;
  *CFila = *CFila - 1;
}
void Abastecer(float *Somavendida, float *Somagasolina, float *Tgasolina,
               float *Precogasolina, float *SomaTotal, int *CAbastecido,
               int *CFila, int gasto) {
  *Somavendida += *Somavendida + gasto;
  *Somagasolina = gasto * *Precogasolina;
  *SomaTotal = *SomaTotal + *Somagasolina;
  *Tgasolina = *Tgasolina - gasto;
  *CAbastecido = *CAbastecido + 1;
  *CFila = *CFila - 1;
}
////Tabelas
void FilaEspera(int *CFila, struct TCarro vetorCarro[]) {
  printf(MAG "     =-=" BYEL "  FILA DE ESPERA  " MAG "=-=     \n\n");
  if (*CFila == 0) {
    printf(RED "\nNão há nenhum carro na fila.\n" WHT);
  } else if (*CFila == 1) {
    printf(YEL "\nEstá presente " BBLU "%d" YEL " veículo na fila\n" WHT,
           *CFila);

    for (int i = 0; i < *CFila; i++) // NÃO MEXER
      imprimeUmCarro(vetorCarro[i]); // NÃO MEXER
  } else {
    printf(YEL "\nEstão presentes " BBLU "%d" YEL " veículos na fila\n" WHT,
           *CFila);

    for (int i = 0; i < *CFila; i++) // NÃO MEXER
      imprimeUmCarro(vetorCarro[i]); // NÃO MEXER
  }                                  //
  printf(MAG "\n\n    =-=" BYEL "  FILA DE ESPERA  " MAG "=-=     \n\n");
  printf(GRN "\nPressione a tecla Enter para continuar.\n" WHT);
}
void TabelaGasoResto(float Tgasolina) {
  printf("\nRestam %.f Litros de Gasolina", Tgasolina);
}
void FilaAtendido(int *CAbastecido, struct TCarro VetorAbastecido[]) {
  if (*CAbastecido == 0) {
    printf(RED "\nNenhum carro foi atendido.\n" WHT);
  } else if (*CAbastecido == 1) {
    printf(CYN "\nApenas " BYEL "1" CYN " carro foi atendido.\n" WHT);

    for (int i = 0; i < *CAbastecido; i++) // NÃO MEXER
      imprimeUmCarro(VetorAbastecido[i + 1]);
  } else {
    printf(CYN "\nForam atendidos " BYEL "%d" CYN " carros.\n" WHT,
           *CAbastecido);

    for (int i = 0; i < *CAbastecido; i++) // NÃO MEXER
      imprimeUmCarro(VetorAbastecido[i + 1]);
  }
} // Imprimir no Arquivo.txt
void Tabela(float preco, float *gasolina, int *CFila) {
  printf(BYEL "Preço da Gasolina: " BLU "R$ %.2f " BYEL "Reais.\n", preco);
  if (*gasolina > 100) {
    printf(MAG "\nGasolina disponível: " BGRN "%.f Litros.\n" WHT, *gasolina);
  } else if (*gasolina > 50) {
    printf(MAG "\nGasolina disponível: " BYEL "%.f Litros.\n" WHT, *gasolina);
  } else {
    printf(MAG "\nGasolina disponível: " RED "%.f Litros.\n" WHT, *gasolina);
  }

  if (*CFila == 0) {
    printf(GRN "\nNenhum veículo na fila.\n" WHT);
  } else {
    printf(GRN "\nVeículos na fila:" BLU " %d.\n" WHT, *CFila);
  }
}
void TabelaGasoDisp(float *gasolina) {
  printf(MAG "Gasolina Disponível: " BLU "%1.f" MAG " Litros\n" WHT, *gasolina);
}
void TabelaComCarro(float *Somavendida, float *SomaTotal, int *CAbastecido,
                    float *Tgasolina) {
  if (*CAbastecido == 1) {
    printf(CYN "\nForam vendidos " BBLU "%.f litros" CYN
               " de gasolina;\nForam vendidos até "
               "agora " BGRN "R$ "
               "%.f" CYN " de combustível;\nFoi atendido " BYEL "%d Carro" CYN
               ";\nRestam " BBLU "%.f "
               "litros " CYN " de combustível.\n" WHT,
           *Somavendida, *SomaTotal, *CAbastecido, *Tgasolina);
  } else if (*CAbastecido > 1) {
    printf(CYN "\nForam vendidos " BBLU "%.f litros" CYN
               " de gasolina;\nForam vendidos até "
               "agora " BGRN "R$ "
               "%.f" CYN " de combustível;\nForam atendidos " BYEL
               "%d Carros;" CYN "\nRestam " BBLU "%.f "
               "litros" CYN " de combustível.\n" WHT,
           *Somavendida, *SomaTotal, *CAbastecido, *Tgasolina);
  } else {
    printf(CYN "\n" RED "Não foi vendido nenhum combustível;\nNão houve nenhum "
               "Lucro;\nNenhum Carro foi atendido;\n" BGRN
               "O Tanque de combustível está cheio.\n" WHT);
  }
} 