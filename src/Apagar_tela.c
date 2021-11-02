#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

//STANDART LIBRARIES
#include <stdio.h>
#include <stdlib.h>

/*
int main(void)
{

    ALLEGRO_DISPLAY* display = NULL;

    // !!!______SETUP______!!!
    // Inicialização e análise de erro
    printf("\nEXECUTANDO MAIN\n");
    if (!al_init())
    {
        printf("\nfalha ao inicializar allegro");
        return -1;
    }

    // Inicialização das estruturas ALLEGRO
    ALLEGRO_DISPLAY* display = al_create_display(500, 500);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 2);
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
    bool rodando = true;
    int oxygen = 100;
 


    while (rodando)
    {
       
        ALLEGRO_EVENT evento;
        ALLEGRO_KEYBOARD_STATE keystate;

        al_get_keyboard_state(&keystate);
        al_wait_for_event(queue, &evento);
    
           if (oxygen <= 0)
             rodando = termino();
       
    }

    // Destruição das estruturas ALLEGRO

    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_destroy_timer(timer);
    printf("\n");
}
*/
bool termino()
{
    
    if (!al_init())
    {
        printf("\nfalha ao inicializar allegro");
        return -1;
    }

    int width = 640;
    int height = 480;
    bool done = false;

    int imagewidth = 0;
    int imageHeight = 0;
    
    al_install_keyboard();
    al_init_image_addon();

    ALLEGRO_DISPLAY* display = al_create_display(width, height);;
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_BITMAP* image = al_load_bitmap("perdeu.bmp");

    

    imagewidth = al_get_bitmap_width(image);
    imageHeight = al_get_bitmap_height(image);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    while (!done)
    {       
        
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(image, width / 2 - imagewidth / 2, height / 2 - imageHeight / 2, 0);

        al_flip_display();
        

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ENTER:
                done = true;
                break;
            }
        }

    }

    al_destroy_bitmap(image);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
  
   
    return 0;

}