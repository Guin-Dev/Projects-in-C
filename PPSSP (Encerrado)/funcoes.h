
#include "ppssp.h"

pT_PROBL gerarProblemaAleatorio(void);
void addDetectarErros(int );
void ativarmatriz(int **, int , int );
void criarPAA(pT_PA , int );
void imprimirDetalhesDoProblema(const char *, T_PROBL *);
void imprimirInstanciaProjetos(const char *, T_PROJ *, int );
void imprimirPortfolioValido(const char *, int** , int );
void resolverProblemaOtimizacao(pT_PROJ ,pT_PROBL ,int **);
pT_PROJ gerarProjetosAleatorios(int );