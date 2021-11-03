

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

void chat_stream(ALLEGRO_DISPLAY *display, bool run, int code)
{
	
	if (code < 0 || code > 9)
	{
		printf("\nDADO code EM CHAT_STREAM INVÁLIDO: %d",code);
		return;
	}

	if(!run) // não deve rodar o jogo enquanto acontece.
	{
		// LÊ	
		// sabe o arquivo que deve ler com base em code
		char filename[15];
		strmov(12, filename, "../text/texto");
		filename[13] = code + '0'; 	
		filename[14] = '\0';

		// abre o arquivo e prepara comment
		FILE *arquivo = fopen(filename, "r"); 
		char *comment = (char*)malloc(sizeof(char)*10);
		int  *image   = (int *)malloc(sizeof(int)*10);

		// começa a formatar comment
		{ // bloco de código
			char leitor; 
			int tamj = 10; 	// tamanho artificial 
			int tami = 10;  // tamanho artificial
			int j = 0;		// tamanho bruto
			int i = 0;		// vetor de personagens
			bool imagem = true; 
			while(((leitor = fgetc(arquivo)) != EOF) && (leitor != '#'))
			{
				if (!imagem)
				// estamos lendo o comentarista?
				{
					if (leitor == '\n')	
						comment[j] = ';'; 
					
					else
						comment[j] = leitor;
					
					j++; //incrementa j
					if (j == tamj) 
					{
						// aumenta o espaço em comment
						tamj+=10;
						comment = (char *)realloc(comment, sizeof(char)*tamj);
					}
				}	
				else
				//quem deve quem fala o comentário i?
				{
					image[i] = leitor - '0'; 
					i++; //incrementa i
					if (i == tami)
					{
						// aumenta espaço em image
						tami +=10;
						image = (int *)realloc(image, sizeof(int)*tami);
					}
					imagem = false;
				}	
			}
			// depois de ler o arquivo e organizar o comentário,
			// aloca o espaço certinho em comment e imagem
			// j+1 pois precisa ter espaço para o '\0'
			comment = (char*)realloc(comment, sizeof(char)*(j+1));
			image  = (int *)realloc(image,  sizeof(int )*i);
			comment[j] = '\0'; //finaliza
			
			// fecha o arquivo
			fclose(arquivo);
		}
		// carrega as imagens dos personagens;
		//ALLEGRO_BITMAP *personagem[2];
		//personagem[0] = al_load_bitmap("../imagens/astpfp.png");
		//personagem[1] = al_load_bitmap("../imagens/holpfp.png");

		// para pausar, salva o display
		ALLEGRO_BITMAP *backup = al_create_bitmap(width,height);
		{
			al_set_target_bitmap(backup);
			al_clear_to_color(al_map_rgb(0, 0, 0));
			render_map();
			render_player();
			render_boxes(false); 		
			al_set_target_backbuffer(display);	
		}

		// inicia nova seção de eventos
		ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue(); 	
		al_register_event_source(queue, al_get_keyboard_event_source());
		ALLEGRO_FONT *FONT =  al_load_font("../fonts/OpenSans-Regular.ttf", 12, 0);
		ALLEGRO_FONT *BOLD =  al_load_font("../fonts/OpenSans-Bold.ttf",18,0);
		ALLEGRO_EVENT evento;
		
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

bool termino()
{
    bool done = false;
    int imagewidth = 0;
    int imageHeight = 0;
    
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_BITMAP* image = al_load_bitmap("../imagens/perdeu.bmp"); 
    imagewidth = al_get_bitmap_width(image);
    imageHeight = al_get_bitmap_height(image);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    while (!done)
    {       
        
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(
            image, width / 2 - imagewidth / 2, 
            height / 2 - imageHeight / 2, 0);

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
   
    return false;
}
