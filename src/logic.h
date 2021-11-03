// Transforma um vetor de caracteres em inteiro
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

// move de uma str para outra do ponto vec1[i++] para vec[j++], cortando vec1
char *strcrop(unsigned int i, unsigned int j, char *vec1, char *vec2)
{ 
  int size = 4;
  while(vec1[i]!=';')
  {
    vec2[j++] = vec1[i++];
    if( size == j)
    {
      size+=4; //alocamos + 4 de espaço a cada vez
      vec2 = (char*)realloc(vec2, sizeof(char)*size);
    } 
  } 
  //realoca o espaço certo
  vec2 = (char*)realloc(vec2, sizeof(char)*(j+1));
  vec2[j] = '\0'; // coloca ponto de parada
  return vec2;
}