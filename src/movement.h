void checkInput(ALLEGRO_KEYBOARD_STATE keystate, bool* pulando, bool* caindo)
{
    //Movimentacao X

    if (al_key_down(&keystate, ALLEGRO_KEY_RIGHT)) {
        player.posx += 5;
    }

    if (al_key_down(&keystate, ALLEGRO_KEY_LEFT)) {
        player.posx += -5;
    }

    //Movimentacao Y

    if ((al_key_down(&keystate, ALLEGRO_KEY_UP)) && !(*caindo)) {
        player.posy += 5;
        *pulando = true;
    }
    if (
        !(al_key_down(&keystate, ALLEGRO_KEY_UP)) && (*pulando)
        || (player.posy >= 60)
        ) {
        *pulando = false;
        *caindo = true;
    }

    if (*caindo)
    {
        player.posy -= 5;
    }
    if (player.posy <= 0)
    {
        *caindo = false;
    }

}