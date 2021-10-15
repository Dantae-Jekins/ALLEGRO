#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>

#define height 720
#define width 1080

//Mapa
int mapColu = 10;	//quantidade de colunas
int mapSize = 100;		//tamanho total do mapa
int tileSiz = 50;		//pixel por tile

int map[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
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
  int tamx;
  int tamy;
  int posx;
  int posy;

} player;

//FUN«’ES
bool setup(void)
{
  // Retorna true se conclu√≠do com sucesso
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
    printf("\nal_init n√o inicializado");
    checkup = false;
  }
  if (!al_install_keyboard())
  {
    printf("\nal_install_keyboard n√o inicializado");
    checkup = false;
  }
  if (!al_init_font_addon())
  {
    printf("\nal_init_font_addon n√o inicializado");
    checkup = false;
  }
  if (!al_init_ttf_addon())
  {
    printf("\nal_init_ttf_addon n√o inicializado");
    checkup = false;
  }
  if (!al_init_primitives_addon())
  {
    printf("\nal_init_primitives_addon n√o inicializado");
    checkup = false;
  }
  if (!al_init_image_addon())
  {
    printf("\nal_init_image_addon n„o inicializado");
    checkup = false;
  }

  return checkup;
  // permite que a fun√ß√£o analise v√°rios de
  // uma vez, sem parar no primeiro.
}

void setupPlayer()
{
  player.estado = 1;
  player.oxygen = 20;
  player.tamx   = 25;
  player.tamy   = 50;
}

void genQuadrado
(int posx1, int posy1, int posx2, int posy2, ALLEGRO_COLOR cor)
{
  al_draw_filled_rectangle(posx1, posy1, posx2, posy2, cor);
}

int genBox()
{
  // prepara uma estrutura "box" de posi√ß√µes, tamanhos definidos
  // e que deve ser renderizada por outra fun√ß√£o.
  int ID = -1;
  printf("\nBUSCANDO BLOCO LIVRE");
  for (size_t i = 0; i < caixas; i++)
  {
    // loop entre os blocos para ver qual est√° dispodin√≠vel
    if (!box[i].existe)
    {
      // achou um bloco dispon√≠vel
      ID = i;
      box[ID].existe = true;
      printf("\nBLOCO LIVRE ID.%d",ID);
      break;
    }
  }
  if (ID < 0)
  {
    printf("\nN√O EXISTEM BLOCOS DISPONÕVEIS");
    return -1;
  }

  // a fun√ß√£o retorna o ID da textbox.
  return ID;
}


int genChat(char *text, int type, int ID)
{
  // a fun√ß√£o ou recebe ou desenha uma txtbox 
  // e ent√£o altera seus valores.
  
  // negativo para inexist√™ncia
  if (ID < 0)
  {
    printf("\nBUSCANDO BLOCO DE TEXTO LIVRE");
    for (size_t i = 0; i < txt_boxes; i++)
    {
      // loop entre os blocos para ver qual est√° dispodin√≠vel
      if (!txtbox[i].existe)
      {
        // achou um bloco dispon√≠vel
        ID = i;
        txtbox[ID].existe = true;
        printf("\nBLOCO DE TEXTO LIVRE ID.%d",ID);
        break;
      }
    }
    if (ID < 0)
    {
      printf("\nN√O EXISTEM BLOCOS DE TEXTO DISPONÕVEIS");
      return -1;
    }
  }
  // se achou deve alterar os conte√∫dos.
  txtbox[ID].text = text;
  txtbox[ID].type = type;

  printf("\nCAIXA DE ID.%d SETTADA", ID);
  return ID;
}


int main(void)
{
  // !!!______SETUP______!!!
  // Inicializa√ß√£o e an√°lise de erro 
  printf("\nEXECUTANDO MAIN\n");
  if (!setup())
  {
    printf("\nAbortando execu√ß√£o");
    return -1;
  }
  
  // Inicializa√ß√£o das estruturas ALLEGRO
  ALLEGRO_DISPLAY   *display = al_create_display(width, height);
  ALLEGRO_TIMER       *timer = al_create_timer(1.0 / 30.0);
  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  ALLEGRO_FONT *SANS18 = 
  al_load_font("fonts/OpenSans-Bold.ttf", 18, 0);
  
  if(!display || !timer || !queue)
  {
    printf("\n Estruturas ALLEGRO n√£o inicializadas");
    return -1;
  }

  // Registro dos eventos ALLEGRO
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_keyboard_event_source());
  
  
  // Inicializa√ß√£o do jogo
  bool pausado = false;
  bool rodando = true;

  al_start_timer(timer);
  
  //EXPERIMENTAL v !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  
  int inix = 10;
  int iniy = 10;  

  //EXPERIMENTAL ^ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  while (rodando)
  {
    //limpa a tela
    al_clear_to_color(al_map_rgb(200,200,200));
    ALLEGRO_EVENT evento;

    //espera um evento
    al_wait_for_event(queue, &evento);

    //encerra√ß√£o do programa
    if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
      rodando = false;
    }
    else
    {
      //renderiza a tela aqui  
      //responde ‡ colisıes aqui
      for (int id = 0; id < caixas; id++)       
      {
          if (box[id].existe) 
          {
              int tamx;
              int tamy;
              bool colisao;
              printf("\nAchamos a caixa %d!", id);

              //define o tamanho para cada caixa
              if (box[id].type == 1)               
              {
                  tamx = 50;
                  tamy = 50;
              }
              else if (box[id].type == 2)
              {
                  tamx = 30;
                  tamy = 60;
              }

              //vÍ se existe colis„o
              for (int x = 0; x <= player.tamx; x++)               
              {
                  for (int y = 0; y <= player.tamy; y++)
                  {
                      int cdx = player.posx + x; 
                      int cdy = player.posy + y; 

                      if ((cdx >= box[id].posx) && (cdx <= box[id].posx + tamx)     
                          && (cdy >= box[id].posy) && (cdy <= box[id].posy + tamy)) 
                      {
                        // analisa colisıes
                        if(box[id].type == 2) // obst·culo
                        { 
                          player.posx = inix;
                          player.posy = iniy;
                          player.oxygen -= 2;
                          printf("\nOcorreu a colis„o no bloco tipo 2: %d", id);
                          colisao = true;
                          break;
                        }
                        else if(box[id].type == 1) // cilindro
                        {
                          player.oxygen += 5; 
                          box[id].existe = false;
                          printf("\nOcorreu a colis„o no bloco tipo 1: %d", id);
                          colisao = true;
                          break;
                        }
                      }
                  }
                  if (colisao)
                      break;
              }
          }
      }
    }

    al_flip_display();
  }
    
  // Destrui√ß√£o das estruturas ALLEGRO
  al_destroy_event_queue(queue);
  al_destroy_display(display);
  al_destroy_timer(timer);
  al_uninstall_keyboard();
  printf("\n");
}

