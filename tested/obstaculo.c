#include <stdio.h>
#include <stdbool.h>

#define caixas 10
struct caixa
{
  bool existe; // atributos da caixa
  int posx;
  int posy;
  int type;

} box[caixas]; // 10 caixas

// caixa = struct
// caixas = variável

//jogador
struct jogador
{
  int estado;
  int oxygen;
  int posx;
  int posy;
  int tamx;
  int tamy;

} player;

int main()
{
  // Caixas para teste:
  box[2].existe = true;
  box[2].posx = 32;
  box[2].posy = 36;
  box[2].type = 2;
  //32 36
  //52 56

  box[3].existe = true;
  box[3].posx = 17;
  box[3].posy = 12;
  box[3].type = 2;
  //17 12
  //37 32

  // Apenas teste
  //tipo=1 OXIGENIO
  player.estado = 1;  // vivo
  player.oxygen = 10; // oxigênio
  scanf("%d %d", &player.posx, &player.posy);

  player.tamx = 10;
  player.tamy = 10;

  int inix = 5; // posição inicial do player x
  int iniy = 5; // posição inicial do player y

  // Daqui pra baixo será tudo implementado
  for (int id = 0; id < caixas; id++) // PERCORRE TODAS AS CAIXAS
  {
    if (box[id].existe) //caixas, tipo é um atributo da caixa
    {
      // variáveis caixa
      int tamx;
      int tamy;
      bool colisao;
      printf("\nAchamos a caixa %d!", id);

      // Quando for do tipo 2 (Obstáculo)
      if (box[id].type == 2)
      {
        tamx = 20;
        tamy = 20;

        //Colisão
        for (int x = 0; x <= player.tamx; x++) // quando x = 0, cdx = player.posx; quando  x =1, cdx 1 + player.posx, esse x vai até o tamanho do jogador (player.tamx = 10, x = 10)
        {
          for (int y = 0; y <= player.tamy; y++)
          {
            int cdx = player.posx + x; // tudo o que o jogador ocupa na horizontal
            int cdy = player.posy + y; // tudo que o jogador ocupa na vertical

            // if que verifica a colisão entre player (cdx) e as caixas box[id]
            if ((cdx >= box[id].posx) && (cdx <= box[id].posx + tamx)     // tudo o que a caixa ocupar na horizontal
                && (cdy >= box[id].posy) && (cdy <= box[id].posy + tamy)) // tudo o que a caixxa ocupar na vertical
            {
              player.posx = inix;
              player.posy = iniy;
              player.oxygen -= 2;
              printf("\nOcorreu a colisão no bloco tipo 2: %d", id);
              colisao = true;
              break;
            }
          }
          if (colisao)
            break;
        }

        // vê se existe colisão entre player e caixa;
        // dependendo do tipo acontece algo diferente;
        // João:   retorna ao ponto 0,0 e perde oxigênio;
        // Arthur: ganha oxigênio e a caixa é destruida;
      }
    }
    else
    {
      printf("\nCaixa do ID %d não existe", id);
    }
  }
  return 0;
}