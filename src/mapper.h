#ifndef MAPPER
#define MAPPER

int load_map (int nivel) 
{	
  int aux           = 0;
  int classe        = 0;
  int contagem      = 0;
  int atributo      = 0;

  char ch;
  char aux_ch[4];
  char nome_arquivo[25];
  printf("aaa \n\n"); 
  if (nivel == 0)
    strcpy_s(nome_arquivo, 25,"../fases/fase1"); //fase 0
  else
    strcpy_s(nome_arquivo, 25, "../fases/fase2"); //fase 1

  FILE* fase;
  fopen_s(&fase, nome_arquivo, "r"); //Abre o arquivo

  printf("aaa \n\n"); 
  FILE *fase;

  if(_unix)
    fase = fopen(nome_arquivo, "r");
  else
    fopen_s(&fase, nome_arquivo, "r"); //Abre o arquivo
 

  printf("aaa \n\n"); 
  /////teste de leitura/////
  if (fase == NULL)
  {
    printf("Não abriu o %s", nome_arquivo);
    return 1;
  }
  printf("aaa \n\n"); 
	while (((ch = getc(fase)) != EOF))
	{
    if (classe == 0)
    {
      if(atributo == 0)
      {       
        if(ch == 44)            
        { 
          atributo++;
          box[contagem].type = jatoi(aux_ch, &aux);
          printf ("%d ", box[contagem].type);
        }

        else if (ch > 47 && ch < 58)
        {
          aux_ch[aux] = ch;
          aux++;
        }
      }

      else if(atributo == 1)
      {
        if(ch == 44)
        { 
          atributo++;
          box[contagem].posx = jatoi(aux_ch, &aux);
          printf ("%d ", box[contagem].posx);

        }

        else if (ch > 47 && ch < 58)
        {
          aux_ch[aux] = ch;
          aux++;
        }
      }

      else if(atributo == 2)
      {
        if( ch == 59) // ;
        {
            atributo = 0;
            box[contagem].existe = true;
            box[contagem].posy = jatoi(aux_ch, &aux);  
            printf ("%d\n", box[contagem].posy);
            contagem++;
        }

        else if (ch > 47 && ch < 58)
        {
          aux_ch[aux] = ch;
          aux++;
        }
      }  
      // terminou atributos
      if( ch == 35) // #
      {
        atributo = 0;
        contagem = 0;
        classe  += 1;
        printf ("#\n");
      }
    }
    
    else if (classe == 1)
    {
      if(atributo == 0)
      {       
        if(ch == 44)            
        { 
          atributo++;
          mapa.inix = jatoi(aux_ch, &aux);
          printf ("posx inicial: %d\n", mapa.inix);
        }
        else if (ch > 47 && ch < 58)
        {
          aux_ch[aux] = ch;
          aux++;
        }
      }

      else if(atributo == 1)
      {
        if(ch == 35)
        { 
          atributo = 0;
          classe  += 1;  
          mapa.iniy = jatoi(aux_ch, &aux);
          printf ("posy inicial: %d\n#\n", mapa.iniy);

          aux = 10;
          mapa.map  = realloc(mapa.map,sizeof(int)*aux);
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
          mapa.map = realloc(mapa.map, sizeof(int)*aux);
        }
      }

      else if (ch == '\n')
        mapa.col = 0;

      else if (ch == '#')
      {
        mapa.map = realloc(mapa.map, sizeof(int)*mapa.tam);
        printf("tam: %d\n", mapa.tam);
        printf("col: %d\n", mapa.col);
        mapa.map = realloc(mapa.map, sizeof(int)*mapa.tam);
      }
      
    } 

  }
  printf("aaa \n\n"); 
	fclose(fase);
  printf("aaa \n\n"); 
  return 0;
}

#endif