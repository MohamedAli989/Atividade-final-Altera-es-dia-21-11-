#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void ArquivoCarros(struct TCarro vetor[], int CAbastecido, FILE *A);
void ArquivoDados(float *Somavendida, float *SomaTotal, int *CAbastecido,
                  float *Tgasolina, FILE *A);

int MenuR;
int main(void) {
  int tamFila, CFila = 0, opcao = 0, oprelatorio, CAbastecido = 0, OpAB;
  float Precogasolina, Tgasolina = 200, gasto, Somagasolina = 0, SomaTotal = 0,
                       Somavendida = 0;
  struct TCarro *VetorCarro;
  struct TCarro *VetorAbastecido;
  FILE *Arquivo;

  Precogasolina = inicio(Precogasolina);
  printf("\nQual será o tamanho da fila?:\n");
  scanf("%d", &tamFila);
  VetorCarro = (struct TCarro *)calloc(tamFila, sizeof(struct TCarro));
  VetorAbastecido = (struct TCarro *)calloc(0, sizeof(struct TCarro));
  system("clear");

  // menu--------------------------------------------

  int opMenu = 0;
  while (opMenu != 5) {
    Tabela(Precogasolina, &Tgasolina, &CFila);
    opMenu = menu(opcao);
    system("clear");
    switch (opMenu) {
    case 1:
      system("clear");
      if (CFila < tamFila) {
        VetorCarro[CFila] = criaCarro();
        CFila++;
        printf(GRN "\n+1 Veículo adicionado à fila!\n" WHT);
        printf(GRN "\nPressione a tecla Enter para continuar.\n" WHT);

      } else {
        printf(RED "\nFila máxima atingida!\n" WHT);
      }
      break;
    case 2:
      if (CFila > 0) {
        if ((Tgasolina < 201) && (Tgasolina >= 1)) {
          TabelaGasoDisp(&Tgasolina);
          printf(YEL "\nDiga quantos litros quer abastecer?:\n" WHT "Digite: ");
          scanf("%f", &gasto);
          if (gasto > Tgasolina) {
            TabelaGasoDisp(&Tgasolina);
            OpAB = menuabastecer(opcao);
            switch (OpAB) {
            case 1:
              system("clear");
              TabelaGasoDisp(&Tgasolina);
              printf(YEL "\nDiga quantos litros quer abastecer?: " WHT);
              scanf("%f", &gasto);
              if (gasto > Tgasolina) {
                TabelaGasoDisp(&Tgasolina);
                menuabastecer(opcao);
              }
              break;
            case 2:
              AbastecerAlem(&Somavendida, &Somagasolina, &Tgasolina,
                            &Precogasolina, &SomaTotal, &CAbastecido, &CFila);

              copiarPrincipalParaAtendidos(VetorAbastecido[CFila],
                                           VetorCarro[0]);
              VetorAbastecido = realloc(
                  VetorAbastecido, CAbastecido + 1 * sizeof(struct TCarro));

              reorganizarVetor(VetorCarro, CFila);
              system("clear");
              printf(GRN "\nVeículo Abastecido!\n" WHT);
              break;
            case 3:
              printf(
                  RED
                  "\nVocê foi removido da fila, desculpe pelo imprevisto" WHT);
              CFila = CFila - 1;
              copiarPrincipalParaAtendidos(VetorAbastecido[CFila],
                                           VetorCarro[0]);
              reorganizarVetor(VetorCarro, CFila);
            }
          } else {
            Abastecer(&Somavendida, &Somagasolina, &Tgasolina, &Precogasolina,
                      &SomaTotal, &CAbastecido, &CFila, gasto);
            copiarPrincipalParaAtendidos(VetorAbastecido[CFila], VetorCarro[0]);
            VetorAbastecido = realloc(
                VetorAbastecido, (CAbastecido + 1) * sizeof(struct TCarro));
            VetorAbastecido[CAbastecido] = VetorCarro[0];

            reorganizarVetor(VetorCarro, CFila);
            system("clear");
            printf(GRN "\nVeículo Abastecido!\n" WHT);
          }

        } else {
          printf(RED "'Tamo sem gasolina, patrão, procure outro posto de "
                     "gasolina!\n E vo" WHT);
        }
      } else {
        printf(RED "\nNão há Veículos para abastecer!\n" WHT);
      }
      break;
    case 3:
      flush_in();
      FilaEspera(&CFila, VetorCarro);
      break;
    case 4:
      MenuR = 0;
      // submenu---------------------------------------------------------------------
      while (MenuR != 6) {
        MenuR = menurelatorio(opcao);
        switch (MenuR) {
        case 1:
          system("clear");
          printf(CYN "\nForam vendidos %.f litros de gasolina\n" WHT,
                 Somavendida);
          break;
        case 2:
          system("clear");
          printf(CYN "\nForam vendidos até agora R$ %.f de combustível\n" WHT,
                 SomaTotal);
          break;
        case 3:
          system("clear");
          FilaAtendido(&CAbastecido, VetorAbastecido);
          break;
        case 4:
          system("clear");
          TabelaGasoResto(Tgasolina);
          break;
        case 5:
          system("clear");
          TabelaComCarro(&Somavendida, &SomaTotal, &CAbastecido,
                         &Tgasolina); // ser o arquivo
          Arquivo = fopen("Dados.txt", "w");
          ArquivoDados(&Somavendida, &SomaTotal, &CAbastecido, &Tgasolina,
                       Arquivo);
          ArquivoCarros(VetorAbastecido, CAbastecido, Arquivo);
          fclose(Arquivo);
          break;
        case 6:
          printf(GRN "Voltando ao menu principal...\n" WHT);
          break;
        default:
          printf(RED "Opção Inválida!\n" WHT);
          break;
        }
      }
    case 5:
      system("clear");
      printf(GRN "Menu do Relatório encerrado.\n\n" WHT);
      break;
    default:
      printf(RED "Opção invalida!\n\n" WHT);
      break;
    }
    getchar();
  }
  return 0;
}
//  Impressão do Dados.txt (não consegui colocar no header/impl)
void ArquivoDados(float *Somavendida, float *SomaTotal, int *CAbastecido,
                  float *Tgasolina, FILE *A) {
  if (*CAbastecido == 1) {
    fprintf(A,
            "==-== Informações gerais ==-==\nForam vendidos %.f litros de "
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
  fprintf(A,"\n==-= Veículos Atendidos ==-==\n");
  for (int cont = 0; cont < CAbastecido; cont++) {
    fprintf(A, "\nInformações do Veículo %d", cont + 1);
    fprintf(A, "\nProprietário: %s", vetor[cont + 1].NomeProprietario);
    fprintf(A, "\nModelo: %s", vetor[cont + 1].ModeloDoCarro);
    fprintf(A, "\nAno de Produção: %d", vetor[cont + 1].AnoDoCarro);
    fprintf(A, "\nPlaca: %s", vetor[cont + 1].Placa);
  }
}