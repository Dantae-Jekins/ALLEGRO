#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
