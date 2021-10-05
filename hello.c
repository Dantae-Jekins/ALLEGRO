#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    // VARIÁVEIS DO JOGO
    int width = 640;
    int height = 480;
    bool done = false;

    // VARIÁVEIS SPRITES
    const int maxFrame = 8; // quantidade de frames de animação
    int curFrame = 0;       // frame atual
    int frameCount = 0;     // ciclos totais desde a última mudança de animação
    int frameDelay = 5;     // quanto maior o número mais devagar fica

    al_init();

    if (!al_init())
    {
        printf("ERRO: al_init não inicializado!");
        return -1;
    }

    // Variáveis do Allegro
    ALLEGRO_TIMER *timer;                    // Cria um temporizador, seus parâmetros são em segundos por tick. Atualiza 60 vezes por segundo
    ALLEGRO_EVENT_QUEUE *event_queue = NULL; // Event_Queue funciona como um "armazém" de eventos.
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *image[maxFrame]; // array de bitmaps (toda vez que o personagem andar para um novo bloco é criado uma bitmap. Vão ser criados 8 bitmaps)

    display = al_create_display(width, height); //criando o objeto de display

    if (!display)
        return -1;

    // addon inicialização (módulos)
    al_install_keyboard(); // Função que Inicializa drive do teclado
    al_init_image_addon();
    al_init_primitives_addon(); // Módulo que possibilita adição de primitivos

    image[0] = al_load_bitmap("marte.jpg");
    image[1] = al_load_bitmap("marte.jpg");
    image[2] = al_load_bitmap("marte.jpg");
    image[3] = al_load_bitmap("marte.jpg");
    image[4] = al_load_bitmap("marte.jpg");
    image[5] = al_load_bitmap("marte.jpg");
    image[6] = al_load_bitmap("marte.jpg");
    image[7] = al_load_bitmap("marte.jpg");

    // Registro dos eventos ALLEGRO
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60); // dispara 60 vezes por segundo

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_start_timer(timer);

    //al_start_timer(timer);
    // jogo rodando
    while (!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            if (++frameCount >= frameDelay)
            {
                if (++curFrame >= maxFrame)
                    curFrame = 0;

                frameCount = 0;
            }
        }

        al_draw_bitmap(image[curFrame], 200, 100, 0);

        al_flip_display(); // UTILIZAR POR ÚLTIMO, passa do Back buffering pro display normal
        al_clear_to_color(al_map_rgb(0, 0, 0));
    }

    al_destroy_event_queue(event_queue);
    al_destroy_display(display); // libera memória

    return 0;
}
