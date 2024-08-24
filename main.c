#include "src/Interface.h"
#include <stdio.h>
#include <stdlib.h>

#define TESTE "usersTESte.dat"
#define ORDERFILE "orders.dat"

int main(){  
    generateUserBase(TESTE, 1);
    
    TUser *user = createUser("athus", "csa", "cpf");
    if (user == NULL) {
        printf("Erro ao criar o usuário.\n");
        return 1;
    }

    TOrder *order = createOrderWithRandomProducts(10, "27/05/2004");
    TOrder *order1 = createOrderWithRandomProducts(2, "22/02/2002");
    // char *namefile = charUserOrderName(user->name);
    FILE* orderF = fopen(ORDERFILE, "wb");
    // FILE* userOrderFile = fopen(namefile, "wb");
    if (orderF == NULL) {
        printf("Erro ao abrir o arquivo para gravação.\n");
        return 1;
    }

    saveOrder(order, ORDERFILE);
    saveOrder(order1, ORDERFILE);
    // printOrders(orderF);

    fclose(orderF);

    printf("\nsalvando no arquivo do usuário...\n");
    // rewind(userOrderFile);
    saveOrderInUserFile(order, user);
    saveOrderInUserFile(order1, user);

    printf("\nConcluído...\n");
    // rewind(userOrderFile);
    printAllOrders(user);

    // Libere a memória alocada
    free(order);
    free(order1);
    free(user);

    return 0;
}