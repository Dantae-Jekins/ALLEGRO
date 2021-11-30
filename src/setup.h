#ifndef SETUP
#define SETUP

void scale_bitmap(int id, int tamx, int tamy, char *file)
{
  ALLEGRO_BITMAP *aux = al_load_bitmap(file);
  bitmap[id] = al_create_bitmap(tamx, tamy);
  al_set_target_bitmap(bitmap[id]);
  al_clear_to_color(al_map_rgba(0, 0, 0, 0));
  al_draw_scaled_bitmap(
      aux, 0, 0,
      al_get_bitmap_width(aux),
      al_get_bitmap_height(aux),
      0, 0, tamx, tamy, 0);
  al_destroy_bitmap(aux);
}

void setupBitmaps(void) // 0 - 9 player     10 - 19 - Interagiveis    20 - 25 Tiles
{
  scale_bitmap(0, ply_x, ply_y, "../imagens/ast0.png");
  scale_bitmap(1, ply_x, ply_y, "../imagens/ast1.png");
  scale_bitmap(2, ply_x, ply_y, "../imagens/ast0.png");
  scale_bitmap(3, ply_x, ply_y, "../imagens/ast2.png");
  scale_bitmap(4, 80, 80, "../imagens/ast_prof.png");
  scale_bitmap(5, 80, 80, "../imagens/holo_prof.png");
  
  scale_bitmap(8, typ9x, typ9y, "../imagens/rct0.png");
  scale_bitmap(9, 40, 40, "../imagens/event.png");
  
  scale_bitmap(11, typ1x, typ1y, "../imagens/oxy0.png");
  scale_bitmap(12, typ2x, typ2y, "../imagens/oxy0.png");
  
  scale_bitmap(13, typ3x, typ3y, "../imagens/spk0.png");
  scale_bitmap(14, typ3x, typ3y, "../imagens/spk1.png");
  
  scale_bitmap(16, 120, 80, "../imagens/roc0.png");
  
  scale_bitmap(18, width, height, "../imagens/perdeu.png");
  scale_bitmap(19, width, height, "../imagens/ganhou.jpeg");
  
  scale_bitmap(20, tileSiz, tileSiz, "../imagens/til0.png");
  scale_bitmap(21, tileSiz, tileSiz, "../imagens/til1.png");
  
  scale_bitmap(27, width, height, "../imagens/menu.png");
  
  scale_bitmap(28, width, height, "../imagens/bac0.png");
  scale_bitmap(29, width, height, "../imagens/bac1.jpeg");

  obst = 13;
  back = 28;
  tile = 20;

}


void setupFonts(void)
{
  FONTES[0] = al_load_ttf_font
  (
    "../fonts/roboto/Roboto-Regular.ttf",
    18, 0
  );
  FONTES[1] = al_load_ttf_font
  (
    "../fonts/roboto/Roboto-Bold.ttf",
    22, 0
  );
}

void setupBoxes(void)
{
  for (size_t i = 0; i < txt_boxes; i++)
    txtbox[i].existe = false;

  for (size_t i = 0; i < caixas; i++)
    box[i].existe = false;
}

void setupPlayer(void)
{
  player.posx = mapa.inix;
  player.posy = mapa.iniy;
  player.sentido = true;
  player.anim = 0;
  player.estado = 1;
  player.oxygen = 1000;
}

bool setup(void)
{
  // Retorna true se concluído com sucesso
  // ou false se ocorreu algum erro.

  // Inicializa as estruturas
  printf("\nsettando estruturas\n");
  setupBoxes();

  printf("\nsettando allegro\n");
  bool checkup = true;
  if (!al_init())
  {
    printf("\nal_init n�o inicializado");
    checkup = false;
  }
  if (!al_install_keyboard())
  {
    printf("\nal_install_keyboard n�o inicializado");
    checkup = false;
  }
  if (!al_init_font_addon())
  {
    printf("\nal_init_font_addon n�o inicializado");
    checkup = false;
  }
  if (!al_init_ttf_addon())
  {
    printf("\nal_init_ttf_addon n�o inicializado");
    checkup = false;
  }
  if (!al_init_primitives_addon())
  {
    printf("\nal_init_primitives_addon n�o inicializado");
    checkup = false;
  }
  if (!al_init_image_addon())
  {
    printf("\nal_init_image_addon n�o inicializado");
    checkup = false;
  }
  printf("allegro settado\n");
  setupBoxes();
  
  mapa.map = malloc(sizeof(int)*1);
  load_map(0);
  
  printf("boxes settadas\n");
  setupPlayer();
  printf("player settado\n"); 
  setupBitmaps();
  printf("bitmaps settados\n");
  setupFonts();
  printf("fontes settadas\n");

  
  setupPlayer();
  return checkup;
  // permite que a função analise vários de
  // uma vez, sem parar no primeiro.
}

#endif