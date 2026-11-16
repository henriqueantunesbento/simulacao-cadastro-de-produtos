#ifndef DATA_FUNCTIONS_H
#define DATA_FUNCTIONS_H

typedef struct {
    char id[12];
    char product_name[50];
    char category[50];
    char price[20];
    char quantity[20];
    char supplier[50];
} StringProduct;

void string_product (Product *list_product, int size, StringProduct *converted_product);

#endif