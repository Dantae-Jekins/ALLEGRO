#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>

#define height 720
#define width 1080

bool setup(void)
{
	// Retorna true se concluído com sucesso
	// ou false se ocorreu algum erro.
	bool checkup = true;
	if(!al_init())
	{
		printf("\nal_init não inicializado");
		checkup = false;
	}
	if(!al_install_keyboard())
	{
		printf("\nal_install_keyboard não inicializado");
		checkup = false;
	}
	if(!al_init_font_addon())
	{
		printf("\nal_init_font_addon não inicializado");
		checkup = false;
	}
	if(!al_init_ttf_addon())
	{
		printf("\nal_init_ttf_addon não inicializado");
		checkup = false;
	}

	return checkup; 
	// permite que a função analise vários de
	// uma vez, sem parar no primeiro.
}

void chatbox(char *text, ALLEGRO_FONT *fonte)
{
	printf("EXECUTANDO CHATBOX\n");
	al_draw_text( 
		fonte, al_map_rgb(100,255,100), 
		10.0, 10.0, ALLEGRO_ALIGN_LEFT,
		text
	);
	al_flip_display();
	getchar();
}

int main(int argc, char **argv)
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
	ALLEGRO_TIMER       *timer = al_create_timer(1.0 / 30.0);
	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();

	// Adição de fontes
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
	
	bool chatexample = true;
	bool rodando = true;
	al_start_timer(timer);
	while (rodando)
	{
		//limpa a tela
		al_clear_to_color(al_map_rgb(255,255,255));

		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);
		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			rodando = false;
		}
		if (chatexample)
		{
			chatbox("Testando comentário", SANS18);
			chatexample = false;
		}

	}

	al_destroy_event_queue(queue);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_uninstall_keyboard();
}
