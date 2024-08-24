#include "../structs.h"
#include "../algorithms/classificacaoInterna.h"
#include "../algorithms/intercalacaoBasico.h"
#include "../file/FileUtils.h"

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
    int vet[tam];
    TProd *p;
    for(int i = 0 ; i<tam ; i++){
        vet[i] = i+1;
    }
    printf("\nGenerating a ordenated database...\n");
    for(int i = 0 ; i < tam; i++){
        //rever como quantidade do produto é gerada! 
        p = prod(vet[i],i*10,"PROD", "00/00/0000",10*i);
        save(p,out);
    }
    free(p);
}

//date mixup
void mix_up(int *vet,int MAX,int exchanges){
    srand(time(NULL));
    for (int i = 0; i <= exchanges; i++) {
        int j = rand() % (MAX-1);
        int k = rand() % (MAX-1);
        int tmp = vet[j];
        vet[j] = vet[k];
        vet[k] = tmp;
    }
}

void c_disorded_database(FILE *out, int tam, int exchanges){
    int vet[tam];
    TProd *p;
    for(int i = 0 ; i<tam ; i++){
        vet[i] = i+1;
    }
    mix_up(vet,tam,exchanges);
    printf("\nGenerating a disorded database...\n");
    for(int i = 0 ; i < tam; i++){
        double temp = generateRandomValue();
        p = prod(vet[i], i*10,"PROD", "00/00/0000",temp);
        save(p,out);
    }
    free(p);
}

void printBase(FILE *out){
printf("\nPrinting database...\n");
    rewind(out);
    TProd *p;
    while ((p = readProd(out)) != NULL)
        printProd(p);
    free(p);
}

TProd *buscaBinariaPorCod(FILE *arq, int cod,int inicio, int fim){
    static int  i =0;
    i++;
    int meio = trunc((inicio+fim)/2);
    fseek(arq,sizeProd()*meio,SEEK_SET);
    TProd *f = readProd(arq);
    if (f->cod==cod){
        printf("\nNUMERO DE COMPARACOES BINARIA: %d\n",i);
        return f;
    }
    else if(cod> f->cod){
        return buscaBinariaPorCod(arq,cod, meio,fim);
    }
    else if(cod < f->cod){
        return buscaBinariaPorCod(arq,cod,inicio,meio);
    }
    
    return NULL;

}

bool checkIfFolderExist(const char *directory){
    struct stat info;
    if(stat(directory,&info)!= 0){
        return false;
    }else if(info.st_mode & S_IFDIR){
        return true;
    }
    return false;
}


double generateRandomValue() {
    return (double) (rand() % 10000);
}