bool check_if_inside_map(int x, int y, int px, int py, bool *value);

void check_map_collision(int id, bool *direita, bool *esquerda, bool *baixo, bool *cima);

void collide_with_box(int id);

void check_box_collision(int id, int tamx, int tamy);

bool render_paused_chat(size_t id, ALLEGRO_BITMAP *background);

bool count_Words(size_t page, size_t *i, char *str );

void chat_stream(bool run, int code);

bool menu();

bool decrement_oxygen();

bool termino();

bool vitoria();

int jatoi (char *vec, int *x);

char *strcrop(unsigned int i, unsigned int j, char *vec1, char *vec2);

void strmov(unsigned int i, char *vec1, char *vec2);

int difference_module(int i, int j);

int load_map (int nivel);

void checkInput(ALLEGRO_KEYBOARD_STATE keystate);

void render_txt(int posx0, int posy0, int posx1, int posy1, char *texto, ALLEGRO_FONT *fonte);

void render_seta(int posx, int posy, ALLEGRO_COLOR cor);

bool render_txtbox(int ID);

void draw_tile(int px, int py, int bm, ALLEGRO_COLOR cor);

bool render_oxigenio();

bool render_map();

bool render_player(int timer);

bool draw_box(int bm, int posx, int posy, ALLEGRO_COLOR cor, int tamx, int tamy);

bool render_boxes(bool colide, bool primitives);

