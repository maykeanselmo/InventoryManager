#include "Product.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>


TProd *prod(int cod, int qtd, char *name, char *duedate, double value){
    TProd *prod = (TProd * ) malloc(sizeof(TProd));
    if (prod) memset(prod, 0, sizeof(TProd));
    prod->cod = cod;
    prod->qtd = qtd;
    strcpy(prod->name, name);
    strcpy(prod->due_date, duedate);
    prod->value = value;
    return prod;
}

// writes a product to the file at the current cursor position
void save(TProd *prod, FILE *out){
    fwrite(&prod->cod, sizeof(int), 1, out);
    fwrite(&prod->qtd, sizeof(int), 1, out);
    fwrite(prod->name, sizeof(char), sizeof(prod->name), out);
    fwrite(prod->due_date, sizeof(char), sizeof(prod->due_date), out);
    fwrite(&prod->value, sizeof(double),1,out);
}

TProd *readProd(FILE *in){
    TProd *prod = (TProd * ) malloc(sizeof(TProd));
    if (0 >= fread(&prod->cod, sizeof(int), 1, in)) {
        free(prod);
        return NULL;
    }
    fread(&prod->qtd, sizeof(int), 1, in);
    fread(prod->name, sizeof(char), sizeof(prod->name), in);
    fread(prod->due_date, sizeof(char), sizeof(prod->due_date), in);
    fread(&prod->value, sizeof(double), 1, in);
    return prod;
}

void printProd(TProd *prod){
    printf("\n---------------------------------------");
    printf("\nPRODUCT\t\t\t- %d -",prod->cod);
    printf("\nNAME:\t\t%s",prod->name);
    printf("\nVALUE:\t\t%4.2f",prod->value);
    printf("\nQUANTITY:\t\t- %ld -",prod->qtd);
    printf("\n---------------------------------------\n");
}

int sizeProd(){
    return sizeof(int) * 2  //cod
        + sizeof(char) * 30 //name
        + sizeof(char) * 11 //due_date
        + sizeof(double); //value
}

int number_of_products(FILE* arq){
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / sizeProd());
    return tam;
}

TProd *findProdSequential(int cod, FILE *arq){
    clock_t ti,tf;

    TProd *p = NULL;


    int i = 0;
    rewind(arq);
    ti = clock();
    while ((p = readProd(arq)) != NULL){ 
        i++;    
        if (p->cod == cod){
            tf = clock();
            printf("\nTEMPO: %f\n",(double)(tf - ti) / CLOCKS_PER_SEC);
            printf("\nCOMPARACOES BUSCA SEQUENCIAL: %d\n",i);

            return p;
        }
        free(p); 
    }
    return p;
    

}

void editProduct(int cod, FILE *stock) {
    TProd *p = findProdSequential(cod, stock);
    if (p != NULL) {
        int posi = ftell(stock) - sizeProd(); // Posição do produto no arquivo
        displayEditMenu(p); // Função que apresentará o menu de edição
        fseek(stock, posi, SEEK_SET); // Posiciona o cursor no produto
        save(p, stock); // Salva as alterações
        free(p); // Libera a memória alocada
    } else {
        printf("\nProduto não encontrado...");
    }
}

void displayEditMenu(TProd *p) {
    int op = -1;
    while (op != 0) {
        printf("\nSelecione o campo que deseja alterar: ");
        printf("\n[1] - name");
        printf("\n[2] - duedate");
        printf("\n[3] - value");
        printf("\n[4] - qtd");
        printf("\n[0] - leave");
        printf("\nOpção: ");
        fflush(stdin);
        scanf("%d", &op);
        processEditChoice(op, p); // Função que processa a escolha
    }
}


void processEditChoice(int choice, TProd *p) {
    switch (choice) {
        case 1:
            printf("\nplease enter new name:\n");
            fflush(stdin);
            fgets(p->name, sizeof(p->name), stdin);
            strtok(p->name, "\n"); // Remove o caractere de nova linha
            break;

        case 2:
            printf("\nplease enter new dueDate (dd/mm/aaaa):\n");
            fflush(stdin);
            fgets(p->due_date, sizeof(p->due_date), stdin);
            strtok(p->due_date, "\n"); // Remove o caractere de nova linha
            break;

        case 3:
            printf("\nplease enter new value:\n");
            fflush(stdin);
            scanf("%lf", &p->value);
            break;

        case 4:
            printf("\nplease enter new amount:\n");
            fflush(stdin);
            scanf("%lu", &p->qtd);
            break;

        case 0:
            printf("\nLeaving edit menu...");
            break;

        default:
            printf("\nInvalid option!");
            break;
    }
}

void posSearchProcess(TProd* p){
    int op;
    if(p!=NULL){
        printf("\nproduct found.Do you want to print?");
        printf("\n[0] - not.\n[1] - yes.\n: ");
            scanf("%d",&op);
            if(op!=0){
                printProd(p);
                return;
            }else op =0;
    }else {
        printf("\nproduct not found.");
        return;
        }
}

TProd *searchAndPrintProd(TProd* p, FILE* stock){
    p= (TProd*)malloc(sizeof(TProd*));
                int cod,op,qtd;
                printf("\nplease enter the code of the product: ");
                    scanf("%d",&cod);
                p = findProdSequential(cod,stock);
                
                posSearchProcess(p);
                system("pause");
    return p;
}
















