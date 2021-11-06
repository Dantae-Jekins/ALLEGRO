//ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

//STANDART LIBRARIES
#include <stdio.h>
#include <stdlib.h>

//LOCAL FILES
#include "logic.h"     // FNS GERAIS
#include "variaveis.h" // VARS GLOBAIS
#include "objects.h"   // STRUCTS
#include "setup.h"     // SETUP
#include "mapper.h"    // MAPA
#include "render.h"    // RENDERIZAÇÃO
#include "texter.h"    // CHATS
#include "movement.h"  // MOVIMENTAÇÃO

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
  ALLEGRO_DISPLAY *display = al_create_display(width, height);
  ALLEGRO_TIMER *timer = al_create_timer(1.0 / fps);
  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();

  if (!display || !timer || !queue)
  {
    printf("\n Estruturas ALLEGRO não inicializadas");
    return -1;
  }

  // Registro dos eventos ALLEGRO
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_keyboard_event_source());

  // Inicialização do jogo
  bool rodando = true;
  int timezin = 0;
  //EXPERIMENTAL v !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  int ID1 = genBox();
  box[ID1].posx = 200;
  box[ID1].posy = 280;
  box[ID1].type = 1;

  int ID2 = genBox();
  box[ID2].posx = 400;
  box[ID2].posy = 320;
  box[ID2].type = 2;

  //EXPERIMENTAL ^ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  printf("\n\nSETUP COMPLETO\n");
  al_start_timer(timer);

  // experimental

  while (rodando)
  {
    //Espera um evento
    ALLEGRO_EVENT evento;
    ALLEGRO_KEYBOARD_STATE keystate;

    al_get_keyboard_state(&keystate);
    al_wait_for_event(queue, &evento);
    if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
      rodando = false;
    }
    if (evento.type == ALLEGRO_EVENT_TIMER)
    {
      //renderiza a tela aqui
      al_clear_to_color(al_map_rgb(0, 0, 0));

      bool checkout = true;
      checkout = render_map();
      checkout = render_player();
      checkout = render_boxes(true);
      if (!checkout)
        rodando = 0;
      al_flip_display();

      if (evento.type == ALLEGRO_EVENT_TIMER)
      {
        checkInput(keystate);

        if (timezin == 30)
        {
          player.oxygen -= 1;
          timezin = 0;
          printf("\33[2K oxygen: %d\n", player.oxygen);
          printf("\33[2K posx:   %d\n", player.posx);
          printf("\33[2K posy:   %d\n", player.posy);
          printf("\33[3A");
        }
        timezin++;

        // se o jogador morrer seu pc se fode
      }
    }
  }

  // Destruição das estruturas ALLEGRO

  for(int i = 0; i < bitmap_count; i++)
    al_destroy_bitmap(bitmap[i]);
  al_destroy_event_queue(queue);
  al_destroy_display(display);
  al_destroy_timer(timer);
  al_uninstall_keyboard();
  printf("\n");
}
