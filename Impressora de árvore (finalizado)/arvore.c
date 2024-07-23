/*
    Programa: Árvore.
    Descrição: Programa que recebe uma árvore no formato .txt e a imprime na tela.
    Programador: Nícolas Herculano Pires
    RGM: 47164
    Data da última modificação: 20/11/2023
    Como compilar: gcc -o arvore.exe arvore.c funcoes.c conio_v3.2.4.c console_v1.5.4.c -Werror -Wextra -Wall -pedantic
    Como executar: arvore.exe < entrada.txt
*/

#include "funcoes.h"
/*
Funções utilizadas na int main(): 
    ativaVetorPontArea(); buscaNo(); calcularAlturaArvore(); calcularQtdDigitos(); contadigito(); DespersonalizarConsoleFULL(); 
    encontrarNivelMaisAlto(); freetudo(); insereFilho(); MSTdeCOORDENADAS(); PersonalizarConsoleFULL(); PrintaNos(); PrintaVertice();
    trenaPorAltura(); 
Defines utilizadas:
    CRIAR_NO; ESPACOMIN; M; NIVEL_INICIAL; PRIMEIRO_NIVEL; UMDIGITO;
Structs utilizadas:
    DADOS; TAREA; TIPONO;
*/
#include <stdio.h>
/*
Funções utilizadas na int main(): 
    scanf(); 
*/
#include <stdlib.h>
/*
Funções utilizadas na int main(): 
    free(); 
Defines utilizadas: NULL;
*/
int main(int argc, char **argv)
{
    int x, antx; /*variaveis auxiliares*/

    /*ativando o primeiro no*/
    TIPONO *pno = (TIPONO *)CRIAR_NO;
    TIPONO *raiz;

    /*ativando prompt*/
    TAREA **prompt;

    /*ativando a memoria do console*/
    DADOS console = PersonalizarConsoleFULL("arvore");

    /*silenciador de warings*/
    argc = argc;
    argv = argv;

    /*ativando prompt*/
    ativaVetorPontArea(&prompt, M);
    prompt[NIVEL_INICIAL]->no = pno;

    /*ativando nos*/
    raiz = pno;
    pno->qtd_filhos = 0;
    raiz->pai = NULL;

    /*iniciando o programa*/
    scanf("%d", &antx);
    do
    {
        scanf("%d", &x);            /*le o valor*/
        if (antx == PRIMEIRO_NIVEL) /* se o antecessor era 0, então execute a raiz*/
        {
            scanf("%d", &x);
            antx = UMDIGITO; /*desativando flag de inicio*/
            raiz->conteudo = x;
            raiz->etiqueta.caixinha.qtd_digit = contadigito(x) + ESPACOMIN;
            scanf("%d", &x);       /*le a qtd de filhos pertencentes a raiz*/
            insereFilho(&raiz, x); /*insere na raiz*/
        }
        else
        {
            if (x != -1)
            {
                pno = (TIPONO *)buscaNo(raiz, x); /*busca endereço do valor informado*/
                scanf("%d", &x);                  /*le a qtd de filhos pertencentes ao no*/
                insereFilho(&pno, x);             /*insere na arvore*/
            }
        }
    } while (x != -1); /*sair do loop*/

    /*calculando altura da arvore*/
    calcularAlturaArvore(raiz);
    raiz->nivel_max = encontrarNivelMaisAlto(raiz);
    MSTdeCOORDENADAS(raiz, raiz, prompt);
    calcularQtdDigitos(raiz);

    /*mapeando os nos e printando os mesmos*/
    PrintaNos(prompt, TrenaPorAltura(prompt));
    PrintaVertice(prompt);

    /*desativando o console e liberando memoria*/
    DespersonalizarConsoleFULL(console);
    freetudo(prompt);
    free(pno);
    /*programa executado com sucesso*/
    return (0);
}

