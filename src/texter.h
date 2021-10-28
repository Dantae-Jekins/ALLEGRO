/*
fn inicia texto pausado

	grab o display atual
	para preservar o display

	while (mensagem de texto)
	{
		(qual mensagem renderizar?)
		msg 0
		{
			renderiza o display inicial
			renderiza a mensagem 
		}
		msg 1
		{
			renderiza o display inicial
			renderiza a mensagem
		}
	}	
fin
*/

void chat_stream(ALLEGRO_DISPLAY *display, bool running, int code)
{
	if(running) // jogo está rodando
	{
		// salva o display
		ALLEGRO_BITMAP *backup = al_create_bitmap(width,height);
		al_set_target_bitmap(backup);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		renderMap();
		renderPlayer();
		renderBoxes(false); 		
		al_set_target_backbuffer(display);	
		// inicia nova seção de eventos
		ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue(); 
		ALLEGRO_FONT *FONT =  al_load_font("../fonts/OpenSans-Regular.ttf", 18, 0);
		ALLEGRO_FONT *BOLD =  al_load_font("../fonts/OpenSans-Bold.ttf",22,0);
		ALLEGRO_EVENT evento;
		
		al_register_event_source(queue, al_get_keyboard_event_source());
		bool paused = true;
		switch (code)
		{
			case 0: // caixa de texto teste
			{
				char *str = "Testando1; Testando2; Testando3;";
				char *aux = malloc(sizeof(char)*4);				
				int id = 0, i = 0, pg = 0;
				id = genChat(str, -1);
				txtbox[id].type = 0; 
			
				while (paused)
				{	
					// formata o texto que vai aparecer na caixa:
					// depende de PG que é short para página
					int j = 0; i = 0;
					while(j < pg)
					{
						if(str[i++] == ';') // conta quantos chars
							j++;							// se for ; é outra pg
					}
						
					// i vai representar qual é o ponto inicial.	
					// for mata o texto que vai aparecer na caixa:
					// j vai começar no 0
					int size = 4; j = 0;
					while(str[i]!=';')
					{
						aux[j] = str[i++];
						if( size == (j+1))
						{
							size+=4; //alocamos + 4 de espaço a cada vez
											//para economizar processo.
							aux = realloc(aux, sizeof(char)*size);
						} 
					} 
					aux = realloc(aux, sizeof(char)*(j+1));
					aux[j] = '\0'; 

					txtbox[id].text = aux;
					al_clear_to_color(al_map_rgb(0,0,0));
					al_draw_bitmap(backup,0,0,0);
					paused = renderText(id, BOLD);
					al_flip_display();
					
					al_wait_for_event(queue, &evento);
					if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
						pg ++;
					
				}
				box[id].existe = false;
				free(aux);
				free(str);
			}
		}
		al_destroy_event_queue(queue);
		al_destroy_bitmap(backup);
		al_destroy_font(FONT);
		al_destroy_font(BOLD);
	}
}
