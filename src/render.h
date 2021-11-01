// TEXTOS
void render_txt (int posx0, int posy0, int posx1, int posy1, char *texto, ALLEGRO_FONT *fonte)
{
      al_draw_filled_rectangle(
        posx0, posy0,
        posx1, posy1,
        CIANLITE
      );
      
      al_draw_filled_rectangle(
        posx0+15, posy0+15,
        posx1-10, posy1-10,
        AZULBOLD  
      );

      al_draw_multiline_text(
        fonte, BRANCO,
        posx0+20, posy0+20,
        posx1-10, 15,
        ALLEGRO_ALIGN_LEFT,
        texto        
      );
}

bool render_txtbox (int ID, ALLEGRO_FONT *fonte)
{
  bool set = true;

  switch (txtbox[ID].type)
  {
    case 0: // log de teste 
    {
      render_txt(
        width/2-120, height/2-60,
        width/2+120, height/2+60,
        "Teste", fonte
      );
      break;
    }
    
    case 1:
    {
      render_txt(
        comment_x0, comment_y0,
        comment_x1, comment_y1,
        txtbox[ID].text, fonte
      );

      break;
    }
    
    default:
    {
      break;
    }
  }
  return set;
}


// MAPA
bool render_map ()
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


// JOGADOR
bool render_player ()
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
    {
      ALLEGRO_BITMAP *bitmap = al_load_bitmap("../imagens/ast0.png");
      al_draw_bitmap(bitmap, px, py, 0);
      /* code */
    }
    
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


// CAIXAS
bool render_boxes (bool colide)
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

      if (box[id].type == 1)
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
          box[id].posx + tamx,
          box[id].posy + tamy,
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
