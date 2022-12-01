#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MenuR;
int main(void) {
  int tamFila, CFila = 0, opcao = 0, oprelatorio, CAbastecido = 0, OpAB, CarroTotal=0, CarroResto;
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
  while (opMenu != 6) {
   Tabela(Precogasolina, &Tgasolina, &CFila);
   if(CFila==0){
     printf(MAG"\nAtualmente atendendo nenhum veículo.\n");
   } else if (CFila >=1){
     printf(MAG"\nAtualmente atendendo o veículo:"BLU" %d\n"MAG"Proprietário: "BLU"%s\n\n", CarroTotal+1, VetorCarro[0].NomeProprietario);
   }
    opMenu = menu(opcao);
    system("clear");
    switch (opMenu) {
    case 1:
      system("clear");
      if (Tgasolina == 0) {
        printf(RED "'Tamo sem gasolina, patrão, procure outro posto de "
                   "gasolina! Volte em outro momento!\n\n" WHT);
        printf(RED "Desta maneira, todos os outros veículos na fila "
                         "foram removidos\n\n" WHT);
        CFila=0;

      } else if (CFila < tamFila) {
        VetorCarro[CFila] = criaCarro(CarroTotal);
        CFila++;
CarroTotal++;
        system("clear");
        printf(GRN "+1 Veículo adicionado à fila!\n\n" WHT);
        printf(GRN "Pressione a tecla Enter para continuar.\n" WHT);

      } else {
        printf(RED "\nFila máxima atingida!\n\n" WHT);
      }
      break;
    case 2:
      if (CFila > 0) {
        if ((Tgasolina < 201) && (Tgasolina >= 1)) {
          TabelaGasoDisp(&Tgasolina);
          printf(YEL "\nDiga quantos litros quer abastecer?:\n" WHT "Digite: ");
          scanf("%f", &gasto);
          system("clear");
          if (gasto > Tgasolina) {
            TabelaGasoDisp(&Tgasolina);
            OpAB = menuabastecer(opcao);
            switch (OpAB) {
            case 1:
              system("clear");
              TabelaGasoDisp(&Tgasolina);
              printf(YEL "\nDiga quantos litros quer abastecer?:\n" WHT
                         "Digite: ");
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
                  VetorAbastecido, (CAbastecido + 1) * sizeof(struct TCarro));
              VetorAbastecido[CAbastecido] = VetorCarro[0];

              reorganizarVetor(VetorCarro, CFila);
              CarroTotal++;
              system("clear");
              printf(GRN "Veículo Abastecido!\n\n" WHT);
              printf(RED "Desta maneira, todos os outros veículos na fila "
                         "foram removidos\n\n" WHT);
              CarroTotal++;
              CarroResto=CFila-1;
              
              break;
            case 3:
              printf(RED "Você foi removido da fila, desculpe pelo "
                         "imprevisto\n\n" WHT);
              CFila--;
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
            CarroTotal++;
            system("clear");
            printf(GRN "\nVeículo Abastecido!\n\n" WHT);
          }

        } else {
          printf(RED "'Tamo sem gasolina, patrão, procure outro posto de "
                     "gasolina! Volte em outro momento!\n\n" WHT);
          CFila = 0;
        }
      } else {
        printf(RED "\nNão há Veículos para abastecer!\n\n" WHT);
      }
      break;
    case 3:
      flush_in();
      system("clear");
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
          printf(CYN "Foram vendidos " YEL "%.f litros" CYN
                     " de gasolina\n\n" WHT,
                 Somavendida);

          break;
          case 2:
          system("clear");
          printf(CYN "Foram vendidos até agora" GRN "R$ %.f" CYN
                     " de combustível\n\n" WHT,
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
                         &Tgasolina, CarroResto); // ser o arquivo
          Arquivo = fopen("Dados.txt", "w");
          ArquivoDados(&Somavendida, &SomaTotal, &CAbastecido, &Tgasolina,
                       Arquivo, CarroResto);
          if (CAbastecido != 0) {
            ArquivoCarros(VetorAbastecido, CAbastecido, Arquivo);
          }
          fclose(Arquivo);

          break;
          case 6:
            system("clear");
          printf(GRN "Voltando ao menu principal...\n\n" WHT);
          break;
        default:
          printf(RED "Opção Inválida!\n\n" WHT);
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
