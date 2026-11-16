#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product_functions.h"
#include "data_functions.h"

void string_product (Product *list_product, int size, StringProduct *converted_product) {

    for (int i = 0; i < size; i++) {
        strcpy(converted_product[i].id, list_product[i].id);
        strcpy(converted_product[i].product_name, list_product[i].product_name);
        strcpy(converted_product[i].category, list_product[i].category);
        snprintf(converted_product[i].price, sizeof(converted_product[i].price), "%.2f", list_product[i].price);
        snprintf(converted_product[i].quantity, sizeof(converted_product[i].quantity), "%d", list_product[i].quantity);
        strcpy(converted_product[i].supplier, list_product[i].supplier);
    }
}