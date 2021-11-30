//ALLEGRO
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

//STANDART LIBRARIES
#include <stdio.h>
#include <stdlib.h>

//LOCAL FILES
#include "functions.h"

#include "logic.h"      // FNS GERAIS
#include "variaveis.h"  // VARS GLOBAIS
#include "objects.h"    // STRUCTS  
#include "mapper.h"     // MAPA
#include "setup.h"      // SETUP
#include "colisions.h"  // COLISÕES
#include "render.h"     // RENDERIZAÇÃO
#include "eventos.h"    // CHATS
#include "movement.h"   // MOVIMENTAÇÃO

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
    display = al_create_display(width, height);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / fps);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

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
    int timezin = 0;
    printf("\n\nSETUP COMPLETO\n");
    al_start_timer(timer);

    bool rodando = menu();
    while (rodando)
    {
      // evento
      ALLEGRO_EVENT evento;
      ALLEGRO_KEYBOARD_STATE keystate;
      al_get_keyboard_state(&keystate); 
      al_wait_for_event(queue, &evento);
    
      // renderiza
      al_clear_to_color(al_map_rgb(0, 0, 0)); 
      bool checkout = true;
      checkout = render_map();
      checkout = render_player(timezin);
      checkout = render_boxes(true, true);
      checkout = render_oxigenio();
      if (!checkout)
        rodando = 0;
      al_flip_display();

      // espera timer
      if (evento.type == ALLEGRO_EVENT_TIMER)
      {
        checkInput(keystate);
        if (timezin == 20)
        {
          if (!decrement_oxygen())
          {
            rodando = termino();
            player.estado = 0;
          }
          timezin = 0;
          printf("\33[2K estado:    %d\n",player.estado);
          printf("\33[2K oxygen: %.4d\n", player.oxygen);
          printf("\33[2K anim:   %.4d\n", player.anim);
          printf("\33[2K posx:   %.4d\n", player.posx);
          printf("\33[2K posy:   %.4d\n", player.posy);
          printf("\33[5A");
        } timezin++;
        if (player.estado == 3)
          rodando = vitoria();  
      }
    }

  // Destruição das estruturas ALLEGRO

  for (int i = 0; i < bitmap_count; i++)
    al_destroy_bitmap(bitmap[i]);

  for(int i = 0; i < font_count; i++)
    al_destroy_font(FONTES[i]);
  
  al_destroy_event_queue(queue);
  al_destroy_display(display);
  al_destroy_timer(timer);
  al_uninstall_keyboard();
  printf("\n");
}

#define x 65
#define y 94
#define z 10
