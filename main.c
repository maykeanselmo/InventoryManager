#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Product.c"
#include "Order.c"
#include "User.c"
#include "FileUtils.c"
// #include "Interface.c"

int main(){
    // TProd *prodTest = (TProd *)malloc(sizeof(TProd));
    // prodTest->cod = 123;
    // prodTest->qtd = 1;
    // strcpy(prodTest->name,"TESTPRODUCT");
    // strcpy(prodTest->due_date,"27/02/0505");
    // prodTest->value = 0.00;
    // printProd(prodTest);
    // TOrder* order1 = (TOrder *)malloc(sizeof(TOrder));
    /* printf("hello");    // orderPrint(order1);    // menu();
    TUser* user1 = user("ab","ab","ba","ba");
    printf("hello2");    // orderPrint(order1);    // menu();
    TUser* user2 = user("cd","cd","dc","dc");

    TOrder *pedido = order(user1,10,"1/1/1");
    TOrder *pedido2 = order(user2,4,"2/2/2");
    printBase(user1->orderFile);
    printf("\n\nESPAÇO\n\n");
    printBase(user2->orderFile); */

    TUser* user1 = user("ab","ab","ba","ba");
    TOrder *pedido1 = order(user1,2,"1/1/1");
    TOrder *pedido2 = order(user1,3,"2/1/1");
    TOrder *pedido3 = order(user1,4,"3/1/1");
    //orderPrint(pedido1);
   // printf("\n");
    //orderPrint(pedido2);
    //printf("\n");
    //orderPrint(pedido3);
    printOrders(user1->orderFile);





    

}