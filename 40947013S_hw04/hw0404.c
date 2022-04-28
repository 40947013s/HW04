#include "hw0404.h"

int main()
{
    char *input = malloc(128);
    printf("Revise file name：");
    fgets(input, 128, stdin);
    input[strlen(input)-1] = 0;
    
    char *output = malloc(128);
    printf("Output file name：");
    fgets(output, 128, stdin);
    output[strlen(output)-1] = 0;
    
    FILE *fp = NULL, *out = NULL;    
    if((fp = fopen(input, "rb")) == NULL)
    {
        printf("File could not open.\n");
        return 0;
    }
    out = fopen(output, "wb");
    info *i0 = calloc(1, sizeof(info));
    fread(i0, 1, sizeof(info), fp);
    time(i0);
    
    attribute *i1 = calloc(1, sizeof(attribute));
    fread(i1, 1, sizeof(attribute), fp);
    //att(i1);
    
    judge *i2 = calloc(1, sizeof(judge));
    fread(i2, 1, sizeof(judge), fp);
    //jud(i2);
    
    capability *i3 = calloc(1, sizeof(capability));
    fread(i3, 1, sizeof(capability), fp);
    //cap(i3);
    
    performance *i4 = calloc(1, sizeof(performance));
    fread(i4, 1, sizeof(performance), fp);
    //per(i4);
    
    other *i5 = calloc(1, sizeof(other));
    fread(i5, 1, sizeof(other), fp);
    //oth(i5);

    body *i6 = calloc(1, sizeof(body));
    fread(i6, 1, sizeof(body), fp);
    b(i6, i0);
    
    fwrite(i0, 1, sizeof(info), out);
    fwrite(i1, 1, sizeof(attribute), out);
    fwrite(i2, 1, sizeof(judge), out);
    fwrite(i3, 1, sizeof(capability), out);
    fwrite(i4, 1, sizeof(performance), out);
    fwrite(i5, 1, sizeof(other), out);
    fwrite(i6, 1, sizeof(body), out);
    
    int count = 0;
    while(!feof(fp))
    {
        uint16_t p;
        fread(&p, 1, sizeof(p), fp);        
        fwrite(&p, 1, sizeof(p), out);
    }
    fclose(fp);
}