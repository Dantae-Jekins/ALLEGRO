

bool render_paused_chat(size_t id, ALLEGRO_BITMAP *background, ALLEGRO_FONT *font)
{
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_bitmap(background,0,0,0);
	bool paused = render_txtbox(id, font);
	al_flip_display();
	return paused;
}

bool count_Words(size_t page, size_t *i, char *str )
{
	int j = 0;
	while (j < page)
	{	
		if (str[*i] == ';') 	
			j++; 
		
		*i += 1;
	}
	if (str[*i] == '\0')
		return false; 			// retorna falso se for o último ';'
	
	return true;				// retorna verdadeiro se houverem +
}

void chat_stream(ALLEGRO_DISPLAY *display, bool running, int code)
{
	if(running) // jogo está rodando
	{
		// salva o display
		printf("\nCHAT_STREAM CODE: %d", code);
		ALLEGRO_BITMAP *backup = al_create_bitmap(width,height);
		al_set_target_bitmap(backup);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		render_map();
		render_player();
		render_boxes(false); 		
		al_set_target_backbuffer(display);	
		
		// inicia nova seção de eventos
		ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue(); 
		ALLEGRO_FONT *FONT =  al_load_font("../fonts/OpenSans-Regular.ttf", 12, 0);
		ALLEGRO_FONT *BOLD =  al_load_font("../fonts/OpenSans-Bold.ttf",18,0);
		ALLEGRO_EVENT evento;
		
		al_register_event_source(queue, al_get_keyboard_event_source());
		bool paused = true;
		switch (code)
		{
			case 0: // caixa de texto teste
			{
				// aloca as strings a serem utilizadas
				char *str = "Testando1 e quebra de linha.;Testando2;Testando3;";
				char *aux = malloc(sizeof(char)*4);				
				
				size_t id = 0;
				size_t i  = 0;
				size_t pg = 0;

				id = genChat();
				txtbox[id].type = 1; 	
				while (paused)
				{	
					i = 0;
					if (!count_Words(pg, &i, str))
					{
						free(aux);
						paused = false;
						break;
					}
						
					txtbox[id].text = strcrop(i, 0, str, aux);						
					render_paused_chat(id, backup, BOLD);
					
					//espera input
					al_wait_for_event(queue, &evento);
					if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
						pg ++;
					
				}
				txtbox[id].existe = false;
				break;
			}
			case 1:
			{
				break;
			}
			default:
			{
				break;
			}
		}
		al_destroy_event_queue(queue);
		al_destroy_bitmap(backup);
		al_destroy_font(FONT);
		al_destroy_font(BOLD);
	}
}
