/*
 *   Arquivo "funcoes.c", responsavel pelo desenvolvimento da parte lógica e funcional
 *   do arquivo "CAUEMA.c".
 *
 */

#include "funcoes.h"

/*
 * #include <funcoes.h>
 * Utiliza todos os cabeçalhos de funções e procedimentos, além de todas as structs, bibliotecas e constantes.
 */

/* Bibliotecas atreladas à "funcoes.h", as quais teve impacto no arquivo "funcoes.c" e "CAUEMA.c"
*
*   #include <ctype.h>
    +Funções utilizadas:
    isdigit();

*   #include <math.h>
    +Funções utilizadas:
    pow();

*   #include <stdio.h>  (utilizada apenas no arquivo CAUEMA.c)
    +Funções utilizadas:
    printf(); fgets();

*   #include <string.h>
    +Funções utilizadas:
    strlen();

*   #include <stdbool.h>
    +Defines utilizadas:
    true; false;

*/

/*
    *Função: antecessor();
    *Descrição: Busca retornar um grau de hierarquia relacionado ao parametro passado no escopo, no caso apresentado,
    3(exponenciação) será de um alto grau de importância, dessa forma, todos os numeros que antecedem o 3 (2, 1 e 0), não estarão no
    topo da hierarquia. Quanto mais próximo de 0 menos irrelevante será para a resolução do exercício.
*/
int antecessor(char op)
{
    switch (op)
    {
    case '+':
        return (1);
    case '-':
        return (1); /*soma e subtração possuem grau de relevância 1*/
    case '*':
        return (2);
    case '/':
        return (2); /*multiplicação e divisão possuem grau de relevancia 2*/
    case '$':
        return (3); /*exponenciação possui grau de relevancia 3*/
    default:
        return (0); /*demais operações (parenteses e numeros) possuem grau de relevancia 0, pois não são operadores*/
    }
}

/*
 *Função: AvaliarPosFixo();
 *Descrição: Dada uma notação no modelo pós-fixo, a função a seguir realiza operações utilizando de mecanismos de pilhas.
 */
int AvaliarPosFixo(char *postfix)
{
    /* Declaração da pilha de caracteres*/
    PILHA pilha;

    /* Declaração de uma pilha manual de inteiros*/
    PILHAINT inteiros;

    int num; /*variavel que guarda um digito de número, o qual virá da notação dada como entrada*/

    int op2; /*variável que guarda o segundo operando da aritmética*/
    int op1; /*variável que guarda o primeiro operando da aritmética*/
    /*
    Observação: Ainda que seja apenas dois operandos apresentado, ainda é possível fazer aritmeticas com mais do que dois operandos.
    Esta função apenas divide o problema, por exemplo:

    - Dada a seguinte expressão:
        2 * 3 * 4
    - A função irá resolver da seguinte maneira:
        + Passo 1: 2 * 3 = 6
        + Passo 2: 6 * 4 = 24

    No caso apresentado, é feita a operação dentre dois operandos, o resultado destes dois operandos é utilizado como o primeiro
    parâmetro para realizar a expressão com o terceiro operando. Desta maneira, podendo multiplicar inúmeras sequências.
    */

    int resultado; /*variável que guarda o resultado de cada operação feita. Eminentemente, ela é utilizada como retorno do valor final*/
    int i;         /*variável auxiliar para controle de vetores e strings*/

    iniciarPilha(&pilha); /*função que inicializa a pilha de caracteres*/
    inteiros.topo = 0;    /*inicializando a pilha de inteiros*/

    for (i = 0; postfix[i] != '\0'; i++) /*laço o qual percorre toda a string até o fim dela*/
    {
        if (isdigit(postfix[i])) /* verifica se é um dígito*/
        {
            /* reset da variável num, pois ela guarda apenas um operando por vez,
            sendo ele de -2^(31) a 2^(31) - 1. (levando em consideração uma arquitetura de 32 bits)*/
            num = 0;

            /*loop que busca finalizar apenas após um dígito acabar, sendo interrompido
            por quaisquer parâmetros que não sejam números inteiros*/
            while (postfix[i] != '\0' && isdigit(postfix[i]) != 0)
            {
                num = num * 10 + (postfix[i] - '0'); /*multiplica o valor obtido por 10 a cada ordem detectada e converte de char para int*/
                i++;                                 /*incremento para detecção do próximo operando*/
            }
            i--; /*decremento da variavel de controle para não pular uma unidade*/

            /*atualização da pilha de inteiros (push)*/
            inteiros.conteudo[inteiros.topo] = num;
            inteiros.topo++;

            continue; /*ignore as próximas linhas e continue para o próximo laço de repetição*/
        }
        if (umOperador(postfix[i])) /*Verifica se é um operador aritmético*/
        {
            /*realização de dois pop na pilha de inteiros*/
            inteiros.topo--;
            op2 = inteiros.conteudo[inteiros.topo];
            inteiros.topo--;
            op1 = inteiros.conteudo[inteiros.topo];

            /*realiza a operação solicitada*/
            switch (postfix[i])
            {
            case '+': /*soma*/
                resultado = op1 + op2;
                break;
            case '-': /*subtração*/
                resultado = op1 - op2;
                break;
            case '*': /*multiplicação*/
                resultado = op1 * op2;
                break;
            case '/':         /*divisão*/
                if (op2 == 0) /*se o operador 2 (denominador) for zero, será impressao que não é possivel dividir por zero e o resultado informado será zero*/
                {
                    printf("Impossivel dividir por zero!\n");
                    return 0;
                }
                resultado = op1 / op2;
                break;
            case '$': /*exponenciação*/
                resultado = pow(op1, op2);
                break;
            }
            /*operação de push com o resultado das operações*/
            inteiros.conteudo[inteiros.topo] = resultado;
            inteiros.topo++; /*volta a apontar para o proximo bloco a ser ocupado*/
        }
    }
    return resultado; /* Retorna o resultado de toda a operação*/
}

/*
    *Função: bemFormado();
    *Descrição: Dada uma expressão matemática, é verificado se a sintaxe e a lógica da expressão enviada estão corretas.
    Sendo que:
        + true = bem formada
        + false = mal formada

 */
bool bemFormado(char *expr)
{
    PILHA pilha;

    int i;            /*variavel de controle*/
    int ops = 0;      /*contador de operador*/
    int opnds = 0;    /*contador de operandos*/
    int espacos = 0;  /*contador de espaços*/
    char item;        /*um único item de char*/
    char topo;        /*unico item de char que recebe o conteúdo do topo de um pilha*/
    bool aux = false; /*auxiliador de operandos; false = novo operando, true = operando ja lido*/
    bool operador = false; /*auxiliador de operadores; false = um operador que fez a ultima modificação, true = um operando que fez a ultima modificação (utilizado para verificar um operador entre outro)*/

    /*inicia a pilha*/
    iniciarPilha(&pilha);

    /*laço que percorre a sintaxe lida até seu fim*/
    for (i = 0; expr[i] != '\0'; i++)
    {
        item = expr[i];  /*extrair uma variável da string*/
        if (item == '(') /*se for lido um parênteses, coloque-o na pilha*/
        {
            push(&pilha, item);
        }
        else
        {
            if (item == ')') /* se for um parêntese fechado, verificar na pilha se ele de fato possui lógica sintática*/
            {
                if (PilhaVazia(&pilha))
                {
                    return false; /*retorne falso, pois o parêntese informado, não está correto sintáticamente*/
                }
                topo = pop(&pilha); /*desempilha*/
                if (item == ')' && topo != '(')
                {
                    return false; /*retorna falso pois foi desempilhado qualquer coisa que não seja o parêntese de retorno*/
                }
            }
            else
            {
                if (umOperador(item)) /*se o item informado for um operador*/
                {
                    ops++;       /*incremente o número total de operador*/
                    if (i == 0 || !operador)
                    {
                        /* retorne falso, pois o operador foi detectado em um local sintáticamente incorreto
                        (inicio, entre outros operadores ou no fim da expressão)*/
                        return false;
                    }
                    operador = false;
                    aux = false; /*troque o valor da variável auxiliar para falso, pois o que se espera a seguir é um dígito*/
                }
            }
        }
        if (item == ' ') /*se for detectado um espaco em branco*/
        {
            espacos++;   /*incremente a quantidade total de espacos da sequencia informada*/
            aux = false; /*troque o valor da variável auxiliar para falso, pois o que se espera a seguir é um dígito*/
        }
        if (isdigit(item) && !aux) /*se o item selecionado for um digito de 0 a 9 e antes dele não veio outro digito*/
        {
            /*troque o valor para verdadeiro, pois caso seja um numero com casas
            acimas das unidades, ele não ser contado mais de uma vez*/
            aux = true;
            operador = true;
            opnds++; /*incremente o total de operandos encontrado na sintaxe passada como parãmetro*/
        }
    }
    if (!(opnds - ops == 1))
    {
        /*se a relação entre os operandos não tiver diferença de um parametro, retorne falso, pois existe
        uma quantidade maior de operandos para operadores ou a quantidade de operadores é maior que a de
        operandos*/
        return false;
    }
    if (ops == 0 && espacos > 0)
    {
        /*Retorne falso, pois o que foi passado foi apenas números sem lógica*/
        return false;
    }
    return PilhaVazia(&pilha); /*se a pilha estiver vazia e o loop foi executado com sucesso, será retornado true, no caso, expressão bem formada*/
}

/*
 *Função: InfixaParaPosFixa();
 *Descrição: Busca transformar a notação infixa para pós-fixa.
 Ex:
 Infixa = 1 + 1
 Pós-fixa = 1 1 +
 */
void InfixaParaPosFixa(char *infixa, char *posfixa)
{
    PILHA pilha; /*pilha utilizada na função*/
    int j = 0; /*variavel de controle, a qual ira percorrer o vetor de ntoação pós-fixa*/
    int i;  /*variavel de controle, a qual ira percorrer o vetor de ntoação infixa*/
    char aux; /*variavel auxiliar a qual guardará certos parâmetros ao decorrer da função*/

    iniciarPilha(&pilha);/*inicializa a pilha*/

    for (i = 0; infixa[i] != '\0'; i++) /*laço que percorre toda a notação infixa*/
    {
        if (isdigit(infixa[i])) /*verifica se a intância selecionada é um dígito*/
        {
            while (infixa[i] != '\0' && isdigit(infixa[i])) /*enquanto for um digito, e não chegar ao fim da string passe os digitos para a string de notação pós-fixa*/
            {
                posfixa[j] = infixa[i];
                j++;
                i++;
            }
            posfixa[j] = ' '; /*separa os digitos com um espaço*/
            j++;
            i--;
            continue; /*ignore as outras linhas e continue para a proxima repetição do laço*/
        }
        if (infixa[i] == '(') /*caso seja uma abertura de parêntese, realize um push.*/
        {
            push(&pilha, '(');
            continue;
        }
        if (infixa[i] == ')') /*caso seja fechado um parêntese, realize um pop enquanto o elemento que ficar no topo não ser um abre parêntese*/
        {
            while (!PilhaVazia(&pilha) && olhadinha(&pilha) != '(')
            {
                posfixa[j] = pop(&pilha);
                j++;
            }
        }
        if (umOperador(infixa[i]))/* caso seja um operador*/
        {
            while (antecessor(olhadinha(&pilha)) >= antecessor(infixa[i])) /* enquanto o nivel de hierarquia de operadores da pilha for maior que o operador selecionado, realize um pop*/
            {
                posfixa[j] = pop(&pilha);/*recebe os operadores de nivel superior ou igual ao selecionado*/
                j++;
            }
            aux = infixa[i];/*recebe o operador como parâmetro*/
            push(&pilha, aux);/*faz um push com o operador selecionado para manter a hierarquia de operadores*/
        }
    }/*fim do laço que faz a maior parte de conversão*/
    while (!PilhaVazia(&pilha))/*enquanto a pilha não estiver vazia, desempilhe ignorando os parênteses*/
    {
        if (olhadinha(&pilha) == ')' || olhadinha(&pilha) == '(')
        {
            pop(&pilha);
            continue;
        }

        posfixa[j] = pop(&pilha);
        j++;
    }
    posfixa[j] = '\0'; /*finalize indicando o final da notação pofixa*/
}

/*
 *Função: iniciarPilha();
 *Descrição: Inicia o topo da pilha com sua numeração base (-1).
 */
void iniciarPilha(PILHA *pilha)
{
    pilha->topo = -1;
}

/*
    *Função: olhadinha();
    *Descrição: Retorna o conteúdo do topo da pilha caso a mesma não esteja vazia. Caso contrário, é retornado '\0'
    como caractere nulo.
 */
char olhadinha(PILHA *pilha)
{
    if (!PilhaVazia(pilha))
    {
        return (pilha->conteudo[pilha->topo]);
    }
    return ('\0');
}

/*
    *Função: PilhaVazia();
    *Descrição: Retorna true (se o topo da pilha corresponder ao topo inicial), ou false (se o topo da pilha nao
    corresponder ao topo inicial, indicando pilha cheia).
 */
bool PilhaVazia(PILHA *pilha)
{
    return (pilha->topo == -1);
}

/*
    *Função: pop();
    *Descrição: Função que faz a operação padrão de desempilhar, decrementando a altura da pilha e retornando o
    conteúdo que estava sendo armazenado no topo.
 */
char pop(PILHA *pilha)
{
    if (!PilhaVazia(pilha))
    {
        return pilha->conteudo[pilha->topo--];
    }
    return ('\0'); /* null character for empty pilha*/
}

/*
 *Função: push();
 *Descrição: Função que faz a operação padrão de empilhar, incrementando a altura da pilha e seus conteúdos.
 */
void push(PILHA *pilha, char ch)
{
    pilha->topo++;
    if (pilha->topo < TAMMAX - 1)
    {
        pilha->conteudo[pilha->topo] = ch;
    }
}

/*
 *Função: umOperador();
 *Descrição: Retorna true (caso seja um operador) ou false (caso não seja um operador).
 */
bool umOperador(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '$');
}
