#include <stdio.h>
#include <string.h>
#include "product_functions.h"

Product create_product() {

    Product product;
    printf("Digite o nome do produto (para nomes compostos separe o nome com '_'): ");
    scanf("%s", product.product_name);
    printf("O nome do produto ficou: %s\n", product.product_name);

    printf("Digite o nome da categoria: ");
    scanf("%s", product.category);
    printf("A categoria ficou: %s\n", product.category);

    printf("Digite o preco: ");
    scanf("%f", &product.price);
    printf("O preco ficou: %.2f\n", product.price);

    printf("Digite a quantidade: ");
    scanf("%d", &product.quantity);
    printf("A quantidade ficou: %d\n", product.quantity);

    printf("Digite o nome do fornecedor: ");
    scanf("%s", product.supplier);
    printf("O nome do fornecedor ficou: %s\n", product.supplier);
    int j = 0, k = 0, l = 0;  

    for (int i = 0; i <= 11; i++) {

        if (i <= 2) {
            product.id[i] = product.product_name[j];
            j++;
        }

        if (i == 3) {
            product.id[i] = '-';
        }

        if (i >= 4 && i <= 6) {
            product.id[i] = product.category[k];
            k++;
        }

        if (i == 7) {
            product.id[i] = '-';
        }

        if (i >= 8 && i <= 10) {
            product.id[i] = product.supplier[l];
            l++;
        }

        if (i == 11) {
            product.id[i] = '\0';
        }
    }

    return product;

}
