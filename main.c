#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>
#include <stdlib.h>

#define height 720
#define width 1080

//Estruturas do jogo
#define txt_boxes 4
struct textos
{
  bool existe; 
  int type;
  char *text;
  
} txtbox[txt_boxes];

#define caixas 64
struct caixa
{
  bool existe;
  int posx;
  int posy;
  int type;

} box[caixas];


//FUNÇÕES
bool setup(void)
{
  // Retorna true se concluído com sucesso
  // ou false se ocorreu algum erro.
  
  // Inicializa as estruturas
  for (size_t i = 0; i < txt_boxes; i++)
    txtbox[i].existe = false;

  for (size_t i = 0; i < caixas; i++)
    box[i].existe = false;

  // Inicializa o ALLEGRO
  bool checkup = true;
  if (!al_init())
  {
    printf("\nal_init não inicializado");
    checkup = false;
  }
  if (!al_install_keyboard())
  {
    printf("\nal_install_keyboard não inicializado");
    checkup = false;
  }
  if (!al_init_font_addon())
  {
    printf("\nal_init_font_addon não inicializado");
    checkup = false;
  }
  if (!al_init_ttf_addon())
  {
    printf("\nal_init_ttf_addon não inicializado");
    checkup = false;
  }
  if (!al_init_primitives_addon())
  {
    printf("\al_init_primitives_addon não inicializado");
    checkup = false;
  }

  return checkup;
  // permite que a função analise vários de
  // uma vez, sem parar no primeiro.
}

void genQuadrado
(int posx1, int posy1, int posx2, int posy2, ALLEGRO_COLOR cor)
{
  al_draw_filled_rectangle(posx1, posy1, posx2, posy2, cor);
}

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
      printf("\nBLOCO LIVRE ID.%d",ID);
      break;
    }
  }
  if (ID < 0)
  {
    printf("\nNÃO EXISTEM BLOCOS DISPONÍVEIS");
    return -1;
  }
  // a função retorna o ID da textbox.
  return ID;
}


int genChat(char *text, int type, int ID)
{
  // a função ou recebe ou desenha uma txtbox 
  // e então altera seus valores.
  
  // negativo para inexistência
  if (ID < 0)
  {
    printf("\nBUSCANDO BLOCO DE TEXTO LIVRE");
    for (size_t i = 0; i < txt_boxes; i++)
    {
      // loop entre os blocos para ver qual está dispodinível
      if (!txtbox[i].existe)
      {
        // achou um bloco disponível
        ID = i;
        txtbox[ID].existe = true;
        printf("\nBLOCO DE TEXTO LIVRE ID.%d",ID);
        break;
      }
    }
    if (ID < 0)
    {
      printf("\nNÃO EXISTEM BLOCOS DE TEXTO DISPONÍVEIS");
      return -1;
    }
  }
  // se achou deve alterar os conteúdos.
  txtbox[ID].text = text;
  txtbox[ID].type = type;

  printf("\nCAIXA DE ID.%d SETTADA", ID);
  return ID;
}


int main(void)
{
  // !!!______SETUP______!!!
  // Inicialização e análise de erro 
  printf("\nEXECUTANDO MAIN\n");
  if (!setup())
  {
    printf("\nAbortando execução");
    return -1;
  }
  
  // Inicialização das estruturas ALLEGRO
  ALLEGRO_DISPLAY   *display = al_create_display(width, height);
  ALLEGRO_TIMER       *timer = al_create_timer(1.0 / 30.0);
  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  ALLEGRO_FONT *SANS18 = 
  al_load_font("fonts/OpenSans-Bold.ttf", 18, 0);
  
  if(!display || !timer || !queue)
  {
    printf("\n Estruturas ALLEGRO não inicializadas");
    return -1;
  }

  // Registro dos eventos ALLEGRO
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_keyboard_event_source());
  
  
  // Inicialização do jogo
  bool pausado = false;
  bool rodando = true;

  al_start_timer(timer);
  
  while (rodando)
  {
    //limpa a tela
    al_clear_to_color(al_map_rgb(200,200,200));
    ALLEGRO_EVENT evento;

    //espera um evento
    al_wait_for_event(queue, &evento);

    //encerração do programa
    if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
      rodando = false;
    }
    else
    {
      //renderiza a tela aqui e 
      //responde à outros eventos aqui
    }
    al_flip_display();
  }
  
  // Destruição das estruturas ALLEGRO
  al_destroy_event_queue(queue);
  al_destroy_display(display);
  al_destroy_timer(timer);
  al_uninstall_keyboard();
  printf("\n");
}
