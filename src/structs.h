#ifndef STRUCTS_H
#define STRUCTS_H

/* Include Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

#define bool  int
#define FALSE 0
#define TRUE  1

/* Struct Definitions */
typedef struct {
    FILE* orderFile; 
    char name[30];
    char address[30];
    char cpf[12];
} TUser;

typedef struct Produto {
    int cod;
    unsigned long int qtd;
    char name[30];
    char due_date[11];
    double value;
} TProd;

typedef struct ProductNode {
    TProd *product; 
    struct ProductNode *next;
} TProdNode;

typedef struct {
    int cod;
    int numOfTypes;
    char date[11];
    double value;
    char paymentMethod[20];
    TProdNode *products;
} TOrder;

typedef struct File{
    TProd *func;
    long init_p;
    long end_p;
    FILE *filePartition;
}TVetFile;



/* User Functions */
TUser *createUser(char *name, char *address, char *cpf);
int sizeUser(void);
int number_of_users(FILE* arq);
void saveUsers(const char *filename, TUser *users, int count);
TUser *readUser(const char *filename);
int qtdUserInFile(FILE* file);
void printUser(TUser user);
void printAllUsers(const char *filename);
void generateRandomUsers(TUser *users, int count);
void generateUserBase(const char *filename, int numberOfUsers);
void generateRandomCPF(char* cpf);
char* charUserOrderName(char name[]);
void generateRandomName(char* name);
void generateRandomAddress(char* address);
void generateRandomPaymentMethod(char* paymentMethod);
TUser *userSequentialSearch(const char * filename, const char * targetCPF);
void updateUser(const char *filename, const char *targetCPF, TUser *updatedUser);
void deleteUser(const char *filename, const char *cpfToDelete);


/* Product Functions */
TProd* prod(int cod, int qtd, char *name, char *duedate, double value);
void save(TProd *prod, FILE *out);
TProd* readProd(FILE *in);
void printProd(TProd *prod);
int sizeProd(void);
int number_of_products(FILE* arq);
void c_ordenate_database(FILE *out, int tam);
void mix_up(int *vet, int MAX, int exchanges);
void c_disorded_database(FILE *out, int tam, int exchanges);
void printBase(FILE *out);
TProd* findProdSequential(int cod, FILE *arq);
void displayEditMenu(TProd *p);
void editProduct(int cod, FILE *stock);
void processEditChoice(int choice, TProd *p);
void posSearchProcess(TProd* p);
void preRemoveProcess(TProd* p, FILE *stock);
TProd* searchAndPrintProd(TProd* p, FILE* stock);

/* TProdNode Functions */
TProdNode* criaNo(TProd *product);
void insertProduct(TProdNode **head, TProd *product);
void freeProductList(TProdNode *head);

/* Order Functions */
TOrder* order(TUser* user, int numOfTypes, char *date);
void orderPrint(TOrder *order);
int qtdOrderInFile(FILE *file);
int orderSize();
int generateRandomProductCode();
void generateRandomDueDate(char* due_date);
TProd* createRandomProduct();
void freeOrder(TOrder* order);
void saveOrder(TOrder* order, const char *filename);
void saveOrderInUserFile(TOrder* order, TUser* user);
TOrder* createOrderWithRandomProducts(int numOfTypes, const char* date);
void printOrders(FILE *out);
TOrder *readOrderWithProd(FILE *in);
TOrder *readOrder(FILE *in);
void printAllOrders(TUser *user);
void createMultipleOrdersWithRandomProducts(TUser* user, int orderCount);
void deleteOrder(TUser *user, int orderCode);

#endif