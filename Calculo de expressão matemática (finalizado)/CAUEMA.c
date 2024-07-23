/*
 * Programa: CALCULO DE UMA EXPRESSAO MATEMATICA (CaUEMa).
 * Descrição: Programa o qual busca calcular uma expressão matemática dada pelo usuário.
 *
 * Programador: Nícolas Herculano Pires
 * RGM: 47164
 * conteudo da última modificação: 25/09/2023
 *
 * Código para compilar: gcc -o CAUEMA.exe CAUEMA.c funcoes.c -pedantic -Wall -Werror -Wextra
 *
 */

#include "funcoes.h" /* Biblioteca principal, a qual contém as funções criadas e as utilizadas para a criação e resolução deste programa*/
/* Funções utilizadas: bemFormado(); InfixaParaPosFixa(); AvaliarPosFixo(); */
/* Constantes utilizadas: TAMMAX*/

/* Bibliotecas atreladas à "funcoes.h", as quais teve impacto no arquivo "CAUEMA.c"
*
*   #include <stdio.h>
    +Funções utilizadas:
    fgets(); printf();

*   #include <string.h>
    +Funções utilizadas:
    strcpy(), strlen();

*/

int main(int argc, char **argv)
{

    char expr[TAMMAX];    /* String que guardará a expressão*/
    char postfix[TAMMAX]; /* String que guardará a expressão pós fixa*/

    /* Artifício para silenciar warning */
    argc = argc;
    argv = argv;

    /* Entrada da expressão*/
    printf("Digite a expressao: ");   /* Solicitar a entrada para o usuário*/
    fgets(expr, sizeof(expr), stdin); /* Ler a entrada dada pelo usuário*/
    expr[strlen(expr) - 1] = '\0';    /* Remover nova linha (Enter)*/

    /* Validação da expressão informada*/
    if (!bemFormado(expr)) /* "Se a expressão enviada não for bem formada (conter algum erro do usuário)"*/
    {
        printf("Expressao malformada!\n"); /* Caso tenha alguma falha na expressão de entrada dada pelo usuário*/
        return (1);                        /* Programa finalizado com erros*/
    }
    /* Calculo da expressão e apresentação da mesma*/
    InfixaParaPosFixa(expr, postfix);                   /* Conversor de notação infixa para pós fixa*/
    printf("Resultado: %d\n", AvaliarPosFixo(postfix)); /* Mostrar o resultado*/

    return (0); /* Programa finalizado com sucesso*/
}
