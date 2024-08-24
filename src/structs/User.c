#include "../structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

TUser *createUser(char *name, char *address, char *cpf) {
    char *namefile = charUserOrderName(name);

    FILE *file = fopen(namefile, "a+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return NULL;
    }

    TUser *user = (TUser *) malloc(sizeof(TUser));
    if (user == NULL) {
        printf("Erro ao alocar memória para o usuário.\n");
        fclose(file);
        return NULL;
    }

    strncpy(user->name, name, sizeof(user->name) - 1);
    user->name[sizeof(user->name) - 1] = '\0'; 

    strncpy(user->address, address, sizeof(user->address) - 1);
    user->address[sizeof(user->address) - 1] = '\0'; 

    strncpy(user->cpf, cpf, sizeof(user->cpf) - 1);
    user->cpf[sizeof(user->cpf) - 1] = '\0'; 

    fclose(file);
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

TUser *readUser(const char *filename) {
    FILE *in = fopen(filename, "rb");
    if (in == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return NULL;
    }
    
    TUser *user = (TUser *) malloc(sizeof(TUser));
    if (fread(user, sizeof(TUser), 1, in) <= 0) {
        free(user);
        fclose(in);
        return NULL;
    }
    
    fclose(in);
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
        printUser(user);
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
        if (remove(filename) != 0) {
            printf("Erro ao remover o arquivo original.\n");
            return;
        }
        if (rename("temp.dat", filename) != 0) {
            printf("Erro ao renomear o arquivo temporário.\n");
            return;
        }
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

    printf("%d users were generated and saved in '%s'.\n", numberOfUsers, filename);
}

int sizeUser() {
    return sizeof(char) * 30
           + sizeof(char) * 30
           + sizeof(char) * 50
           + sizeof(char) * 12;
}

int number_of_users(FILE *file) {
    fseek(file, 0, SEEK_END);
    return ftell(file) / sizeUser();
}

TUser *userSequentialSearch(const char *filename, const char *targetCPF) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    TUser *user = (TUser *) malloc(sizeof(TUser)); 
    if (user == NULL) {
        perror("Erro ao alocar memória");
        fclose(file);
        return NULL; 
    }

    while (fread(user, sizeof(TUser), 1, file)) { 
        if (strcmp(user->cpf, targetCPF) == 0) {
            fclose(file);
            return user;
        }
    }

    if (ferror(file)) {
        fprintf(stderr, "Erro ao ler o arquivo\n");
    }

    fclose(file);
    free(user); 
    return NULL; 
}

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
        fseek(file, pos, SEEK_SET);
        fwrite(updatedUser, sizeof(TUser), 1, file);
        printf("Usuário com CPF %s atualizado com sucesso.\n", targetCPF);
    } else {
        printf("Usuário com CPF %s não encontrado.\n", targetCPF);
    }

    fclose(file);
}

void printUser(TUser user) {
    printf("\n*****************************************");
    printf("\nUSER\t%s\tCPF\t%s", user.name, user.cpf);
    printf("\nADDRESS:%s", user.address);
    printf("\n*****************************************");
}

char* charUserOrderName(char name[]) {
    char* namefile = (char*) malloc(strlen(name) + 11);
    if (namefile == NULL) {
        return NULL; 
    }
    strcpy(namefile, name);
    strcat(namefile, "order.dat");
    return namefile;
}
