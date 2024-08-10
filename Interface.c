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
int op = 0;
int cod;



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
    printf("\n[9] - edit a product.");
    printf("\n[10] - edit a order.");
    printf("\n[11] - remove a order.");
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
                rewind(stock);
                listBase();
                system("pause");
                break;

            
            case 9:
                printf("\nplease enter a code: ");
                scanf("%d",&cod);
                int posi;
                p = findProdSequential(cod,stock);
                //posição atual do cursor quando ele encontra o produto
                posi = ftell(stock) - sizeProd();
                printf("\n---------------------------------------");
                if(p!= NULL){
                    op = -1;
                    while(op!=0){
                        printf("\nPlease select the field you wish to change: ");
                        printf("\n[1] - name  ");
                        printf("\n[2] - duedate  ");
                        printf("\n[3] - value\n: ");
                        printf("\n[0] - exit\n: ");
                        fflush(stdin);
                        scanf("%d",&op);
                        switch (op)
                        {
                        case 1:
                            printf("\nplease enter a new name:\n");
                            fflush(stdin); 
                            fgets(p->name,sizeof(p->name),stdin);
                            op = 0;
                            break;
                        
                        case 2:
                            printf("\nplease enter a new duedate:\n");
                            fflush(stdin);
                            fgets(p->due_date,sizeof(p->due_date),stdin);
                            system("pause");
                            op = 0;
                            break;

                        case 3:
                            printf("\nplease enter a new value:\n");
                            fflush(stdin);
                            scanf("%lf",&p->value);
                            op = 0;
                            break;
                        
                        
                        case 0:
                            printf("\nleaving...");
                            op = 0;
                            break;
                        
                        default:
                            printf("\ninvalid option!");
                            break;
                        }
                    }

                    //posiciona o cursor para a posição do produto p
                    fseek(stock, posi, SEEK_SET);
                    save(p,stock);
                }else {
                    printf("\nop not found...");
                    break;
                }
            
            case 10:
                
                break;

            
            default:
                printf("\ninvalid option...");
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



