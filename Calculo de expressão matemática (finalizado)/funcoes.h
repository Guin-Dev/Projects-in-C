/*
 *   Arquivo cabeçalho "funcoes.h"
 *   Contém todas as Defines, Structs e Includes utilizados no arquivo "funcoes.c"
 *   Arquivo o qual complementa o arquivo main "CAUEMA.c".
 */

/*
 *INICIO DAS BIBLIOTECAS INCLUÍDAS, JUNTO DAS DESCRIÇÕES  DO QUE FOI UTILIZADO DAS MESMAS+++
 */

#include <stdio.h>

#include <ctype.h>

#include <string.h>

#include <math.h>

#include <stdbool.h>

/*
 *FIM DAS BIBLIOTECAS INCLUÍDAS, JUNTO DAS DESCRIÇÕES  DO QUE FOI UTILIZADO DAS MESMAS---
 */

/*==========================================================================================*/

/*
 *INICIO DAS CONSTANTES (DEFINES) CRIADAS PARA O PROGRAMA, JUNTO DAS DESCRIÇÕES DAS MESMAS+++
 */

#define TAMMAX 1000 /* Tamanho máximo */

/*
 *FIM DAS CONSTANTES (DEFINES) CRIADAS PARA O PROGRAMA, JUNTO DAS DESCRIÇÕES DAS MESMAS---
 */

/*==========================================================================================*/

/*
 *INICIO DAS ESTRUTURAS (STRUCTS) CRIADAS PARA O PROGRAMA, JUNTO DAS DESCRIÇÕES DAS MESMAS+++
 */

typedef struct
{
    char conteudo[TAMMAX];
    int topo;
} PILHA;
typedef struct
{
    int conteudo[TAMMAX];
    int topo;
} PILHAINT;


/*
 *FIM DAS ESTRUTURAS (STRUCTS) CRIADAS PARA O PROGRAMA, JUNTO DAS DESCRIÇÕES DAS MESMAS---
 */

/*==========================================================================================*/

/*
 *INICIO DAS DECLARAÇÕES DE FUNÇÕES E PROCEDIMENTOS CRIADAS PARA O PROGRAMA+++
 */
int antecessor(char );
int AvaliarPosFixo(char *);
bool bemFormado(char *);
void InfixaParaPosFixa(char *, char *);
void iniciarPilha(PILHA *);
char olhadinha(PILHA *);
bool PilhaVazia(PILHA *);
char pop(PILHA *);
void push(PILHA *, char );
bool umOperador(char );
/*
 *FIM DAS DECLARAÇÕES DE FUNÇÕES E PROCEDIMENTOS CRIADAS PARA O PROGRAMA---
 */
/*====================================| FIM DO DOCUMENTO |====================================*/