#ifndef MAPPER
#define MAPPER

void create_box(int type, int posx, int posy)
{
  int id = genBox();
  if (id != -1)
  {
    box[id].type = type;
    box[id].posx = posx;
    box[id].posy = posy;
    box[id].existe = true;
  }
}
int load_map(int nivel)
{
  int aux = 0;
  int classe = 0;
  
  //contagem
  int cnt = 0;
  
  //atributo 
  int atr = 0; 

  //reseta o mapa
  mapa.code = nivel;
  mapa.col  = 0;
  mapa.tam  = 0;
  mapa.inix = 0;
  mapa.iniy = 0;

  // arquivo
  char *arquivo;
  arquivo = str_copy("../fases/fase"); // copia a string
  // e depois aloca mais um espaço nela:
  arquivo = realloc(arquivo, sizeof(char)*15);
  //13 caracteres + 1 nulo -> 13 caracteres + 1 nulo + espaço

  // transforma em ASCII copiando código
  arquivo[13] = mapa.code + 48; // 0 - > '0'
  // abre o arquivo
  FILE *fase = fopen(arquivo, "r"); 
  
  //leitura do arquivo
  char ch;
  char aux_ch[4];
  while (((ch = getc(fase)) != EOF))
  {
    if (classe == 0)
    {
      if (atr == 0)
      {
        if (ch == 44)
        {
          atr++;
          box[cnt].type = jatoi(aux_ch, &aux);
          printf("%d ", box[cnt].type);
        }

        else if (ch > 47 && ch < 58)
        {
          aux_ch[aux] = ch;
          aux++;
        }
      }

      else if (atr == 1)
      {
        if (ch == 44)
        {
          atr++;
          box[cnt].posx = jatoi(aux_ch, &aux);
          printf("%d ", box[cnt].posx);
        }

        else if (ch > 47 && ch < 58)
        {
          aux_ch[aux] = ch;
          aux++;
        }
      }

      else if (atr == 2)
      {
        if (ch == 59) // ;
        {
          atr = 0;
          box[cnt].existe = true;
          box[cnt].posy = jatoi(aux_ch, &aux);
          printf("%d\n", box[cnt].posy);
          cnt++;
        }

        else if (ch > 47 && ch < 58)
        {
          aux_ch[aux] = ch;
          aux++;
        }
      }
      // terminou atrs
      if (ch == 35) // #
      {
        atr = 0;
        cnt = 0;
        classe += 1;
        printf("#\n");
      }
    }

    else if (classe == 1)
    {
      if (atr == 0)
      {
        if (ch == 44)
        {
          atr++;
          mapa.inix = jatoi(aux_ch, &aux);
          printf("posx inicial: %d\n", mapa.inix);
        }
        else if (ch > 47 && ch < 58)
        {
          aux_ch[aux] = ch;
          aux++;
        }
      }

      else if (atr == 1)
      {
        if (ch == 35)
        {
          atr = 0;
          classe += 1;
          mapa.iniy = jatoi(aux_ch, &aux);
          printf("posy inicial: %d\n#\n", mapa.iniy);

          aux = 10;
          mapa.map = realloc(mapa.map, sizeof(int) * aux);
        }
        else if (ch > 47 && ch < 58)
        {
          aux_ch[aux] = ch;
          aux++;
        }
      }
    }

    else if (classe == 2)
    {
      if (ch >= '0' && ch <= '9')
      {
        mapa.map[mapa.tam] = ch - 48;
        mapa.tam++;
        mapa.col++;

        if (mapa.tam == aux)
        {
          aux += 10;
          mapa.map = realloc(mapa.map, sizeof(int) * aux);
        }
      }

      else if (ch == '\n')
        mapa.col = 0;

      else if (ch == '#')
      {
        mapa.map = realloc(mapa.map, sizeof(int) * mapa.tam); // ?
        printf("tam: %d\n", mapa.tam);
        printf("col: %d\n", mapa.col);
        mapa.map = realloc(mapa.map, sizeof(int) * mapa.tam);
      }
    }
  }
  fclose(fase);
  return 0;
}

#endif