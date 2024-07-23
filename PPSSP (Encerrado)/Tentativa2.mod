
 # Modelo de Programação Linear Inteira para o Problema de Seleção de Projetos  
 # com Prazos e Orçamento Anual  


 # Declaração dos conjuntos  
set I;  # Conjunto de projetos  
set W;  # Conjunto de pontos de atenção  
set MESES;  # Conjunto de anos no horizonte de planejamento  
set DURMAX;  # Conjunto de durações máximas de projetos
 # Parâmetros  
param R_w{w in W};  # Risco associado ao ponto de atenção w  
param G_w{p in I,w in W} binary;  # Projetos que resolvem o ponto de atenção w (matriz binária)  
param d_p{p in I};  # Duração em meses de um projeto p  
param custo_p{p in I, d in DURMAX};  # Custo de cada projeto p  
param C_mes{m in MESES};  # Orçamento anual  
param deadline_w{w in W};  # Prazo limite para resolver um ponto de atenção w  
param intoleravel_w{w in W} binary;  # Indica se o ponto de atenção w é intolerável  
param HP:= 24;  # Horizonte de Planejamento  

 # Variáveis de Decisão  
var x_p{p in I} binary;  # 1 se o projeto p é selecionado, 0 caso contrário  
var m_p{p in I} >= 0, <= HP integer;  # Mês de início do projeto p  
var c_p{p in I} >= 0;  # Custo do projeto p  



 # Função Objetivo  
minimize Z: sum{p in I} (c_p[p]);  # Minimizar o custo


 # Restrições  

 # Prazo Limite de Resolução de um Ponto de Atenção intolerável 
s.t. DeadlineResolution{ p in I, w in W}: m_p[p] + d_p[p] <= deadline_w[w]; # para cada p em i e w rm i, dado que g,w seja 1 seja um ponto intoleravel 

 # Agendamento Consistente  
s.t. ConsistentScheculing{p in I}: m_p[p] <= HP * x_p[p]; # para cada p em i, se x_p[p] = 1, m_p[p] + d_p[p] = 1, senão, m_p[p] + d_p[p] = 0 

 # Restrição de Recursos  
s.t. ResourceConstraint{m in MESES, d in DURMAX}:  sum{p in I}(custo_p[p,d] * x_p[p]) <= C_mes[m]; # somatorio dos meses menor que o custo anual 

 # Restrição para ajustar o custo com base na seleção 
s.t. AdjustCost{p in I}: c_p[p] = (sum{d in DURMAX} custo_p[p,d]) + 1000 * (1 - x_p[p]);

 # Restrição para garantir que pelo menos um projeto seja selecionado
s.t. AdjustVariable: (sum{p in I} x_p[p]) >= 1;

 # Restrição para ajustar o risco com base na seleção
s.t. AdjustRisk{w in W}: (sum{p in I} G_w[p,w] * x_p[p]) <= R_w[w];

# Restrição para garantir que pelo menos um projeto resolva um ponto de atenção
s.t. AdjustRisk2{w in W}: sum{p in I} G_w[p,w] >= 1;

# Restrição para ajustar o agendamento
s.t. AdjustScheduling{p in I}: m_p[p] >= x_p[p];

# Restrição para ajustar os custos
s.t. AdjustCusts: (sum{m in MESES} C_mes[m]) - (sum{p in I, d in DURMAX}custo_p[p,d]*x_p[p]) <= (sum{m in MESES} C_mes[m])/2; #custo total durante o HP

# s.t. Test{p in I}:  x = min(m_p[p],max(m_p[p] + d_p[p] - 1,0));

 # Resolução do problema  
solve;

 # Exibição dos resultados  
printf "Projetos selecionados e seus meses de inicio:\n";
for {p in I: x_p[p] = 1} {
    printf "Projeto %s, Mes de Inicio: %d\n", p, m_p[p];
}

end;

 #

 