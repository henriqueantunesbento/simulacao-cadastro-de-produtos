#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H

void write_file(char *filename, Product *list_product, int size);
void read_file(char *filename);  
void filter_product(char *filename);
void edit_file(char *filename);

#endif