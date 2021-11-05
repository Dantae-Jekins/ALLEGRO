void mapColision(bool* direita, bool* esquerda, bool* baixo, bool* cima)
{
    for (int i = 0; i < mapa.tam; i++)
    {
        if (mapa.map[i] != 1)
        {
            int px0 = tileSiz * (i % mapa.col);
            int py0 = tileSiz * (i / mapa.col);

            for (int px1 = px0; px1 < (px0 + tileSiz); px1++)
            {
                for (int py1 = py0; py1 < (py0 + tileSiz); py1++)
                {
                    if ((px1 > player.posx) && (px1 < player.posx + ply_x) && (py1 == player.posy - 1))
                    {
                        *cima = false;
                    }
                    if ((py1 > player.posy) && (py1 < player.posy + ply_y) && (px1 == player.posx + ply_x + 1))
                    {
                        *direita = false;
                    }
                    if ((px1 > player.posx) && (px1 < player.posx + ply_x) && (py1 == player.posy + ply_y + 1))
                    {
                        *baixo = false;
                    }
                    if ((py1 > player.posy) && (py1 < player.posy + ply_y) && (px1 == player.posx - 1))
                    {
                        *esquerda = false;
                    }
                }
            }
        }
    }
}


void checkInput(ALLEGRO_KEYBOARD_STATE keystate)
{
    //Movimentacao X
    bool direita = true;
    bool esquerda = true;
    bool baixo = true;
    bool cima = true;
    // ANTES SE MOVIMENTAR

    mapColision(&direita, &esquerda, &baixo, &cima);

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

