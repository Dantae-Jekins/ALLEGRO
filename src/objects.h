//Mapa

struct mapp
{
  int col;
  int tam;
  int code;
  int inix;
  int iniy;
  int *map;
} mapa;

//Estruturas do jogo
#define txt_boxes 4
struct textos
{
  bool existe;
  int type;
  char *text;
} txtbox[txt_boxes];

//interagiveis
#define caixas 10
struct caixa
{
  bool existe;
  int posx;
  int posy;
  int type;
} box[caixas];

//jogador
struct jogador
{
  int estado;
  int oxygen;
  int posx;
  int posy;
  int fimy;

  bool pulando;
  bool caindo;
} player;

// funções
int genBox()
{
  // prepara uma estrutura "box" de posições, tamanhos definidos
  // e que deve ser renderizada por outra função.
  
  printf("\nBUSCANDO BLOCO LIVRE");
  for (size_t i = 0; i < caixas; i++)
  {
    // loop entre os blocos para ver qual está dispodinível
    if (!box[i].existe)
    {
      // achou um bloco disponível
      box[i].existe = true;
      printf("\nBLOCO LIVRE ID.%ld", i);
      return i;
    }
  }
  printf("\nNÃO EXISTEM BLOCOS LIVRES");
  return -1;
}

int genChat()
{
  // a função ou recebe ou desenha uma txtbox
  // e então altera seus valores.

  printf("\nBUSCANDO BLOCO DE TEXTO LIVRE");
  for (size_t i = 0; i < txt_boxes; i++)
  {
    // loop entre os blocos para ver qual está dispodinível
    if (!txtbox[i].existe)
    {
      // achou um bloco disponível
      txtbox[i].existe = true;
      printf("\nBLOCO DE TEXTO LIVRE ID.%ld", i);
      return i;
    }
  }
  printf("\nN�O EXISTEM BLOCOS DE TEXTO DISPON�VEIS");
  return -1;
}
