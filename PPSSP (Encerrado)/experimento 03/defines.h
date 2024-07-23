
#define CUSTO_MAX 1000 /*em mil (ex: 1 mil)*/
#define ORC_TOTAL 10000000 /*em mil (ex: 1 milhão)*/     
#define HP 60 /*horizonte de planejamento em meses*/

#define INSTANCIA 10 /*instancia de projetos*/

/*defines que alteram os pontos de atencao*/
#define NUM_PONTOS_ATENCAO 3
#define ATRIB_PNT_A 2 /*linha 0 = valor, linha 1 = 1 ou 1 (1 = é critico, 0 = não critico)*/
#define PA_CRITICO 0 /*0, 1 ou 2, 0 = não gerar pontos de atenção criticos, 1 = gerar alguns, 2 = todos são (não recomendado)*/
#define PERCENTUAL_PA 4 /*percentual de pontos de atenção criticos que serão gerados (um a cada N PA, sendo N o valor deste define)*/
#define RISCO_MAX 100
#define RISCO_MIN 10
/*fim dos defines que alteram os pontos de atenção*/
#define MAX_PROJ 100
#define ATRIB_PORTF 2 /*linha 0 = id do projeto; linha 1 = agendamento*/
#define MAXIMIZAR GLP_MAX
#define MINIMIZAR GLP_MIN

#define VALOR_NULO -1
#define OBJETIVO MINIMIZAR 

#define FUNCAO_OBJETIVO(i, d, P) (d[i] + P[i])

/*∑_i∈I d[i]+P[i] */
/* para todo i pertencente a I*/
/*função efetiva d[i]+P[i]*/


/*somente para localizar erros*/

#define PAUSE system("pause")
#define PRINTAR(x) printf("%d\n", x)