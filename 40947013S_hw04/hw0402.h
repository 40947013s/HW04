#ifndef HW0402_H_INCLUDE
#define HW0402_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

char *deal(char *s);
char *lower(char *s);
int count_item(char *filename);
void store_item(char *filename, char ***store, int *value, int size);
int choice(int c);
void write_h(char *filename, char *struct_name, char **store, int *value, int size);
void write_c(char *filename, char *struct_name, char **store, int *value, int size);

#endif