#ifndef USERUTILS_H
#define USERUTILS_H


#include "User.h"
#include <stdio.h>
#include <stdlib.h>

// Função para gerar um CPF aleatório
void generateRandomCPF(char* cpf);

// Função para gerar um nome aleatório
void generateRandomName(char* name);

// Função para gerar um endereço aleatório
void generateRandomAddress(char* address);

// Função para gerar um método de pagamento aleatório
void generateRandomPaymentMethod(char* paymentMethod);

void posSearchProcessUser(TUser* u);



#endif 