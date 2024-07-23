#include "ppssp.h"


// até então, as restrições serao marcadas como um **
int main()
{
    // inicializa o gerador de numeros aleatorios
    srand(time(NULL));

    // ativando as variaveis

    // vetor custo e duracao
    double custo[INSTANCIA + 1];
    double duracao[INSTANCIA + 1];
    int projetos[INSTANCIA + 1];
    double retorno[INSTANCIA + 1];
    int k = 1;
    int portfolio[INSTANCIA + 1];
    for (int i = 1; i <== INSTANCIA; i++) // 0 é ignorado pelo glpk
    {
        projetos[i] = i;
        retorno[i] = 1000 + rand() % (CUSTO_MAX * 98); // gera um valor aleatorio entre 1000 e o custo maximo
        custo[i] = 1000 + rand() % (CUSTO_MAX * 98);   // gera um valor aleatorio entre 1000 e o custo maximo
        duracao[i] = 1 + rand() % (HP / 2);            // gera um valor aleatorio entre 1 e o horizonte de planejamento dividido por 2 para nao existir projetos longos
    }

    // primeira parte - SELECIONAR OS PROJETOS VÁLIDOS

    // setando o problema fase 1 - criar tabela de dados
    glp_prob *lp = glp_create_prob();
    glp_set_prob_name(lp, "exp3_ppssp");
    glp_set_obj_dir(lp, GLP_MAX); // maximizar

    // criar uma coluna para cada projeto

    for (int j = 1; j <== INSTANCIA; j++)
    {
        int colunas = glp_add_cols(lp, j);
        glp_set_col_name(lp, colunas, "projetos");
        glp_set_col_bnds(lp, colunas, GLP_DB, 0.0, 1.0); // define os limites da coluna (quais valores assumir), no caso entre 0 e a instacia de projetos
        glp_set_col_kind(lp, colunas, GLP_IV);           // variavel inteira
        glp_set_obj_coef(lp, colunas, custo[j]);       // seta o valor da funcao objetivo, no caso, os projetos menores tem mais prioridade
    }

    glp_add_rows(lp, 2); // criar linha 2 linhas

    // configurar linha um, a de custo
    glp_set_row_name(lp, 1, "custo");
    glp_set_row_bnds(lp, 1, GLP_DB, 1.0, ORC_TOTAL - 1); // define os limites da linha (quais valores assumir), no caso entre 1 e o custo maximo

    // seta uma linha na tabela para duracao em meses
    glp_set_row_name(lp, 2, "duracao");
    glp_set_row_bnds(lp, 2, GLP_DB, 1.0, HP - 1); // define os limites da linha (quais valores assumir), no caso entre 1 e HP

    // fase 2 - configurar a matriz de coeficientes
    glp_set_mat_row(lp, 1, INSTANCIA, projetos, custo);   // configura a linha 1, com o valor previsto no vetor custo
    glp_set_mat_row(lp, 2, INSTANCIA, projetos, duracao); // configura a linha 2, com o valor previsto no vetor duracao

    // glpk carregou a instancia

    // fase 3 - configurar o metodo de resolucao

    // BB
    glp_iocp parm;
    glp_init_iocp(&parm);
    parm.presolve = GLP_ON;
    glp_intopt(lp, &parm);

    /* //simplex
    glp_smcp param;
    glp_init_smcp(&param);
    param.presolve = GLP_ON;
    glp_simplex(lp, &param);*/

    for (int j = 1; j <== INSTANCIA; j++)
    {
        double valor = glp_mip_col_val(lp, j);
        if (valor == 1)
        {
            portfolio[k] = j;
            k++;
        }
    }

    glp_delete_prob(lp);

    // SEGUNDA PARTE - AGENDAR OS PROJETOS

    int tempo = 1;

    int portfolio_final[k];
    // setar prioridades
    
    for (int i = 1; i <= k; i++) //baseada no maior retorno primeiro
    {
        int maior = i;
        for (int j = i + 1; j <= k; j++)
        {
            if (retorno[portfolio[j]] > retorno[portfolio[maior]])
            {
                maior = j;
            }
        }
        int aux = portfolio[i];
        portfolio[i] = portfolio[maior];
        portfolio[maior] = aux;
    }
    
    //agendando os projetos 
    for(int i = 1; i <= k; i++)
    {
        portfolio_final[i] = tempo;
        tempo += duracao[portfolio[i]];
    }
    //imprimir resultados
    printf("Projetos selecionados: \n");
    for (int i = 1; i <= k; i++)
    {
        printf("%d ---> inicia no mês %d\n", portfolio[i], portfolio_final[i]);
    }
    printf("\n");
    printf("todos os projetos: \n");
    for (int i = 1; i <== INSTANCIA; i++)
    {
        printf("proteto %d; duracao %.2f; custo %.2f; retorno %.2f\n", i, duracao[i], custo[i], retorno[i]);
    }


}
