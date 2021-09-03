#include <allegro5/allegro.h>
#include <stdio.h>

int main()
{
	// Teste do ALLEGRO
	ALLEGRO_DISPLAY *display = NULL;
	if(!al_init())
	{
		return -1;
	}

	display =	al_create_display(720, 480);
	getchar();

	return 0;	

	/* Pesudocódigo inicial
	
	Setup
	{
		Inicialização do display
		
		Inicialização dos elementos
		 - Personagem
		 - Matriz dos mapas (uma para vários) 
		 - Variáveis globais
	
	}

	while (jogo rodando) - Limitar a velocidade do game (fps)
	{

		Atualizar o display

		Responder a eventos
			- Recebimento de inputs
			- Analisar colisões
	  
		Os eventos são diversos e mudam conforme quais inputs/
		quais colisões ocorrem.
	}

	Término do game.
	*/
}
