#include "Product.h"
#include "Interface.h"
#include "Order.h"
#include "User.h"
#include "UserUtils.h"
#include "FileUtils.h"
#include "intercalacaoBasico.h"
#include "classificacaoInterna.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>

#define USERSFILE "users.dat"

static FILE* stock;
static TProd *p;
static TUser *u;
int op,qtd = 0;
int cod;



void printMenu(){
    printf("\n---------------------------------------");
    printf("\n\tWELCOME TO THE INVENTORY SYSTEM\n");
    printf("\n[1] - Generate disordered base.");//C
    printf("\n[2] - Search for a product.");//C
    printf("\n[3] - Remove product.");//C
    printf("\n[4] - Add product.");//c
    printf("\n[5] - Create a random User.");//c
    printf("\n[6] - Generate a order.");
    printf("\n[7] - Finish the order.");
    printf("\n[8] - list all base.");//c
    printf("\n[9] - edit a product.");//c
    printf("\n[10] - edit a order.");
    printf("\n[11] - remove a order.");//c
    printf("\n[12] - remove an user.");//c
    printf("\n[13] - Interleaving and internal classification.");//c
    printf("\n[14] - List all Users.");//c
    printf("\n[15] - Remove a User.");//c
    printf("\n[16] - Search for a user.");//C
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
                p = searchAndPrintProd(p,stock);
                int qtd = 0;
                if(p!= NULL){
                    printf("\nPlease enter the quantity of products you wish to remove: ");
                    scanf("%d",&qtd);
                    if(qtd>p->qtd){
                        printf("\nInvalid input");
                    }

                    else if(qtd<=p->qtd){
                        printf("\nAre you sure you want to remove %d itens of the product %d\n[1]- yes\n[0]- not\n",qtd,p->cod);
                        fflush(stdin);
                        scanf(" %d",&op);
                        if (op !=0){
                            p->qtd = p->qtd-qtd;
                            fseek(stock, -sizeProd(), SEEK_CUR);
                            save(p, stock);
                            printf("\nProduct removed successfully.");
                            op = 0;

                        }
                    }
                }
                break;


            case 4:
                p = searchAndPrintProd(p,stock);
                    qtd = 0;
                    if(p!= NULL){
                    printf("\nPlease enter the quantity of products you wish to add: ");
                    scanf("%d",&qtd);
                            p->qtd = p->qtd + qtd;
                            // Posiciona o cursor no local do produto encontrado
                            fseek(stock, -sizeProd(), SEEK_CUR);
                            // Atualiza o produto no arquivo com a quantidade zero
                            save(p, stock);
                            printf("\nProduct added successfully.");    
                
                break;


            case 5:
                printf("\nplease enter the desired number of users: ");
                        scanf(" %d",&qtd);
                generateUserBase(USERSFILE,qtd);
                system("pause");
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
               printf("\nplease enter a code of product: ");
                scanf("%d", &cod);
                editProduct(cod, stock);
                system("pause");
                break;
            
            case 10:
                
                break;
            
            case 11:
                
                break;
            
            case 12:
                
                break;
            
            case 13:
                inteleavingAndIC(stock, p);
                system("pause");
                break;
            
            case 14:
                printAllUsers(USERSFILE);
                system("pause");
                break;
            
            case 15:

                u = user(" "," "," "," ");
                    printf("\nplease enter the user cpf : ");
                    fflush(stdin);
                    fgets(u->cpf, sizeof(u->cpf), stdin);

                deleteUser(USERSFILE,u->cpf);
                system("pause");
                break;

            
            default:
                printf("\ninvalid option...");
                break;
        }
        
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
    printf("\nplease enter search method\n[1] - Sequential\n[2] - Binary");
        scanf("%d",&op);
    if(op==1){
        p = findProdSequential(cod,stock);
    }else{
        p = buscaBinariaPorCod(stock,cod,1,number_of_products(stock));

    }
    posSearchProcess(p);

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

void searchUser(){
     

}




