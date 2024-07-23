#include "funcoes.h"/*TODAS AS FUNÇÕES, STRUCTS, DEFINES e ENUMS*/
/********************************************
****INICIO DAS BIBLIOTECAS UTILIZADAS
********************************************/
#include "conio_v3.2.4.h"
/*
Biblioteca:"conio_v3.2.4.h"
O que foi utilizado:
->enum: 
COLORS, WHITE.

->functions:
clrscr();
gotoxy();
textcolor();
*/

#include "console_v1.5.4.h"
/*
Biblioteca:"console_v1.5.4.h"
O que foi utilizado:
->struct:
COORD

->functions:
getCoresJanela()
getPosicaoJanela()
getResolucaoJanela()
MaxDimensaoJanela()
setTituloJanela()
setPosicaoJanela()
setResolucaoJanela()
tamanhoJanelaConsole()
*/

#include <stdbool.h>
/*
Biblioteca:<stdbool.h>
O que foi utilizado:
->defines:
false
true

->tipo:
bool
*/	

#include <stdio.h>
/*
Biblioteca:<stdio.h>
O que foi utilizado:
->defines:
NULL

->functions:
putchar()
scanf()
*/

#include <stdlib.h>
/*
Biblioteca:<stdlib.h>
O que foi utilizado:
->functions:
free()
malloc()
realloc()
*/

#include <windows.h>
/*
Biblioteca:
O que foi utilizado:
->functions:
SetConsoleOutputCP()
*/	
/********************************************
****FIM DAS BIBLIOTECAS UTILIZADAS
********************************************/

/****************************************************************************************************************************************************************
****OBSERVAÇÃO: tudo da "funcoes.h" foi utilizado neste arquivo "funcoes.c", logo, não será comentado novamente.
*****************************************************************************************************************************************************************/

/*
atribuirAltura()
O que faz: atribui a altura de cada nó da arvore por meio de um percurso em pré-ordem.*/
void atribuirAltura(TIPONO *raiz, int altura)
{
    int i; /*auxiliar*/
    if (raiz == NULL)
    {
        return; /*retorno vazio*/
    }

    raiz->nivel = altura; /*recebe a altura relacionada ao nó*/

    for (i = 0; i < raiz->qtd_filhos; i++)
    {
        atribuirAltura(raiz->filho[i], altura + 1); /*passo recursivo*/
    }
}

/*
ativaVetorPontArea()
o que faz: ativa um vetor de ponteiros para TAREA, o qual será utilizado para armazenar os nós da arvore.*/
void ativaVetorPontArea(TAREA ***tela, int qtdIndice)
{
    int i;                                                 /*variavel auxiliar*/
    *tela = (TAREA **)malloc(sizeof(TAREA *) * qtdIndice); /*endereço que recebe um ponteiro de ponteiro no tamanho de qtd indice*/
    for (i = 0; i < qtdIndice; i++)
    {
        (*tela)[i] = (TAREA *)malloc(sizeof(TAREA));
        (*tela)[i]->ocupado = false;
        (*tela)[i]->prox = NULL; /*ativa o encadeamento externo com NULL*/
    }
}

/*
buscaespaco()
O que faz: busca um espaço vazio no vetor de ponteiros para TAREA, se necessário, realiza o encadeamento externo.*/
void buscaespaco(TAREA **tela, TIPONO *selecionado)
{

    TAREA *proximo; /*ponteiro que armazena indice da area*/

    proximo = tela[selecionado->nivel HASH]; /*hash do resto de 10*/
    while (proximo->ocupado)                 /*enquanto os endereços encaedados percorridos estiver ocupado, refaça o loop*/
    {
        if (proximo->prox == NULL) /*se o proximo encadeamento for NULL, crie um encadeamento novo e armazene o nó.*/
        {
            proximo->prox = (TAREA *)malloc(sizeof(TAREA)); /*ativa o ponteiro para o proximo*/
            proximo = proximo->prox;                        /*recebe o novo encadeamento*/
            proximo->ocupado = false;                       /*informa que está vazio para sair do laço*/
            proximo->prox = NULL;                           /*atribui NULL ao proximo para informar que é o último da lista*/
            proximo->no = (TIPONO *)malloc(sizeof(TIPONO)); /*ativa o ponteiro para recepção de um nó*/
        }
        else
        {
            proximo = proximo->prox; /*passa para o proximo encadeamento*/
        }
    }
    proximo->no = selecionado; /*recebe o endereço do nó contemplado*/
    proximo->ocupado = true;   /*informa que está ocupado*/
}


/*
bucaNo()
o que faz: busca um nó na arvore, retornando o endereço do nó encontrado.*/
TIPONO *buscaNo(TIPONO *raiz, int x)
{
    int i;             /*variavel auxiliar*/
    TIPONO *resultado; /*ponteiro que guarda o endereço do resultado*/
    if (raiz == NULL)
    {
        return NULL; /* Elemento não encontrado */
    }
    if (raiz->conteudo == x)
    {
        resultado = raiz;
        return resultado; /* Encontrou o nó com o valor x (retorna o próprio nó) */
    }

    for (i = 0; i < raiz->qtd_filhos && raiz->filho != NULL; i++)
    {
        resultado = buscaNo(raiz->filho[i], x); /*passo recursivo*/
        if (resultado != NULL)
        {
            return resultado; /* Encontrou o nó com o valor x em um dos filhos */
        }
    }
    return NULL; /* Elemento não encontrado na subárvore atual */
}

/*
calcularAlturaArvore()
O que faz: calcula a altura de cada nó da arvore chamando a função atribuirAltura().*/
void calcularAlturaArvore(TIPONO *raiz)
{
    atribuirAltura(raiz, PRIMEIRO_NIVEL); /*chamada inicial da função*/
}

/*
calcularQtdDigitos()
O que faz: Calcula a quantidade de digitos de cada nó, além disso, calcula a largura do nó, a qual é a soma da quantidade de digitos
            do nó com a quantidade de digitos dos filhos, mais 3 espaços para cada filho.
Observação: se ele não tiver filhos, ainda sim é incrementado 3 espaços (para cada lado) para a largura do nó. Isto serve para que seja conservado o
            espaço para o desenho do nó.
observação 2: a função é chamada após a função MSTdeCOORDENADAS(), pois é necessário que os nós já tenham sido distribuidos para que seja possível
            calcular a largura do nó. Além disso, faz o percurso em pós-ordem, pois é necessário que os espaços
            dos filhos já tenham sido calculados.*/
void calcularQtdDigitos(TIPONO *raiz)
{
    int i;                                   /*variavel auxiliar*/
    int qtdDigitosFilhos = ESPACO_ENTRE_NOS; /*espaço entre os nós*/
    if (raiz == NULL)                        /*se o no atual dor nulo, retorne void*/
    {
        return; /*vazio*/
    }

    for (i = 0; i < raiz->qtd_filhos; i++) /*laço de repetição para percorrer os filhos*/
    {
        calcularQtdDigitos(raiz->filho[i]); /*passo recursivo*/
    }
    for (i = 0; i < raiz->qtd_filhos; i++) /*soma do espaço dos filhos + espaços entre os nos em ambos os lados (esquerdo e direito)*/
    {
        qtdDigitosFilhos += raiz->filho[i]->etiqueta.caixinha.qtd_digit + ESPACO_ENTRE_NOS;
    }
    raiz->etiqueta.caixinha.largura_digit_filho = qtdDigitosFilhos; /*recebe o espaço necessário para caber todos os digitos dos filhos do nó atual*/
    /*se nao tiver filhos*/
    if (raiz->qtd_filhos == NENHUM_FILHO) /*é passado que ele necessita de um espaço mínimo, no caso, apenas seu digito e o espaço em ambos os lados*/
    {
        raiz->etiqueta.caixinha.largura_digit_filho = raiz->etiqueta.caixinha.qtd_digit + (ESPACO_ENTRE_NOS << 1);
    }
}

/*
contadigito()
o que faz: conta a quantidade de digitos de um numero de maneira recursiva.*/
int contadigito(int n)
{
    return (n / 10 != 0) ? 1 + contadigito(n / 10) : 1;
}

/*
DespersonalizarConsoleFULL()
o que faz: despersonaliza o console, retornando as configurações antigas.*/
void DespersonalizarConsoleFULL(DADOS antigo)
{
    /*titulo*/
    setTituloConsole(antigo.titulo);
    /*dimensionar*/
    setDimensaoJanela(antigo.resolucao.X, antigo.resolucao.Y);
    /*posicionar*/
    setPosicaoJanela(antigo.posicao.X, antigo.posicao.Y);
    textbackground(antigo.cor.CorFundo);
    textcolor(antigo.cor.CorTexto);
    /*setar cursor na cordenada mais distante para a vizualização da arvore*/
    gotoxy(FIMX, FIMY);
}

/*
encontrarNivelMaisAlto()
O que faz: encontra o nivel mais alto da arvore, retornando o valor do nivel mais alto
observação: a função é chamada após a função calcularAlturaArvore(), além disso, o valor do nível
            mais alto é atribuido apenas ao nó raiz para facilitar a passagem de parametro para a função.
observação 2: nível está diretamente relacionado a altura do nó, logo, o nível mais alto é o nó mais alto da arvore.*/
int encontrarNivelMaisAlto(TIPONO *raiz)
{
    int i, nivelMaximo, nivelFilho; /*variaveis auxiliares e de memória para o nivel*/
    if (raiz == NULL)
    {
        return PRIMEIRO_NIVEL; /*chegou em um nó nulo*/
    }

    nivelMaximo = raiz->nivel; /*maior nivel recebe a altura do nó selelcionado*/

    for (i = 0; i < raiz->qtd_filhos; i++) /*laço para percorrer os filhos se houver*/
    {
        nivelFilho = encontrarNivelMaisAlto(raiz->filho[i]); /*passo recursivo*/
        if (nivelFilho > nivelMaximo)                        /*verificação entre as alturas dos nós*/
        {
            nivelMaximo = nivelFilho; /*atribuir o nó mais alto*/
        }
    }

    return nivelMaximo; /*retorna o nivel máximo*/
}

/*
freeRecursivo()
O que faz: libera toda a memoria alocada para a arvore de maneira recursiva.
*/
void freeRecursivo(TAREA *prompt)
{
    if(prompt->prox != NULL)
    {
        freeRecursivo(prompt->prox);
    }
    free(prompt->no);
    free(prompt);
}

/*
freetudo()
O que faz: libera toda a memoria alocada para a arvore.
*/
void freetudo(TAREA **prompt)
{
    int i;
    for (i = 0; i < M; i++)
    {
        freeRecursivo(prompt[i]);
    }
    free(prompt);
}

/*
graficoQuadrado()
O que faz: Imprime um quadrado na tela, o qual é o nó da arvore.
observação: a função utiliza o percurso em pré-ordem para percorrer os nós, logo, o nó raiz será o primeiro a ser percorrido.
            e o valor de M neste programa, é 10.*/
void graficoQuadrado(TIPONO *no, COORD coordenada)
{
    COORD p1, p2, p3, p4; /*pontos do quadrado*/
    int i = 0;
    int cor = WHITE; /*cor do quadrado*/
    int x = coordenada.X;
    int y = coordenada.Y;

    /*ativa variavel*/
    p1.X = coordenada.X;
    p1.Y = coordenada.Y - UMDIGITO; /*meio para o canto*/
    p2.X = p1.X + no->etiqueta.caixinha.qtd_digit - UMDIGITO;
    p2.Y = coordenada.Y - UMDIGITO; /*meio para o canto*/
    p3.X = coordenada.X;
    p3.Y = coordenada.Y + UMDIGITO; /*meio para o canto*/
    p4.X = coordenada.X + no->etiqueta.caixinha.qtd_digit - UMDIGITO;
    p4.Y = coordenada.Y + UMDIGITO; /*meio para o canto*/

    /*printa quadrado*/
    textcolor(cor);

    /*linha superior*/
    for (i = p1.X; i <= p2.X; i++)
    {
        gotoxy(i, p1.Y);
        if (i == p1.X)
        {
            putchar(LATERAL_SE);
            continue;
        }
        if (i == p2.X)
        {
            putchar(LATERAL_SD);
            continue;
        }
        putchar(BASE);
    }
    /*linha inferior*/
    for (i = p3.X; i <= p4.X; i++)
    {
        gotoxy(i, p3.Y);
        if (i == p3.X)
        {
            putchar(LATERAL_IE);
            continue;
        }
        if (i == p4.X)
        {
            putchar(LATERAL_ID);
            continue;
        }
        putchar(BASE);
    }
    /*lado esquerdo*/
    for (i = p1.Y; i <= p3.Y; i++)
    {
        gotoxy(p1.X, i);
        if (i == p1.Y)
        {
            putchar(LATERAL_SE);
            continue;
        }
        if (i == p3.Y)
        {
            putchar(LATERAL_IE);
            continue;
        }
        putchar(LADO);
    }
    /*lado direito*/
    for (i = p2.Y; i <= p4.Y; i++)
    {
        gotoxy(p2.X, i);
        if (i == p2.Y)
        {
            putchar(LATERAL_SD);
            continue;
        }
        if (i == p4.Y)
        {
            putchar(LATERAL_ID);
            continue;
        }
        putchar(LADO);
    }
    /*printa o centro, o conteudo*/
    gotoxy(x + UMDIGITO, y);
    printf("%d", no->conteudo);
}

/*
insereFilho()
o que faz: insere os filhos de um nó, alocando a memoria necessaria para os filhos.*/
void insereFilho(TIPONO **no, int qtdmax)
{
    int i = 0, x;                   /* variavel auxiliar*/
    int qtdmin = (*no)->qtd_filhos; /*qtd minima de filhos, geralmente > 0*/

    if (qtdmin == NENHUM_FILHO) /*se for 0, é porque o nó não tinha filhos antes, portanto, será alocado um espaço*/
    {
        (*no)->filho = (TIPONO **)malloc(sizeof(TIPONO) * (qtdmax + 1));
    }
    else /*se não for 0, é porque tinha filhos e será adicionado mais filhos a cerca deste, logo será realocado o espaço para inserir mais filhos*/
    {
        (*no)->filho = (TIPONO **)realloc((*no)->filho, ((*no)->qtd_filhos + (qtdmax + 1)) * (sizeof(TIPONO)));
    }
    /*soma a quantidade anterior de filhos com a nova*/
    (*no)->qtd_filhos += qtdmax;
    /*le os filhos*/
    for (i = qtdmin; i < qtdmax; i++)
    {
        /*se inicia a alocação de filhos*/
        scanf("%d", &x);
        (*no)->filho[i] = (TIPONO *)malloc(sizeof(TIPONO)); /*ativa unidade do vetor de filhos*/
        if (x != -1)                                        /*se o valor lido for diferente de -1*/
        {
            /*atribuição de valores iniciais padrões*/
            (*no)->filho[i]->conteudo = x;                                     /*conteudo*/
            (*no)->filho[i]->qtd_filhos = NENHUM_FILHO;                        /*quantidade de filhos que o nó possui*/
            (*no)->filho[i]->visitado = true;                                  /*visitado*/
            (*no)->filho[i]->etiqueta.caixinha.qtd_digit = contadigito(x) + 2; /*quantidade de digitos do conteudo*/
            (*no)->filho[i]->fim = false;                                      /*fim*/
            (*no)->filho[i]->filho = NULL;                                     /*filho*/
            (*no)->filho[i]->pai = (*no);                                      /*pai*/
        }
        else
        {
            break; /*foi encontrado um -1*/
        }
    }
    (*no)->filho[i] = NULL; /*atribui NULL para o ultimo filho para prevencao de overflow posteriormente*/
}

/*
linhaX()
O que faz: Imprime uma linha na tela, o qual é o nó da arvore. Além disso, a linha é apenas no eixo das abscissas.*/
void linhaX(COORD inicio, COORD fim)
{
    int i;
    for (i = inicio.X; i <= fim.X; i++)
    {
        gotoxy(i, inicio.Y);
        putchar(BASE);
    }
}

/*
mapeadorDeNos()
O que faz: remapeia os nós, caso haja colisão entre os nós, o qual é feito por meio de um calculo de distancia entre os filhos.*/
void mapeadorDeNos(TIPONO *no)
{
    int x1;          /*filho 0*/
    int x2;          /*filhos mais longe*/
    int coeficiente; /*coeficiente de distancia entre os filhos*/
    int novox;       /*novo x*/

    if (no->qtd_filhos > UM_FILHO) /*mais de um filho*/
    {
        x1 = no->filho[PRIMEIROFILHO]->etiqueta.caixinha.centro.X;
        x2 = no->filho[no->qtd_filhos - 1]->etiqueta.caixinha.centro.X;
        coeficiente = x2 - x1;
        novox = x1 + coeficiente / METADE;
        no->etiqueta.caixinha.centro.X = novox + no->etiqueta.caixinha.qtd_digit / METADE;
    }
}

/*
mnvi()
O que faz: retorna o maior numero de um vetor de inteiros.*/
int mnvi(int *vetor, int n) /*função que retorna o Maior Numero do Vetor de Inteiro*/
{
    int i = 0;
    int maior = 0;
    for (i = 0; i < n; i++)
    {
        if (vetor[i] > maior)
        {
            maior = vetor[i];
        }
    }
    return maior;
}

/*
MSTdeCOORDENADAS()
o que faz: busca fazer a distribuição "justa" de coordenadas para cada nó.
observação: a função é chamada após a função calcularAlturaArvore() e encontrarNivelMaisAlto(). Além disso,
            a coordenada é apenas um local relativo, pois se o nó tiver mais filhos ou digitos e necessitar
            de espaço, o mesmo será deslocado.
observação 2: a função utiliza o encadeamento externo para armazenar os nós, o qual é um vetor de ponteiros para TAREA.
            No caso, o vetor é de tamanho M, o qual é definido como M, logo, o vetor terá M indices, para caber todos os nós.
            Desta forma, facilitando a busca de nós, prezando apenas por busca pela altura, o qual a altura do nó é o resto
            do indice com M.
observação 3: função utiliza o percurso em pré-ordem para percorrer os nós, logo, o nó raiz será o primeiro a ser percorrido.
            e o valor de M neste programa, é 10.*/
void MSTdeCOORDENADAS(TIPONO *raiz, TIPONO *no, TAREA **tela) /*raiz da arvore, nó atual, vetor de tamanho M*/
{
    int i;                             /*variavel auxiliar*/
    buscaespaco(tela, no);             /*chamada da função buscaespaço*/
    if (no->qtd_filhos > NENHUM_FILHO) /*se tiver filho é executado o passo recursivo*/
    {
        for (i = 0; i < no->qtd_filhos; i++)
        {

            MSTdeCOORDENADAS(raiz, no->filho[i], tela); /*passo recursivo*/
        }
    }
}

/*PersonalizarConsoleFULL()
o que faz: personaliza o console, dimensionando a janela para o tamanho maximo
observação: retorna uma struct com as informações antigas do console, necessario para despersonalizar o console
            necessita do codigo de paginação 437 para funcionar corretamente.*/
DADOS PersonalizarConsoleFULL(char *Titulo)
{
    /*declarar variaveis*/
    DADOS tela;
    SetConsoleOutputCP(CP437);
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
    ;
    /*posicionar*/
    setPosicaoJanela(0, 0);
    /*dimensionar*/
    setDimensaoJanela(MaxDimensaoJanela().X, MaxDimensaoJanela().Y);
    /*retornar a memoria*/
    clrscr();
    return tela;
}

/*
PrintaNos()
O que faz: Imprime os nós da arvore, além disso, calcula a posição de cada nó, a qual é armazenada na struct caixinha do nó.
observação: a função não visita o nó por meio de busca envolvendo a árvore, mas sim por meio do vetor de ponteiros para TAREA.
            Desta forma, o vetor de ponteiros para TAREA é percorrido, e se o nó estiver ocupado, é calculado a posição do nó.
            Além disso, a função utiliza o percurso em pré-ordem para percorrer os nós, logo, o nó raiz será o primeiro a ser percorrido.
            e o valor de M neste programa, é 10.*/
void PrintaNos(TAREA **area, int *vetorDeAltura)
{
    /*declaração variaveis*/
    int AlturaArvore = area[PRIMEIROFILHO]->no->nivel_max;      /*altura maxima da arvore*/
    int MaiorLarguraArvore = mnvi(vetorDeAltura, AlturaArvore); /*a altura da arvore que contém a maior largura em colunas*/
    int guardaCalculo = 0;                                      /*auxiliar para economizar espaço ao fazer calculos*/
    COORD PosTempNo;                                            /*posicao temporaria, atualiza em cada nó*/
    TAREA *prox;                                                /*para percorrer os encadeados*/
    int i, j = 0;                                               /*variaveis auxiliares*/
    /*impressão de nós*/

    /*novo percorre TAREA*/
    for (i = 0; i <= AlturaArvore; i++)
    {
        prox = area[i HASH];                    /*recebe o endereço relacionado ao hash do vetor de ponteiros*/
        if (i > PRIMEIRO_NIVEL && prox != NULL) /*se i estiver acima do primeiro nivel e o endereço atual nao for nulo*/
        {
            if (prox->ocupado && prox->no->nivel == i) /*se o endereço que estamos lidando estiver ocupado e no nivel exigido*/
            {
                /*realize o calculo para armazenagem parcial do nó, o qual é apontado pelo endereço atual*/
                guardaCalculo = prox->no->pai->etiqueta.caixinha.centro.X - prox->no->pai->etiqueta.caixinha.largura_digit_filho / ESPACOMIN + UMDIGITO;
            }
        }
        /*percorrer os endereços encadeados*/
        while (prox != NULL)
        {
            if (prox->ocupado && prox->no->nivel == i)
            {
                /*calcula posição do nó*/
                guardaCalculo += prox->no->etiqueta.caixinha.largura_digit_filho / ESPACOMIN + UMDIGITO;
                PosTempNo.X = guardaCalculo;
                guardaCalculo += prox->no->etiqueta.caixinha.largura_digit_filho / ESPACOMIN;
                PosTempNo.Y = ((prox->no->nivel + UMDIGITO) * ALTURA << UMDIGITO) - ESPACO_ENTRE_NOS;

                if (i == NIVEL_INICIAL) /* apenas o primeiro nivel*/
                {
                    PosTempNo.X = FIMX/2 - (MaiorLarguraArvore + prox->no->etiqueta.caixinha.largura_digit_filho);
                    /*o primeiro nó, no caso, a raiz, é centralizada com a largura da árvore, em outras palavras,
                    como o nascimento dos demais nós necessitam da raiz, a mesma não pode nascer em função de seus
                    filhos, causando assim, a descentralização relativa da raiz com seus primeiros filhos.*/
                }
                prox->no->etiqueta.caixinha.centro = PosTempNo; /*guarda a posição calculada*/
            }

            prox = prox->prox; /*vai para o proximo endereço*/
        }
        guardaCalculo = RESET; /*reseta o calculo para o próximo nivel*/
    }

    /*laço que busca interceder por colisões, cada nivel da arvore é ajustado e seu ajuste é repassado dos nós
    para os filhos, dessa forma, a quantidade de nivel que a arvore estiver, será a quantidade que irá se
    repetir para neutralizar a colisão entre os nós.*/
    while (j < AlturaArvore)
    {
        for (i = 0; i < M; i++)
        {
            prox = area[i];
            while (prox != NULL)
            {
                if (prox->ocupado)
                {
                    if (prox->no->qtd_filhos > NENHUM_FILHO) /*se tiver filhos*/
                    {
                        mapeadorDeNos(prox->no); /*remapeia os nós*/
                    }
                }
                prox = prox->prox;
            }
        }
        j++; /*incrementa o j*/
    }

    /*ultimo laço da função, o qual busca imprimir no console*/
    for (i = 0; i < M; i++)
    {
        prox = area[i];
        while (prox != NULL)
        {
            if (prox->ocupado)
            {
                graficoQuadrado(prox->no, prox->no->etiqueta.caixinha.centro); /*imprime o nó selecionado*/
            }

            prox = prox->prox;
        }
    }
    /*libera o vetor passado para a função*/
    free(vetorDeAltura);
}

/*
PrintaVertice()
O que faz: busca imprimir no console os vétices de cada nó em relação ao seu pai e/ou filho*/
void PrintaVertice(TAREA **area)
{
    int i, j;          /*variaveis auxiliares*/
    bool flag = false; /*flag de encontro*/
    COORD raboPai;     /*conexao inferior em coordenadas do no pai*/
    TIPONO *pai;       /*no pai*/
    COORD filho1;      /*coordenadas da coneção superior do primeiro filho*/
    COORD filho2;      /*coordenadas da coneção superior do segundo filho*/
    TAREA *prox;       /*auxiliar para percorrer ovetor de ponteiros*/

    for (i = 0; i < M; i++) /*laço para percorrer o vetor de ponteiros*/
    {
        prox = area[i];
        while (prox != NULL)
        {
            if (prox->ocupado)
            {
                if (prox->no->qtd_filhos > NENHUM_FILHO) /*se o no selecionado tiver filhos*/
                {
                    pai = prox->no;                                                                                                                                 /*no é alocado em variavel pai para resumir espaço*/
                    raboPai.X = pai->etiqueta.caixinha.centro.X + pai->etiqueta.caixinha.qtd_digit / METADE;                                                        /*calcula a posição do rabo do pai*/
                    raboPai.Y = pai->etiqueta.caixinha.centro.Y + ESPACO_ENTRE_NOS;                                                                                 /*calcula a posição do rabo do pai*/
                    filho1.X = pai->filho[PRIMEIROFILHO]->etiqueta.caixinha.centro.X + pai->filho[PRIMEIROFILHO]->etiqueta.caixinha.qtd_digit / METADE;             /*calcula cabeça do filho 1*/
                    filho1.Y = pai->filho[PRIMEIROFILHO]->etiqueta.caixinha.centro.Y - ESPACO_ENTRE_NOS;                                                            /*calcula cabeça do filho 1*/
                    filho2.X = pai->filho[pai->qtd_filhos - 1]->etiqueta.caixinha.centro.X + pai->filho[pai->qtd_filhos - 1]->etiqueta.caixinha.qtd_digit / METADE; /*calcula cabeça do filho 2*/
                    filho2.Y = pai->filho[pai->qtd_filhos - 1]->etiqueta.caixinha.centro.Y - ESPACO_ENTRE_NOS;                                                      /*calcula cabeça do filho 2*/

                    /*linha/vertice principal*/
                    linhaX(filho2, filho1);
                    linhaX(filho1, filho2);
                    /*feito mais de uma vez para garantia de irmãos com coordenadas alteradas*/

                    /*printa ligação*/
                    gotoxy(raboPai.X, raboPai.Y - UMDIGITO);
                    putchar(LADO); /* parte de vertice*/
                    for (j = 0; j < pai->qtd_filhos; j++)
                    {
                        /*imprimir encontro de vertice*/
                        gotoxy(pai->filho[j]->etiqueta.caixinha.centro.X + pai->filho[j]->etiqueta.caixinha.qtd_digit / METADE, pai->filho[j]->etiqueta.caixinha.centro.Y - ESPACO_ENTRE_NOS);
                        putchar(UNIAO_BAIXO);
                        gotoxy(pai->filho[j]->etiqueta.caixinha.centro.X + pai->filho[j]->etiqueta.caixinha.qtd_digit / METADE, pai->filho[j]->etiqueta.caixinha.centro.Y - ESPACOMIN);
                        putchar(LADO);
                        gotoxy(pai->filho[j]->etiqueta.caixinha.centro.X + pai->filho[j]->etiqueta.caixinha.qtd_digit / METADE, pai->filho[j]->etiqueta.caixinha.centro.Y - UMDIGITO);
                        putchar(UNIAO_CIMA);

                        /*detecção de união direta por meio de quantidade de filhos, se for impar, o no precisa de uma uniao direta omnidimensional*/
                        if (pai->etiqueta.caixinha.centro.X == pai->filho[j]->etiqueta.caixinha.centro.X + (pai->filho[j]->etiqueta.caixinha.qtd_digit / METADE - (pai->etiqueta.caixinha.qtd_digit % 2 == 0 ? -1 : 1)))
                        {
                            flag = true;
                        }
                    }

                    /*canto de vertice*/
                    gotoxy(filho1.X, filho1.Y);
                    putchar(LATERAL_SE);

                    gotoxy(filho2.X, filho2.Y);
                    putchar(LATERAL_SD);

                    /*ligar pai a linha*/
                    gotoxy(raboPai.X, raboPai.Y - ESPACOMIN);
                    putchar(UNIAO_BAIXO);
                    gotoxy(raboPai.X, raboPai.Y);
                    putchar(UNIAO_CIMA);

                    /*para casos de arvore "zig-zag"*/
                    if (pai->qtd_filhos == UM_FILHO)
                    {
                        gotoxy(raboPai.X, raboPai.Y);
                        putchar(LATERAL_IE);
                        raboPai.X++;
                        linhaX(raboPai, filho1);
                        raboPai.X--;
                        gotoxy(filho1.X, raboPai.Y);
                        putchar(LATERAL_SD);
                    }
                    if (flag) /*se a flag estiver ativa, imprimir caractere omnidirecional*/
                    {
                        gotoxy(raboPai.X, raboPai.Y);
                        putchar(UNIAO_DUPLA);
                    }
                    flag = false; /*resetar o flag*/
                }
            }
            prox = prox->prox; /*proximo endereço*/
        }
    }
}


/*
TrenaPorAltura()
O que faz: Cria um vetor com a quantidade de niveis relacionada a altura da arvore, para assim, poder calcular a altura de cada nivel,
            após isto, é retornado este vetor já inicializado com os valores necessários.

observação: a função é chamada após a função calcularAlturaArvore() e encontrarNivelMaisAlto(). Além disso,
            a coordenada é apenas um local relativo, pois se o nó tiver mais filhos ou digitos e necessitar
            de espaço, o mesmo será deslocado.*/
int *TrenaPorAltura(TAREA **tela)
{
    int i;                                                                 /*variavel auxiliar*/
    int *vetor = malloc(sizeof(int) * tela[PRIMEIROFILHO]->no->nivel_max); /*ativa o vetor*/
    TAREA *prox;
    /*inicializa*/
    for (i = 0; i <= tela[PRIMEIROFILHO]->no->nivel_max; i++)
    {
        vetor[i] = NIVEL_INICIAL; /*inicializa todas as posições com o valor do nivel inicial, ou seja, 0*/
    }
    /*percorre o vetor de ponteiros para TAREA*/
    for (i = 0; i <= tela[PRIMEIROFILHO]->no->nivel_max; i++)
    {
        prox = tela[i HASH]; /*realiza o hash para a verificação de que está realmente operando em certo nível*/

        while (prox != NULL) /*percorrer o vetor de ponteiros*/
        {

            if (prox->ocupado)
            {
                if (prox->no->nivel == i)
                {
                    /*salva posição relativa da altura*/
                    vetor[i] += prox->no->etiqueta.caixinha.largura_digit_filho;
                }
            }
            prox = prox->prox; /*percorre para o próximo endereço*/
        }
    }

    return vetor; /*retorna o vetor criado*/
}