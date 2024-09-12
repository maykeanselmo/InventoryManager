#include "../structs.h"
// #include "../UserUtils.h"
#include <stdlib.h>
#include <string.h>

void generateRandomCPF(char* cpf) {
    for (int i = 0; i < 11; i++) {
        cpf[i] = '0' + rand() % 10; 
    }
    cpf[11] = '\0';
}

void generateRandomName(char* name) {
    const char* names[] = {"John Doe", "Jane Smith", "Alice Johnson", "Bob Brown", "Charlie Black"};
    strcpy(name, names[rand() % 5]);
}

void generateRandomAddress(char* address) {
    sprintf(address, "%d Main St", rand() % 1000 + 1);
}

void posSearchProcessUser(TUser* u){
    int op;
    if(u!=NULL){
        printf("\nuser found.Do you want to print?");
        printf("\n[0] - not.\n[1] - yes.\n: ");
        scanf("%d",&op);
        if(op!=0){
            printUser(*u);
            return;
        }else op =0;
    }else {
        printf("\nproduct not found.");
        return;
    }

}

