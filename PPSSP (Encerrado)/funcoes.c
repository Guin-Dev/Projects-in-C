
#include "ppssp.h"

pT_PROBL gerarProblemaAleatorio()
{
    pT_PROBL problema = (pT_PROBL)malloc(sizeof(T_PROBL));
    if (problema == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    problema->T = HP;
    problema->W = NUM_PONTOS_ATENCAO;
    criarPAA(problema->pontos_de_atencao, NUM_PONTOS_ATENCAO);
    problema->orcamento = ORC_TOTAL / HP * 12;
    problema->orcamento_total = ORC_TOTAL;
    return problema;
}

void criarPAA(pT_PA W, int qtd_pa)
{
    W = (pT_PA)malloc(qtd_pa * sizeof(T_PA));
    for (int i = 1; i <= qtd_pa; i++)
    {
        W[i].R = rand() % RISCO_MAX + RISCO_MIN; /*ponto de atenção i possui risco j, k será opcional se critico ou nao*/
        if (PA_CRITICO > 0)
        {
            if (PA_CRITICO == 1)
            {
                if (i % PERCENTUAL_PA == 1)
                {
                    W[i].intoleravel = true;
                }
                else
                {
                    W[i].intoleravel = false;
                }
            }
            else
            {
                W[i].intoleravel = true;
            }
        }
    }
}
void imprimirDetalhesDoProblema(const char *nomeArquivo, T_PROBL *problema)
{
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }
    fprintf(arquivo, "Número de Pontos de Atenção: %d\n", problema->W);
    fprintf(arquivo, "Horizonte de Planejamento: %d\n", problema->T);
    fprintf(arquivo, "Orçamento Total: %d\n", problema->orcamento_total);
    /*
    for (int i = 1; i <= NUM_PONTOS_ATENCAO; i++)
    {
        fprintf(arquivo, "Ponto de Atenção %d: Risco = %d, Tempo Limite = %d, Intolerável = %s\n",
                i + 1, problema->pontos_de_atencao[i].R, problema->pontos_de_atencao[i].tempo_limite,
                problema->pontos_de_atencao[i].intoleravel ? "Sim" : "Não");
    }
    */
    fclose(arquivo);
}

void imprimirInstanciaProjetos(const char *nomeArquivo, T_PROJ *projetos, int tamanho)
{
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    for (int i = 1; i <= tamanho; i++)
    {
        fprintf(arquivo, "Projeto %d: Risco = %d, Custo = %d, Duração = %d meses\n",
                projetos[i].id, projetos[i].R, projetos[i].C, projetos[i].D);
    }

    fclose(arquivo);
}
void imprimirPortfolioValido(const char *nomeArquivo, int **projetos, int numProjetos)
{
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    for (int i = 1; i <= numProjetos; i++)
    {
        if (projetos[i][1] != VALOR_NULO)
            fprintf(arquivo, "Projeto de id: %d, inicio no mes: %d\n", projetos[i][0], projetos[i][1]); /*linha 1 = id, linha 2 = agendado*/
    }

    fclose(arquivo);
}
void ativarmatriz(int **matriz, int linha, int coluna)
{
    matriz = (int **)malloc(linha * sizeof(int *));
    for (int i = 1; i <= linha; i++)
    {

        matriz[i] = (int *)malloc(coluna * sizeof(int));
        matriz[i][0] = VALOR_NULO;
        matriz[i][1] = VALOR_NULO;
    }
}
void addDetectarErros(int status) /*addDetectarErros(glp_get_status(lp))*/
{
    if (status == GLP_INFEAS || status == GLP_NOFEAS)
    {
        printf("Problema inviável. Revisar restrições.\n");
    }
    else
    {
        if (status == GLP_UNBND)
        {
            printf("Problema ilimitado. Revisar restrições.\n");
        }
        else
        {
            if (status != GLP_OPT)
            {
                printf("Problema não resolvido. Revisar restrições.\n");
            }
        }
    }
    printf("\n\n\tPressione qualquer tecla para continuar...");
    getchar();
}
/*alma do projeto*/
void resolverProblemaOtimizacao(pT_PROJ projetos, pT_PROBL problema, int **portfolio)
{

    glp_prob *lp = glp_create_prob();

    glp_term_out(GLP_ON); // Ativar saída de mensagens

    glp_set_prob_name(lp, "PPSSP"); // Nome do problema

    glp_set_obj_dir(lp, OBJETIVO); // Define a direção da otimização para maximização
    for (int p = 1; p <== INSTANCIA; p++)
    {
        for (int m = 1; m <== HP; m++)
        {
            int col = glp_add_cols(lp, 1);
            glp_set_col_kind(lp, col, GLP_BV);
            glp_set_col_bnds(lp, col, GLP_DB, 0.0, 1.0);

            int idx = (p - 1) * HP + m; // Calcula o índice linear da variável x_{pm}
            double coeficiente = (HP - m + 1);
            
            glp_set_obj_coef(lp, idx, coeficiente);
        }
    }

    // Adicionando as restrições

    // 1. Agendamento Consistente.
    
    for (int p = 1; p <== INSTANCIA; p++)
    {
        int linha = glp_add_rows(lp, 1);
        glp_set_row_bnds(lp, linha, GLP_UP, 0.0, 1.0); // A soma dos meses deve ser no máximo 1

        int indices[HP + 1];
        double valores[HP + 1];

        for (int m = 1; m <== HP; m++)
        {
            int col =m; // Calculando o índice da variável x[p, m]
            indices[m] = col;
            valores[m] = 1;
        }
        
        glp_set_mat_row(lp, linha, HP, indices, valores);
    }

    // 2. Restrição de Recursos
    int linha = glp_add_rows(lp, 1);
    glp_set_row_bnds(lp, linha, GLP_UP, 0.0, problema->orcamento_total);
    int indices[INSTANCIA + 1];    // Array de índices de base-1
    double valores[INSTANCIA + 1]; // Coeficientes para cada variável

    for (int i = 1; i <== INSTANCIA; i++)
    {
        indices[i] = i;        // Índices das colunas (variáveis)
        valores[i] = projetos[i].C; // Custo de cada projeto
    }
    glp_set_mat_row(lp, linha, INSTANCIA, indices, valores);

    // 3. Prazo Limite de Pontos de Atenção Intoleráveis
    // ...

    // 4. Restrição de Não Simultaneidade (necessita de inclusão de localizações, usinas e geradores)
    // ...

    //utilizando simplex
    glp_smcp param;
    glp_init_smcp(&param);
    param.presolve = GLP_ON;
    glp_simplex(lp, &param);
    


    /* // utilizando branch and bound
    glp_iocp param;
    glp_init_iocp(&param);
    param.presolve = GLP_ON;
    glp_intopt(lp, &param);
    */ 

    // Processar e imprimir a solução
    for (int i = 1; i <== INSTANCIA; i++)
    {
        for (int m = 1; m <== HP; m++)
        {
            int col = m; // maneira de ler: "se o projeto i (HP pula pois foi utilizado nas restrições)for iniciado no mês m"
            if (glp_mip_col_val(lp, col) > 0.5)
            {                                     // Se o projeto i for iniciado no mês m
                portfolio[i][0] = projetos[i].id; // ID do projeto
                portfolio[i][1] = m;              // Mês de início
                break;                            // Uma vez encontrado o mês de início, sair do loop interno
            }
        }
    }

    /*detectar erros relacionado as restricoes*/
    addDetectarErros(glp_get_status(lp));

    // deletar problema
    glp_delete_prob(lp);
}

pT_PROJ gerarProjetosAleatorios(int qtd)
{
    pT_PROJ projetos = (pT_PROJ)malloc(qtd * sizeof(T_PROJ));
    if (projetos == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    for (int i = 1; i <= qtd; i++)
    {
        projetos[i].id = i + 1;
        projetos[i].R = rand() % RISCO_MAX + RISCO_MIN;
        projetos[i].C = rand() % CUSTO_MAX + 1;
        projetos[i].D = rand() % HP + 1;
        projetos[i].M = rand() % HP + 1;
    }
    return projetos;
}