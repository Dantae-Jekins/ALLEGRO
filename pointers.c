#include <stdio.h>

int main( int argc, char *argv[] )
{
	printf("\n PONTEIROS ");
	printf("\n Arquivo puramente para explicação");

	// Ponteiros são variáveis que não armazenam dados
	// diretamente, ao invés disso eles armazenam os 
	// endereços dos dados que você possui, eles são 
	// úteis para coisas como alocação de memória.
	
	//////////////////////////////////////////////////


	int i = 10;
	// Uma variável normalmente declarada cria dois 
	// valores, seu endereço e o seu conteúdo para 
	// que o computador processe seu conteúdo
	
	int *pointer = &i;
	// Enquanto isso, um ponteiro, quando declarado, 
	// faz algo similar, mas o seu conteúdo corresponde
	// ao endereço de outro lugar.
	
	// Qual o motivo disso? Variáveis declaradas 
	// normalmente possuem o seu endereço imutável,
	// ou seja, elas não podem apontar para um
	// outro tipo de estrutura além de seu próprio
	// conteúdo, neste caso um inteiro que aloca
	// 4 bytes de memória.

	// Por outro lado, ponteiros conseguem "apontar"
	// para diversos tipos de estruturas, eles
	// podem deixar de apontar para um inteiro e
	// apontar para um vetor de inteiros, ou no
	// caso do ALLEGRO ele pode apontar para uma
	// estrutura gigante como o display.
	
	// Um endereço de uma variável e seu conteúdo:
	printf("\n END:%p  CONT:%d", &i, i);

	// O endereço que o ponteiro aponta e seu conteúdo:
	printf("\n END:%p  CONT:%d", pointer, *pointer); 

}

