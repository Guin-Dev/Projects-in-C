/*
Título:
  Testador de Limites
  Versão: 1.0

Descrição:
  Programa que faz a média de multiplas requisições estáticas por segundo em um site.
  A utilidade deste programa é demonstrar uma fração do poder que a bibliotexa "curl.h" tem.

Linha de compilação:
  gcc TestadorDeLimites.c -o TestadorDeLimites.exe -L "C:\Executaveis\curl\lib" -lcurl

Observação:
  No arquivo "LEIAME.txt" tem um breve tutorial de instalação da libcurl para a execução deste programa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <C:\Executaveis\curl\include\curl\curl.h>
#include <time.h>

#define MAX_REQUESTS 1000

/* Função para realizar uma request HTTP*/
int faz_request(CURL *curl, char *url)
{
  CURLcode res; /* Variável que receberá um código de retorno no contexto de realizar a request*/

  /* Configurar as opções da sessão Curl, como URL alvo, método HTTP, parâmetros da request, entre outros.*/
  curl_easy_setopt(curl, CURLOPT_URL, url);

  /* Executar a request de acordo com as opções configuradas anteriormente.*/
  res = curl_easy_perform(curl);

  /* Caso de algum erro, encerrar.*/
  if (res != CURLE_OK)
  {
    fprintf(stderr, "Erro ao realizar requisição: %s\n", curl_easy_strerror(res));
    return 1;
  }

  return 0;
}

int main()
{
  char url[256];              /* Variável para guardar a URL*/
  int i, requests_feitas = 0; /* Variáveis auxiliares*/
  time_t tempo_total;         /* Variável para guardar o tempo*/
  double media_rps;           /* Variável para guardar o numero de requests por segundo*/

  /* Inicializa a biblioteca cURL*/
  curl_global_init(CURL_GLOBAL_ALL);

  /* Cria um handle cURL*/
  CURL *curl = curl_easy_init();

  /* Pede a URL do usuário*/
  printf("Digite a URL para testar (www.exemplo.com/):\n> ");
  fgets(url, sizeof(url), stdin);

  /* Remove o caractere de nova linha do final*/
  url[strcspn(url, "\n")] = '\0';

  /* Inicia o cronômetro*/
  tempo_total = time(NULL);

  /* Faz as requests*/
  for (i = 0; i < MAX_REQUESTS; i++)
  {

    /* Se retornar um erro, encerrar*/
    if (faz_request(curl, url))
    {
      break;
    }

    requests_feitas++;
  }

  /* Parar o cronômetro*/
  tempo_total = time(NULL) - tempo_total;

  /* Calcula a média de requests por segundo*/
  media_rps = (double)requests_feitas / (double)tempo_total;

  /* Mostra os resultados*/
  printf("\nTotal de requisições: %d\n", requests_feitas);
  printf("Tempo total: %ld segundos\n", tempo_total);
  printf("Média de requisições por segundo: %.2f\n", media_rps);

  /* Limpa o handle cURL e finaliza a biblioteca*/
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  /* Programa executado com sucesso*/
  return 0;
}
