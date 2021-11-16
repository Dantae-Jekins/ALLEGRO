void checkInput(ALLEGRO_KEYBOARD_STATE keystate)
{
    //Movimentacao X
    bool direita    = true; 
    bool esquerda   = true;
    bool baixo      = true;
    bool cima       = true;
    
    // ANTES SE MOVIMENTAR
    for(int id = 0; id < mapa.tam; id++)
        check_map_collision(id, &direita, &esquerda, &baixo, &cima);

    if (al_key_down(&keystate, ALLEGRO_KEY_RIGHT) && (direita)) {
        player.posx += 5;
    }

    if (al_key_down(&keystate, ALLEGRO_KEY_LEFT) && (esquerda)) {
        player.posx += -5;
    }

    //Movimentacao Y
    
    if (cima && al_key_down(&keystate, ALLEGRO_KEY_UP) && !(player.caindo))
    {
       // se pode ir para cima, apertou para cima, e não está caindo
        player.pulando = true;
       
        if(!baixo)
            player.fimy = player.posy - 200;

        player.posy -= 5;
    }

    if (
    (!cima && player.pulando) || // se bateu a cabeça pulando ou
    (baixo && !player.pulando) || // se pode cair e não está pulando ou
    (!al_key_down(&keystate, ALLEGRO_KEY_UP) || (player.posy == player.fimy)))
    // se parou de pular ou se alcançou o ponto máximo
    {
        player.pulando = false;
        player.caindo  = true;
    }      

    if (player.caindo) // se está caindo
    {
       if (!baixo) // e bateu em baixo
            player.caindo = false;

        else   
            player.posy += 5;
    }
   
}

