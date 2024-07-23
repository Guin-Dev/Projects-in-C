/* 
	Programa: quadrado animado.
    Descrição: Quadrado que se movimenta pela tela, podendo fazer alterações visuais no programa.
    Programador: Nícolas Herculano Pires
    RGM: 47164
    Data da última modificação: 01/05/2023
	Código para compilar: gcc -o QUADRADO_ANIMADO.exe QUADRADO_ANIMADO.c conio_v3.2.4.c console_v1.5.4.c funcoes.c -pedantic -Wall -Werror -Wextra
*/
#include "conio_v3.2.4.h" 
 /* Funções clrscr() */
#include "console_v1.5.4.h"
 /* MaxDimensaoJanela(). Constante ESC. Struct COORD */
#include "funcoes.h"
 /* ApagarQuadrado(), AutomaticoXY()AtivarCOORD(), DetectAuto(), PersonalizarConsole(), Printarquadrado(), SetarArea(). */
 /* Constante COLUNAS, LINHAS, VELOCIDADE INICIAL */
#include <stdlib.h> 
/* Funções malloc(), rand(), srand(). Constante NULL */
#include <time.h> 
/*Função time()*/

/* Início do programa */
int main(int argc, char *argv[])
{
	/* Ativar e declarar as variáveis inteiras do programa */
	int Automatico;	/* Variavel que dita a direção automática da variável */
	int velocidade = VELOCIDADEINICIAL; /* Variável de velocidade do cursor */
	int cor = 1; /* Cor da janela 1 = AZUL */
	int cortxt = 7; /* Cor do texto 7 = LIGHTGRAY */
	
	/* Ativar tamanho das variáveis de coordenadas */
	COORD *padrao = malloc(sizeof(COORD));
	COORD *inicio = malloc(sizeof(COORD));
	COORD *cursor = malloc(sizeof(COORD));
	
	/* Artifício para silenciar warning */
	argc = argc;
	argv = argv;
	
	/* Ativar Variáveis de coordenadas */
	AtivarCOORD( inicio, 1, 1 );
	AtivarCOORD( padrao, COLUNAS, LINHAS );
	
	/* Personalizar o console, por meio do título, largura e altura*/
	PersonalizarConsole( "Quadrado Animado",MaxDimensaoJanela().X, MaxDimensaoJanela().Y );
	
	/* Gerar uma posição central na tela para o cursor e aleatoría para o lado que ele irá se movimentar */
	AtivarCOORD( cursor, (COLUNAS-3)/2, (LINHAS-2)/2 );
	srand( time( NULL ) );
	Automatico = rand() % 4 + 1;
	
	/* Limpar a tela e desenhar o quadrado inicialmente azul */
	clrscr();
	SetarArea( *inicio, *padrao, &cor );
	
	do /* Loop que sai ao teclar ESC */
	{
		 /* Apagar o quadrado de caracteres */
		ApagarQuadrado( cursor );
		
		/* Movimentar o cursor automaticamente */
		AutomaticoXY( &Automatico, cursor, padrao, inicio ); 
		
		/* Escrever o quadrado de caracteres */
		PrintarQuadrado( cursor, &cortxt ); 
	}
	while (  DetectAuto( &velocidade, &Automatico, &cor, &cortxt, inicio, padrao, cursor ) != ESC );
	
	return 0; /* Programa encerrou com sucesso */
}
/* Fim do programa */