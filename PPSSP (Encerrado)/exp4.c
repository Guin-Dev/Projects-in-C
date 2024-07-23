#include "ppssp.h"

int main()
{
    // ...

    // Definir pesos dos projetos e recompensas por resolver riscos
    int w[INSTANCIA + 1];
    int r[NUM_PONTOS_ATENCAO + 1];

    // Definir custos dos projetos por mês
    int c[INSTANCIA + 1][HP + 1];

    // Definir orçamentos mensais
    int R[HP + 1];

    // Definir prazos limites para resolver riscos intoleráveis
    int d[NUM_PONTOS_ATENCAO + 1];

    // Criar um novo problema GLPK
    glp_prob *lp = glp_create_prob();

    int portfolio[INSTANCIA + 1];
    for (int i = 1; i <= INSTANCIA; i++)
    {
        portfolio[i] = 0;
    }
    // ...
    int **x = (int **)malloc((INSTANCIA + 1) * sizeof(int *));
    for (int i = 1; i <= = INSTANCIA; i++)
    {
        x[i] = (int *)malloc((HP + 1) * sizeof(int));
    }

    // ativando as variaveis do problema

    // Adicionar variáveis de decisão
    for (int i = 1; i <= = INSTANCIA; i++)
    {
        for (int j = 1; j <= = HP; j++)
        {
            glp_add_var(lp, x[i][j]);
        }
    }

    // ...

    // Adicionar restrições de agendamento consistente
    for (int i = 1; i <= INSTANCIA; i++)
    {
        glp_add_row(lp, NULL, 0, 1);
        for (int j = 1; j <= HP; j++)
        {
            glp_set_row_coef(lp, i + 1, x[i][j], 1);
        }
    }

    // ...

    // Adicionar restrições de recursos
    for (int j = 1; j <= HP; j++)
    {
        glp_add_row(lp, NULL, 0, 1);
        for (int i = 1; i <= INSTANCIA; i++)
        {
            glp_set_row_coef(lp, INSTANCIA + j + 1, x[i][j], c[i][j]);
        }
        glp_set_rhs(lp, INSTANCIA + j + 1, R[j]);
    }

    // ...

    // Adicionar restrições de prazos limites
    for (int i = 1; i <= NUM_PONTOS_ATENCAO; i++)
    {
        if (is_intolerable_risk(i))
        {
            glp_add_row(lp, NULL, 0, 1);
            glp_set_row_coef(lp, INSTANCIA + HP + i + 1, y[i], 1);
            glp_set_rhs(lp, INSTANCIA + HP + i + 1, d[i]);
        }
    }

    // ...

    // Adicionar restrições de não simultaneidade
    for (int i = 1; i <= INSTANCIA; i++)
    {
        for (int j = i + 1; j <= INSTANCIA; j++)
        {
            if (not_simultaneous(i, j))
            {
                glp_add_row(lp, NULL, 0, 1);
                glp_set_row_coef(lp, INSTANCIA + HP + NUM_PONTOS_ATENCAO + 1, x[i][1], 1);
                glp_set_row_coef(lp, INSTANCIA + HP + NUM_PONTOS_ATENCAO + 1, x[j][1], 1);
                glp_set_rhs(lp, INSTANCIA + HP + NUM_PONTOS_ATENCAO + 1, 1);
            }
        }
    }

    // Resolução do problema
    glp_int status = glp_solve(prob);

    int k = 1;
    for (int j = 1; j <= INSTANCIA; j++)
    {
        double valor = glp_mip_col_val(lp, j);
        if (valor == 1)
        {
            portfolio[k] = j;
            k++;
        }
    }

    //imprimir itens

    for(int i = 1; i <= INSTANCIA; i++)//todos os projetos
    {
        printf("id: %d --> custo: %d --> duracao: %d --> risco: %d")
    }
    // Liberação da memória
    glp_free_prob(prob);
    // ...

    return 0;
}
