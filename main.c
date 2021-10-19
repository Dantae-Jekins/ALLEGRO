#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>

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

// tamanho do jogador
#define ply_x 30
#define ply_y 50

//Mapa
int mapColu = 10;	//quantidade de colunas
int mapSize = 100;		//tamanho total do mapa

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
  int posx;
  int posy;

} player;

//FUN��ES
bool setup(void)
{
  // Retorna true se concluído com sucesso
  // ou false se ocorreu algum erro.
  
  // Inicializa as estruturas
  printf("\nsettando estruturas");
  for (size_t i = 0; i < txt_boxes; i++)
    txtbox[i].existe = false;

  for (size_t i = 0; i < caixas; i++)
    box[i].existe = false;
  
  player.estado = 1;
  player.oxygen = 10;

  // Inicializa o ALLEGRO
  printf("\nsettando allegro");
  bool checkup = true;
  if (!al_init())
  {
    printf("\nal_init n�o inicializado");
    checkup = false;
  }
  if (!al_install_keyboard())
  {
    printf("\nal_install_keyboard n�o inicializado");
    checkup = false;
  }
  if (!al_init_font_addon())
  {
    printf("\nal_init_font_addon n�o inicializado");
    checkup = false;
  }
  if (!al_init_ttf_addon())
  {
    printf("\nal_init_ttf_addon n�o inicializado");
    checkup = false;
  }
  if (!al_init_primitives_addon())
  {
    printf("\nal_init_primitives_addon n�o inicializado");
    checkup = false;
  }
  if (!al_init_image_addon())
  {
    printf("\nal_init_image_addon n�o inicializado");
    checkup = false;
  }
  
  return checkup;
  // permite que a função analise vários de
  // uma vez, sem parar no primeiro.
}

bool render_and_collide()
{    
  ALLEGRO_COLOR cor;
  bool set = true;
  int px;
  int py;
  
  //mapa
  for (int i = 0; i < mapSize; i++)
  {
    px = tileSiz*(i%mapColu);
    py = tileSiz*(i/mapColu);
    
    if (map[i] == 0)
      cor = al_map_rgb(30, 10, 30);
    else if (map[i] == 1) 
      cor = al_map_rgb(120,30,100);
    else
    { 
      printf("render() map[%d] cont�m tipo n�o registrado", i);
      set = false;
    }
    al_draw_filled_rectangle(px, py, px+tileSiz, py+tileSiz, cor);  
  }
  
  //personagem
  px = player.posx;
  py = player.posy;
  switch(player.estado)
  {
    case 1: // vivo
      cor = al_map_rgb(60,60,140);
      int tamx = ply_x;
      int tamy = ply_y;
      al_draw_filled_rectangle(px, py, px+tamx, py+tamy, cor);
      break;

    case 0:
      printf("\nrender() player.estado = 0 n�o implementado"); 
      break;

    default:
      printf("\nrender() player.estado em valores n�o aceit�veis");
      set = false;
      break;
  }

  //caixas
  for(int id = 0; id < caixas; id++)
  {
    if (box[id].existe)
    {
      int tamx;
      int tamy;
      ALLEGRO_COLOR cor;
      if (box[id].type == 0)
      {
        printf("men.?");
        tamx = 5;
        tamy = 5;
        cor = al_map_rgb(0, 0, 0);
      }
      else if (box[id].type == 1)
      {
        tamx = typ1x;
        tamy = typ1y;
        cor = al_map_rgb(50, 50, 200);
      }
      else if (box[id].type == 2)
      {
        tamx = typ2x;
        tamy = typ2y;
        cor = al_map_rgb(200, 50, 50);
      }
      al_draw_filled_rectangle(
      box[id].posx,
      box[id].posy,
      tamx,
      tamy,
      cor
      );  
    }
  }

  return set;
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
    printf("\nN�O EXISTEM BLOCOS DISPON�VEIS");
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
      printf("\nN�O EXISTEM BLOCOS DE TEXTO DISPON�VEIS");
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
  ALLEGRO_TIMER       *timer = al_create_timer(1.0 / fps);     
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
  bool lendo_teclado = false;
  
  //EXPERIMENTAL v !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  
  int inix = 10;
  int iniy = 10;  

  //EXPERIMENTAL ^ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  while (rodando)
  {
    //Espera um evento
    ALLEGRO_EVENT evento;
    ALLEGRO_KEYBOARD_STATE keystate;
    al_start_timer(timer);
    al_get_keyboard_state(&keystate);
    al_wait_for_event(queue, &evento);
    
    if (evento.type == ALLEGRO_EVENT_TIMER)
    {
      if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
      {
        rodando = false;
      }
      else
      {
        //renderiza a tela aqui 
        al_clear_to_color(al_map_rgb(0,0,0));
        render_and_collide(); 
        al_flip_display();
        
        if (evento.type == ALLEGRO_EVENT_TIMER) 
        {
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                lendo_teclado = true;
            }
            else if (evento.type == ALLEGRO_EVENT_KEY_UP) {
                lendo_teclado = false;
            }

            if (al_key_down(&keystate, ALLEGRO_KEY_RIGHT))
                player.posx += 5;

            if (al_key_down(&keystate, ALLEGRO_KEY_LEFT))
                player.posx += -5;

            if (al_key_down(&keystate, ALLEGRO_KEY_UP))
                player.posy += -5;

            if (al_key_down(&keystate, ALLEGRO_KEY_DOWN))
                player.posy += 5;
              
            printf("posx %d\n", player.posx);
            printf("posy %d\n", player.posy);
        }
        //responde � colis�es aqui
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
                    tamx = typ1x;
                    tamy = typ1y;
                }
                else if (box[id].type == 2)
                {
                    tamx = typ2x;
                    tamy = typ2y;
                }

                //v� se existe colis�o
                for (int x = 0; x <= ply_x; x++)               
                {
                    for (int y = 0; y <= ply_y; y++)
                    {
                        int cdx = player.posx + x; 
                        int cdy = player.posy + y; 

                        if ((cdx >= box[id].posx) && (cdx <= box[id].posx + tamx)     
                            && (cdy >= box[id].posy) && (cdy <= box[id].posy + tamy)) 
                        {
                          // analisa colis�es
                          if(box[id].type == 2) // obst�culo
                          { 
                            player.posx = inix;
                            player.posy = iniy;
                            player.oxygen -= 2;
                            printf("\nOcorreu a colis�o no bloco tipo 2: %d", id);
                            colisao = true;
                            break;
                          }
                          else if(box[id].type == 1) // cilindro
                          {
                            player.oxygen += 5; 
                            box[id].existe = false;
                            printf("\nOcorreu a colis�o no bloco tipo 1: %d", id);
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
