#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define height 720
#define width 1080

void genCirculo(int posx, int posy, int tamanho, ALLEGRO_COLOR cor)
{
    al_draw_filled_circle(posx, posy, tamanho, cor);
}

void genQuadrado(int posx1, int posy1, int posx2, int posy2, ALLEGRO_COLOR cor)
{
    al_draw_filled_rectangle(posx1, posy1, posx2, posy2, cor);
}

int main(void)
{
    al_init(); // Função que Inicializa o allegro

    // VARIÁVEIS DO JOGO
    const int width_t = 640;
    const int height_t = 480;

    // Inicialização allegro
    if (!al_init())
    {
        printf("ERRO: al_init não inicializado!");
        return -1;
    }
    al_install_keyboard(); // Função que Inicializa drive do teclado
    if (!al_install_keyboard())
    {
        printf("\n ERRO al_install_keyboard não inicializado!");
        return -2;
    }

    al_init_primitives_addon(); // Módulo que possibilita adição de primitivos
    if (!al_init_primitives_addon())
    {
        printf("\n ERRO: Primitivos não inicializados!");
        return -3;
    }

    // Inicialização das structs
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);   // Cria um temporizador, seus parâmetros são em segundos por tick. Atualiza 30 vezes por segundo
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue(); // Event_Queue funciona como um "armazém" de eventos.
    ALLEGRO_DISPLAY *disp = al_create_display(width_t, height_t);
    ALLEGRO_FONT *font = al_create_builtin_font();

    // Registro dos eventos ALLEGRO
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    // jogo rodando
    while (1)
    {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(23, 55, 6)); // altera a background color
            /* al_draw_text(font, al_map_rgb(255, 255, 25), 0, 0, 0, "Teste de fontes"); */
            //    **** PRIMITIVOS **** //

            //al_draw_filled_circle(250, 250, 10,  al_map_rgb(234, 0, 0)); // x,y, tamanho, cor
            //al_draw_filled_triangle(50, 400, 100, 300, 150, 400, al_map_rgb(255, 255, 25));
            // al_draw_line: x1,y1, x2,y2 cor, >= 1: thick lines --- 0: hairlines
            // esquerda e depois direita 1° quadrante
            /* ***** 360° *****
            al_draw_line(250, 0, 250, 500, al_map_rgb(0, 0, 0), 2); // vertical principal
            al_draw_line(0, 250, 500, 250, al_map_rgb(0, 0, 0), 2); // horizontal principal
            al_draw_line(0, 0, 500, 500, al_map_rgb(0, 0, 0), 2);   // 1/2
            al_draw_line(500, 0, 0, 500, al_map_rgb(0, 0, 0), 2);   // 1/2
            al_draw_line(0, 125, 500, 375, al_map_rgb(0, 0, 0), 2); // 2/4
            al_draw_line(500, 125, 0, 375, al_map_rgb(0, 0, 0), 2); // 2/4
            al_draw_line(125, 0, 375, 500, al_map_rgb(0, 0, 0), 2); // 1/4
            al_draw_line(375, 0, 125, 500, al_map_rgb(0, 0, 0), 2); // 1/4
            genCirculo(250, 250, 15, al_map_rgb(234, 0, 0));
            */

            //al_draw_filled_rectangle(10, 10, 250, 250, al_map_rgb(44, 55, 66));

            for (int i = 0; i <= 16; i++)
            {
                al_draw_line(0, ((height_t / 16) * i), width_t, ((height_t / 16) * i), al_map_rgb(0, 0, 0), 2);
            }

            for (int i = 0; i <= 16; i++)
            {
                al_draw_line((width_t / 16) * i, 0, ((width_t / 16) * i), height_t, al_map_rgb(255, 0, 0), 2);
            }

            genQuadrado(230, 230, 260, 260, al_map_rgb(44, 55, 66));

            al_flip_display(); // Gera o Back Buffer (segunda tela para os primitivos) e depois passa para o display
            redraw = false;
            //al_shutdown_primitives_addon - Desabilita os primitivos
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp); // libera memória
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}