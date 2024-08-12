#include "../structs.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



TUser *user(char *name, char *adress, char *cpf) {
    TUser *user = (TUser *) malloc(sizeof(TUser));
    strcpy(user->name, name);
    strcpy(user->address, adress);
    strcpy(user->cpf, cpf);

    return user;
}



void saveUsers(const char *filename, TUser *users, int count) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }
    fwrite(users, sizeof(TUser), count, file);
    fclose(file);
}


TUser* readUser(FILE *in) {
    TUser* user = (TUser*) malloc(sizeof(TUser));
    if (0 >= fread(&user, sizeof(int), 1, in)) {
        free(user);
        return NULL;
    }
    fread(user->name, sizeof(char), sizeof(user), in);
    fread(user->cpf, sizeof(char), sizeof(user->cpf), in);
    fread(user->address, sizeof(char), sizeof(user->address), in);
    return user;
}



void generateRandomUsers(TUser *users, int count) {
    for (int i = 0; i < count; i++) {
        generateRandomName(users[i].name);
        generateRandomAddress(users[i].address);
        generateRandomCPF(users[i].cpf);
    }
}

void printAllUsers(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        exit(1);
    }

    TUser user;
    while (fread(&user, sizeof(TUser), 1, file)) {
        printUser(&user);
    }

    fclose(file);
}

void deleteUser(const char *filename, const char *cpfToDelete) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        printf("Erro ao abrir o arquivo temporário para escrita.\n");
        fclose(file);
        return;
    }

    TUser user;
    int found = 0;

    while (fread(&user, sizeof(TUser), 1, file)) {
        if (strcmp(user.cpf, cpfToDelete) != 0) {

            fwrite(&user, sizeof(TUser), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {

        remove(filename);
        rename("temp.dat", filename);
        printf("Usuário com CPF %s foi deletado.\n", cpfToDelete);
    } else {

        remove("temp.dat");
        printf("Usuário com CPF %s não foi encontrado.\n", cpfToDelete);
    }
}

void generateUserBase(const char *filename, int numberOfUsers) {
    TUser *users = (TUser *) malloc(numberOfUsers * sizeof(TUser));

    if (users == NULL) {
        printf("Erro ao alocar memória para os usuários.\n");
        exit(1);
    }

    generateRandomUsers(users, numberOfUsers);
    saveUsers(filename, users, numberOfUsers);
    free(users);

    printf("%d usuários foram gerados e salvos em '%s'.\n", numberOfUsers, filename);
}

int number_of_users(FILE* arq){
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / sizeUser());
    return tam;
}



TUser *userSequentialSearch(const char *filename, const char *targetCPF) {
     FILE *file = fopen(filename, "rb");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return NULL;
        }

    TUser *user;
    for (int i = 1; i <=number_of_users(file); ++i) {
        fseek(file,  sizeUser()*i, SEEK_SET);
        user = readUser(file);

        if (user != NULL && user->cpf == targetCPF) {
            return user;
        }
    }
    return  NULL;
}



// TUser *userSequentialSearch(const char *filename, const char *targetCPF) {
//     FILE *file = fopen(filename, "rb");
//     if (file == NULL) {
//         printf("Erro ao abrir o arquivo.\n");
//         return NULL;
//     }

//     TUser user;
//     rewind(file);
//     while (fread(&user, sizeof(TUser), 1, file) == 1) {
//         if (strcmp(user.cpf, targetCPF) == 0) {
//             fclose(file);
//             TUser *foundUser = (TUser *) malloc(sizeof(TUser));
//             *foundUser = user;
//             return foundUser;
//         }   

//     }

//     fclose(file);
//     return NULL;
// }

void updateUser(const char *filename, const char *targetCPF, TUser *updatedUser) {
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    TUser user;
    long pos;
    int found = 0;

    while (fread(&user, sizeof(TUser), 1, file) == 1) {
        if (strcmp(user.cpf, targetCPF) == 0) {
            pos = ftell(file) - sizeof(TUser);
            found = 1;
            break;
        }
    }

    if (found) {
        // Atualiza os dados do usuário
        fseek(file, pos, SEEK_SET); // Move o ponteiro para a posição do usuário encontrado
        fwrite(updatedUser, sizeof(TUser), 1, file);
        printf("\nUsuário com CPF %s atualizado com sucesso.\n", targetCPF);
    } else {
        printf("\nUsuário com CPF %s não encontrado.\n", targetCPF);
    }

    fclose(file); // Fecha o arquivo
}

void printUser(TUser *user) {
    printf("\n*****************************************");
    printf("\nUSER\t%s\tCPF\t%s", user->name, user->cpf);
    printf("\nADRESS:%s\t ", user->address);
    printf("\n*****************************************");
}

int sizeUser() {
    return sizeof(char) * 30
           + sizeof(char) * 30
           + sizeof(char) * 20
           + sizeof(char) * 12;
}

int qtdUserInFile(FILE *file) {
    fseek(file, 0, SEEK_END);
    int tam = trunc(ftell(file) / sizeUser());
    return tam;
}
