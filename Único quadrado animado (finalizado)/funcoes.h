/*****************************************************************************************/
/*				Arquivo cabeçalho que acompanha as funções do arquivo           */
/*				 "QUADRADO_ANIMADO.c".															*/
/*				PS: Detalhamento sobre cada função no arquivo "funcoes.c"		*/
/*																															*/
/*****************************************************************************************/

/******INICIO DA DEFINIÇÃO DE BIBLIOTECAS E INCLUDES******/
#include <stdio.h> 
/*Função Printf()*/

#include <stdlib.h> 
/* Funções srand(), rand(). Constante NULL */

#include <time.h>
/*	Função time()*/

#include "conio_v3.2.4.h" 
/* Funções kbhit(), getch(), gotoxy(), Sleep(), textbackground(), textcolor(), window()*/
/* enum COLORS*/

#include "console_v1.5.4.h"
/* Funções getresolucao(), setDimensaoJanela(), setPosicaoJanela(), setTituloConsole(), */
/* Constantes ESC, TAB, ESPACO, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, SETA_PARA_SIMA, SETA_PARA_BAIXO, SETA_PARA_DIREITA, SETA_PARA_ESQUERDA */
/*	struct COORD*/
/******FIM DA DEFINIÇÃO DE BIBLIOTECAS E INCLUDES******/

/******INICIO DA DEFINIÇÃO DE DEFINES E CONSTANTES*/
#define COLUNAS 100 /* Largura do quadrado */
#define LINHAS 40 /* Altura do quadrado */
#define VELOCIDADEMAX 2000 /* Velocidade de uma coluna e linha a cada 2 segundos */
#define VELOCIDADEPADRAO 100 /* Velocidade de uma coluna e linha a cada 100 milissegundo */
#define VELOCIDADEINICIAL 1000 /* Velocidade inicial de uma coluna e uma linha por segundo */
#define VELOCIDADEMIN 100 /* Velocidade de uma coluna e linha a cada 100 milissegundo */
/******FIM DA DEFINIÇÃO DE DEFINES E CONSTANTES******/

/******INICIO DA DECLARAÇÃO DE FUNÇÕES E PROCEDIMENTOS******/
void Acelerar(int *);
void AlterarLimite(COORD *, COORD *, int, int*);
void ApagarArea();
void ApagarQuadrado(COORD*);
void AtivarCOORD(COORD *, int , int );
void AutomaticoXY(int *, COORD *,COORD *, COORD *);
int CorRand();
char *DescCor(int );
int DetectAuto(int *, int *, int *,int *,COORD *, COORD *, COORD *);
void Direcionamento( int *, int );
void Frear(int *);
void JanelaDeInfo(int , int , int , int ,  COORD);
void PersonalizarConsole(char *, int , int );
void PrintarInfo(int , int , int , int , COORD );
void PrintarQuadrado(COORD*, int*);
void SetarArea(COORD, COORD, int *);
void Veloci(int *, int);
/******FIM DA DECLARAÇÃO DE FUNÇÕES E PROCEDIMENTOS******/





