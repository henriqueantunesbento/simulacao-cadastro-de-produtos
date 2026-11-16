
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "product_functions.h"
#include "list_functions.h"

void verifying_list(Product *list_product, int *size_list) {
    for (int i = 1; i < *size_list; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (strcmp(list_product[i].id, list_product[j].id) == 0) {
                list_product[j].quantity += list_product[i].quantity;

                for (int k = i + 1; k < *size_list; k++) {
                    list_product[k - 1] = list_product[k];
                }
                (*size_list)--;

                i--;             
                break;            
            }
        }
    }
}


void bubble_sort(Product *list_product, int *size_list, char *alphabet) {

    if (*size_list < 2) {
        return; 
    }

    bool finish_bubble = false;

    char ordenation[50];
    printf("Escolha a ordenação (pode ser de a-z, z-a, maior_preco ou menor_preco): ");
    scanf("%s", ordenation);

    if (strcmp(ordenation, "a-z") == 0) {
        while (finish_bubble != true) {

            bool trade = false;
            int j = 0;
            int k = 1;
            int j_char = 0;
            int k_char = 0;
            int i_alpha = 0;
            int false_account = 0;
            Product save_product;

            while (trade == false && k < *size_list) {

                // Procura a posição da letra da palavra 1
                int char_position_j = 0;
                while (alphabet[i_alpha] != '\0' &&  list_product[j].product_name[j_char] != alphabet[i_alpha]) {
                    i_alpha++;
                    if (list_product[j].product_name[j_char] == alphabet[i_alpha]) {
                        char_position_j = i_alpha;
                        i_alpha = 0;
                        break;
                    }
                }

                if (list_product[j].product_name[j_char] == '\0') {
                    char_position_j = -1; 
                }
                
                // Procura a posição da letra da palavra 2
                int char_position_k = 0;
                while (alphabet[i_alpha] != '\0' &&  list_product[k].product_name[k_char] != alphabet[i_alpha]) {
                    i_alpha++;

                    if (list_product[k].product_name[k_char] == alphabet[i_alpha]) {
                        char_position_k = i_alpha;
                        i_alpha = 0;
                        break;
                    }
                    
                }

                if (list_product[k].product_name[k_char] == '\0') {
                    char_position_k = -1;  
                }


                // Se a primeira letra da primeira palavra estiver em um índice maior que a da segunda palavra, elas trocam de posição

                if (char_position_j > char_position_k) {
                    save_product = list_product[j];
                    list_product[j] = list_product[k];
                    list_product[k] = save_product;
                    trade = true;
                    false_account = 0;
                } else {
                    if (char_position_j == char_position_k) {
                            if (list_product[j].product_name[j_char] == '\0') {
                                // palavras iguais até o fim: segue para o próximo par
                                j++; 
                                k++;
                                j_char = 0; 
                                k_char = 0;
                                false_account++; 
                            } else {
                                j_char++;
                                k_char++;
                                i_alpha = 0;
                            }

                    } else {    
                        j++;
                        k++;
                        j_char = 0; 
                        k_char = 0;
                        i_alpha = 0;
                        false_account++;
                    }
                }
                if (false_account == *size_list - 1) {
                    finish_bubble = true;
                    break;
                }
            }    
        }
    } else {
        if (strcmp(ordenation, "z-a") == 0) {
                    while (finish_bubble != true) {

            bool trade = false;
            int j = 0;
            int k = 1;
            int j_char = 0;
            int k_char = 0;
            int i_alpha = 0;
            int false_account = 0;
            Product save_product;

            while (trade == false && k < *size_list) {

                // Procura a posição da letra da palavra 1
                int char_position_j = 0;
                while (alphabet[i_alpha] != '\0' &&  list_product[j].product_name[j_char] != alphabet[i_alpha]) {
                    i_alpha++;
                    if (list_product[j].product_name[j_char] == alphabet[i_alpha]) {
                        char_position_j = i_alpha;
                        i_alpha = 0;
                        break;
                    }
                }
                
                // Procura a posição da letra da palavra 2
                int char_position_k = 0;
                while (alphabet[i_alpha] != '\0' &&  list_product[k].product_name[k_char] != alphabet[i_alpha]) {
                    i_alpha++;

                    if (list_product[k].product_name[k_char] == alphabet[i_alpha]) {
                        char_position_k = i_alpha;
                        i_alpha = 0;
                        break;
                    }
                    
                }

                // Se a primeira letra da primeira palavra estiver em um índice menor que a da segunda palavra, elas trocam de posição

                if (char_position_j < char_position_k) {
                    save_product = list_product[j];
                    list_product[j] = list_product[k];
                    list_product[k] = save_product;
                    trade = true;
                    false_account = 0;
                } else {
                    if (char_position_j == char_position_k) {
                            if (list_product[j].product_name[j_char] == '\0') {
                                // palavras iguais até o fim: segue para o próximo par
                                j++; 
                                k++;
                                j_char = 0; 
                                k_char = 0;
                                false_account++; 
                            } else {
                                j_char++;
                                k_char++;
                                i_alpha = 0;
                            }

                    } else {    
                        j++;
                        k++;
                        j_char = 0; 
                        k_char = 0;
                        i_alpha = 0;
                        false_account++;
                    }
                }
                if (false_account == *size_list - 1) {
                    finish_bubble = true;
                    break;
                }
            }    
        }
        } else {
            if (strcmp(ordenation, "menor_preco") == 0) {
                        while (finish_bubble != true) {

                            bool trade = false;
                            int j = 0;
                            int k = 1;
                            int false_account = 0;
                            Product save_product;

                            while (trade == false && k < *size_list) {

                                // Compara o preco de produto 1 com produto 2, e se produto 1 for maior que produto 2 eles trocam de posicao

                                if (list_product[j].price > list_product[k].price) {
                                    save_product = list_product[j];
                                    list_product[j] = list_product[k];
                                    list_product[k] = save_product;
                                    trade = true;
                                    false_account = 0;
                                } else {
                                        j++;
                                        k++;
                                        false_account++;
                                    }
                                }
                                if (false_account == *size_list - 1) {
                                    finish_bubble = true;
                                    break;
                                }
                            }    
            } else {
                if (strcmp(ordenation, "maior_preco") == 0) {
                                            while (finish_bubble != true) {

                            bool trade = false;
                            int j = 0;
                            int k = 1;
                            int false_account = 0;
                            Product save_product;

                            while (trade == false && k < *size_list) {

                                // Compara o preco de produto 1 com produto 2, e se produto 1 for menor que produto 2 eles trocam de posicao

                                if (list_product[j].price < list_product[k].price) {
                                    save_product = list_product[j];
                                    list_product[j] = list_product[k];
                                    list_product[k] = save_product;
                                    trade = true;
                                    false_account = 0;
                                } else {
                                        j++;
                                        k++;
                                        false_account++;
                                    }
                                }
                                if (false_account == *size_list - 1) {
                                    finish_bubble = true;
                                    break;
                                }
                            }
                }
        }
        
    }

 }
}