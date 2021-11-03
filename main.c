#include <stdio.h>
#include <stdlib.h>
#include <string.h>
<<<<<<< HEAD
#include <stdbool.h>

//MAPA
struct mapp
{
  int col;
  int tam;
  int inix;
  int iniy;
  int *map;
} mapa;

#define caixas 10
struct caixa
{
  bool existe;
  int posx;
  int posy;
  int type;
} box[caixas];

struct jogador
{
  int estado;
  int oxygen;
  int posx;
  int posy;

} player;

int jatoi (char *vec, int *x)
{
  int j = 1;
  int retorno = 0;

  while(*x > 0)
  {
    retorno += (vec[*x-1] - 48) * j;
    *x -=  1;
    j  *= 10;
  }

  return retorno;
}

int carregarMatrix (int nivel) 
{	
  int aux           = 0;
  int classe        = 0;
  int contagem      = 0;
  int atributo      = 0;

  char ch;
  char aux_ch[4];
  char nome_arquivo[25];

  mapa.col = 0;
  mapa.tam = 0;

	if (nivel == 0)
		strcpy(nome_arquivo, "./fase1"); //fase 0
	else
		strcpy(nome_arquivo, "./fases/fase2");	//fase 1

	FILE *fase = fopen(nome_arquivo,"r");
  /////TESTE DE LEITURA/////
	if(fase == NULL)
	{
		printf("Não abriu o %s", nome_arquivo);
		return 1;
	}

  
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
            contagem++;
            atributo = 0;
            box[contagem].posy = jatoi(aux_ch, &aux);
            printf ("%d\n", box[contagem].posy);
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
	fclose(fase);
  return 0;
}

int main()
{
  mapa.map = malloc(sizeof(int)*1);

  carregarMatrix(0);
  int px = 0;
  int py = 0;
  for(int i = 0; i < mapa.tam; i++)
  {
    //px = i % mapa.col;
    //py = i / mapa.col;
    if (i % mapa.col == 0)
      printf("\n");

    printf("%d,", mapa.map[i]);
  } 
  return 0;
}
=======

//Mapa
int mapColu = 10;	//quantidade de colunas
int mapSize = 100;		//tamanho total do mapa

int map[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			        0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int jatoi(char *vec)
{
  int i = 0, j = 1;
  int retorno = 0;
  while (vec[i] != '\0')
    i++;

  while ( i >= 0)
  {
    retorno += (vec[i] - 48)*j;
    i--;    
    j *= 10;
  }

  return retorno;
}

int carregarMatrix (int nivel) { 
	char str[2];
	int i = 0, ch = 0;
	char nome_arquivo[25];
	if (nivel == 0)
		strcpy(nome_arquivo, "./fases/fase1"); //fase 0
	else
		strcpy(nome_arquivo, "./fases/fase2");	//fase 1

	FILE *fase = fopen(nome_arquivo,"r"); //Abre o arquivo 

  /////teste de leitura/////
	if(fase == NULL)
	{ 
		printf("Não abriu o %s", nome_arquivo);
		return 1;
	}

	while ((i < mapSize) && ((ch = getc(fase)) != EOF)) 
	{
    if (!(ch == 44) && !(ch == 10))
    {
      map[i++] = (ch - 48);
    }
  }

	fclose(fase);
  return 0;
}

int main()
{

  carregarMatrix(0);
  
  for (int i = 0; i < mapSize; i++)
    printf("%d", map[i]);

  return 0;
}
>>>>>>> 949f5e2ee5488dab1c965b3df4d6f58310a99fae
