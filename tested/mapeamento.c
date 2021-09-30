#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//TAMANHO DO DISPLAY
const int WIDTH = 500;
const int HEIGHT = 500;

//BASE PARA INPUTS
bool keys[] = { false, false, false, false };
enum KEYS{UP, DOWN, LEFT, RIGHT};

int main(void)
{
	//VARIAVEIS
	bool done = false;
	bool render = false;

	int xOff = 0;
	int yOff = 0;

	int mapColumns = 10;	//quantidade de colunas
	int mapSize = 100;		//tamanho total do mapa
	int tileSize = 50;		//pixel por tile

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

	//VARIAVEIS DO ALLEGRO
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_BITMAP *bgSheet = NULL;

	//TEST INIT
	if (!al_init())
		return -1;

	//CRIAÇÃO DISPLAY
	display = al_create_display(WIDTH, HEIGHT);

	//TEST DISPLAY
	if (!display)
		return -1;

	//INIT MODULOS
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	//ATRIBUINDO A BITMAP PARA A VARIAVEL
	bgSheet = al_load_bitmap("../imagens/basic.png");

	//ATRIBUINDO OS VALORES AS VARIAVEIS
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	//FILA DE AÇÕES
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//inputs
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			//movimentação da tela
			xOff -= keys[RIGHT] * 5;
			xOff += keys[LEFT] * 5;
			xOff -= keys[DOWN] * 5;
			xOff += keys[UP] * 5;

			render = true;
		}
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			
			//Pega o bitmap tiles.png e utiliza dele para fazer outro bitmap usando a matriz.
			for (int i = 0; i < mapSize; i++)
			{
				al_draw_bitmap_region(bgSheet, tileSize* map[i], 0, tileSize, tileSize, xOff + tileSize * (i % mapColumns), yOff + tileSize * (i / mapColumns), 0);
			}

			//DOUBLE BUFFERING
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}
	//LIMPEZA
	al_destroy_bitmap(bgSheet);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}
