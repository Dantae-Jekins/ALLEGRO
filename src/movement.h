void checkInput(ALLEGRO_KEYBOARD_STATE keystate)
{
  // checa o teclado
  if (al_key_down(&keystate, ALLEGRO_KEY_RIGHT))
    player.posx += speed;

  if (al_key_down(&keystate, ALLEGRO_KEY_LEFT))
    player.posx += -speed;

  if (al_key_down(&keystate, ALLEGRO_KEY_UP))
    player.posy += -speed;

	if (al_key_down(&keystate, ALLEGRO_KEY_DOWN))
		player.posy += speed;
}