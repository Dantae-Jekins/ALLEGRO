void mapColision(bool *direita, bool *esquerda, bool *baixo, bool *cima, int *ultpos, bool *colisao)
{
    for( int i = 0; i < mapSize; i++)
    {
        if (map[i] != 1)
        {
            int px0 = tileSiz * (i % mapColu);
            int py0 = tileSiz * (i / mapColu);
            
            for (int px1=px0; px1 < (px0+tileSiz); px1++)    
            {
                for (int py1=py0; py1 < (py0+tileSiz); py1++) 
                {   
                    if ((px1 > player.posx) && (px1 < player.posx + ply_x) && (py1 == player.posy-1))
                    {
                        *cima = false;
                    }   
                    if ((py1 > player.posy) && (py1 < player.posy + ply_y) && (px1 == player.posx+ply_x+1))
                    {
                        *direita = false;
                    }
                    if ((px1 > player.posx) && (px1 < player.posx + ply_x) && (py1 == player.posy+ply_y+1))
                    {
                        *baixo = false;
                        ultpos = player.posy; //tentando pular de plataforma
                        *colisao = true;
                    }   
                    if ((py1 > player.posy) && (py1 < player.posy + ply_y) && (px1 == player.posx-1))
                    {
                        *esquerda = false;
                    }
                }
            }
        }
    }
}

 
void checkInput(ALLEGRO_KEYBOARD_STATE keystate, bool* pulando, bool* caindo)
{
    //Movimentacao X
    bool direita = true;
    bool esquerda = true;
    bool baixo = true;
    bool cima = true;
    int ultpos = 0;
    int vely = 5;
    int acely = 5;
    bool colisao = false;
    // ANTES SE MOVIMENTAR

    mapColision(&direita, &esquerda, &baixo, &cima, &ultpos, &colisao);

    if (al_key_down(&keystate, ALLEGRO_KEY_RIGHT) && (direita)) {
        player.posx += 5;
    }

    if (al_key_down(&keystate, ALLEGRO_KEY_LEFT) && (esquerda)) {
        player.posx += -5;
    }

    //Movimentacao Y

    if ((al_key_down(&keystate, ALLEGRO_KEY_UP)) && !(*caindo) && (baixo))
    {
        player.posy += 5;
        *pulando = true;
    }
    if ((!(al_key_down(&keystate, ALLEGRO_KEY_UP)) || (ultpos + player.posy == 170))
        && (*pulando)){
        *pulando = false;
        *caindo = true;
    }

    if ((*caindo) && (cima))
    //if (*caindo)
    {
        player.posy -= vely;

        if (player.posy <= 5)
        {
            player.posy = 0;
        }
    }
    if ((player.posy <= 0) || (colisao))
    {
        *caindo = false;
    }

}
