
#include "structs.h"
#include "Interface.h"
#include "file/FileUtils.h"
#include "algorithms/intercalacaoBasico.h"
#include "algorithms/classificacaoInterna.h"
#include "algorithms/selecaoporsubstituicao.h"
#include <stdarg.h>
#include <string.h>

#define USERSFILE   "users.dat"
#define PRIVATE     static

static FILE* stock, *temp1;
static TProd *p;
static TUser *u;
static TOrder *o;
int op,qtd = 0;
int l = 1;
int opt = 0;
int cod;
int k = 33;
char tempDate[11];
char tempCpf[12];

PRIVATE int printMenu(void){

    int option;
    
    printf("\n---------------------------------------");
    printf("\n\tWELCOME TO THE INVENTORY SYSTEM\n");
    printf("\n[1] - Generate disordered base.");//C
    printf("\n[2] - Search for a product.");//C
    printf("\n[3] - Remove product.");//C
    printf("\n[4] - Add product.");//c
    printf("\n[5] - Create a random User.");//c
    printf("\n[6] - Generate a order database   .");
    printf("\n[7] - Remove a order");
    printf("\n[8] - list all base.");//c
    printf("\n[9] - edit a product.");//c
    printf("\n[10] - Print all orders");
    printf("\n[11] - ");
    printf("\n[12] - .");//c
    printf("\n[13] - organize files in secondary memory.");//tc
    printf("\n[14] - List all Users.");//c
    printf("\n[15] - Remove a User.");//c
    printf("\n[16] - Search for a user.");//C
    printf("\n[0] - Exit.");
    printf("\n---------------------------------------");
    printf("\nplease enter a value: ");

    scanf("%d",&option);

    return option;
}

void menu(){
    TUser *user = (TUser*)malloc(sizeof(TUser));
    while(1){        
    int option = printMenu();
        switch (option) {
            case 0:
                break;

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
                    fflush(stdin);
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
                    fflush(stdin);
                    scanf("%d",&qtd);
                    p->qtd = p->qtd + qtd;
                    fseek(stock, -sizeProd(), SEEK_CUR);
                    save(p, stock);
                    printf("\nProduct added successfully.");
                }    
                break;


            case 5:
                printf("\nplease enter the desired number of users: ");
                fflush(stdin);
                scanf(" %d",&qtd);
                generateUserBase(USERSFILE,qtd);
                system("pause");
                break;

            case 6: 
                    printf("\nOption [6]: please enter user's cpf: ");
                    fflush(stdin);
                    fgets(tempCpf, sizeof(tempCpf), stdin);
                    user = userSequentialSearch(USERSFILE, tempCpf);
                    if (user  != NULL) {
                        printf("\nOption [6]: please enter the number of orders: ");
                        fflush(stdin);
                        scanf(" %d", &qtd);
                        createMultipleOrdersWithRandomProducts(user, qtd);
                    } else {
                        printf("\nuser not found!");
                    }

                    free (user);
                    system("pause");

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
                fflush(stdin);
                scanf("%d", &cod);
                editProduct(cod, stock);
                system("pause");
                break;
            
            case 10:
                printf("\nplease enter user's cpf: ");
                fflush(stdin);
                fgets(tempCpf, sizeof(tempCpf), stdin);
                user = userSequentialSearch(USERSFILE,tempCpf);
                if (user!=NULL){
                    printAllOrders(user);
                }
                else
                    printf("\nUser not founded");

                system("pause");
                break;
            
            case 11:
                
                break;
            
            case 12:
                
                break;
            
            case 13:
                l=-1;
                while(l!=0){
                    printf("\nplease enter the method:\n");
                    printf("\n[1] - ClassificacaoInterna&IntercalacaoBasica.\n[2] - SelecaoPorSubstituicao&IntercalacaoOtima\n[0] -exit\n ");
                    scanf("%d",&op);
                    switch (op){
                        case 1:
                            inteleavingAndIC(stock);
                            l = 0;
                            break;                        
                        
                        case 2:
                            selecaoSubstE_ESCOLHEOMETODOMAYKE(stock);
                            l = 0;
                            break;                        
                        
                        case 0:
                            l = 0;
                            break;                        
                        
                        default:
                            printf("\nopção inválida...");
                            break;
                    }
                }
                break;
            
            case 14:
                printAllUsers(USERSFILE);
                printf("\n");
                system("pause");
                break;
            
            case 15:
                printf("\nplease enter the user cpf : ");
                fflush(stdin);
                fgets(tempCpf, sizeof( tempCpf), stdin);
                deleteUser(USERSFILE,tempCpf);
                system("pause");
                break;
            
            
            case 16:
                    printf("\nOption [16]: please enter user's cpf: ");
                    fflush(stdin);
                    fgets(tempCpf, sizeof(tempCpf), stdin);
                    user = userSequentialSearch(USERSFILE, tempCpf);
                    
                    if (user != NULL) {
                        printUser(*u);
                        free(u);
                        system("pause");
                    } else {
                        printf("\nUser not found!");
                        system("pause");
                        break;
                    }
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
            fflush(stdin);
            scanf("%d",&tam);
        printf("\nplease enter the number of exchanges of the base: ");
            fflush(stdin);
            scanf("%d",&exchanges);

        c_disorded_database(stock,tam,exchanges);
    }

}

void searchProd(){
    p= (TProd*)malloc(sizeof(TProd*));
    int cod,op;
    printf("\nplease enter the code of the product: ");
        fflush(stdin);
        scanf("%d",&cod);
    printf("\nplease enter search method\n[1] - Sequential\n[2] - Binary");
        fflush(stdin);
        scanf("%d",&op);
    if(op==1){
        p = findProdSequential(cod,stock);
    }else{
        p = buscaBinariaPorCod(stock,cod,1,number_of_products(stock));

    }
    posSearchProcess(p);

}

void listBase(){
    printBase(stock);
}





