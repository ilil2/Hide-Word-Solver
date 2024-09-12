#ifndef __LIB_H__
#define __LIB_H__

#include <stddef.h>

size_t strlen(const char *str);
char char_to_upper(char c);
void to_upper(char *str);
char itoc(char i);
size_t intlen(int i);
void itoa(int i, char *str);
char strcomp(const char *str1, const char *str2);
void strconcat(char *str1, const char *str2);
void ctoa(char c, char *str);
void strcopy(char *dest, const char *src);
void itox(int i, char *hexa);
void xtoRGB(const char hexa[6], int* rgb[3]);
int xtoi(const char *hexa);
void matrix_product(size_t row1, size_t col1, double mat1[row1][col1],
    size_t row2,size_t col2, double mat2[row2][col2], double res[row1][col2]);

#endif
