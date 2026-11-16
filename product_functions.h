#ifndef PRODUCT_FUNCTIONS_H
#define PRODUCT_FUNCTIONS_H
#define MAX_PRODUCTS 50

typedef struct {
    char id[12];
    char product_name[50];
    char category[50];
    float price;
    int quantity;
    char supplier[50];
} Product;

Product create_product();

#endif