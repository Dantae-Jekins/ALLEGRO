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

int carregarMatrix (int nivel) { 
	char str[3];
	int i = 0, j = 0, ch;
	char nome_arquivo[25];
	if (nivel == 0)
		strcpy(nome_arquivo, "../nome/diretorio0.txt"); //fase 0
	else
		strcpy(nome_arquivo, "../nome/diretorio1.txt");	//fase 1

	FILE *fase = fopen(nome_arquivo,"r"); //Abre o arquivo 

  /////teste de leitura/////
	if(fase == NULL)
	{ 
		printf("Não abriu o %c", nome_arquivo);
		return 1;
	}
	while((ch = getc(fase)) != EOF) 
	{ 
		if(ch != 44) //Não encontrar virgula
		{ 
      if (ch == 10)//10 = /n
      {
        i++; //proxima linha
        j = 0;
      }
			else
				sprintf (str, "%c", ch);
    }
    else 
			map [i] = atoi(str);
			
		j++; // proxima coluna
	}
	fclose(fase);
}
