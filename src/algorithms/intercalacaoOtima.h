
#include <stdlib.h>
#include <stdio.h>

#ifndef INVENTORYMANAGER_INTERCALACAOOTIMA_H
#define INVENTORYMANAGER_INTERCALACAOOTIMA_H

int contarParticoes();
int inserirParticoesEmArray(FILE *files[],int numeroDeParticoes);
char* gerarNomeParticaoIntermediaria();
void extrairParticoesParaOrdenacao(FILE *particoesASeremOrdenadas[], int inicio, int numArquivosDeLeitura, FILE *particoes[]);
void ordenaParticoes(FILE *particoes[], FILE *particoesASeremOrdenadas[], int numArquivosDeLeitura, int inicio);
void *intercalaoOtima(FILE *out, int numMaxDeArquivosManipulados);

#endif //INVENTORYMANAGER_INTERCALACAOOTIMA_H
