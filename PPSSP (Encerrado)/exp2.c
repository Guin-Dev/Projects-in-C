/*somente para instancias aleatorias*/
#include "ppssp.h"

int main()
{
    int tamanho = INSTANCIA; /*Defina o tamanho da instância de projetos*/
    T_PROJ *projetos = (T_PROJ *)malloc((tamanho+1) * sizeof(T_PROJ));
    pT_PROBL problema;
    int **portfolio;

    if (projetos == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória.\n");
        return 1;
    }

    /*Inicialize o gerador de números aleatórios*/
    srand(time(NULL));

    /*inicializar matriz de portfólio válido*/
    ativarmatriz(portfolio, tamanho, ATRIB_PORTF);

    /*gerou instancia do problema*/
    problema = gerarProblemaAleatorio();
    /*gerou intancia de projetos*/
    projetos = gerarProjetosAleatorios(tamanho);

    /*gerar arquivo com os detalhes do problema*/
    imprimirDetalhesDoProblema("Dados do Problema", problema);
    imprimirInstanciaProjetos("Instancia de Projetos", projetos, tamanho);

    /*realizar otimização*/
    resolverProblemaOtimizacao(projetos, problema, portfolio);

    /*imprimir resultados*/
    imprimirPortfolioValido("Portfolio Valido", portfolio, tamanho);
    /*Liberar a memória alocada*/ 
    free(projetos);

    return 0;
}

