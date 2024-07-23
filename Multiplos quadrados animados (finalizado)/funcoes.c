#include "funcoes.h" /*Todas as fun��es, procedimentos e defines*/

/*
Função andaquadrado
O objetivo desta função é andar com o quadrado que foi passado como parâmetro apenas uma linha ou coluna no caso de um de seus pontos
estiver fora do limite aceito da tela.
Ela retorna a variável copiada e modificada
*/
QUADRADO andaquadrado(QUADRADO atual)
{
	QUADRADO novo;
	novo = atual;
	/*direita*/
	if (cabenatela(novo.ponto4) == 1) /*cabe dentro da tela, por isso, o quadrado andará para a direita*/
	{
		novo = incrementaDireita(novo);
		novo = decrementaEsquerda(novo);
	}
	if (cabenatela(novo.ponto4) == 2) /*nao cabe por conta da coordenada X, logo, o quadrado busca voltar, porém, seguindo a diagonal*/
	{
		novo = incrementaBaixo(novo);
		novo = decrementaCima(novo);
		novo = incrementaEsquerda(novo);
		novo = decrementaDireita(novo);
	}
	if (cabenatela(novo.ponto4) == 3) /*nao cabe por conta da coordenada Y, logo, o quadrado busca voltar, porém, seguindo a diagonal*/
	{
		novo = incrementaCima(novo);
		novo = decrementaBaixo(novo);
		novo = incrementaDireita(novo);
		novo = decrementaEsquerda(novo);
	}
	return novo; /*retorna o novo quadrado*/
}

/*
Procedimento ApagarQuadrado.
A função dele é apagar o quadrado de caracteres por meio de printf() com espaços em brancos, utilizando como localizador o cursor.
*/
void ApagarQuadrado(COORD quadrado)
{
	int i;
	for (i = 0; i < 3; i++) /*laço de repetição*/
	{
		gotoxy(quadrado.X, quadrado.Y + i); /*utiliza o Y como parâmetro para escrever a cada linha, sendo somado com a variavel i, a qual irá asumir os papeis de 0, 1 e 2*/
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
Procedimento AtivaAleatorio.
A função dele é ativar a posição do cursor inicial, velocidade e direção do quadrado passado como parâmetro.
*/
void AtivaAleatorio(RETANGULOS *atual)
{
	srand(time(NULL));											   /*ativa o srand*/
	atual->velocidade = rand() % VELOCIDADEPADRAO + VELOCIDADEMIN; /*valor aleatório entre a velocidade mínima e padrao*/
	atual->automatico = rand() % 4 + 1;
	atual->cursor.X = atual->tamanho.ponto1.X + 1;
	atual->cursor.Y = atual->tamanho.ponto1.Y + 1;
}

/*
função ativaNil
A função dele é retornar um quadrado dando todos os pontos (linha e coluna) como NIL ou NULO.
*/
QUADRADO ativaNil(void)
{
	QUADRADO unico;

	unico.ponto1.X = NIL;
	unico.ponto1.Y = NIL;
	unico.ponto2.X = NIL;
	unico.ponto2.Y = NIL;
	unico.ponto3.X = NIL;
	unico.ponto3.Y = NIL;
	unico.ponto4.X = NIL;
	unico.ponto4.Y = NIL;

	return unico;
}

/*
Procedimento AutomaticoXY.
A fun��o deste procedimento � movimentar o cursor automaticamente, al�m de impedir que o quadrado de caracteres avance os limites,
fazendo a ilusao de "rebater".
*/
void AutomaticoXY(RETANGULOS *todos)
{
	int limiteX = todos->tamanho.ponto3.X - todos->tamanho.ponto1.X - 2; /*Calculo do limite final menos o inicial subtra�do o tamanha do quadrado de caracteres -1 como desconto para condi��o de rebater*/
	int limiteY = todos->tamanho.ponto2.Y - todos->tamanho.ponto1.Y - 2;

	switch (todos->automatico)
	{
	case CIMA:			 /* Cima */
		if (limiteY > 3) /*Pausar o quadrado de caracteres caso n�o tenha espa�o para ele se mover*/
		{
			if (todos->cursor.Y < todos->tamanho.ponto1.Y + 2)
			{ /*Se a posi��o Y do cursor for inferior a 2 (assumindo o valor de 1), incremente o Y e mude a vari�vel automatica para baixo (4)*/
				todos->cursor.Y = todos->cursor.Y + 1;
				todos->automatico = BAIXO;
			}
			else
			{ /*Senao, decremente o Y at� que ele seja menor do que 2*/
				todos->cursor.Y = todos->cursor.Y - 1;
			}
		}
		break;
	case ESQUERDA:		 /* Esquerda */
		if (limiteX > 3) /*Pausar o quadrado de caracteres caso n�o tenha espa�o para ele se mover*/
		{
			if (todos->cursor.X < todos->tamanho.ponto1.X + 2)
			{ /*Se a posi��o X do cursor for inferior a 2 (assumindo o valor de 1), incremente o X e mude a vari�vel automatica para direita (3)*/
				todos->cursor.X = todos->cursor.X + 1;
				todos->automatico = DIREITA;
			}
			else
			{ /*Senao, decremente o X at� que ele seja menor do que 2*/
				todos->cursor.X = todos->cursor.X - 1;
			}
		}
		break;
	case DIREITA:		 /* Direita */
		if (limiteX > 3) /*Pausar o quadrado de caracteres caso n�o tenha espa�o para ele se mover*/
		{
			if (todos->cursor.X > limiteX - 1)
			{ /*Se a posi��o X do cursor for superior ao limite calculano na linha 105, decremente o X e mude a vari�vel automatica para esquerda (2)*/
				todos->cursor.X = todos->cursor.X - 1;
				todos->automatico = ESQUERDA;
			}
			else
			{ /*Senao, incremente o X at� que seja maior que o limite calculado*/
				todos->cursor.X = todos->cursor.X + 1;
			}
		}
		break;
	case BAIXO:			 /* Baixo */
		if (limiteY > 3) /*Pausar o quadrado de caracteres caso n�o tenha espa�o para ele se mover*/
		{
			if (todos->cursor.Y > limiteY - 1)
			{ /*Se a posi��o Y do cursor for superior ao limite calculano na linha 106, decremente o Y e mude a vari�vel automatica para cima (1)*/
				todos->cursor.Y = todos->cursor.Y - 1;
				todos->automatico = CIMA;
			}
			else
			{ /*Senao, incremente o Y at� que seja maior que o limite calculado*/
				todos->cursor.Y = todos->cursor.Y + 1;
			}
			break;
		}
	}
}

/*
Função cabenatela
O Objetivo dela é dizer se um determinado ponto (X,Y) está dentro dos limites da tela, tendo como retorno:
1 = cabe
2 = não cabe no X
3 = nao cabe no y
4 = um dos parâmetros é zero ou negativo
0 = nao cabe pois ambos os pontos ultrapassaram o limite
*/
int cabenatela(COORD ponto)
{
	COORD dimensao = MaxDimensaoJanela();

	/*se o ponto estiver dentro da dimensao retorne 1*/
	if (ponto.X < dimensao.X && ponto.Y < dimensao.Y && ponto.X > 0 && ponto.Y > 0)
	{
		return (1); /*cabe*/
	}
	/*se o ponto X estiver no limite ou ultrapassado, porém o ponto Y nao, retorne 2*/
	if (ponto.X >= dimensao.X && ponto.Y < dimensao.Y)
	{
		return (2); /*nao cabe no X*/
	}
	/*se o ponto X for menor que o limite, porém o ponto Y estiver no limite ou passado, retorne 3*/
	if (ponto.X < dimensao.X && ponto.Y >= dimensao.Y)
	{
		return (3); /*nao cabe no Y*/
	}
	if (ponto.X <= 0 || ponto.Y <= 0)
	{
		return (4);
	}
	return (0); /*não cabe*/
}

/*
Função controladorGeral
controlador de velocidade geral do programa
*/
int controladorGeral(int velocidade)
{
	if (velocidade >= VELOCIDADEMAX)
	{
		return VELOCIDADEMIN;
	}
	else
	{
		return velocidade + VELOCIDADEPADRAO;
	}
}

/*
Função controle indice.
busca manter o índice na quantidade solicitada, sendo retornado a 0 quando ultrapassada
*/
int controlaIndice(int i, int qtd)
{
	if (i < qtd)
	{
		return i + 1;
	}
	else
	{
		return 0;
	}
}

/*
Função controleDePontos
Função que controla de um ponto (p3) esta entre dois pontos (p1 e p2), retorna verdadeiro caso esteja tornando-o inválido,
caso nao esteja retorna falso.
*/
BOOLEAN controleDePontos(COORD p1, COORD p2, COORD p3)
{
	int minX = p1.X < p2.X ? p1.X : p2.X; /*encontrar o menor X*/
	int maxX = p1.X > p2.X ? p1.X : p2.X; /*encontrar o maior X*/
	int minY = p1.Y < p2.Y ? p1.Y : p2.Y; /*encontrar o menor Y*/
	int maxY = p1.Y > p2.Y ? p1.Y : p2.Y; /*encontrar o maior Y*/
	if (cabenatela(p3) != 1)			  /*se o p3 não estiver dentre os limites aceitos, é dado como ponto inválido*/
	{
		return TRUE;
	}
	if (p3.X >= minX && p3.X <= maxX && p3.Y >= minY && p3.Y <= maxY) /*Se o p3.x for maior ou igual ao menor ponto X e menor ou igual o maior ponto X (o mesmo feito com o Y)*/
	{
		return TRUE;
	}

	return FALSE;
}

/*
Função CorRand.
Função que retorna um inteiro entre 1 e 15, sendo representada pelas cores que variam de 0 (sendo 0 o preto, o qual foi excluido desta fun��o) a 15 (sendo 15 a branca).
As paletas de cores enumeradas de 0 a 15, foi retirada da bibliteca conio_v_3.2.4.c.
*/
int CorRand(void)
{
	srand(time(NULL));
	return (rand() % 15 + 1);
}

/*
Procedimento CriarTela
Tem como objetivo printar um quadrado por meio de seus pontos (linha e coluna)
*/
void CriarTela(QUADRADO telaSolicitada, int cor)
{
	int i, j; /*i mexe no x e j meche no y*/
	int j2;	  /*variável auxiliar*/

	textcolor(cor);
	textbackground(cor);
	j = telaSolicitada.ponto1.Y;
	j2 = telaSolicitada.ponto2.Y;
	for (i = telaSolicitada.ponto1.X; i <= telaSolicitada.ponto3.X; i++) /*imprime as linhas*/
	{
		gotoxy(i, j);
		printf(" ");
		gotoxy(i, j2);
		printf(" ");
	}
	j = telaSolicitada.ponto1.X;
	j2 = telaSolicitada.ponto3.X;
	for (i = telaSolicitada.ponto1.Y; i <= telaSolicitada.ponto2.Y; i++) /*imprime as colunas*/
	{
		gotoxy(j, i);
		printf(" ");
		gotoxy(j2, i);
		printf(" ");
	}
	textcolor(LIGHTGRAY);
	textbackground(BLACK); /*volta as cores padrões*/
}

/*
Funções de decrementos (linha 299 a 340)
Decremento da linha final baseando-se no centro do quadrado
*/
QUADRADO decrementaBaixo(QUADRADO atual)
{
	if (atual.ponto2.Y > atual.ponto1.Y + 4)
	{
		atual.ponto2.Y = atual.ponto2.Y - 1;
		atual.ponto4.Y = atual.ponto4.Y - 1;
	}
	return atual;
}
/*decremento da linha inicial baseando-se no centro do quadrado*/
QUADRADO decrementaCima(QUADRADO atual)
{
	if (atual.ponto1.Y < atual.ponto2.Y - 4)
	{
		atual.ponto1.Y = atual.ponto1.Y + 1;
		atual.ponto3.Y = atual.ponto3.Y + 1;
	}
	return atual;
}
/*decremento da coluna final baseando-se no centro do quadrado*/
QUADRADO decrementaDireita(QUADRADO atual)
{
	if (atual.ponto3.X > atual.ponto1.X + 4)
	{
		atual.ponto3.X = atual.ponto3.X - 1;
		atual.ponto4.X = atual.ponto4.X - 1;
	}
	return atual;
}
/*decremento da coluna inicial baseando-se no centro do quadrado*/
QUADRADO decrementaEsquerda(QUADRADO atual)
{
	if (atual.ponto1.X > atual.ponto3.X - 4)
	{
		atual.ponto1.X = atual.ponto1.X + 1;
		atual.ponto2.X = atual.ponto2.X + 1;
	}
	return atual;
}

/*
Procedimento DespersonalizarConsoleFULL
Procedimento que volta o t�tulo e o tamanho do console para sua resolução anterior, o mesmo para o cursor e barra de tarefas
*/
void DespersonalizarConsoleFULL(MEMORIACONSOLE antigo)
{
	/*titulo*/
	setTituloConsole(antigo.titulo);
	/*dimensionar*/
	setDimensaoJanela(antigo.resolucao.X, antigo.resolucao.Y);
	/*posicionar*/
	setPosicaoJanela(antigo.posicao.X, antigo.posicao.Y);
	/*ligar cursor*/
	setCursorStatus(LIGAR);
	/*barra de tarefas visivel*/
	setEstadoBarraTarefas(VISIVEL);
	textbackground(antigo.cor.CorFundo);
	textcolor(antigo.cor.CorTexto);
	clrscr();
}

/*
Função Detector
Tem como objetivo detectar e direcionar eventos caso aconteça algum, retorna 0 ou ESC.
*/
int Detector(RETANGULOS *todos, EVENTO clique, int *i, int *qtd, int *selecionado)
{
	int salvaI;							  /*backup do índice*/
	if (clique.tipo_evento & MOUSE_EVENT) /*tipo de evento do mouse*/
	{
		if (clique.mouse.botao_clicou & BOTAO_ESQUERDO_PRESSIONADO && pegaQuadrado(todos, *qtd, clique.mouse.posicao) != -1)
		{
			*selecionado = pegaQuadrado(todos, *qtd, clique.mouse.posicao);
			*selecionado = *selecionado == -1 ? *i : *selecionado;
			quadradoAtivo(todos, *selecionado, BLUE, LIGHTGRAY);
		}
		return 0;
	}																				 /*evento vir do teclado*/
	if (clique.tipo_evento & KEY_EVENT && clique.teclado.status_tecla & PRESSIONADA) /*tipo de evento do teclado*/
	{
		if (clique.teclado.codigo_tecla >= F1 && clique.teclado.codigo_tecla <= F10)
		{
			FuncaoF1aoF10(clique.teclado.codigo_tecla, todos, *selecionado, *qtd);
			return 0;
		}
		else
		{																																 /*evento for o CTRL*/
			if (clique.teclado.status_teclas_controle & RIGHT_CTRL_PRESSED || clique.teclado.status_teclas_controle & LEFT_CTRL_PRESSED) /*controle*/
			{
				if (*qtd < QTDQUADRADOS - 1) /*se quantidade for menor do que o número de quadrados declarados*/
				{
					salvaI = *i;
					*qtd = *qtd + 1;
					*i = *qtd;
					todos[*i].id = *i;
					todos[*i].tamanho = validaQuadradoNovo(todos, *qtd); /*valida um quadrado novo*/
					if (todos[*i].tamanho.ponto1.X == NIL)				 /*se for detectado como retorno um quadrado NULO ou com NIL, é poque não tem espaço disponível*/
					{
						*qtd = *qtd - 1;
						*i = salvaI;
						gotoxy(MaxDimensaoJanela().X / 2, MaxDimensaoJanela().Y / 2);
						textbackground(WHITE);
						textcolor(BLACK);
						printf("\t SEM ESPAÇO\t");
						system("pause");
						textbackground(BLACK);
						textcolor(BLACK);
						clrscr();
					}
					else
					{
						quadradoAtivo(&todos[*qtd], *qtd, BLUE, LIGHTGRAY); /*ativa com as cores padores*/
						*selecionado = *qtd;
						AtivaAleatorio(&(todos[*qtd])); /*da os valores de direç~cao*/
						CriarTela(todos[*i].tamanho, BLUE);
					}
					return 0;
				}
				else /*se quantidade não for menor do que o número de quadrados declarados é por que foi atingido o máximo*/
				{
					gotoxy(MaxDimensaoJanela().X / 2, MaxDimensaoJanela().Y / 2);
					textbackground(WHITE);
					textcolor(BLACK);
					printf("\t MAXIMO ATINGIGO\t");
					system("pause");
					textbackground(BLACK);
					textcolor(BLACK);
					clrscr();
					return 0;
				}
			} /*o evento vir do ALT*/
			if (clique.teclado.status_teclas_controle & RIGHT_ALT_PRESSED || clique.teclado.status_teclas_controle & LEFT_ALT_PRESSED)
			{
				*selecionado = *selecionado + 1 <= *qtd ? *selecionado + 1 : 0;
				quadradoAtivo(todos, *selecionado, BLUE, LIGHTGRAY);
				return 0;
			} /*caso venha das demais teclas*/
			switch (clique.teclado.codigo_tecla)
			{
			case ESC:
				return ESC;
				break;
			case SETA_PARA_CIMA:
				todos[*selecionado].automatico = CIMA; /*cima*/
				break;
			case SETA_PARA_BAIXO:
				todos[*selecionado].automatico = BAIXO; /*baixo*/
				break;
			case SETA_PARA_ESQUERDA:
				todos[*selecionado].automatico = ESQUERDA; /*esquerda*/
				break;
			case SETA_PARA_DIREITA:
				todos[*selecionado].automatico = DIREITA; /*direita*/
				break;
			case TAB:
				todos[*selecionado].cortxt = CorRand();
				break;
			case ESPACO:
				todos[*selecionado].cor = CorRand();
				break;
			}
			return 0;
		}
		return 0;
	}
	return 0;
}

/*
Procedimento FunçãoF1aoF10
Busca separar as teclas do F1 ao F10, atualmente, relacionadas a velociade e tamanho.
*/
void FuncaoF1aoF10(int opcao, RETANGULOS *todos, int i, int qtd)
{
	switch (opcao)
	{
	case F1:									 /*controle de velocidade do quadrado*/
		if (todos[i].velocidade > VELOCIDADEMIN) /*diminuir*/
		{
			todos[i].velocidade = todos[i].velocidade - 1;
		}
		break;
	case F2:									 /*controle de velocidade do quadrado*/
		if (todos[i].velocidade < VELOCIDADEMAX) /*aumentar*/
		{
			todos[i].velocidade = todos[i].velocidade + 1;
		}
		break;
	case F3:																	  /*controle de tamanho do quadrado(497 até 544)*/
		if (InterferenciaVetor(todos, incrementaEsquerda(todos[i].tamanho), qtd)) /*incremente, ve se terá interferência, se houver, o comando será ignorado*/
		{
			todos[i].tamanho = incrementaEsquerda(todos[i].tamanho);
		}
		break;
	case F4:
		if (InterferenciaVetor(todos, decrementaEsquerda(todos[i].tamanho), qtd)) /*decremente, ve se terá interferência, se houver, o comando será ignorado*/
		{
			todos[i].tamanho = decrementaEsquerda(todos[i].tamanho);
		}
		break;
	case F5:
		if (InterferenciaVetor(todos, incrementaDireita(todos[i].tamanho), qtd)) /*incremente, ve se terá interferência, se houver, o comando será ignorado*/
		{
			todos[i].tamanho = incrementaDireita(todos[i].tamanho);
		}
		break;
	case F6:
		if (InterferenciaVetor(todos, decrementaDireita(todos[i].tamanho), qtd)) /*decremente, ve se terá interferência, se houver, o comando será ignorado*/
		{
			todos[i].tamanho = decrementaDireita(todos[i].tamanho);
		}
		break;
	case F7:
		if (InterferenciaVetor(todos, incrementaCima(todos[i].tamanho), qtd)) /*incremente, ve se terá interferência, se houver, o comando será ignorado*/
		{
			todos[i].tamanho = incrementaCima(todos[i].tamanho);
		}
		break;
	case F8:
		if (InterferenciaVetor(todos, decrementaCima(todos[i].tamanho), qtd)) /*decremente, ve se terá interferência, se houver, o comando será ignorado*/
		{
			todos[i].tamanho = decrementaCima(todos[i].tamanho);
		}
		break;
	case F9:
		if (InterferenciaVetor(todos, incrementaBaixo(todos[i].tamanho), qtd)) /*incremente, ve se terá interferência, se houver, o comando será ignorado*/
		{
			todos[i].tamanho = incrementaBaixo(todos[i].tamanho);
		}
		break;
	case F10:
		if (InterferenciaVetor(todos, decrementaBaixo(todos[i].tamanho), qtd)) /*decremente, ve se terá interferência, se houver, o comando será ignorado*/
		{
			todos[i].tamanho = decrementaBaixo(todos[i].tamanho);
		}
		break;
	}
	clrscr();
}

/*
Funções de decrementos (linha 551 a 594)
Decremento da linha final baseando-se no centro do quadrado
*/
/*incremento da linha final baseando-se no centro do quadrado*/
QUADRADO incrementaBaixo(QUADRADO atual)
{
	if (atual.ponto2.Y <= MaxDimensaoJanela().Y)
	{
		atual.ponto2.Y = atual.ponto2.Y + 1;
		atual.ponto4.Y = atual.ponto4.Y + 1;
	}
	return atual;
}
/*incremento da linha inicial baseando-se no centro do quadrado*/
QUADRADO incrementaCima(QUADRADO atual)
{

	if (atual.ponto1.Y > 0)
	{
		atual.ponto1.Y = atual.ponto1.Y - 1;
		atual.ponto3.Y = atual.ponto3.Y - 1;
	}
	return atual;
}
/*incremento da coluna final baseando-se no centro do quadrado*/
QUADRADO incrementaDireita(QUADRADO atual)
{
	if (atual.ponto3.X < MaxDimensaoJanela().X)
	{
		atual.ponto3.X = atual.ponto3.X + 1;
		atual.ponto4.X = atual.ponto4.X + 1;
	}
	return atual;
}
/*incremento da coluna inicial baseando-se no centro do quadrado*/
QUADRADO incrementaEsquerda(QUADRADO atual)
{
	if (atual.ponto1.X > 0)
	{
		atual.ponto1.X = atual.ponto1.X - 1;
		atual.ponto2.X = atual.ponto2.X - 1;
	}
	return atual;
}

/*
Função Interferência
Função que diz se um quadrado é valido (TRUE) ou nao (FALSE), para ser colocado ou se um de seus pontos esta causando interferencia no quadrado selecionado.
*/
BOOLEAN Interferencia(QUADRADO novo, QUADRADO atual)
{
	int testador = 0;
	/*teste do primeiro ponto*/
	if (controleDePontos(atual.ponto1, atual.ponto3, novo.ponto1) || (controleDePontos(atual.ponto1, atual.ponto2, novo.ponto1)))
	{
		testador++;
	}
	if (controleDePontos(atual.ponto3, atual.ponto4, novo.ponto1) || (controleDePontos(atual.ponto2, atual.ponto4, novo.ponto1)))
	{
		testador++;
	}
	/*teste do segundo ponto*/
	if (controleDePontos(atual.ponto1, atual.ponto3, novo.ponto2) || (controleDePontos(atual.ponto1, atual.ponto2, novo.ponto2)))
	{
		testador++;
	}
	if (controleDePontos(atual.ponto3, atual.ponto4, novo.ponto2) || (controleDePontos(atual.ponto2, atual.ponto4, novo.ponto2)))
	{
		testador++;
	}
	/*teste do terceiro ponto*/
	if (controleDePontos(atual.ponto1, atual.ponto3, novo.ponto3) || (controleDePontos(atual.ponto1, atual.ponto2, novo.ponto3)))
	{
		testador++;
	}
	if (controleDePontos(atual.ponto3, atual.ponto4, novo.ponto3) || (controleDePontos(atual.ponto2, atual.ponto4, novo.ponto3)))
	{
		testador++;
	}
	/*teste do quarto ponto*/
	if (controleDePontos(atual.ponto1, atual.ponto3, novo.ponto4) || (controleDePontos(atual.ponto1, atual.ponto2, novo.ponto4)))
	{
		testador++;
	}
	if (controleDePontos(atual.ponto3, atual.ponto4, novo.ponto4) || (controleDePontos(atual.ponto2, atual.ponto4, novo.ponto4)))
	{
		testador++;
	}
	/*se o testador dele estiver em mais de dois ponto, retorne FALSO*/
	return ((testador > 2 ? FALSE : TRUE));
}

/*
Função InterferênciaVetor
Função que busca ver se um quadrado estaria causando interferência com todos os outros
*/
BOOLEAN InterferenciaVetor(RETANGULOS *vetor, QUADRADO atual, int qtd)
{
	int i;
	for (i = 0; i < qtd; i++)
	{
		if (Interferencia(atual, vetor[i].tamanho) == FALSE) /*se houver interferencia*/
		{
			return FALSE; /*retorne falso*/
		}
	}

	return TRUE; /*senao, retorne verdadeiro*/
}

/*
Função PegaQuadrado
Objetivo dela é retornar um quadrado selecionado por meio do mouse
*/
int pegaQuadrado(RETANGULOS *todos, int qtd, COORD tecla)
{
	int i;
	for (i = 0; i <= qtd; i++)
	{ /*se o clique foi entre os 4 pontos de um quadrado, retorne a id deste quadrado*/
		if (controleDePontos(todos[i].tamanho.ponto1, todos[i].tamanho.ponto4, tecla) && controleDePontos(todos[i].tamanho.ponto2, todos[i].tamanho.ponto3, tecla))
		{
			return (todos[i].id);
		}
	}
	return (-1); /*senão, retorne -1*/
}

/*
Procedimento PersonalizarConsoleFULL
Procedimento que altera o t�tulo e o tamanho do console para sua resolução maxima, isto claro, ocultando o cursor e salvando seus valores como retorno
*/
MEMORIACONSOLE PersonalizarConsoleFULL(char *Titulo)
{
	/*declarar variaveis*/
	MEMORIACONSOLE tela;
	/*gravar cores antigas de fonte e fundo*/
	tela.cor = getCoresJanela();
	/*gravar resolução atual do console*/
	tela.resolucao = tamanhoJanelaConsole();
	/*gravar posição da janela*/
	tela.posicao = getPosicaoJanela();
	/*titulo antigo*/
	tela.titulo = getTituloConsole();
	/*titulo*/
	setTituloConsole(Titulo);
	/*desligar cursor*/
	setCursorStatus(DESLIGAR);
	/*barra de tarefas invisivel*/
	setEstadoBarraTarefas(INVISIVEL);
	/*posicionar*/
	setPosicaoJanela(1, 1);
	/*dimensionar*/
	setDimensaoJanela(MaxDimensaoJanela().X, MaxDimensaoJanela().Y);
	/*retornar a memoria*/
	return tela;
}

/*
Procedimento PrintarInfo.
Procedimento que busca imprimir os dados do programa, atualmente, velocidade.
*/
void PrintarInfo(RETANGULOS atual)
{
	textcolor(BLACK);
	textbackground(WHITE);
	gotoxy(1, MaxDimensaoJanela().Y);
	printf("|Velocidade em ms: %d de %d (MAX)", atual.velocidade, VELOCIDADEMAX);
	textcolor(BLACK);
	textbackground(BLACK);
}

/*
Procedimento PrintarQuadrado.
A fun��o dele � escrever o quadrado de caracteres por meio de printf() com asteristicos, utilizando como localizador o cursor.
*/
void PrintarQuadrado(COORD *quadrado, int cor)
{
	int i;
	textcolor(cor);			/*Cor dado aleatoriamente caso seja solicitado (inicialmente � LIGHTGRAY e na forma randomizada, o 0 (preto) nunca � selecionado)*/
	for (i = 0; i < 3; i++) /*la�o de repeti��o*/
	{
		gotoxy(quadrado->X, quadrado->Y + i); /*utiliza o Y como par�metro para escrever a cada linha, sendo somado com a variavel i, a qual ir� asumir os papeis de 0, 1 e 2*/
		printf("***");
	}
}

/*
Procedimento QuadradoAtivo
Busca privilegiar um unico quadrado dentre n, em que N < = QTDQUADRADOS
*/
void quadradoAtivo(RETANGULOS *selecionado, int id, int cor, int cortxt) /*apenas o que bater com a id vai ser o selecionado*/
{
	selecionado[id].cor = cor;
	selecionado[id].cortxt = cortxt;
}

/*
Procedimento QuadradoAtivo
Busca tornar os quadrados não selecionados como quadrados "cinza"
*/
void quadradoInativo(RETANGULOS *selecionado)
{
	selecionado->cor = LIGHTGRAY;
	selecionado->cortxt = LIGHTGRAY;
}

/*
Função validaQuadradoNovo
Busca criar um quadrado e validar o mesmo.
Tenta se espelhar nos pontos dos outros quadrados antecessores, após se encaixar em algum ele é verificado
se na verificação for apontado alguma interferência, o quadrado será movido de coordenada de um a um ponto.
Desta maneira, o melhor caso desta função é dado como a primeira iteração, quanto ao pior caso se deve a encontrar um espaço de 5x5.
OBS:
	O quadrado inicia com o mesmo tamanho do primeiro quadrado, caso não seja encontrado espaço para ele, ele é diminuído
	até que ele encaixe, caso ele seja totalmente diminuido a ponto de não caber o quadrado de asterísticos, ele é atualizado
	com os valores de NIL, tornando-o um quadrado inexistente por falta de espaço. O usuário é informado caso não haja mais
	espaço para o quadrado.
*/
QUADRADO validaQuadradoNovo(RETANGULOS *vetor, int qtd)
{
	int i, aux;
	QUADRADO novo;
	int linhas = LINHAS;   /*largura padrao*/
	int colunas = COLUNAS; /*altura padrao*/
	aux = 0;
	for (i = qtd - 1; i >= 0 && aux == 0; i--) /*i receberá quantidade e por meio de uma variável lógica executará o for*/
	{
		/*testa do lado direito do quadrado anterior*/
		novo.ponto4.X = vetor[i].tamanho.ponto3.X + colunas;
		novo.ponto4.Y = vetor[i].tamanho.ponto3.Y + linhas;

		if (cabenatela(novo.ponto4) == 1) /*se couber no primeiro ponto, aux será atualizado e o laço será quebrado*/
		{
			aux = 1;
			novo.ponto1.X = vetor[i].tamanho.ponto3.X + 1;
			novo.ponto1.Y = vetor[i].tamanho.ponto3.Y;
		}
		else
		{
			if (cabenatela(novo.ponto4) >= 2) /*nao cabe na direita*/
			{
				/*testa na esquerda*/
				novo.ponto4.X = vetor[i].tamanho.ponto2.X - 1;
				novo.ponto4.Y = vetor[i].tamanho.ponto2.Y;
				if (cabenatela(novo.ponto4) == 1)
				{
					aux = 1;
					novo.ponto1.X = vetor[i].tamanho.ponto2.X - colunas;
					novo.ponto1.Y = vetor[i].tamanho.ponto2.Y - linhas;
				}
				else
				{ /*testa em cima*/
					novo.ponto4.X = vetor[i].tamanho.ponto1.X + colunas;
					novo.ponto4.Y = vetor[i].tamanho.ponto1.Y + 1;
					if (cabenatela(novo.ponto4) == 1)
					{
						aux = 1;
						novo.ponto1.X = vetor[i].tamanho.ponto1.X;
						novo.ponto1.Y = vetor[i].tamanho.ponto1.Y - linhas;
					}
					else
					{ /*testa embaixo*/
						novo.ponto4.X = vetor[i].tamanho.ponto2.X + colunas;
						novo.ponto4.Y = vetor[i].tamanho.ponto2.Y + linhas;
						if (cabenatela(novo.ponto4) == 1)
						{
							aux = 1;
							novo.ponto1.X = vetor[i].tamanho.ponto2.X;
							novo.ponto1.Y = vetor[i].tamanho.ponto2.Y + 1;
						}
					}
				}
			}
		}

		novo.ponto2.X = novo.ponto1.X;
		novo.ponto2.Y = novo.ponto4.Y;
		novo.ponto3.X = novo.ponto4.X;
		novo.ponto3.Y = novo.ponto1.Y;

		/*condição com operador ternario*/
		if (i == 0 && aux == 0)
		{
			colunas = (colunas > 4) ? colunas - 1 : 3;
			linhas = (linhas > 4) ? linhas - 1 : 3;
			i = (colunas > 3 || linhas > 3) ? qtd - 1 : i;
			aux = (colunas > 3 || linhas > 3) ? 1 : 0;
		}
	}
	/*enquanto aux for verdadeiro e houver interferência*/
	while (aux == 1 && InterferenciaVetor(vetor, novo, qtd) == FALSE)
	{
		novo = andaquadrado(novo);
		novo.ponto2.X = novo.ponto1.X;
		novo.ponto2.Y = novo.ponto4.Y;
		novo.ponto3.X = novo.ponto4.X;
		novo.ponto3.Y = novo.ponto1.Y;
	}

	return ((aux == 1 ? novo : ativaNil()));
}

/*
Procedimento ValoresPadroes
Busca inicializar um registro como primeira variavel e com valores padroes
*/
void ValoresPadroes(RETANGULOS *retangulo)
{
	int x, y;
	retangulo->cor = BLUE;		   /* Cor da janela 1 = AZUL */
	retangulo->cortxt = LIGHTGRAY; /* Cor do texto 7 = LIGHTGRAY */
	retangulo->id = 0;			   /* Identificação do primeiro quadrado*/

	x = retangulo->tamanho.ponto1.X + 2;
	y = retangulo->tamanho.ponto1.Y + 2;
	/* Ativar Variáveis de coordenadas */
	AtivarCOORD(&retangulo->tamanho.ponto1, 1, 1);
	AtivarCOORD(&retangulo->tamanho.ponto2, 1, LINHAS);
	AtivarCOORD(&retangulo->tamanho.ponto3, COLUNAS, 1);
	AtivarCOORD(&retangulo->tamanho.ponto4, COLUNAS, LINHAS);
	AtivarCOORD(&retangulo->cursor, x, y);
}
