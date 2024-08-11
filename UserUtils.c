
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateRandomCPF(char* cpf) {
    for (int i = 0; i < 11; i++) {
        cpf[i] = '0' + rand() % 10; // Gera um dígito aleatório de 0 a 9
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

