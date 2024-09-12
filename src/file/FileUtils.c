#include "../structs.h"
#include "../algorithms/classificacaoInterna.h"
#include "../algorithms/intercalacaoBasico.h"
#include "../algorithms/intercalacao_otima.h"
#include "../algorithms/selecaoporsubstituicao.h"
#include "../file/FileUtils.h"
#include <math.h>
#define  NUM_MAX_ARQUIVOS_MANIPULADOS 3
#define PARTITION_PATH "src/partitions/partition"

void inteleavingAndIC(FILE* stock){
    rewind(stock);
    int num_particoes = classificacao_interna(stock, number_of_products(stock)*0.1);

    rewind(stock);
    intercalacao_basica(stock, num_particoes);
    rewind(stock); 
}

// Função para chamar a Seleção Natural e fazer intercalação ótima
void selecaoSubstE_ESCOLHEOMETODOMAYKE(FILE* stock) {
    rewind(stock);
    int nProds = number_of_products(stock);
    printf("\nNúmero total de produtos: %d\n", nProds);
    int num_particoes = selecao_por_substituicao(stock, nProds * 0.1);
    if (num_particoes < 0) {
        printf("Erro ao criar partições.\n");
        return;
    }
    printf("\nNúmero de partições: %d\n", num_particoes);
    
    // Passa o caminho do arquivo stock para a função intercalacao_otima
    intercalacao_otima(num_particoes, "stock.dat");
    
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

void saveRegisterProduct(TProd *prod, FILE *out) {
    fwrite(&prod->cod, sizeof(int), 1, out);                          
    fwrite(prod->name, sizeof(char), sizeof(prod->name), out);        
    fwrite(prod->due_date, sizeof(char), sizeof(prod->due_date), out); 
    fwrite(&prod->value, sizeof(double), 1, out);                     
    fwrite(&prod->qtd, sizeof(unsigned long int), 1, out);            
}

void treeWinner(TProd **func, FILE *file, int sizeInTreeOfWinners, int *auxTreeWinner) {

    int aux;

    for (int i = sizeInTreeOfWinners - 1; i > 0; i--){

        if (i % 2 != 0 && i == sizeInTreeOfWinners - 1){
            aux = (i - 1) / 2;
            *func[aux] = *func[i];
        }
        else{
            if (i % 2 == 0 && func[i]->cod < func[i-1]->cod){
                aux = (i - 2) / 2;
                *func[aux] = *func[i];
            }
            else if (i % 2 == 0 && func[i-1]->cod < func[i]->cod){
                aux = (i - 2) / 2;
                *func[aux] = *func[i - 1];
            }
        }
    }

    saveRegisterProduct(func[0], file);
    *auxTreeWinner +=1;
}

TProd*readRegisterProduct(FILE *in) {
    TProd *func = (TProd*) malloc (sizeof(TProd));

    if ( 0 >= fread(&func->cod, sizeof(int), 1, in)) {
        free(func);
        return NULL;
    }

    fread(func->name, sizeof(char), sizeof(func->name), in);
    fread(func->due_date, sizeof(char), sizeof(func->due_date), in);
    fread(&func->cod, sizeof(int), 1, in);
    fread(&func->value, sizeof(double), 1, in);
    fread(&func->qtd, sizeof(unsigned long int), 1, in);
    return func;
}



void printSortedFile(const char *fileName) {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", fileName);
        return;
    }

    TProd product;  

    
    memset(product.name, 0, sizeof(product.name));
    memset(product.due_date, 0, sizeof(product.due_date));

    printf("Conteúdo do arquivo %s:\n", fileName);
    printf("----------------------------------------------------\n");
    printf("|   Cod   |       Nome       |   Data    |   Valor   | Qtd |\n");
    printf("----------------------------------------------------\n");

  
    while (fread(&product.cod, sizeof(int), 1, file) == 1) {
        fread(product.name, sizeof(char), sizeof(product.name), file);
        fread(product.due_date, sizeof(char), sizeof(product.due_date), file);
        fread(&product.value, sizeof(double), 1, file);
        fread(&product.qtd, sizeof(unsigned long int), 1, file);

        
        if (feof(file)) break;

        
        printf("| %7d | %15s | %10s | %9.2f | %3lu |\n",
               product.cod, product.name, product.due_date, product.value, product.qtd);
    }

    printf("----------------------------------------------------\n");

    fclose(file);  
}