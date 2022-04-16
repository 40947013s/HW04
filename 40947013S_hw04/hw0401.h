#ifndef HW0401_H_INCLUDE
#define HW0401_H_INCLUDE

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct _sBmpHeader
{
    char		bm[2];
    uint32_t	size;
    uint32_t	reserve;
    uint32_t	offset;
    uint32_t	header_size;
    uint32_t	width;
    uint32_t	height;
    uint16_t	planes;
    uint16_t	bpp;
    uint32_t	compression;
    uint32_t	bitmap_size;
    uint32_t	hres;
    uint32_t	vres;
    uint32_t	used;
    uint32_t	important;
}__attribute__ ((__packed__));

typedef struct _sBmpHeader sBmpHeader;

bool is_bmp(sBmpHeader header);
void twice(char *ori_name, char *big_name);
void gray(char *big_name, char *gray_name);
void generate(char *gray_name, char *name1, char *name2);
void overlap(char *name1, char*name2, char *mix);
void name(char *input, char *layer1, char *layer2, char *overlap);

#endif