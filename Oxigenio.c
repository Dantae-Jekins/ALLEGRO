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
    box[0].existe = true;
    box[0].posx = 3;
    box[0].posy = 5;
    box[0].type = 1;
    //3  5
    //13 15

    box[1].existe = true;
    box[1].posx = 27;
    box[1].posy = 32;
    box[1].type = 1;
    //27 32
    //37 42

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

            // Quando for do tipo 1 (Cilindro Oxigenio)
            if (box[id].type == 1) // tamanho da caixa depende do tipo dela
            {
                // atribuindo valor as variáveis caixa
                tamx = 10;
                tamy = 10;
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
                            player.oxygen += 5; // atribui +5 de oxigenio assim que o player colidir
                            box[id].existe = false;
                            printf("\nOcorreu a colisão no bloco tipo 1: %d", id);
                            colisao = true;
                            break;
                        }
                    }
                    if (colisao)
                        break;
                }
            }
        }
        else
        {
            printf("\nCaixa do ID %d não existe", id);
        }
    }
    return 0;
}