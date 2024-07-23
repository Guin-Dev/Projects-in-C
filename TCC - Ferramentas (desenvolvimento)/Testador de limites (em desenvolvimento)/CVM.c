/*
Testar limites na CVM em específico na Composição da carteira
Site:https://cvmweb.cvm.gov.br/SWB/Sistemas/SCW/CPublica/CDA/CPublicaCDA.aspx?PK_PARTIC=

Range do PK_PARTIC:
1 - 247465 (as primeiras estão estagnadas por se tratar de registro antigo)
*/

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <time.h>
#include <string.h>

#define URL "https://cvmweb.cvm.gov.br/SWB/Sistemas/SCW/CPublica/CDA/CPublicaCDA.aspx?PK_PARTIC=%d"
#define MAX_REQUESTS 247465

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
void extract_line(const char *html, const char *start_tag, char *output) {
    const char *start = strstr(html, start_tag);
    if (start) {
        const char *end = strchr(start, '\n');
        if (end) {
            size_t length = end - start;
            strncpy(output, start, length);
            output[length] = '\0';
        }
    }
}

int main()
{
  int i, requests_feitas = 0; /* Variáveis auxiliares*/
  time_t tempo_total;         /* Variável para guardar o tempo*/
  double media_rps;           /* Variável para guardar o numero de requests por segundo*/

  /* Inicializa a biblioteca cURL*/
  curl_global_init(CURL_GLOBAL_ALL);

  /* Cria um handle cURL*/
  CURL *curl = curl_easy_init();

  /* Inicia o cronômetro*/
  tempo_total = time(NULL);

  /* Faz as requests*/
  for (i = 1; i < MAX_REQUESTS; i++)
  {
    /* Se retornar um erro, encerrar*/
    char url[256];              /* Variável para guardar a URL*/
    snprintf(url, sizeof(url), URL, i);
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
