#include <allegro5/allegro.h>
#include <stdio.h>

<<<<<<< Updated upstream
int main()
{

    al_init();
    al_install_keyboard();
      
    // nós lemos do display.
    ALLEGRO_DISPLAY     *display    = al_create_display(100, 100);
    ALLEGRO_EVENT_QUEUE *EventQueue = al_create_event_queue();

    al_register_event_source(EventQueue, al_get_keyboard_event_source()); ///Tell allegro to get events from the keyboard
    al_register_event_source(EventQueue, al_get_display_event_source(display));    
    bool Exit = false;
    bool lendo_teclado = false;
    while ( !Exit )
    {
      ALLEGRO_EVENT Event;
      // Espera por um evento
      al_wait_for_event(EventQueue, &Event);

      // Checa se o teclado foi pressinado
      if (Event.type == ALLEGRO_EVENT_KEY_DOWN)
      {
        lendo_teclado = true;
      }
      else if (Event.type == ALLEGRO_EVENT_KEY_UP)
      {
        lendo_teclado = false;
      } 
      
      // Checa qual foi a tecla
      if ( lendo_teclado )
      {
        system("clear");
        if (Event.keyboard.keycode == ALLEGRO_KEY_LEFT)
        {
         printf("<--"); 
        }
        if (Event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
        {
          printf("-->"); 
        }
        if (Event.keyboard.keycode == ALLEGRO_KEY_UP)
        {
          printf("cima");
        }
        if (Event.keyboard.keycode == ALLEGRO_KEY_DOWN)
        { 
          printf("baixo");
          Exit = true;
        }
        fflush(stdout);
      }
    }
    al_destroy_display(display);
    al_uninstall_keyboard();
    al_destroy_event_queue(EventQueue);
    return 0;
}

=======

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
    int velocidade = 0;

    player.posx = 0;

    al_init();
    al_install_keyboard();
    ALLEGRO_DISPLAY * display = al_create_display(100, 100);
    ALLEGRO_EVENT_QUEUE * EventQueue = al_create_event_queue();
    ALLEGRO_TIMER * timer = al_create_timer(1.0 / 10);

    al_register_event_source(EventQueue, al_get_keyboard_event_source());
    al_register_event_source(EventQueue, al_get_display_event_source(display));
    al_register_event_source(EventQueue, al_get_timer_event_source(timer));

    bool Exit = false;
    bool lendo_teclado = false;
    
    while (!Exit){

        al_start_timer(timer);

        ALLEGRO_EVENT Event;
        al_wait_for_event(EventQueue, &Event);
        ALLEGRO_KEYBOARD_STATE keystate;
        al_get_keyboard_state(&keystate);

        if (Event.type == ALLEGRO_EVENT_TIMER) {

            if (Event.type == ALLEGRO_EVENT_KEY_DOWN) {
                lendo_teclado = true;
            }
            else if (Event.type == ALLEGRO_EVENT_KEY_UP) {
                lendo_teclado = false;
            }

            if (al_key_down(&keystate, ALLEGRO_KEY_RIGHT))
                player.posx += 5;
                printf("posx %d\n", player.posx);
                printf("posy %d\n", player.posy);

            if (al_key_down(&keystate, ALLEGRO_KEY_LEFT))
                player.posx += -5;
                printf("posx %d\n", player.posx);
                printf("posy %d\n", player.posy);
        }
    
    }
    system("pause");
    al_destroy_display(display);
    al_uninstall_keyboard();
    al_destroy_event_queue(EventQueue);
    al_destroy_timer(timer);
    return 0;
}
>>>>>>> Stashed changes
