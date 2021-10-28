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
		printf("\nCHAT_STREAM CODE: %d",code);
		ALLEGRO_BITMAP *backup = al_create_bitmap(width,height);
		al_set_target_bitmap(backup);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		renderMap();
		renderPlayer();
		renderBoxes(false); 		
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
				char *str = "Testando1 e quebra de linha.;Testando2;Testando3;";
				char *aux = malloc(sizeof(char)*4);				
				int id = 0, i = 0, pg = 0;
				id = genChat();
				txtbox[id].type = 0; 
			
				while (paused)
				{	
					// formata o texto que vai aparecer na caixa:
					// depende de PG que é short para página
					int j = 0; i = 0;
					while(j < pg)
					{
						if(str[i++] == ';') // conta quantos chars
							j++;			// conta j com ';'	
					}
					if(str[i] == '\0')		// condição para parar
					{
						free(aux);
						paused = false;
						break;
					}
						
					// i vai representar qual é o ponto inicial
					// contado anteriormente

					// formata o texto que vai aparecer na caixa:
					// j vai começar no 0

					//então de str[i] vai para aux[j].
					int size = 4; j = 0;
					while(str[i]!=';')
					{
						aux[j++] = str[i++];
						if( size == j)
						{
							size+=4; //alocamos + 4 de espaço a cada vez
							aux = realloc(aux, sizeof(char)*size);
						} 
					} 
					//realoca o espaço certo
					aux = realloc(aux, sizeof(char)*(j+1));
					aux[j] = '\0'; // coloca ponto de parada
					txtbox[id].text = aux; // atribui

					//renderiza
					al_clear_to_color(al_map_rgb(0,0,0));
					al_draw_bitmap(backup,0,0,0);
					paused = renderText(id, BOLD);
					al_flip_display();
					
					//espera input
					al_wait_for_event(queue, &evento);
					if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
						pg ++;
					
				}
				txtbox[id].existe = false;
			}
			printf("\nCHAT_STREAM COMPLETO");
		}
		al_destroy_event_queue(queue);
		al_destroy_bitmap(backup);
		al_destroy_font(FONT);
		al_destroy_font(BOLD);
	}
}
