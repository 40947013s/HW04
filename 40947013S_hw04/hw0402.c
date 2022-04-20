#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

struct option long_options[] = 
{  
    {"i", 1, NULL, 'i'},
    {"n", 1, NULL, 'n'},
    {"p", 1, NULL, 'p'},
    {0, 0, 0, 0},  
}; 

char *deal(char *s)
{
    char *p = s;
    int i = 0;
	while(p[i] != '\0') 
    {
		if(p[i] == ' ') 
        {
			for(int j = i; j < strlen(p); j++) 
				p[j] = p[j+1];
			continue;
		}
        else p[i] = tolower(p[i]);
        i++;
	}
    return p;
}

char *lower(char *s)
{
    char p[strlen(s)+1], *str;
    int i = 0;
	for(int i = 0; i < strlen(s); i++)
		p[i] = tolower(s[i]);
    p[strlen(s)] = 0;
    str = p;
    return str;
}

int count_item(char *filename)
{
    FILE *input; 
    char line[600];
    if((input = fopen(filename, "r")) == NULL)
    {
        printf("Could not find file.\n");
        exit(0);
    }
    fgets(line, 600, input);
    fgets(line, 600, input);
    int item = 0, max = (strlen(line)-1)/2;    
    while(fgets(line, 600, input))
    {
        if(line[0] == '|')
        {
            int count = 0;
            char *token = strtok(line, "|");
            while(token)
            {
                count += (strlen(token)+1)/2;
                if(count > max) break;
                item++;
                token = strtok(NULL, "|");
            }   
        }
    }
    return item;
    //fcolse(input);
}

void store_item(char *filename, char ***store, int *value, int size)
{
    FILE *input = fopen(filename, "r"); 
    char line[600];
    fgets(line, 600, input);
    fgets(line, 600, input);
    int item = 0, max = (strlen(line)-1)/2;
    *store = calloc(size, sizeof(char*));
    
    while(fgets(line, 600, input))
    {
        if(line[0] == '|')
        {
            int count = 0;
            char *token = strtok(line, "|");
            while(token)
            {
                count += (strlen(token)+1)/2;
                if(count > max) break;
                value[item] = (strlen(token)+1)/2;
                char *str = deal(token);
                char *str_copy = calloc(strlen(str)+1, sizeof(char));                
                for(int i = 0; i < strlen(str); i++)
                    str_copy[i] = str[i];
                *(*store+item) = str_copy;
                item++;
                token = strtok(NULL, "|");
            }           
        }
    }
}

int choice(int c)
{
    if(c <= 8) return 8;
    else if(c <= 16) return 16;
    else if(c <= 24) return 24;
    else if(c <= 32) return 32;
    else return 64;
}

void write_h(char *filename, char *struct_name, char **store, int *value, int size)
{
    FILE *output = NULL;
    char h[128];
    sprintf(h, "%s.h", filename);
    if((output = fopen(h, "w")) == NULL)
    {
        printf("File fail to be opened.\n");
        exit(0);
    }
    fprintf(output, "#pragma once\n\n#include <stdint.h>\n\ntypedef struct _s%s\n{\n", struct_name);
    for(int i = 0; i < size; i++)
    {
        if(choice(value[i]) != 24)
            fprintf(output, "    uint%d_t %s;\n", choice(value[i]), store[i]);
        else
            fprintf(output, "    uint8_t %s[3];\n", store[i]);
    }
    fprintf(output, "}%s;\n\n", struct_name);
    fprintf(output, "%s * %s_init( void );\n", struct_name, lower(struct_name));
    fprintf(output, "void %s_free( %s * );\n", lower(struct_name), struct_name);
    fprintf(output, "int %s_encode( void *, const %s * );\n", lower(struct_name), struct_name);
    fprintf(output, "int %s_decode( const void *, %s * );\n", lower(struct_name), struct_name);

}

int main(int argc, char *argv[])
{
    char *txt_name, *struct_name = NULL, *file_name = NULL, c;
    while((c = getopt_long(argc, argv, "i:n:p:", long_options, 0)) != -1)
    {
        switch(c)
        {
            case 'i':
                if(strstr(optarg, ".txt"))
                    txt_name = optarg; 
                break;
            case 'n':
                struct_name = optarg; break;
            case 'p':
                printf("%s", optarg);
                file_name = optarg; break; 
            default : break;
        }
    }
    if(!struct_name) struct_name = "Test\0";
    if(!file_name) file_name = "test\0";
    char **store = NULL; int *value;
    int size = count_item(txt_name);
    store_item(txt_name, &store, value, size);
    //for(int i = 0; i < size; i++)
        //printf("%d\n", value[i]);
    write_h(file_name, struct_name, store, value, size);
}