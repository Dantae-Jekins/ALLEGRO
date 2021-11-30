#ifndef MOVEMENT
#define MOVEMENT

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

    // Vê as velocidades
    // player.anim = 0;
    if (baixo)
    { 
        // player.anim = 1;
        if ( player.vely <= 10)
            player.vely += gravidade;
    }

    if ((!cima && player.vely < 0) || (!baixo && player.vely > 0))
        player.vely = 0;
    

    // Vê o teclado
    if(!baixo)
    {    
        player.vely = 0;
        
        if (al_key_down(&keystate, ALLEGRO_KEY_UP))
            player.vely = -22;
    }

    if (player.anim == 0)
    {
        player.anim = 1;
    }  

    player.velx = 0;
    if (al_key_down(&keystate, ALLEGRO_KEY_RIGHT))
    {
        if(direita) 
            player.velx =  6; 
        player.sentido = true;

    }
    else if (al_key_down(&keystate, ALLEGRO_KEY_LEFT)) 
    {
        if(esquerda)
            player.velx = -6; 
        player.sentido = false;
        
    }
    else     
    {
        player.anim = 0;
    }
    //Movimentacao Y    



    // Aplica as velocidades
    player.posx += player.velx;
    player.posy += player.vely; 
}

#endif