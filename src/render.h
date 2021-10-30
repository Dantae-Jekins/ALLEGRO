bool renderBoxes (bool colide)
{
  ALLEGRO_COLOR cor;
  bool set = true;

  //caixas
  for (int id = 0; id < caixas; id++)
  {
    if (box[id].existe)
    {
      int tamx;
      int tamy;
      bool colisao = false;
      ALLEGRO_COLOR cor;
      if (box[id].type == 0)
      {
        printf("men.?");
        tamx = 5;
        tamy = 5;
        cor = al_map_rgb(0, 0, 0);
      }
      else if (box[id].type == 1)
      {
        tamx = typ1x;
        tamy = typ1y;
        cor = al_map_rgb(50, 50, 200);
      }
      else if (box[id].type == 2)
      {
        tamx = typ2x;
        tamy = typ2y;
        cor = al_map_rgb(200, 50, 50);
      }
      al_draw_filled_rectangle(
          box[id].posx,
          box[id].posy,
          box[id].posx+tamx,
          box[id].posy+tamy,
          cor);
      
      // verifica colisões com a caixa
      if (colide)
      {     
        for (int x = 0; x <= ply_x; x++)
        {
          for (int y = 0; y <= ply_y; y++)
          {
            int cdx = player.posx + x;
            int cdy = player.posy + y; 
            if ((cdx >= box[id].posx) && (cdx <= (box[id].posx + tamx)) 
              && (cdy >= box[id].posy) && (cdy <= (box[id].posy + tamy)))
            {
              // analisa colis�es
              if (box[id].type == 2) // obst�culo
              {
                player.posx = initx;
                player.posy = inity;
                player.oxygen -= 40;
                colisao = true;
                break;
              }
              else if (box[id].type == 1) // cilindro
              {
                player.oxygen += 40;
                box[id].existe = false;
                colisao = true;
                break;
              }
            }
          }
          if (colisao)
            break;
        }
      }
    }
  }
  return set;
}

bool renderText (int ID, ALLEGRO_FONT *fonte)
{
  bool set = true;

  switch (txtbox[ID].type)
  {
    case 0: // log de teste 
    {
      // aparece no meio da tela 
      // caixote preto com o texto
      int posx = width/2 - 120;
      int posy = height/2 - 60;
      int tamx = 240;
      int tamy = 120;
      al_draw_filled_rectangle( 
        posx, posy,
        posx+tamx, posy+tamy,
        al_map_rgba(30,30,40,120));
      
      al_draw_filled_rectangle( 
        posx+15, posy+15,
        posx+tamx-15, posy+tamy-15,
        al_map_rgb(15,15,15));

      al_draw_multiline_text(
        fonte, BRANCO,
        posx+20, posy+20,
        tamx-30, 30,
        ALLEGRO_ALIGN_LEFT,
        txtbox[ID].text
      );
      break;
    }
    /*
    case 1:
    {
      
      al_draw_filled_rectangle(
        cposx0, cposy0,
        cposy1, cposy1,
        CIANLITE
      );
      
      al_draw_filled_rectangle(
        cposx0+20, cposy0+20,
        cposy1-20, cposy1-20,
        AZULLITE  
      );

      al_draw_multiline_text(
        fonte, BRANCO,
        cposx0+40, cposy0+40,
        cposx1-40, cposy1-40,
        ALLEGRO_ALIGN_LEFT,
        txtbox[ID].text
      );
    }
    */
    default:
    {
      break;
    }
  }
  return set;
}

bool renderMap ()
{
  //mapa
  ALLEGRO_COLOR cor;
  bool set = true;
  int px;
  int py;

  for (int i = 0; i < mapSize; i++)
  {
    px = tileSiz * (i % mapColu);
    py = tileSiz * (i / mapColu);

    if (map[i] == 0)
      cor = al_map_rgb(30, 10, 30);
    else if (map[i] == 1)
      cor = al_map_rgb(120, 30, 100);
    else
    {
      printf("render() map[%d] contem tipo nao registrado", i);
      set = false;
    }
    al_draw_filled_rectangle(px, py, px + tileSiz, py + tileSiz, cor);
  }

  return set;
}

bool renderPlayer ()
{
  //personagem
  ALLEGRO_COLOR cor;
  bool set = true;
  int px;
  int py;

  px = player.posx;
  py = player.posy;
  switch (player.estado)
  {
  case 1: // vivo
    cor = al_map_rgb(60, 60, 140);
    int tamx = ply_x;
    int tamy = ply_y;
    al_draw_filled_rectangle(px, py, px + tamx, py + tamy, cor);
    break;

  case 0:
    printf("\nrender() player.estado = 0 n�o implementado");
    break;

  default:
    printf("\nrender() player.estado em valores n�o aceit�veis");
    set = false;
    break;
  }

  return set;
}


