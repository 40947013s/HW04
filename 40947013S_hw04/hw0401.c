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

bool is_bmp(sBmpHeader header)
{
    if(header.bm[0]!= 'B' || header.bm[1]!= 'M')
    {
        printf("This is not a bmp file!\n");
        return false;
    }
    return true;
}
 
void twice(char *ori_name, char *big_name)
{
    sBmpHeader header;
    FILE *ori_file = NULL, *big_file = NULL;    
    if((ori_file = fopen(ori_name, "rb")) == NULL)
    {
        printf("File could not be opened!\n");
        exit(0);
    }
    
    if((big_file = fopen(big_name, "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        exit(0);
    }
    
    fread(&header, sizeof(sBmpHeader), 1, ori_file);
    if(!is_bmp(header)) exit(0);
    int old_w = header.width, old_h = header.height;  
    int new_w = 2*old_w, new_h = 2*old_h; 
    header.size = 54 + new_h*(new_w*3+new_w%4);
    header.width = new_w;
    header.height = new_h; 
    fwrite(&header, sizeof(sBmpHeader), 1, big_file);
    
    int x, y;
    int p_times = old_h*(old_w*3+old_w%4), n_times = new_h*(new_w*3+new_w%4);
    char *p_row, *n_row;
    uint8_t *p_color = (uint8_t*)malloc(p_times);
    uint8_t *n_color = (uint8_t*)malloc(n_times);
    memset(p_color, 0, p_times);
    memset(n_color, 0, n_times);
    fread(p_color, p_times, 1, ori_file);
    
    for(int i = 0; i < new_h; i++)
    {
        y = i * old_h/new_h;
        n_row = n_color + i*(new_w*3+new_w%4);
        p_row = p_color + y*(old_w*3+old_w%4);
        for(int j = 0; j < new_w; j++)
        {
            x = j*old_w/new_w;
            strncpy(n_row+j*3, p_row+x*3, 3);
        }
    }    
    fwrite(n_color, n_times, 1, big_file); 
    free(n_color); free(p_color); 
    fclose(ori_file); fclose(big_file);
}

void gray(char *big_name, char *gray_name)
{
    sBmpHeader header;
    FILE *big_file = NULL, *gray_file = NULL;    
    if((big_file = fopen(big_name, "rb")) == NULL)
    {
        printf("File could not be opened!\n");
        exit(0);
    }
    if((gray_file = fopen(gray_name, "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        exit(0);
    }
    fread(&header, sizeof(sBmpHeader), 1, big_file);
    fwrite(&header, sizeof(sBmpHeader), 1, gray_file);
    int size = header.width*3 + header.height%4;
    uint8_t *color = (uint8_t*)malloc(size);
    for(int i = 0; i < header.height; i++)
    {
        fread(color, size, 1, big_file);
        for(int j = 0; j < size; j+=3)
        {
            uint8_t gray = 0.299*color[j+2] + 0.587*color[j+1] + 0.114*color[j];            
            for(int k = 0; k < 3; k++)
                color[j+k] = gray;
        }
        fwrite(color, size, 1, gray_file);
    }    
    fclose(big_file); fclose(gray_file);
}

void generate(char *gray_name, char *name1, char *name2)
{
    sBmpHeader header;
    FILE *gray_file = NULL, *layer1 = NULL , *layer2 = NULL;
    if((gray_file = fopen(gray_name, "rb")) == NULL)
    {
        printf("File could not be opened!\n");
        exit(0);
    }
      
    if((layer1 = fopen(name1, "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        exit(0);
    }
    if((layer2 = fopen(name2, "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        exit(0);
    }
    
    fread(&header, sizeof(sBmpHeader), 1, gray_file);
    fwrite(&header, sizeof(sBmpHeader), 1, layer1);
    fwrite(&header, sizeof(sBmpHeader), 1, layer2);
    if(!is_bmp(header)) exit(0);
    int size = header.width*3 + header.height%4;
    uint8_t *p1_color = (uint8_t*)malloc(size);
    uint8_t *p2_color = (uint8_t*)malloc(size);
    uint8_t *n1_color = (uint8_t*)malloc(size);
    uint8_t *n2_color = (uint8_t*)malloc(size);
    uint8_t *n3_color = (uint8_t*)malloc(size);
    uint8_t *n4_color = (uint8_t*)malloc(size);
    
    for(int i = 0; i < header.height; i+=2)
    {
        fread(p1_color, size, 1, gray_file);
        fread(p2_color, size, 1, gray_file);   
        
        for(int j = 0; j < size; j+=6)
        {
            if(p1_color[j] > 250)
            {
                for(int k = 0; k < 3; k++)
                {
                    n1_color[j+k] = p1_color[j+k];
                    n2_color[j+k] = 255;
                    n3_color[j+k] = p1_color[j+k];
                    n4_color[j+k] = 255;     
                }
                for(int k = 3; k < 6; k++)
                {
                    n1_color[j+k] = 255;
                    n2_color[j+k] = p1_color[j+k];
                    n3_color[j+k] = 255;
                    n4_color[j+k] = p1_color[j+k];
                }
            }
            else
            {
                for(int k = 0; k < 3; k++)
                {
                    n1_color[j+k] = 255;
                    n2_color[j+k] = p1_color[j+k];
                    n3_color[j+k] = p1_color[j+k];
                    n4_color[j+k] = 255;     
                }
                for(int k = 3; k < 6; k++)
                {
                    n1_color[j+k] = p1_color[j+k];
                    n2_color[j+k] = 255;
                    n3_color[j+k] = 255;
                    n4_color[j+k] = p1_color[j+k];
                }
            }
        }
        
        fwrite(n1_color, size, 1, layer1);
        fwrite(n2_color, size, 1, layer1);
        fwrite(n3_color, size, 1, layer2);
        fwrite(n4_color, size, 1, layer2);
        
    }
    fclose(gray_file); fclose(layer1); fclose(layer2);     
}

void overlap(char *name1, char*name2, char *mix)
{
    FILE *layer1 = NULL, *layer2 = NULL, *merge = NULL;
    sBmpHeader header;
    if((layer1 = fopen(name1, "rb")) == NULL)
    {
        printf("File could not be opened!\n");
        exit(0);
    }
    if((layer2 = fopen(name2, "rb")) == NULL)
    {
        printf("File could not be opened!\n");
        exit(0);
    }
    if((merge = fopen(mix, "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        exit(0);
    }
    
    fread(&header, sizeof(sBmpHeader), 1, layer1);
    fread(&header, sizeof(sBmpHeader), 1, layer2);
    fwrite(&header, sizeof(sBmpHeader), 1, merge);
    int size = header.width*3 + header.height%4;
    uint8_t *l1_color = (uint8_t*)malloc(size);
    uint8_t *l2_color = (uint8_t*)malloc(size);
    uint8_t *color = (uint8_t*)malloc(size);
    for(int i = 0; i < header.height; i++)
    {
        fread(l1_color, size, 1, layer1);
        fread(l2_color, size, 1, layer2);
        for(int j = 0; j < size; j+=3)
        {      
            uint8_t c = l1_color[j] <= l2_color[j] ? l1_color[j] : l2_color[j]; 
            for(int k = 0; k < 3 ; k++)
                color[j+k] = c;
        }
        fwrite(color, size, 1, merge);
    }    
    fclose(layer1); fclose(layer2); fclose(merge);    
}

void name(char *input, char *layer1, char *layer2, char *overlap)
{
    if(!strstr(input, ".bmp"))
    {
        printf("Wrong file!\n");
        exit(0);
    }
    char base[128];
    for(int i = 0; i < strlen(input)-4; i++)
        base[i] = input[i];

    sprintf(layer1, "%s_layer1.bmp", base);    
    sprintf(layer2, "%s_layer2.bmp", base);    
    sprintf(overlap, "%s_overlap.bmp", base);   
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Wrong file numbers input.\n");
        return 0;
    }

    char l1_name[128], l2_name[128], o_name[128];
    name(argv[1], l1_name, l2_name, o_name);
    printf("%s", l1_name);
    twice(argv[1], "enlarge.bmp");    
    gray("enlarge.bmp", "gray.bmp");    
    remove("enlarge.bmp");
    generate("gray.bmp", l1_name, l2_name);
    remove("gray.bmp");
    overlap(l1_name, l2_name, o_name);
    
    return 0; 
}
