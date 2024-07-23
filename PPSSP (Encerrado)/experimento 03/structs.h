
#include "ppssp.h"

typedef struct Projeto {
    int id;       // Identificador do projeto
    int R;        // Risco associado ao projeto
    int C;        // Custo associado ao projeto
    int D;        // Duração do projeto
    int M;        // Mês de início do projeto (variável de decisão)
} T_PROJ, *pT_PROJ;

typedef struct Ponto_de_Atencao {
    int R;            // Risco associado ao ponto de atenção
    int tempo_limite; // Tempo limite para resolução do ponto de atenção
    bool intoleravel; // Indica se é um ponto de atenção intolerável
} T_PA, *pT_PA;

typedef struct Problema {
    int T;                   // Horizonte de planejamento em meses
    int W;                   // Quantidade total de pontos de atenção
    pT_PA pontos_de_atencao; // Vetor com os pontos de atenção
    int orcamento;           // Orçamento disponível anualmente
    int orcamento_total;     // Orçamento total disponível
} T_PROBL, *pT_PROBL;
