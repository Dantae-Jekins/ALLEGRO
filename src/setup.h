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
  scale_bitmap(9, ply_x, ply_y, "../imagens/rct0.png");
  scale_bitmap(10, ply_x, ply_y, "../imagens/spk0.png");
  scale_bitmap(11, ply_x, ply_y, "../imagens/oxy0.png");
  scale_bitmap(12, ply_x, ply_y, "../imagens/roc0.png");
  scale_bitmap(13, ply_x, ply_y, "../imagens/mon0.png");
  scale_bitmap(14, ply_x, ply_y, "../imagens/lav0.png");
  scale_bitmap(20, tileSiz, tileSiz, "../imagens/til0.png");
  scale_bitmap(30, ply_x, ply_y, "../imagens/bac0.png");
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
  player.estado = 1;
  player.oxygen = 100;
  player.bitmap = al_load_bitmap("../imagens/ast0.png");
}

bool setup(void)
{
  // Retorna true se concluído com sucesso
  // ou false se ocorreu algum erro.

  // Inicializa as estruturas
  printf("\nsettando estruturas");

  printf("\nsettando allegro");
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
  setupBoxes();
  setupPlayer();
  setupBitmaps();

  return checkup;
  // permite que a função analise vários de
  // uma vez, sem parar no primeiro.
}