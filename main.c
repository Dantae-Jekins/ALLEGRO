#include <allegro5/allegro.h>
#include <stdio.h>

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

int main(){

    bool pulando = false;
    bool caindo  = false;

    player.posx = 0;
    player.posy = 0;

    al_init();
    al_install_keyboard();
    ALLEGRO_DISPLAY * display = al_create_display(100, 100);
    ALLEGRO_EVENT_QUEUE * EventQueue = al_create_event_queue();
    ALLEGRO_TIMER * timer = al_create_timer(1.0 / 10);

    al_register_event_source(EventQueue, al_get_keyboard_event_source());
    al_register_event_source(EventQueue, al_get_display_event_source(display));
    al_register_event_source(EventQueue, al_get_timer_event_source(timer));

    bool Exit = false;
    
    while (!Exit){

        al_start_timer(timer);

        ALLEGRO_EVENT Event;
        al_wait_for_event(EventQueue, &Event);
        ALLEGRO_KEYBOARD_STATE keystate;
        al_get_keyboard_state(&keystate);

        if (Event.type == ALLEGRO_EVENT_TIMER) {

            //Movimenta��o X

            if (al_key_down(&keystate, ALLEGRO_KEY_RIGHT)) {
                player.posx += 5;
            }

            if (al_key_down(&keystate, ALLEGRO_KEY_LEFT)) {
                player.posx += -5;
            }

            //Movimenta��o Y

            if ((al_key_down(&keystate, ALLEGRO_KEY_UP)) && !(caindo)) {
                player.posy += 5;
                pulando = true;
            }
            if (
                !(al_key_down(&keystate, ALLEGRO_KEY_UP)) && (pulando)
                ||(player.posy >= 60) 
                ) {
                pulando = false;
                caindo  = true;
            }  

            if (caindo)
            {
                player.posy -= 5;    
            }
            if (player.posy <= 0)
            {
                caindo  = false;
            }

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