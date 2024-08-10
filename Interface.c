#include "Product.h"
#include "Interface.h"
#include "Order.h"
#include "User.h"
#include "FileUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>


static FILE* stock;
static TProd *p;


void printMenu(){
    printf("\n---------------------------------------");
    printf("\n\tWELCOME TO THE INVENTORY SYSTEM\n");
    printf("\n[1] - Generate disordered base.");
    printf("\n[2] - Search for a product.");
    printf("\n[3] - Remove product.");
    printf("\n[4] - Add product.");
    printf("\n[5] - Create a User.");
    printf("\n[6] - Generate a order.");
    printf("\n[7] - Finish the order.");
    printf("\n[8] - list all base.");
    printf("\n[0] - Exit.");
    printf("\n---------------------------------------");
    printf("\nplease enter a value: ");
}

void menu(){

    int looping = -1;

    while(looping != 0){
        printMenu();
        scanf("%d",&looping);
        switch (looping)
        {
            case 1:
                genDisordedBase();
                system("pause");
                break;
            case 2:
                searchProd();
                system("pause");
                break;


            case 3:
                break;


            case 4:
                break;


            case 5:
                break;


            case 6:
                break;


            case 7:
                break;

            case 8:
                listBase();
                system("pause");
                break;
            
            default:
                printf("\nsaindo...");
                break;
        }
        
    }

    
}

void genDisordedBase(){
    if ((stock = fopen("stock.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }else{
        int tam, exchanges;
        printf("\nplease enter the size of base: ");
            scanf("%d",&tam);
        printf("\nplease enter the number of exchanges of the base: ");
            scanf("%d",&exchanges);

        c_disorded_database(stock,tam,exchanges);
    }

}

void searchProd(){
    p= (TProd*)malloc(sizeof(TProd*));
    int cod,op;
    printf("\nplease enter the code of the product: ");
            scanf("%d",&cod);
    p = findProdSequential(cod,stock);
    if(p!=NULL){
        printf("\nproduct found.Do you want to print?");
        printf("\n[0] - n\n[1] - y\n: ");
            scanf("%d",&op);
            if(op!=0){
                printProd(p);
                return;
            }
    }else printf("\nproduct not found.");

    

}
void removeProd(){

}
void createUser(){

}
void createOrder(){

}
void finishOrder(){

}
void listBase(){
    printBase(stock);
}



