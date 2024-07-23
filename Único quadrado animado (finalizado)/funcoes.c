#include "funcoes.h"/*Todas as fun��es, procedimentos e defines*/

/*
Procedimento Acelerar.
O intuito deste procedimento � alterar o ponteiro de ponteiro velocidade. Ela acrescenta 100 de valor a cada if que � executado com sucesso, com o limite de 200.
*/

void Acelerar( int *velocidade)
{
	if(*velocidade < VELOCIDADEMAX) /*Se a variavel velocidade for inferior ao limite de 2000, ambos em milissegundos, acrescente +100 missegundos*/
	{
		*velocidade =  *velocidade + VELOCIDADEPADRAO;
	}
}

/*
Procedimento AlterarLimite.
O intuito deste procedimento, � controlar quadrado (inicialmente na cor azul) por meio das teclas que variam do F3 at� o F10.
Por se tratar de uma fun��o que executa a fun��o window() duas vezes, causa a ilus�o de que esta sendo alterada as bordas ou limiites do quadrado azul.
Como por fim foi decidido desenhar a �rea do quadrado, a cor selecionada (inicialmente azul) tamb�m � passada como par�metro.
*/

void AlterarLimite(COORD *inicio, COORD *fim, int tecla, int *cor)
{
	if(tecla == F3 && inicio->X > 1) /*se Pressionar F3 e o X inicial nao for negativo, decremente o x inicial*/
	{
		inicio->X = inicio->X - 1;
	}
	if(tecla == F4 && inicio->X <= fim->X-6)/*se Pressionar F4 e o X inicial for menor que o x final subtraido com a excecao dos caracteres, incremente o x inicial*/
	{
		inicio->X = inicio->X + 1;
	}
	if(tecla == F5 && fim->X < COLUNAS)/*se Pressionar F5 e o X final for menor que o limite de colunas somado com a execao de 3 caracteres, incremente o x final*/
	{
		fim->X = fim->X + 1;
	}
	if(tecla == F6 && fim->X >= inicio->X+6)/*se Pressionar F6 e o X final for maior que o X inicial com execao de 5 caracteres(1 para cada borda), decremente o x final*/
	{
		fim->X = fim->X - 1;
	}
	if(tecla == F7 && inicio->Y > 1)/*se Pressionar F7 e o Y inicial for positivo, decremente o Y inicial*/
	{
		inicio->Y = inicio-> Y - 1;
	}
	if(tecla == F8 && inicio->Y+5 <= fim->Y)/*se Pressionar F8 e o Y inicial somado com a execao de 5 caracteres for menor que Y final, incremente o Y inicial*/
	{
		inicio->Y = inicio->Y + 1;
	}
	if(tecla == F9 && fim->Y < LINHAS)/*se Pressionar F9 e o Y final for menor que o LIMITE de linhas somado a execao de 3 caracteres, incremente o Y final*/
	{
		fim->Y = fim->Y + 1;
	}
	if(tecla == F10 && fim->Y >= inicio->Y+5)/*se Presssionar F10 e o Y final for maior que o Y inicial somado a execao de 5 caracteres, decremente o Y final*/
	{
		fim->Y = fim->Y -  1;
	}
	SetarArea(*inicio, *fim, cor);
}

/*
Procedmento ApagarArea.
Cria uma window da cor preta, a qual se sobrep�e aos limites de linha e coluna.
*/

void ApagarArea()
{
	textbackground(BLACK);
	window(1, 1, COLUNAS+1, LINHAS+1 );
}

/*
Procedimento ApagarQuadrado.
A fun��o dele � apagar o quadrado de caracteres por meio de printf() com espa�os em brancos, utilizando como localizador o cursor.
*/

void ApagarQuadrado(COORD *quadrado)
{
	int i;
	for(i = 0; i < 3; i++)	/*la�o de repeti��o*/
	{
		gotoxy(quadrado->X, quadrado->Y + i); /*utiliza o Y como par�metro para escrever a cada linha, sendo somado com a variavel i, a qual ir� asumir os papeis de 0, 1 e 2*/
		printf("   ");
	}
}

/*
Procedimento AtivarCOORD.
Este procedimento inicializa as vari�veis do tipo COORD passando os par�metros X e Y. O objetivo deste procedimento � reduzir o tamanho da decla��o de vari�veis.
*/

void AtivarCOORD(COORD *Item, int ValorX, int ValorY)
{
	Item->X = ValorX;
	Item->Y = ValorY;
}

/*
Procedimento AutomaticoXY.
A fun��o deste procedimento � movimentar o cursor automaticamente, al�m de impedir que o quadrado de caracteres avance os limites, fazendo a ilusao de
"rebater", necessitando dos seguintes par�metros:

autom		-> Para se localizar em qual dire��o seguir, sendo 1 para cima, 2 esquerda, 3 direita e 4, para baixo. Alterado caso atinja limite.
posicao 	-> Para localizar o cursor e garantir que ele nao ultrapasse os limites do quadrado (inicialmente da cor azul) .
final			-> Para localizar o limite do quadrado (inicialmente da cor azul).
inicial		-> Para localizar o inicio do quadrado (inicialmente da cor azul).
*/

void AutomaticoXY( int *autom, COORD *posicao, COORD *final, COORD *inicial)
{
	int limiteX = final->X - inicial->X - 4; /*Calculo do limite final menos o inicial subtra�do o tamanha do quadrado de caracteres -1 como desconto para condi��o de rebater*/
    int limiteY = final->Y - inicial->Y - 4;
	
    switch (*autom) {
        case 1: /* Cima */
            if(limiteY > 3)	/*Pausar o quadrado de caracteres caso n�o tenha espa�o para ele se mover*/
			{
				if (posicao->Y < 2)
				{					/*Se a posi��o Y do cursor for inferior a 2 (assumindo o valor de 1), incremente o Y e mude a vari�vel automatica para baixo (4)*/
					posicao->Y = posicao->Y + 1;
					*autom = 4;
				}
				else
				{										/*Senao, decremente o Y at� que ele seja menor do que 2*/
					(*posicao).Y = (*posicao).Y - 1;
				}
			}
            break;
        case 2: /* Esquerda */
            if(limiteX > 3) /*Pausar o quadrado de caracteres caso n�o tenha espa�o para ele se mover*/
			{
				if (posicao->X < 2)
				{					/*Se a posi��o X do cursor for inferior a 2 (assumindo o valor de 1), incremente o X e mude a vari�vel automatica para direita (3)*/
					posicao->X = posicao->X + 1;
					*autom = 3;
				}
				else
				{										/*Senao, decremente o X at� que ele seja menor do que 2*/
					posicao->X = posicao->X - 1;
				}
			}
            break;
        case 3: /* Direita */
			if(limiteX > 3) /*Pausar o quadrado de caracteres caso n�o tenha espa�o para ele se mover*/
			{
				if (posicao->X > limiteX) {			/*Se a posi��o X do cursor for superior ao limite calculano na linha 105, decremente o X e mude a vari�vel automatica para esquerda (2)*/
					posicao->X = posicao->X - 1;
					*autom = 2;
				}
				else
				{										/*Senao, incremente o X at� que seja maior que o limite calculado*/
					posicao->X = posicao->X + 1;
				}
			}
            break;
        case 4: /* Baixo */
		if(limiteY > 3) /*Pausar o quadrado de caracteres caso n�o tenha espa�o para ele se mover*/
		{
		    if (posicao->Y > limiteY)
			{			/*Se a posi��o Y do cursor for superior ao limite calculano na linha 106, decremente o Y e mude a vari�vel automatica para cima (1)*/
                posicao->Y = posicao->Y - 1;
                *autom = 1;
            }
			else
			{										/*Senao, incremente o Y at� que seja maior que o limite calculado*/
                posicao->Y = posicao->Y + 1;
            }
            break;
		}
    }
}

/*
Fun��o CorRand.
Fun��o que retorna um inteiro entre 1 e 15, sendo representada pelas cores que variam de 0 (sendo 0 o preto, o qual foi excluido desta fun��o) a 15 (sendo 15 a branca).
As paletas de cores enumeradas de 0 a 15, foi retirada da bibliteca conio_v_3.2.4.c.
*/

int CorRand()
{
	srand(time(NULL));
	return ((rand() % 15 + 1));
}

/*
Fun��o DescCor.
Fun��o que retorna uma string. Tem por objetivo descobrir e imprimir a cor arual da vari�vel "opcao", utilizando a enumera��o de cores da biblioteca conio ja apresentada na fun��o anterior (CorRand()).
*/

char *DescCor( int opcao)
{
	if ( opcao == 0)
	{
		return("PRETO");
	}
	if ( opcao == 1)
	{
		return("AZUL");
	}
	if ( opcao == 2)
	{
		return("VERDE");
	}
	if ( opcao == 3)
	{
		return("CIANO");
	}
	if ( opcao == 4)
	{
		return("VERMELHO");
	}
	if ( opcao == 5)
	{
		return("MAGENTA");
	}
	if ( opcao == 6)
	{
		return("MARROM");
	}
	if ( opcao == 7)
	{
		return("CINZA CLARO");
	}
	if ( opcao == 8)
	{
		return("CINZA ESCURO");
	}
	if ( opcao == 9)
	{
		return("AZUL CLARO");
	}
	if ( opcao == 10)
	{
		return("VERDE CLARO");
	}
	if ( opcao == 11)
	{
		return("CIANO CLARO");
	}
	if ( opcao == 12)
	{
		return("ROSA");
	}
	if ( opcao == 13)
	{
		return("ROXO");
	}
	if ( opcao == 14)
	{
		return("AMARELO");
	}
	if ( opcao == 15)
	{
		return("BRANCO");
	}
	return(0);
}

/*
Fun��o DetectAuto.
Fun��o inteira que devolve o valor da tecla pressionada, no programa ela � utilizada como condi��o do la�o de repeti��o, sendo que ele apenas para se a tecla ESC for pressionada,
pela fun��o retornar os valores  das tecla pressionada, se for teclado esc, o la�o � interrompido. Ademais, essa fun��o � centralizada para a dete��o de teclas. A fun��o detecta a
tecla pressionada e automatiza sobre o que fazer se for apertar uma tecla.
Por ser uma fun��o que direciona sobre o que fazer ao pressionar uma determinada tecla, foi identada outras fun��es que necessitam de vari�veis, por isso a grande quantidade
de vari�veis declaradas no escopo da fun��o. Utiliza o kbhit(), fun��o utilizada na biblioteca conio, a qual foi implementada neste programa.
*/

int DetectAuto(int *velocidade, int *automatico, int *corborda, int *cortexto, COORD *inicio, COORD *final, COORD *cursor)
{
	int tecla;
	int i = 0;
	do		/*la�o de repeti��o com tempo de 1ms, para enquanto ele for menor que a velocidade, o programa executar outras fun��es, [...]*/
	{									/*[...]far� o mesmo papel que um sleep(*velocidade)*/
		if ( kbhit() )
		{
			tecla = getch();		/*se o kbhit() retornar 1, � porque uma tecla foi pressionada, a tecla ser� guardada em uma var�avel do tipo char*/
			switch(tecla)
			{  
			   case TAB:
			   		*corborda = CorRand();
					SetarArea(*inicio, *final, corborda);
					break;
			   case ESPACO:
					*cortexto = CorRand();
					break;
			   case ESC:
					return (tecla);
					break;
			   case 0:	 		/* tecla estendida */
			   case 224:		 /* direcionamento */
					tecla = getch();
					if (tecla >= SETA_PARA_CIMA && tecla <= SETA_PARA_BAIXO) /*se a tecla for uma seta de dire��o, ser� chamada a fun��o de direcionamento de cursor*/
					{
						Direcionamento(automatico, tecla);
					}
					if (tecla >= F1 && tecla <= F2)/*Se a tecla for F1 ou F2, ser� chama a fun��o de velocidade*/
					{
						Veloci(velocidade, tecla);
					}
					if (tecla >= F3 && tecla <= F10) /*Se a tecla for do F3 ao F10, ser� chamada a fun��o para alterar os limites do quadrado (inicialmente azul)*/
					{
						AlterarLimite(inicio, final, tecla, corborda);
						AtivarCOORD( cursor, (final->X - inicio->X - 3)/2, (final->Y - inicio->Y - 2)/2 ); /*Recentralizar o cursor*/
					}
					break;
			}
		}
		JanelaDeInfo(*automatico,*velocidade,*cortexto,*corborda, *cursor);
		i++;		   /*incremento de i*/
		Sleep(0.001); /*detectar em 1ms*/
	}while(i < *velocidade);
	SetarArea(*inicio, *final, corborda);/*imprimir a borda no fim de cada vez que a fun��o DetectAuto for chamada*/
	return (tecla);
}

/*
Procedimento Direcionamento.
Procefimento o qual ap�s selecionado uma tecla, � alterada a vari�vel autom�tica, a qual � respons�vel por informar a dire��o que o quadrado
de caracteres ir� seguir, sendo 1 para cima, 2 esquerda, 3 direita e 4, para baixo.
*/

void Direcionamento( int *autom, int tecla)
{
	if ( tecla == SETA_PARA_DIREITA )
	{
		*autom = 3;
	}
	if ( tecla == SETA_PARA_BAIXO )
	{
		*autom = 4;
	}
	if ( tecla == SETA_PARA_CIMA)
	{
		*autom = 1;
	}
	if ( tecla == SETA_PARA_ESQUERDA)
	{
		*autom = 2;
	}
}

/*
Procedimento Frear.
O intuito deste procedimento � alterar o ponteiro de ponteiro velocidade. Ela decrementa 100 de valor a cada if que � executado com sucesso, com o limite de 0.
*/

void Frear( int *velocidade)
{
	if(*velocidade > VELOCIDADEMIN )
	{
		*velocidade = *velocidade - VELOCIDADEPADRAO;
	}
}

/*
Procedimento JanelaDeInfo
O intuito deste procedimento � desenhar uma janela de informa��es
*/

void JanelaDeInfo(int direcao, int velocidade, int cortexto, int corlimite, COORD cursor)
{
	
	textbackground(BLACK);
	window(2, LINHAS + 1, COLUNAS, LINHAS + 10);
	gotoxy(1,1);
	PrintarInfo( direcao, velocidade, cortexto,  corlimite,  cursor);/*procedimento que printa na tela os dados de controle*/
}

/*
Procedimento PersonalizarConsole
Procedimento que altera o t�tulo e o tamanho no console
*/

void PersonalizarConsole(char *Titulo, int Largura, int Altura)
{
	setTituloConsole(Titulo);
	setDimensaoJanela(Largura,Altura);
	setPosicaoJanela(1, 1);
}

/*
Procedimento PrintarInfo.
Procedimento que busca imprimir os dados do programa.
*/

void PrintarInfo( int direcao, int velocidade, int cortexto, int corlimite, COORD cursor)
{
	textcolor(7);
	printf("||Coordenada(X,Y): (%d , %d)", cursor.X, cursor.Y);
	printf(" ||Cor QUADRADO: %s", DescCor( cortexto ));
	printf(" ||Direcao: ");
	if( direcao == 1 )
	{
		printf("CIMA");
	}
	if( direcao == 2)
	{
		printf("ESQUERDA");
	}
	if( direcao == 3)
	{
		printf("DIREITA");
	}
	if (direcao == 4)
	{
		printf("BAIXO");
	}
	gotoxy(1,3);
	printf("||COR LIMITE: %s", DescCor( corlimite ));
	printf(" ||VELOCIDADE: %d ", velocidade);
	printf(" ||PRESSIONE ESC PARA SAIR");
}

/*
Procedimento PrintarQuadrado.
A fun��o dele � escrever o quadrado de caracteres por meio de printf() com asteristicos, utilizando como localizador o cursor.
*/

void PrintarQuadrado(COORD *quadrado, int *cor)
{
	int i;
	textcolor(*cor);		/*Cor dado aleatoriamente caso seja solicitado (inicialmente � LIGHTGRAY e na forma randomizada, o 0 (preto) nunca � selecionado)*/
	for(i = 0; i < 3; i++) /*la�o de repeti��o*/
	{
		gotoxy(quadrado->X, quadrado->Y + i); /*utiliza o Y como par�metro para escrever a cada linha, sendo somado com a variavel i, a qual ir� asumir os papeis de 0, 1 e 2*/
		printf("***");
	}
}

/*
Procedimento SetarArea
Desenha o quadrado inicialmente azul, utilizando duas fun��es window, sendo uma da cor solicitada =! de 0, e outra preta (0) de tamanho inferior de uma linha e uma coluna, ocorrendo
esta diferen�a duas vezes, uma no come�o e outra no fim. Dessa maneira, causando a ilus�o de que existem apenas bordas na tela.
*/
void SetarArea(COORD inicio, COORD fim, int *cor)
{
	ApagarArea();
	textbackground(*cor);
	window(inicio.X, inicio.Y, fim.X ,fim.Y);
	textbackground(BLACK);
	window(inicio.X + 1, inicio.Y + 1, fim.X -1, fim.Y -1);
}

/*
Procedimento Veloci.
Procedimento que encaminha a tecla selecionada para as fun��es de velocidade do sleep.
*/

void Veloci(int *velocidade, int tecla)
{
	if(tecla == F1) /*Pressionar F1*/
	{
		Frear(velocidade);
	}
	if(tecla == F2)/*Pressionar F2*/
	{
		Acelerar(velocidade);
	}
}

