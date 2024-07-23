/*
    #Funcoes.h

        Biblioteca de funções para o programa arvore.c.
        Cabeçalho que complementa a biblioteca "funcoes.c".
        Autor: Nícolas Herculano Pires
    
    Ultima modificação: 20/11/2023
*/

/********************************************
****INICIO DAS BIBLIOTECAS UTILIZADAS
********************************************/

#include "console_v1.5.4.h"
/*
Biblioteca:"console_v1.5.4.h"
O que foi utilizado:
->struct:
COORD

->functions:
MaxDimensaoJanela()
*/
	
#include <stdbool.h>
/*
Biblioteca:<stdbool.h>
O que foi utilizado:

->tipo:
bool
*/	

#include <stdlib.h>
/*
Biblioteca:<stdlib.h>
O que foi utilizado:
->functions:
malloc()
*/

/********************************************
****FIM DAS BIBLIOTECAS UTILIZADAS
********************************************/

/********************************************
****INICIO DAS DEFINES UTILIZADAS
********************************************/

#define ALTURA 3/*altura de cada no*/
#define BASE 196/*base do quadrado em ascii*/
#define CP437 437/*codigo de paginação utilizado*/
#define CRIAR_NO malloc(sizeof(TIPONO))/*criar nó resumido*/
#define ESPACO_ENTRE_NOS 3/*espaço ideal entre os nós*/
#define ESPACOMIN 2/*espaço minimo entre os nós*/
#define FIMX MaxDimensaoJanela().X /*maior resolução da janela no eixo das abscissas*/
#define FIMY MaxDimensaoJanela().Y/*maior resolução da janela no eixo das ordenadas*/
#define HASH % M/*hash simples, o qual se baseia no resto da divisão por 0, seguindo a lógica do vetor de ponteiros, os primeiros indices alocados
               o mais proximo da origem, sempre será os niveis mais proximos da raiz, ou seja, dado o indice 1 com seus hipoteticos 3 ponteiros para nos, teremos o 
               seguinte:                                                                                                                                            
               indice[1]: pno |-|>|pno |-|>|pno |-|>|                                                                                                                
               a probabilidade do primeiro pno |-|>| estar no nivel 1, é exata, ele sempre estará, ja o segundo nó(com base contexto do encadeamento), sabe-se que pode estar tanto no nivel 1       
               quanto no nível 11, porém, impossível ele estar no nivel 21 se nao foi passado pelo nó 11.                                                        
               */
#define INICIOXEY 0/*inicio do eixo das abscissas e ordenadas*/
#define LADO 179/*lado do quadrado correspondente ao numero da tabela ascii*/
#define LATERAL_IE 192/*quina do quadrado inferior esquerda correspondente ao numero da tabela ascii*/
#define LATERAL_ID 217/*quina do quadrado inferior direita correspondente ao numero da tabela ascii*/
#define LATERAL_SE 218/*quina do quadrado superior esquerda correspondente ao numero da tabela ascii*/
#define LATERAL_SD 191/*quina do quadrado superior direita correspondente ao numero da tabela ascii*/
#define M 10/*tamanho tabela hash*/
#define METADE 2/*metade de algo*/
#define NIVEL_INICIAL 0/*nivel inicial de uma arvore*/
#define PRIMEIROFILHO 0/*primeiro filho de um no*/
#define PRIMEIRO_NIVEL 0/*primeiro nivel de uma arvore*/
#define RESET 0/*resetar com o 0*/
#define TETO 196/*teto do quadrado correspondente ao numero da tabela ascii*/
#define UMDIGITO 1/*um unico digito ou coluna, utilizado para somar ou subtrair*/
#define UNIAO_BAIXO 194/*uniao de vertice para baixo correspondente ao numero da tabela ascii */
#define UNIAO_CIMA 193/*uniao de vertice para cima correspondente ao numero da tabela ascii*/
#define UNIAO_DUPLA 197/*uniao dupla, para cima e para baixo correspondente ao numero da tabela ascii*/
#define VERTICE_H 196  /*vertice horizontal correspondente ao numero da tabela ascii*/
#define VERTICE_V 179  /*vertice vertical correspondente ao numero da tabela ascii*/
/********************************************
****FIM DAS DEFINES UTILIZADAS
********************************************/

/********************************************
****INICIO DOS ENUMS UTILIZADOS
********************************************/

typedef enum info_filhos/*informação de filhos*/
{
    NENHUM_FILHO,/*nenhum filho*/
    UM_FILHO,/*apenas um filho*/
    DOIS_FILHOS/*dois filhos*/
} FILHOS;
/********************************************
****FIM DOS ENUMS UTILIZADOS
********************************************/

/********************************************
****INICIO DAS STRUCTS UTILIZADAS
********************************************/

/*struct: DADOS*/
/*objetivo: armazenar dados do console antes de executar o programa*/
typedef struct dados_pc
{
    COORD resolucao;
    COORD posicao;
    CORES cor;
    char *titulo;
} DADOS;

/*struct: QUADRADO*/
/*objetivo: armazenar dados de um quadrado, com a finalidade de alterar e imprimir posteriormente*/
typedef struct QUADRADO
{
    COORD p1, p2, p3, p4;/*pontos do quadrado, 4 pontos se forma um quadrado*/
    /*
    p1----p2
    |       |
    |       |
    p3----p4
    */
    COORD centro;/*centro do quadrado*/
    /*
    p1----p2
    |centro|
    |centro|
    p3----p4
    */
    COORD centro_topo;/*centro topo do quadrado*/
    /*
    centro_topo == x
    p1--X--p2
    |       |
    |       |
    p3----p4
    */
    COORD centro_base;/*centro base do quadrado*/
    /*
    centro_base == x
    p1----p2
    |       |
    |       |
    p3--X--p4
    */
    int qtd_digit;/*qtd de digito de largura do quadrado*/
    int largura_digit_filho;/*qtd de digitos de largura do proximo quadrado(quadrado dos filhos do nó)*/
} QUADRADO;

/*struct: TNG(Tipo nó grafico)*/
/*objetivo: armazenar dados de um nó, com base em informações graficas relevantes*/
typedef struct t_no_g
{
    QUADRADO caixinha;
    int nivel;/*nivel que o nó está*/
} TNG;

/*struct: T_PROPRIEDADE(Tipo Propriedade)*/
/*objetivo: armazenar dados de um nó, com base em informações de localização relativa relevantes*/
typedef struct t_prop /* propriedade do nó*/
{
    int altura;/*altura do nó em relação a linhas*/
    int LarguraRelativa; /*largura relativa do ramo de mesmo nivel até chegar ao nó*/
    int LarguraTotal;    /*largura total dos nós de mesma altura*/
} T_PROPRIEDADE;

/*struct: TIPONO(tipo nó)*/
/*objetivo: armazenar dados de um nó, com base em informações gerais relevantes e exatas*/
typedef struct t_no
{
    bool visitado;/*booleano para saber se foi visitado ou não*/
    bool fim;/*booleano para saber o nó é uma folha*/
    int conteudo;/*inteiro que guarda o valor do nó*/
    int qtd_filhos;/*qtd de filhos que um nó tem, geralmente, se não tiver filhos o valor é 0*/
    int nivel;/*nivel ou altura em que o nó se encontra, a raiz é altura/nível 0*/
    int nivel_max;/*nivel máximo que um nó chega(apenas a raiz guarda tal informação, a pesar de outros nós também suportarem tal atributo)*/
    T_PROPRIEDADE propriedade;/*propriedades relativas, mas úteis do nó*/
    TNG etiqueta;/*parte gráfica do nó*/
    struct t_no *pai;/*ponteiro que aponta para o pai do nó, se for a raiz, este atributo contará com NULL*/
    struct t_no **filho; /*aponta para varios nos filhos, se não tiver filhos, este atributo será NULL*/
} TIPONO;

/*struct: TAREA(tipo área)*/
/*objetivo: Criado a fim de servir como um vetor de ponteiros, o qual converte uma árvore em uma tabela hash de alocação externa*/
typedef struct t_area
{
    bool ocupado;/*booleano que define se está opcupado ou não, true = está ocupado, false = está livre para ser ocupado*/
    TIPONO *no;/*ponteiro que aponta para o endereço do nó contemplado com tal posição de TAREA*/
    struct t_area *prox;/*ponteiro que aponta para o encadeamento de uma lista externa, normalmente, quando chega ao fim da lista, o valor é NULL*/
} TAREA;
/********************************************
****FIM DAS STRUCTS UTILIZADAS
********************************************/

/********************************************
****INICIO DOS CABEÇALHOS DE FUNÇÕES	
********************************************/

/*# atribuirAltura()
Dado a raiz e o valor inicial dado como "ponto de início à arvore", a função atribui a altura de cada nó,
com base na altura do nó pai, ou seja, se o nó pai tem altura 2, então o nó filho terá altura 3.*/
void atribuirAltura(TIPONO *, int );

/*# atribuirLargura()
Dado o ponteiro de ponteiro (vetor de ponteiros) do tipo área, ativar o mesmo com a quantidade de índices
informado no escopo, atualmente, este índice é M*/
void ativaVetorPontArea(TAREA ***, int );

/*# buscaespaco()
Dado o ponteiro de ponteiro (vetor de ponteiros) do tipo área, e o ponteiro do tipo nó, a função busca um
endereço no vetor de ponteiros do tipo área, o qual esteja livre para ser ocupado, caso não encontre, a função
aloca um novo endereço, o encadeando com o último endereço do vetor de ponteiros do tipo área.*/
void buscaespaco(TAREA **, TIPONO *);

/*# buscaNo()
Dado a raiz como parâmetro, e o valor do nó que se deseja encontrar, a função busca o endereço do nó e o retorna,
caso não encontre, a função retorna NULL*/
TIPONO *buscaNo(TIPONO *, int );

/*# calcularAlturaArvore()
Dado a raiz como parâmetro, a função calcula a altura de cada nó, com base na altura do nó pai, o qual é alterado
pelo #define PRIMEIRONIVEL. O pai recebe o primeiro nível/altura, e os filhos recebem o primeiro nível/altura + 1.
Além disso, esta função conta com a função atribuirAltura(), a qual atribui a altura de cada nó, com base na altura*/
void calcularAlturaArvore(TIPONO *);

/*# calcularQtdDigitos()
Dado um nó como parâmetro, a função calcula a quantidade de dígitos que os filhos do nó possui, e o armazena no
atributo, caso o nó não tenha filhos, ele ainda receberá um valor no atributo, no caso, sua própria quantidade de dígitos
junto com a soma dos limites entre nó.

OBSERVAÇÃO: o fator do nó ter filho ou não, independe da soma dos limites entre nó, o qual é definido pelo #define ESPACO_ENTRE_NOS*/
void calcularQtdDigitos(TIPONO *);

/*# contadigito()
Dado um valor inteiro, a função conta a quantidade de dígitos que o valor possui, e retorna a quantidade de dígitos.*/
int contadigito(int );

/*# DespersonalizarConsoleFULL()
Dado o tipo DADOS como parâmetro, a função desativa o console, retornando-o ao estado inicial, com base nos dados coletados ao
iniciar o programa.*/
void DespersonalizarConsoleFULL(DADOS );

/*# encontrarNivelMaisAlto()
Dado a raiz da árvore, com todos os nós com suas respectivas variáveis de altura, a função busca o nível mais alto da 
árvore, e retorna o valor.*/
int encontrarNivelMaisAlto(TIPONO *);

/*# freeRecursivo()
Dado um nó como parâmetro, a função libera o nó associado a cada encadeamento */
void freeRecursivo(TAREA *);

/*# freetudo()
Dado o ponteiro de ponteiro (vetor de ponteiros) do tipo área, a função libera todos os nós alocados no vetor de ponteiros do tipo área*/
void freetudo(TAREA **);

/*# graficoQuadrado()
Dado um nó e uma coordenada, a função imprime um quadrado na tela, com base na coordenada informada, e embutido, imprime
o valor do nó junto.
A coordenada passada como parâmetro, deve ser considerada como o centro do quadrado, sendo que o quadrado vai ser desenhado
em volta deste centro e respeitando os limites de digitos do nó também passado como parâmetro*/
void graficoQuadrado(TIPONO *, COORD );

/*# insereFilho()
Dado um ponteiro com a quantidade de filhos que será colocado no nó, e o nó que receberá os filhos, a função insere os filhos no nó,
caso o nó não tenha filhos, a função não faz nada.*/
void insereFilho(TIPONO **, int );

/*# linhaX()
Dado um ponto de inicio e um ponto de destino, esta função traça uma linha com base em putchar().*/
void linhaX(COORD , COORD );

/*# mapeadorDeNos()
Dado um nó, o qual obrigatóriamente, deve ter ao menos um filho, a função mapeia os nós, com base na quantidade de filhos,
buscando o centralizar em relação aos.*/
void mapeadorDeNos(TIPONO *);

/*# mnvi()
Dado um vetor e seu índice, a função mnvi (maior numero do vetor inteiro) busca o maior número do vetor e retorna o valor
observação: Não retorna o índice, apenas o maior valor encontrado em todo o conteúdo do vetor*/
int mnvi(int *, int );

/*# MSTdeCORDENADAS()
Dado a raiz, um nó selecionado e um vetor de ponteiro baseado em HASH de encadeamento esterno,
a função busca fazer a distribuição "justa" de coordenadas para cada nó.
observação: a coordenada é apenas um local relativo, pois se o nó tiver mais filhos ou digitos e necessitar
            de espaço, o mesmo será deslocado.
observação 2: a função utiliza o encadeamento externo para armazenar os nós, o qual é um vetor de ponteiros para TAREA.
            No caso, o vetor é de tamanho M, o qual é definido como M, logo, o vetor terá M indices, para caber todos os nós.
            Desta forma, facilitando a busca de nós, prezando apenas por busca pela altura, o qual a altura do nó é o resto
            do indice com M.
observação 3: função utiliza o percurso em pré-ordem para percorrer os nós, logo, o nó raiz será o primeiro a ser percorrido.
            e o valor de M é definido por #define M, atualmente, está em 10.*/
void MSTdeCOORDENADAS(TIPONO *, TIPONO *, TAREA **);

/*# PersonalizarConsoleFULL()
Dado uma string com o nome que o console deve ficar, o mesmo troca o nome do prompt e retorna os dados do console antes de
realizar a alteração.*/
DADOS PersonalizarConsoleFULL(char *);

/*# PrintaNos()
Dado um vetor de ponteiros do tipo área, e um vetor de inteiros o qual obrigatoriamente, tem que estar relacionado
a altura da árvore armazenada no vetor de ponteiros do tipo área. a função imprime os nós, com base na altura de cada nó.
Observação: Para o vetor de alturas estar relaciondo à árvore, cada índice dele deve se referir à largura de colunas referente
a altura de mesmo nível. Por exemplo, altura 0, tem apenas o nó raiz, portanto, o indice 0 do vetor de alturas, deve ser igual
a quantidade de colunas que o nó raiz possui, ou seja, o valor do nó raiz->etiqueta.caixinha.qtd_digit. Isto é válido para todos.
Observação 2: O vetor de alturas tem,q ue ser utilizado, por conta que o vetor de ponteiros possúi apenas 10 posições, logo, se
a arvore contar com mais de 10 posições, o vetor de inteiros deve acomparanhar tal posição.*/
void PrintaNos(TAREA **, int *);

/*# PrintaVertice()
Dado um vetor de ponteiros do tipo área, a função imprime os vértices, com base na altura de cada nó.
Observação: é obrigatório todos os nós estarem com as devidas coordenadas EXATAS e com seu respectivo
"quadrado" impresso na tela, caso contrário, a função não funcionará corretamente.*/
void PrintaVertice(TAREA **);

/*# TrenaPorAltura()
Dado um vetor de ponteiros, do tipo área, a função irá percorrer cada altura e armazenar a largura total, já embutido outros dados,
por exemplo, o de distancia mínima entre um nó e a quantidade que os filhos de um nó irá ocupar, esta função retorna um vetor de inteiros,
o qual cada índice X corresponde a altura X, ou seja, o indice 4 corresponde a largura que a altura 4 ocupa na árvore.
Observação: A Largura que é salvo já conta com o espaço de filhos para melhor centralização dos nós.*/
int *TrenaPorAltura(TAREA **);

/********************************************
****FIM DOS CABEÇALHOS DE FUNÇÕES	
********************************************/

