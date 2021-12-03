#ifndef J_WEKTORY_H
#define J_WEKTORY_H
#include <stdlib.h>
#include "j_math.h"

// retorna TAM elementos de array em outro vetor
int *copy_array(int *array, int tam)
{
    int *aux = (int*)malloc(sizeof(int)*tam);
    for(int i = 0; i < tam; i++)
        aux[i] = array[i];
    return aux;
}

// retorna o valor correspondente unsigned de str1
unsigned return_unsigned(char *str1)
{
    int count = 0, size = 0;
    for(int i = 0; str1[i] != 0; i++)
        size += 1;

    for(int j = 1; size >= j; j++)
        count += (str1[size-j] - 48) * int_podniesc(10, j-1);

    return count;
}

// retorna o valor correspondente inteiro de str1
int return_integer(char *str1)
{
    // retorna o valor em inteiros da palavra
    int count = 0, size = 0;

    int negativo = 0;
    if(str1[0] == '-')
        negativo = 1;
 
    for(int i = 0; str1[i] != 0; i++)
        size += 1;

    for(int j = 1; size >= j+negativo; j++)
        count += (str1[size-j] - 48) * int_podniesc(10, j-1);

    if(negativo)
        return -count;
    
    return count;
}

#endif