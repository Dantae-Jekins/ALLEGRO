// variáveis gerais
#define height 720
#define width 1080
#define tileSiz 60
#define fps 60.0

// constantes de posições do chat
// útil para pre-processamento
const int cposx0 = (width/10+120);
const int cposy0 = (height-180);
const int cposx1 = (width-(width / 10 + 120));
const int cposy1 = (height-60);

// constantes de tamanho das box
#define typ1x 40
#define typ1y 80
#define typ2x 50
#define typ2y 50
#define speed 5

// variáveis de tamanho
#define ply_x 30
#define ply_y 50


#define AZULBOLD    al_map_rgb(80, 80, 160)
#define AZULLITE    al_map_rgba(80, 80, 160, 80)

#define CIANBOLD    al_map_rgb(120, 200, 240)
#define CIANLITE    al_map_rgba(120, 200, 240, 80)

#define BRANCO      al_map_rgb(255, 255, 255)