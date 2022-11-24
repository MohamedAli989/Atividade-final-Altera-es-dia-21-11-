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
         "\n==-== " BGRN " Menu " YEL " ==-==\n" BLU "(" BGRN "1" BLU ")" YEL
         " Adicione um veículo para a fila.\n" BLU "(" BGRN "2" BLU ")" YEL " "
         "Abasteça o veículo.\n" BLU "(" BGRN "3" BLU ")" YEL
         " Fila de Espera.  \n" BLU "(" BGRN "4" BLU ")" YEL
         " Abrir o menu do relatório."
         "\n" BLU "(" BGRN "5" BLU ")" RED " Fechar menu.\n" YEL "==-== " BGRN
         " Menu " YEL " ==-==" WHT);
  printf("\nDigite: ");
  scanf("%d", &op);
  return op;
}

int menurelatorio(int op) {
  printf(MAG
         "\n==-== " BYEL "Menu do Relatório " MAG "==-== \n\n" BYEL "(" MAG
         "1" BYEL ")" BLU " Quantidade de litros"
         " vendida;\n" BYEL "(" MAG "2" BYEL ")" BLU
         " Valor total arrecadado com as vendas;\n" BYEL "(" MAG "3" BYEL
         ")" BLU " "
         "Quantidade de veículos atendidos; \n" BYEL "(" MAG "4" BYEL ")" BLU
         " Quantidade de combustível "
         "restante no tanque;\n" BYEL "(" MAG "5" BYEL ")" BLU
         " Gerar arquivo para impressão (Informações de 1, 2, 3 e 4); \n" BYEL
         "(" MAG "6" BYEL ")" RED " Voltar ao menu "
         "anterior.\n\n" MAG "==-== " BYEL " Menu do Relatório " MAG
         "==-==" WHT);
  printf("\nDigite: ");
  scanf("%d", &op);
  return op;
}

int menuabastecer(int op) {
  printf(RED "\nNão temos a gasolina suficiente que você está pedindo.\n"
             "" GRN "Por favor, escolha uma das opções\n\n" BLU "(" YEL "1" BLU
             ")" GRN " Pedir outra "
             "quantidade de combustível.\n" BLU "(" YEL "2" BLU ")" GRN ""
             " Abastecer com o combustível "
             "restante.\n" BLU "(" YEL "3" BLU ")" RED " Sair da fila\n" WHT
             "Digite: ");
  scanf("%d", &op);
  return op;
}

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
  atendidos.AnoDoCarro = principal.AnoDoCarro;
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
  *CFila = 0;
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
  if (Tgasolina > 100) {
    printf(MAG "\nRestam " BGRN "%.f Litros.\n" WHT, Tgasolina);
  } else if (Tgasolina > 50) {
    printf(MAG "\nRestam " BYEL "%.f Litros.\n" WHT, Tgasolina);
  } else {
    printf(MAG "\nRestam " RED "%.f Litros.\n" WHT, Tgasolina);
  }
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

  printf(GRN "\nPressione a tecla Enter para continuar.\n" WHT);
}

void Tabela(float preco, float *gasolina, int *CFila) {
  printf(BYEL "Preço da Gasolina: " BLU "R$ %.2f Reais.\n", preco);
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
  printf(MAG "Gasolina Disponível: " BLU "%1.f Litros\n" WHT, *gasolina);
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
    printf(GRN "\nArquivo impresso!\n");
   
  } else if (*CAbastecido > 1) {
    printf(CYN "\nForam vendidos " BBLU "%.f litros" CYN
               " de gasolina;\nForam vendidos até "
               "agora " BGRN "R$ "
               "%.f" CYN " de combustível;\nForam atendidos " BYEL
               "%d Carros;" CYN "\nRestam " BBLU "%.f "
               "litros" CYN " de combustível.\n" WHT,
           *Somavendida, *SomaTotal, *CAbastecido, *Tgasolina);
    printf(GRN "\nArquivo impresso!\n");
   
  } else {
    printf(CYN "\n" RED "Não foi vendido nenhum combustível;\nNão houve nenhum "
               "Lucro;\nNenhum Carro foi atendido;\n" BGRN
               "O Tanque de combustível está cheio.\n" WHT);
    printf(GRN "\nArquivo impresso!\n");
  
  }
}

void ArquivoDados(float *Somavendida, float *SomaTotal, int *CAbastecido,
                  float *Tgasolina, FILE *A) {
  if (*CAbastecido == 0) {
    fprintf(A, "Nenhum carro foi informado.");
  } else if (*CAbastecido == 1) {
    fprintf(A,"==-== Informações gerais ==-==\nForam vendidos %.f litros de "
            "gasolina;\nForam vendidos até "
            "agora R$ %.f de combustível;\nFoi atendido %d Carro;\nRestam %.f "
            "litros de combustível.\n",
            *Somavendida, *SomaTotal, *CAbastecido, *Tgasolina);
  } else if (*CAbastecido > 1) {
    fprintf(A,
            "==-== Informações gerais ==-==\nForam vendidos %.f litros de "
            "gasolina;\nForam vendidos até "
            "agora R$ %.f de combustível;\nForam atendidos %d Carros;\nRestam "
            "%.f litros de combustível.\n",
            *Somavendida, *SomaTotal, *CAbastecido, *Tgasolina);
  } else {
    fprintf(A, "==-== Informações gerais ==-==\n"
               "Não foi vendido nenhum combustível;\nNão houve nenhum "
               "Lucro;\nNenhum Carro foi atendido;\n"
               "O Tanque de combustível está cheio.\n");
  }
}

void ArquivoCarros(struct TCarro vetor[], int CAbastecido, FILE *A) {
  fprintf(A, "\n==-= Veículos Atendidos ==-==\n\n");
  for (int cont = 0; cont < CAbastecido; cont++) {
    fprintf(A, "\nInformações do Veículo %d", cont + 1);
    fprintf(A, "\nProprietário: %s", vetor[cont + 1].NomeProprietario);
    fprintf(A, "\nModelo: %s", vetor[cont + 1].ModeloDoCarro);
    fprintf(A, "\nAno de Produção: %d", vetor[cont + 1].AnoDoCarro);
    fprintf(A, "\nPlaca: %s", vetor[cont + 1].Placa);
  }
}