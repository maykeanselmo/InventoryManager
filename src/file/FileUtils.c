#include "../structs.h"
#include "../algorithms/classificacaoInterna.h"
#include "../algorithms/intercalacaoBasico.h"

#include <math.h>

// double adjust_value(double value) {
//     double factor;
    
//     // Calculate the number of zeros (n) by taking the logarithm base 10 of the value
//     int num_zeros = (int)log10(value);
    
//     // The factor is calculated as 1 divided by 10 raised to the power of (number of zeros - 1)
//     factor = 1.0 / pow(10, num_zeros - 1);
    
//     return value * factor;
// }
void inteleavingAndIC(FILE* stock){
    rewind(stock);

    int num_particoes = classificacao_interna(stock, number_of_products(stock)*0.1);

    rewind(stock);
    intercalacao_basica(stock, num_particoes);
    rewind(stock); 
}

void c_ordenate_database(FILE *out, int tam){
    int *vet = malloc(tam * sizeof(int)); // Alocação dinâmica do vetor
    TProd *p = NULL;
    for(int i = 0 ; i < tam ; i++){
        vet[i] = i+1;
    }
    printf("\nGenerating an ordered database...\n");
    for(int i = 0 ; i < tam; i++){
        p = prod(vet[i], i*10, "PROD", "00/00/0000", 10*i);
        save(p, out);
        free(p); // Liberação de memória a cada iteração
    }
    free(vet); // Liberação do vetor
}

void mix_up(int *vet, int MAX, int exchanges){
    srand(time(NULL));
    for (int i = 0; i < exchanges; i++) {
        int j = rand() % MAX;
        int k = rand() % MAX;
        int tmp = vet[j];
        vet[j] = vet[k];
        vet[k] = tmp;
    }
}

void c_disorded_database(FILE *out, int tam, int exchanges){
    int *vet = malloc(tam * sizeof(int)); // Alocação dinâmica do vetor
    TProd *p = NULL;
    for(int i = 0 ; i < tam ; i++){
        vet[i] = i+1;
    }
    mix_up(vet, tam, exchanges);
    printf("\nGenerating a disordered database...\n");
    for(int i = 0 ; i < tam; i++){
        p = prod(vet[i], i*10, "PROD", "00/00/0000", 10*i);
        save(p, out);
        free(p); // Liberação de memória a cada iteração
    }
    free(vet); // Liberação do vetor
}

void printBase(FILE *out){
    printf("\nPrinting database...\n");
    rewind(out);
    TProd *p = NULL;
    while ((p = readProd(out)) != NULL) {
        printProd(p);
        free(p); // Liberação de memória a cada iteração
    }
}

TProd *buscaBinariaPorCod(FILE *arq, int cod, int inicio, int fim){
    static int i = 0;
    i++;
    int meio = trunc((inicio+fim)/2);
    fseek(arq, sizeProd()*meio, SEEK_SET);
    TProd *f = readProd(arq);
    if (f->cod == cod){
        printf("\nNUMERO DE COMPARACOES BINARIA: %d\n", i);
        return f;
    } else if (cod > f->cod) {
        free(f); // Libera memória antes da próxima chamada recursiva
        return buscaBinariaPorCod(arq, cod, meio, fim);
    } else if (cod < f->cod) {
        free(f); // Libera memória antes da próxima chamada recursiva
        return buscaBinariaPorCod(arq, cod, inicio, meio);
    }
    free(f); // Libera memória caso o produto não seja encontrado
    return NULL;
}
