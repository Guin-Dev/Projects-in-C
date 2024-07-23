/*tentativa N-01 de modelar o PPSSP inteiramente em mathprog*/
/* Modelo de Programação Linear Inteira para o Problema de Seleção de Projetos */
/* com Prazos e Orçamento Anual */


/* Declaração dos conjuntos */
set I; /* Conjunto de projetos */
set W; /* Conjunto de pontos de atenção */
set ANOS; /* Conjunto de anos no horizonte de planejamento */

/* Parâmetros */
param R_w{w in W}; /* Risco associado ao ponto de atenção w */
param G_w{p in I,w in W} binary; /* Projetos que resolvem o ponto de atenção w (matriz binária) */
param d_p{p in I}; /* Duração em meses de um projeto p */
param custo_p{p in I}; /* Custo de cada projeto p */
param C_ano{a in ANOS}; /* Orçamento anual */
param T; /* Horizonte de planejamento em meses */
param deadline_w{w in W}; /* Prazo limite para resolver um ponto de atenção w */
param intoleravel_w{w in W} binary; /* Indica se o ponto de atenção w é intolerável */

/* Variáveis de Decisão */
//var x_p{p in I} binary; /* 1 se o projeto p é selecionado, 0 caso contrário */
var m_p{p in I} >= 1, <= T integer; /* Mês de início do projeto p */

/* Função Objetivo */
maximize Z: sum{p in I} m_p[p];


/* Restrições */

/* Agendamento Consistente */
s.t. ConsistentScheduling{p in I}:;
/* Restrição de Recursos */

s.t. ResourceConstraint{a in ANOS}:;
/* Prazo Limite de Resolução de um Ponto de Atenção */
s.t. DeadlineResolution{ p in I, w in W:}:;


/* Resolução do problema */
solve;

/* Exibição dos resultados */
printf "Projetos selecionados e seus meses de início:\n";
for {p in I: x_p[p] = 1} {
    printf "Projeto %s, Mês de Início: %d\n", p, m_p[p];
}

end;
