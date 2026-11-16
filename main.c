#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "product_functions.h"
#include "list_functions.h"
#include "file_functions.h"

char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";

int main () {

    bool play = false;
    char filename[20];
    char confirm_play[10];
    int confirm;
    printf("comecar ou encerrar? ");
    scanf("%s", confirm_play);

    if(strcmp(confirm_play, "comecar") == 0) {
        play = true;
    }

    while (play == true) {
        Product list_product[MAX_PRODUCTS];
        printf("Deseja criar produtos(0), ler arquivos(1), ou encerrar(2)? Digite o respectivo numero: ");
        scanf("%d", &confirm);
        int size = 0;

        if (confirm == 0) {
            while (size < MAX_PRODUCTS) {
                    
                list_product[size] = create_product();
                size++;
                verifying_list(list_product, &size);
                printf("Deseja criar produtos(0), ler arquivos(1), ou encerrar(2)? Digite o respectivo numero: ");
                scanf("%d", &confirm);
                bubble_sort(list_product, &size, alphabet);

                if(confirm != 0) {
                    break;
                }
            }

            printf("Escreva o nome do arquivo");
            scanf("%s", filename);
            strcat(filename, ".csv");
            printf("O nome do arquivo ficou: %s\n", filename);
        }

        if (confirm == 1) {
            printf("Escreva o nome do arquivo");
            scanf("%s", filename);
            strcat(filename, ".csv");
            read_file(filename);
        }

        if (confirm == 2) {
            play = false;
        }
    }

    return 0;
}