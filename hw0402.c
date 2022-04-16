#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

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

/*bool is_bmp(sBmpHeader header)
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
    int new_w = 2 * old_w, new_h = 2 * old_h; 
    header.size = 54 + new_w*new_h*3;
    header.width = new_w;
    header.height = new_h;
 
    fwrite(&header, sizeof(sBmpHeader), 1, big_file);
    
    int x, y;
    int p_times = old_w*old_h*3, n_times = new_w*new_h*3;
    char *p_row, *n_row;
    char *p_color = (char*)malloc(p_times);
    char *n_color = (char*)malloc(n_times);
    fread(p_color, p_times, 1, ori_file);
    
    for(int i = 0; i < new_h; i++)
    {
        y = i * old_h/new_h;
        n_row = n_color + i*new_w*3;
        p_row = p_color + y*old_w*3;
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
    while(!feof(big_file))
    {
        uint8_t	ori[999] = {0}, mod[999] = {0};        
        int count = fread(ori, 1, 999, big_file);
        for(int i = 0;i < count; i+=3)
        {
            uint8_t gray = 0.299*ori[i+2] + 0.587*ori[i+1] + 0.114*ori[i];            
            for(int j = 0; j < 3 ; j++)
                mod[i+j] = gray;
        }        
        fwrite(mod, count, 1, gray_file);        
    }    
    
    fclose(big_file); fclose(gray_file);
}

void draw_white(uint8_t **color, int index)
{
    for(int i = index; i < index+3; i++)
    {
        color[0][i] = 0;
        color[1][i] = 255;
    }
    for(int i = index+3; i < index+6; i++)
    {
        color[0][i] = 255;
        color[1][i] = 0;
    }
}

void draw_layer(uint8_t **color, int index, uint8_t pixel, bool flag)
{
    for(int i = index; i < index+3; i++)
    {
        color[0][i] = flag ? pixel : 255;
        color[1][i] = !flag ? pixel : 255;
    }
    for(int i = index+3; i < index+6; i++)
    {
        color[0][i] = !flag ? pixel : 255;
        color[1][i] = flag ? pixel : 255;
    }
}

void draw(uint8_t **p_color, uint8_t **color, int width, bool flag)
{
    for(int i = 0; i < width; i+=6)
    {
        if(p_color[0][i] == 256)
            draw_white(color, i);
        else
            draw_layer(color, i, p_color[0][i], flag);
    }
}*/

/*void generate(char *gray_name, char *name1, char *name2)
{
    //sprintf(name1, "%s_layer1.bmp", name1);
    //sprintf(name2, "%s_layer2.bmp", name1);    
    
    sBmpHeader header;
    FILE *gray_file = NULL; 
    int *layer1 , *layer2;
    if((gray_file = fopen(gray_name, "rb")) == NULL)
    {
        printf("File could not be opened!\n");
        exit(0);
    }
      
    if((open(name1, O_WRONLY)) == -1)
    {
        printf("File could not be opened!\n");
        exit(0);
    }
    if((open(name2, O_WRONLY)) == -1)
    {
        printf("File could not be opened!\n");
        exit(0);
    }
    
    fread(&header, sizeof(sBmpHeader), 1, gray_file);
    if(!is_bmp(header)) exit(0);
    /*int size = header.width*3 + header.width%4;
    uint8_t **p_color = (uint8_t**)malloc(2*sizeof(uint8_t*));
    *p_color = (uint8_t*)malloc(size);
     uint8_t **n1_color = (uint8_t**)malloc(2*sizeof(uint8_t*));
    *n1_color = (uint8_t*)malloc(size);
    uint8_t **n2_color = (uint8_t**)malloc(2*sizeof(uint8_t*));
    *n2_color = (uint8_t*)malloc(size);
    /*for(int i = 0; i < header.height/2; i++)
    {
        fread(&p_color[i%2], size, 1, gray_file);
        fread(&p_color[(i+1)%2], size, 1, gray_file);
        draw(p_color, n1_color, size, 1);
        draw(p_color, n2_color, size, 0);
        fwrite(&n1_color[0], size, 1, layer1);
        fwrite(&n1_color[1], size, 1, layer1);
        fwrite(&n2_color[0], size, 1, layer2);
        fwrite(&n2_color[0], size, 1, layer2);
    }
    fclose(gray_file); fclose(layer1); fclose(layer2); 
    
}*/
 
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Wrong file numbers input.\n");
        return 0;
    }
    FILE *p = fopen("p.txt", "w");
    fwrite(argv[1], 3, 1, p);
    
    return 0; 
}