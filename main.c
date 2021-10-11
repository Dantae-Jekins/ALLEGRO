#include <allegro5/allegro.h>
#include <stdio.h>

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

