#ifndef RENDER
#define RENDER


// TEXTOS
void render_txt(int posx0, int posy0, int posx1, int posy1, char *texto, ALLEGRO_FONT *fonte)
{
  al_draw_filled_rectangle(
      posx0, posy0,
      posx1, posy1,
      CIANLITE);

  al_draw_filled_rectangle(
      posx0 + 15, posy0 + 15,
      posx1 - 10, posy1 - 10,
      AZULBOLD);
  //printf("\n { ");
  //printf("%d %d %d %d \n", posx0, posx1, posy0, posy1);
  //printf("%s \n", texto);

  //!!!
  int como_assim;
  int pq_isso_funciona;
  char **que = (char **)malloc(sizeof(char **) * 1);
  *que = malloc(sizeof(char *) * 1); //?????????????????????
  for (int i = 0; texto[i] != '\0'; i++)
  {
    **que = '?';
  } // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  // PQ Q ISSO RESOLVE O MEU PROBLEMA??
  // ACHEI DO NADA E N POSSO DAR FREE

  al_draw_multiline_text(
      fonte, BRANCO,
      (posx0 + 20),
      (posy0 + 20),
      (posx1 - posx0 - 40),
      20, 0, texto);
  //printf("\n }\n");
}

void render_seta(int posx, int posy, ALLEGRO_COLOR cor)
{
  al_draw_filled_triangle(posx, posy+20, posx+40, posy, posx+40, posy+40, cor);
  al_draw_filled_rectangle(posx+40, posy+10, posx+80, posy+30, cor);
}

bool render_txtbox(int ID)
{
  bool set = true;
  switch (txtbox[ID].type)
  {
  case 0: // log de teste
  {
    render_txt(
        width / 2 - 120, height / 2 - 60,
        width / 2 + 120, height / 2 + 60,
        "Teste", FONTES[0]);
    break;
  }

  case 1:
  {
    render_txt(
        comment_x0, comment_y0,
        comment_x1, comment_y1,
        txtbox[ID].text, FONTES[0]);

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
void draw_tile(int px, int py, int bm, ALLEGRO_COLOR cor)
{
  if (cor.a == 0)
    al_draw_bitmap(
        bitmap[bm],
        px + width / 2 - player.posx,
        py + height / 2 - player.posy,
        0);

  else
  {
    int posx = px + width / 2 - player.posx;
    int posy = py + height / 2 - player.posy;
    al_draw_filled_rectangle(
        posx, posy, posx + tileSiz, posy + tileSiz,
        cor);
  }
}

//OXIGENIO
bool render_oxigenio()
{
  bool set = true;

  al_draw_filled_rectangle(
      40, width / 2 - (50),
      70, width / 2 + (150),
      al_map_rgb(30, 30, 30)
  );
  al_draw_filled_rectangle(
      45, width / 2 + 145 - (player.oxygen/5.25), //PLAYER.OXIGEN
      65, width / 2 + (145),
      al_map_rgb(50, 40, 250)
  );   

  return set;
}

//MAPA
bool render_map()
{

  al_draw_bitmap(bitmap[29], 0, 0, 0);
  ALLEGRO_COLOR cor;
  cor.a = 0;
  bool set = true;
  int px;
  int py;

  for (int i = 0; i < mapa.tam; i++)
  {
    px = tileSiz * (i % mapa.col);
    py = tileSiz * (i / mapa.col);
    if (mapa.map[i] == 0)
      draw_tile(px, py, 20, cor);

    else if (mapa.map[i] == 2)
      draw_tile(px, py, 16, cor);
  }

  return set;
}

// JOGADOR
bool render_player(int timer)
{
  //personagem
  ALLEGRO_COLOR cor;
  bool set = true;

  if (player.estado == 2)
  {
    cor = al_map_rgb(255, 255, 255);
    al_draw_filled_rectangle(
        width / 2 + 10,
        height / 2 - 20,
        width / 2 + 20,
        height / 2,
        cor);
  }
  switch (player.anim)
  {
  case 0: // parado
    if(player.sentido)
      al_draw_bitmap(bitmap[0], width / 2, height / 2, 0);
    else
      al_draw_bitmap(bitmap[0], width / 2, height / 2, ALLEGRO_FLIP_HORIZONTAL);
    break;
  
  default: // correndo
    
    if(player.sentido)
      al_draw_bitmap(bitmap[player.anim-1], width / 2, height / 2, 0);
    else
      al_draw_bitmap(bitmap[player.anim-1], width / 2, height / 2, ALLEGRO_FLIP_HORIZONTAL);

    if(timer%10 == 0)
    {
      player.anim += 1;

      if(player.anim > 4)
      {
        player.anim = 1;
      }
    }      
    break;      
  }
  
  return set;
}

bool draw_box(int bm, int posx, int posy, ALLEGRO_COLOR cor, int tamx, int tamy)
{
  // vê aonde desenha
  // deve desenhar ao redor do jogador.
  if (cor.a == 0)
    al_draw_bitmap(
        bitmap[bm],
        posx + width / 2 - player.posx,
        posy + height / 2 - player.posy,
        0);

  else
    al_draw_filled_rectangle(
        posx + width / 2 - player.posx,
        posy + height / 2 - player.posy,
        posx + width / 2 - player.posx + tamx,
        posy + height / 2 - player.posy + tamy,
        cor);
}

// CAIXAS
bool render_boxes(bool colide, bool primitives)
{
  ALLEGRO_COLOR cor;
  cor.a = 0;
  bool set = true;

  //caixas
  for (int id = 0; id < caixas; id++)
  {
    if (box[id].existe)
    {
      int tamx;
      int tamy;
      ALLEGRO_COLOR cor;
      cor.a = 0;
      if (box[id].type == 0) // peça
      {
        tamx = typ0x;
        tamy = typ0y;
        cor = al_map_rgb(255, 255, 255);
        draw_box(11, box[id].posx, box[id].posy, cor, tamx, tamy);
      }
      else if (box[id].type == 1) // oxigênio
      {
        tamx = typ1x;
        tamy = typ1y; 
        draw_box(11, box[id].posx, box[id].posy, cor, tamx, tamy);
      }
      else if (box[id].type == 2) // meio oxy
      {
        tamx = typ2x;
        tamy = typ2y;
        //cor = al_map_rgba(75, 75, 175, 255);
        draw_box(11, box[id].posx, box[id].posy, cor, tamx, tamy);
      }
      else if (box[id].type == 3) // obstáculo
      {
        tamx = typ3x;
        tamy = typ3y;
        draw_box(13, box[id].posx, box[id].posy, cor, tamx, tamy);
      }
      else if (box[id].type == 4) // gás
      {
        tamx = typ4x;
        tamy = typ4y;
        cor = al_map_rgba(150, 100, 150, 100);
        draw_box(13, box[id].posx, box[id].posy, cor, tamx, tamy);
      }
      // EXPERIMENTAL
      else if (box[id].type == 5) // lava
      {
        tamx = typ5x;
        tamy = typ5y;
        al_draw_bitmap(bitmap[14], box[id].posx, box[id].posy, 0);
      }
      else if (box[id].type == 6) // móvel
      {
 
      }
      
      else if (box[id].type == 9) // nave
      {
        tamx = typ9x;
        tamy = typ9y;
        //cor = al_map_rgba(150, 150, 50, 100);
        draw_box(8, box[id].posx, box[id].posy, cor, tamx, tamy);
      }
      else if (box[id].type >= 10)
      {
        tamx = 30;
        tamy = 30;
        draw_box(9, box[id].posx, box[id].posy, cor, tamx, tamy);
      }
      // verifica colisões com a caixa
      if (colide)
        check_box_collision(id, tamx, tamy);
    }
  }
  return set;
}

#endif