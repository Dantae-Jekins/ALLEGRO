#include <allegro5/allegro.h>
#include <stdio.h>

int main()
{
	ALLEGRO_DISPLAY* display = NULL;
	if (!al_init())
	{
		return -1;
	}

	display = al_create_display(720, 480);
	getchar();

	return 0;
}

//