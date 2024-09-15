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
int atoi(const char *str);
void matrix_product(size_t row1, size_t col1, const double **mat1,
    size_t row2, size_t col2, const double **mat2, double **res);
void matrix_transpose(size_t x, size_t y, const double **mat,
		double **res);
void matrix_addition(size_t row, size_t col, const double **mat1,
		const double **mat2, double **res);

#endif
