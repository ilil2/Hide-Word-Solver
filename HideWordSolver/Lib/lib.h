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
void matrix_product(size_t row1, size_t col1, float **mat1,
    size_t row2, size_t col2, float **mat2, float **res,
	size_t threads_nbr);
void matrix_product_t(size_t row1, size_t col1, float **mat1,
        size_t row2, size_t col2, float **mat2, float **res,
		char trans_nbr, size_t threads_nbr);
void matrix_transpose(size_t x, size_t y, float **mat,
		float **res);
void matrix_addition(size_t row, size_t col, float **mat1,
		float **mat2, float **res);
void matrix_shuffle(float **array, float **array2, int rows1,
	int rows2, int cols);
void shuffle(char array[], int n);
float max(float d1, float d2);

#endif
