#include <stdio.h>
#include "intercalacaoOtima.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "IntercalacaoBasicaAdaptada.h"
#define FILENAME_LENGTH 100

int contarParticoes() {
    DIR *dir;
    struct dirent *entry;
    int contador = 0;
    char *caminho = "src/partitions";
    char prefixo[20] = "partition";

    dir = opendir(caminho);
    if (dir == NULL) {
        printf("Erro ao abrir o diretório: %s\n", caminho);
        return -1;
    }

    // Lê os arquivos no diretório
    while ((entry = readdir(dir)) != NULL) {
        // Verifica se o arquivo começa com "partition" e termina com ".dat"
        if (strncmp(entry->d_name, prefixo, strlen(prefixo)) == 0 && strstr(entry->d_name, ".dat") != NULL) {
            contador++;
        }
    }
    closedir(dir);
    return contador;
}
int inserirParticoesEmArray(FILE *files[],int numeroDeParticoes) {
    DIR *dir;
    struct dirent *entry;
    int contador = 0;
    char *caminho = "src/partitions";
    char prefixo[20] = "partition";
    char nomeArquivo[100];

    dir = opendir(caminho);
    if (dir == NULL) {
        printf("Erro ao abrir o diretório: %s\n", caminho);
        return -1;
    }

    // Lê os arquivos no diretório
    while ((entry = readdir(dir)) != NULL) {
        // Verifica se o arquivo começa com "partition" e termina com ".dat"
        if (strncmp(entry->d_name, prefixo, strlen(prefixo)) == 0 && strstr(entry->d_name, ".dat") != NULL) {
            if (contador < numeroDeParticoes) {
                // Constrói o nome completo do arquivo
                snprintf(nomeArquivo, sizeof(nomeArquivo), "src/partitions/%s", entry->d_name);

                // Abre o arquivo e armazena o ponteiro no array
                files[contador] = fopen(nomeArquivo, "rb");
                if (files[contador] == NULL) {
                    printf("Erro ao abrir o arquivo: %s\n", nomeArquivo);
                } else {
                    contador++;
                }
            } else {
                printf("Número máximo de partições atingido.\n");
                break;
            }
        }
    }

    closedir(dir);

    return contador;
}
char* gerarNomeParticaoIntermediaria() {
    // Aloca memória para o nome do arquivo
    char *filename = malloc(FILENAME_LENGTH);
    if (filename == NULL) {
        perror("Erro ao alocar memória para o nome do arquivo");
        return NULL;
    }

    // Obtém o timestamp atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Formata o nome do arquivo
    snprintf(filename, FILENAME_LENGTH, "particao_intermediaria_%d-%02d-%02d_%02d-%02d-%02d.dat",
             tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
             tm.tm_hour, tm.tm_min, tm.tm_sec);

    return filename;
}

void extrairParticoesParaOrdenacao(FILE *particoesASeremOrdenadas[], int inicio, int numArquivosDeLeitura, FILE *particoes[]){
    for (int i = 0; i < numArquivosDeLeitura; ++i) {
        particoesASeremOrdenadas[i]= particoes[inicio + i];
    }
}

void ordenaParticoes(FILE *particoes[], FILE *particoesASeremOrdenadas[], int numArquivosDeLeitura, int inicio){
    FILE * file = intercalacaoBasicaAdaptada(particoesASeremOrdenadas,numArquivosDeLeitura,gerarNomeParticaoIntermediaria());

    for (inicio ; inicio  < (numArquivosDeLeitura); ++inicio ) {
        if( inicio  == (numArquivosDeLeitura - 1)){
            free(particoes[inicio ] );
            particoes[inicio] = file;
        }
        free(particoesASeremOrdenadas[inicio] );
    }
}
void *intercalaoOtima(FILE *out, int numMaxDeArquivosManipulados){

    int numArquivosDeLeitura = numMaxDeArquivosManipulados - 1;
    int numeroDeParticoes = contarParticoes();
    FILE *particoes[numeroDeParticoes];
    FILE *particoesASeremOrdenadas[numArquivosDeLeitura];
    int inicio = 0;

    while(inicio != (numeroDeParticoes) ){
        inserirParticoesEmArray(particoes, numeroDeParticoes);
        extrairParticoesParaOrdenacao(particoesASeremOrdenadas, inicio,numArquivosDeLeitura, particoes);
        ordenaParticoes(particoes,particoesASeremOrdenadas,numArquivosDeLeitura,inicio);
        inicio = inicio + numArquivosDeLeitura - 1;
    }
    out = particoes[numeroDeParticoes];
}

