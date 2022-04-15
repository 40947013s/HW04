#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

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

int main(int argc, char *argv[])
{
    FILE *pFile = NULL;
    FILE *pFile2 = NULL;

    if(argc != 2)
    {
        printf("Wrong file numbers input.\n");
        return 0;
    }
    
    if((pFile = fopen(argv[1], "rb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    
    if((pFile2 = fopen("maldives_gray.bmp", "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    
    sBmpHeader	header;
    fread(&header, sizeof(header), 1, pFile);
    fwrite(&header, sizeof(header), 1, pFile2);

    while(!feof(pFile))
    {
        uint8_t	original[999] = {0};
        uint8_t modified[999] = {0};        
        size_t count = fread(original, 1, 999, pFile);

        for(size_t i = 0;i < count; i+=3)
        {
            uint8_t gray = 0.299 * original[i+2] + 0.587 * original[i+1] + 0.114 * original[i];
            
            for( size_t j = 0; j < 3 ; j++ )
            {
                modified[i+j] = gray;
            }
        }
        
        fwrite( modified, count, 1, pFile2 );
        
    }
    
                
    fclose( pFile );
    fclose( pFile2 );
    
    return 0;
}