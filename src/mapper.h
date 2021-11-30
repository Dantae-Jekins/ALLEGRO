int jatoi(char *vec)
{
  int i = 0, j = 1;
  int retorno = 0;
  while (vec[i] != '\0')
    i++;

  while (i >= 0)
  {
    retorno += (vec[i] - 48) * j;
    i--;
    j *= 10;
  }

  return retorno;
}

int carregarMatrix(int nivel)
{
  char str[2];
  int i = 0, ch = 0;
  char nome_arquivo[25];
  if (nivel == 0)
    strcpy_s(&nome_arquivo, nome_arquivo, "../fases/fase1"); //fase 0
  else
    strcpy_s(&nome_arquivo, nome_arquivo, "../fases/fase2"); //fase 1

  FILE* fase;
  fopen_s(&nome_arquivo, nome_arquivo, "r"); //Abre o arquivo

  /////teste de leitura/////
  if (fase == NULL)
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