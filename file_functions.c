#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product_functions.h"
#include "data_functions.h"
#include "list_functions.h"
#include "file_functions.h"

void write_file(char *filename, Product *list_product, int size) {

    StringProduct converted_product[MAX_PRODUCTS];
    string_product(list_product, size, converted_product);

    FILE *fp = fopen(filename, "w");

    if(fp == NULL) {
        printf("Nao ha dados para escrever o arquivo");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
            converted_product[i].id,
            converted_product[i].product_name,
            converted_product[i].category,
            converted_product[i].price,
            converted_product[i].quantity,
            converted_product[i].supplier);
    }

    fclose(fp);
}

void edit_file(char *filename) {

    char action[10];
    printf("Deseja alterar ou inserir um produto?\n");
    scanf("%s", &action);

    if (strcmp(action, "alterar") == 0) {
        FILE *fp = fopen(filename, "r+");
        
        if(fp == NULL) {
            printf("O arquivo nao foi encontrado ou esta vazio.");
            return;
        }

        char id_target[12];
        printf("Digite o id do produto que deseja alterar: ");
        scanf("%s", &id_target);
        printf("O id digitado foi: %s", id_target); 

        char line[300];
        int target_field;

        printf("Digite o atributo que deseja alterar (1 para nome, 2 para categoria, 3 para preco, 4 para a quantidade, e 5 para fornecedor): ");
        scanf("%d", &target_field);

        // novo valor, variaveis auxiliares e lista que guarda as linhas do arquivo
        char new_value[50];
        printf("Digite o novo valor: ");
        scanf("%s", new_value);

        char attribute[50];
        char new_line[300];
        char lines[MAX_PRODUCTS][300];
        int count = 0;
        int found = 0;
        
        while(fgets(line, sizeof(line), fp) != NULL && count < MAX_PRODUCTS) {

            int j = 0;
            int field = 0;
            int match = 0;
            new_line[0] = '\0';

            for(int i = 0; line[i] != '\0'; i++) {
                
                if(line[i] == ',' || line[i] == '\n') {
                    attribute[j] = '\0';

                    if (field == 0) {
                        if (strcmp(attribute, id_target) == 0) {
                            match = 1;
                            found = 1;
                        }
                    }

                    if (match == 1 && field == target_field) {
                        strcat(new_line, new_value);
                    }
                    else {
                        strcat(new_line, attribute);
                    }

                    if (line[i] == ',') {
                        strcat(new_line, ",");
                    }
                    else {
                        strcat(new_line, "\n");
                    }

                    field++;
                    j = 0;
                }
                else {
                    attribute[j] = line[i];
                    j++;
                }
            }

            strcpy(lines[count], new_line);
            count++;
        }

        fclose(fp);

        if (found == 0) {
            printf("Produto nao encontrado.\n");
            return;
        }

        // cria um arquivo de previa com as alteracoes feitas
        char filename_preview[40];
        strcpy(filename_preview, "(previvew_)");
        strcat(filename_preview, filename);

        fp = fopen(filename_preview, "w");

        for (int i = 0; i < count; i++) {
            fprintf(fp, "%s", lines[i]);
        }

        fclose(fp);
        printf("Criado um arquivo de previa do produto, confira as informacoes.\n");
        read_file(filename_preview);

        // confirma se esta correto e, se estiver, sobrescreve o arquivo antigo
        char confirm[4];
        printf("\nO arquivo esta correto? Digite sim ou nao: ");
        scanf("%s", confirm);

        if (strcmp(confirm, "sim") == 0) {
            fp = fopen(filename, "w");

            for (int i = 0; i < count; i++) {
                fprintf(fp, "%s", lines[i]);
            }

            fclose(fp);
            printf("Arquivo atualizado com sucesso.\n");
        }
        else {
            printf("Alteracoes descartadas, o arquivo original foi mantido.\n");
        }

        remove(filename_preview);
    }

    if (strcmp(action, "inserir") == 0) {
 
        printf("Crie novo produto (se o produto ja estiver na lista, vai somar a quantidade)\n");
        
        // loop onde o usuario cria a lista de produtos nova
        char confirm[4];
        Product new_products[MAX_PRODUCTS];
        int new_size = 0;

        printf("Deseja criar produtos? Digite sim ou nao: ");
        scanf("%s", confirm);

        while (strcmp(confirm, "sim") == 0 && new_size < MAX_PRODUCTS) {
            new_products[new_size] = create_product();
            new_size++;
            verifying_list(new_products, &new_size);

            printf("Deseja criar produtos? Digite sim ou nao: ");
            scanf("%s", confirm);
        }

        FILE *fp = fopen(filename, "r");
        
        if(fp == NULL) {
            printf("O arquivo nao foi encontrado ou esta vazio.");
            return;
        }

        // le os produtos que ja estao no arquivo csv (tudo como string)
        StringProduct file_products[MAX_PRODUCTS];
        int file_size = 0;
        char line[300];
        char attribute[50];

        while (fgets(line, sizeof(line), fp) != NULL && file_size < MAX_PRODUCTS) {

            int j = 0;
            int field = 0;

            for (int i = 0; line[i] != '\0'; i++) {

                if (line[i] == ',' || line[i] == '\n') {
                    attribute[j] = '\0';

                    if (field == 0) {
                        strcpy(file_products[file_size].id, attribute);
                    }

                    if (field == 1) {
                        strcpy(file_products[file_size].product_name, attribute);
                    }

                    if (field == 2) {
                        strcpy(file_products[file_size].category, attribute);
                    }

                    if (field == 3) {
                        strcpy(file_products[file_size].price, attribute);
                    }

                    if (field == 4) {
                        strcpy(file_products[file_size].quantity, attribute);
                    }

                    if (field == 5) {
                        strcpy(file_products[file_size].supplier, attribute);
                    }

                    field++;
                    j = 0;
                }
                else {
                    attribute[j] = line[i];
                    j++;
                }
            }

            file_size++;
        }

        fclose(fp);

        // converte os produtos novos para string, para poder compara-los com os do arquivo
        StringProduct converted_new[MAX_PRODUCTS];
        string_product(new_products, new_size, converted_new);

        // compara o id de cada produto novo com o id de cada produto do arquivo
        for (int i = 0; i < new_size; i++) {

            int found = 0;

            for (int k = 0; k < file_size; k++) {

                // se, e somente se o id for igual, soma a quantidade
                if (strcmp(converted_new[i].id, file_products[k].id) == 0) {
                    int sum = atoi(file_products[k].quantity) + new_products[i].quantity;
                    snprintf(file_products[k].quantity, sizeof(file_products[k].quantity), "%d", sum);
                    found = 1;
                    break;
                }
            }

            // se o id nao existir, adiciona como produto novo
            if (found == 0 && file_size < MAX_PRODUCTS) {
                file_products[file_size] = converted_new[i];
                file_size++;
            }
        }

        // volta os dados para Product para poder fazer o bubble_sort
        Product sorted_products[MAX_PRODUCTS];

        for (int i = 0; i < file_size; i++) {
            strcpy(sorted_products[i].id, file_products[i].id);
            strcpy(sorted_products[i].product_name, file_products[i].product_name);
            strcpy(sorted_products[i].category, file_products[i].category);
            sorted_products[i].price = atof(file_products[i].price);
            sorted_products[i].quantity = atoi(file_products[i].quantity);
            strcpy(sorted_products[i].supplier, file_products[i].supplier);
        }

        char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
        bubble_sort(sorted_products, &file_size, alphabet);

        // cria um arquivo de previa com as alteracoes feitas
        char filename_preview[40];
        strcpy(filename_preview, "(previvew_)");
        strcat(filename_preview, filename);

        write_file(filename_preview, sorted_products, file_size);
        printf("Criado um arquivo de previa da lista, confira as informacoes.\n");
        read_file(filename_preview);

        // confirma se esta correto e, se estiver, sobrescreve o arquivo antigo
        printf("\nO arquivo esta correto? Digite sim ou nao: ");
        scanf("%s", confirm);

        if (strcmp(confirm, "sim") == 0) {
            write_file(filename, sorted_products, file_size);
            printf("Arquivo atualizado com sucesso.\n");
        }
        else {
            printf("Alteracoes descartadas, o arquivo original foi mantido.\n");
        }

        remove(filename_preview);
    }
}

void filter_product(char *filename) {

    FILE *fp = fopen(filename, "r");

    if(fp == NULL) {
        printf("O arquivo nao foi encontrado ou esta vazio.");
        return;
    }

    int filter_field;
    printf("Deseja filtrar por nome ou por categoria? (1 para nome, 2 para categoria): ");
    scanf("%d", &filter_field);

    char search[50];
    printf("Digite o que deseja buscar: ");
    scanf("%s", search);

    char line[300];
    char attribute[50];
    char id[12];
    char product_name[50];
    char category[50];
    char price[20];
    char quantity[20];
    char supplier[50];
    int found = 0;

    printf("----------------------------------------------------\n");
    printf("| ID | Produto | Categoria | Preco (R$) | Quantidade | Fornecedor |\n");
    printf("----------------------------------------------------\n");
    while (fgets(line, sizeof(line), fp) != NULL) {
        int j = 0;
        int field = 0;
        for (int i = 0; line[i] != '\0'; i++) {

            if (line[i] == ',' || line[i] == '\n') {
                attribute[j] = '\0';

                if (field == 0) {
                    strcpy(id, attribute);
                }

                if (field == 1) {
                    strcpy(product_name, attribute);
                }

                if (field == 2) {
                    strcpy(category, attribute);
                }

                if (field == 3) {
                    strcpy(price, attribute);
                }

                if (field == 4) {
                    strcpy(quantity, attribute);
                }

                if (field == 5) {
                    strcpy(supplier, attribute);
                }

                field++;
                j = 0;
            }
            else {
                attribute[j] = line[i];
                j++;
            }
        }

        // so exibe a linha se o nome ou a categoria (conforme a escolha) conter o que foi buscado
        if ((filter_field == 1 && strstr(product_name, search) != NULL) || (filter_field == 2 && strstr(category, search) != NULL)) {
            printf("| %s | %s | %s | %s | %s | %s |\n", id, product_name, category, price, quantity, supplier);
            found = 1;
        }
    }

    if (found == 0) {
        printf("Nenhum produto encontrado.\n");
    }

    printf("----------------------------------------------------");

    fclose(fp);
}

void read_file(char *filename) {

    FILE *fp = fopen(filename, "r");

    if(fp == NULL) {
        printf("O arquivo nao foi encontrado ou esta vazio.");
        return;
    }   

    char line[300];
    char attribute[50];
    char option[10];

    printf("Deseja ver a tabela inteira ou filtrar a busca? Digite inteira ou filtrar: ");
    scanf("%s", option);

    if (strcmp(option, "filtrar") == 0) {
        filter_product(filename);
    }
    else {
        printf("----------------------------------------------------\n");
        printf("| ID | Produto | Categoria | Preco (R$) | Quantidade | Fornecedor |\n");
        printf("----------------------------------------------------\n");
        while (fgets(line, sizeof(line), fp) != NULL) {
            int j = 0;
            int field = 0;
            for (int i = 0; line[i] != '\0'; i++) {

                if (line[i] == ',' || line[i] == '\n') {
                    attribute[j] = '\0';

                    if (field == 0) {
                        printf("| %s ", attribute);
                    }

                    if (field == 1) {
                        printf("| %s ", attribute);
                    }

                    if (field == 2) {
                        printf("| %s ", attribute);
                    }

                    if (field == 3) {
                        printf("| %s ", attribute);
                    }

                    if (field == 4) {
                        printf("| %s ", attribute);
                    }

                    if (field == 5) {
                        printf("| %s |\n", attribute);
                    }

                    field++;
                    j = 0;
                }
                else {
                    attribute[j] = line[i];
                    j++;
                }
            }
            
        }

        printf("----------------------------------------------------");
    }

    fclose(fp);

    // pergunta se o usuario quer editar ou excluir o arquivo
    char action[10];
    printf("\nDeseja editar ou excluir o arquivo? Digite editar ou excluir: ");
    scanf("%s", action);

    if (strcmp(action, "editar") == 0) {
        edit_file(filename);
    }
    else {
        remove(filename);
        printf("Arquivo excluido com sucesso.\n");
    }
}

