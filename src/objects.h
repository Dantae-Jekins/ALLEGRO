// variáveis gerais
#define height 720
#define width 1080
#define tileSiz 50
#define fps 60.0

// tamanhos dos tipos
#define typ1x 40
#define typ1y 80
#define typ2x 50
#define typ2y 50
#define speed 5

// tamanho do jogador
#define ply_x 30
#define ply_y 50

//Mapa
int mapColu = 10;  //quantidade de colunas
int mapSize = 100; //tamanho total do mapa
int initx = 10;
int inity = 10;
int endx = 100;
int endy = 100;
int map[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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
} player;

int genBox()
{
  // prepara uma estrutura "box" de posições, tamanhos definidos
  // e que deve ser renderizada por outra função.
  int ID = -1;
  printf("\nBUSCANDO BLOCO LIVRE");
  for (size_t i = 0; i < caixas; i++)
  {
    // loop entre os blocos para ver qual está dispodinível
    if (!box[i].existe)
    {
      // achou um bloco disponível
      ID = i;
      box[ID].existe = true;
      printf("\nBLOCO LIVRE ID.%d", ID);
      break;
    }
  }
  if (ID < 0)
  {
    printf("\nN�O EXISTEM BLOCOS DISPON�VEIS");
    return -1;
  }

  // a função retorna o ID da textbox.
  return ID;
}

int genChat(char *text, int type)
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
  // se achou deve alterar os conteúdos.
}
