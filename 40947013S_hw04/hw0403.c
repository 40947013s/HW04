#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

#define NONE "\033[m"
#define RED "\033[0;32;31m"

int table[5] = 
{44, 84, 38, 51, 53};

char languages[5][31] = 
{ "C", "C++", "Java", "JS", "Rust" };

struct option long_options[] = 
{  
    {"linenum", 0, NULL, 'n'},
    {"color", 0, NULL, 'c'},
    {"language", 1, NULL, 'l'},
    {0, 0, 0, 0},  
}; 

char *deal(char *s)
{
    char *t = malloc(31);
    for(int i = 0; i < strlen(s); i++)
        if(s[i] == '~') t[i] = ' ';
    else t[i] = s[i];
    return t;
}

char *change_line(char *line)
{
    char new_one[1500];
    char *res = malloc(1500);    
    int count = 0;
    for(int i = 0; i < strlen(line)-1; i++)
    {
        if((line[i] == '(' || line[i] == '{' || line[i] == ')' || line[i] == '}') && line[i+1] != ' ')
        {
            new_one[count++] = ' ';            
            new_one[count++] = line[i];
            new_one[count++] = ' ';
        } 
        else if(line[i] == ';' && isalpha(line[i+1]))
        {
            new_one[count++] = line[i];
            new_one[count++] = ' ';
        }
        else new_one[count++] = line[i];
    }
    new_one[count++] = 0;    
    strncpy(res, new_one, strlen(new_one));
    return res;
}

void print_label(int _th, int max)
{
    if(_th == 1) printf(" %d", _th);
    else printf("%d", _th);
    for(int i = log10(_th); i < log10(max)+1; i++)
        printf(" ");
}

int quotation_count(char *s)
{
    int count = 0;
    for(int i = 0; i < strlen(s); i++)
        if(s[i] == '"') count++;
    return count;
}

int main(int argc, char *argv[])
{    
    FILE *fp = fopen("Keyword.txt", "r");
    if(argc == 1)
    {
        printf("Source code NULL.\n");
        return 0;
    }
    char c, *src = argv[argc-1]; 
    bool label = false, color = false; int pivot = 0;
    while((c = getopt_long(argc, argv, "ncl:", long_options, 0)) != -1)
    {
        switch(c)
        {
            case 'n':
                label = true; break;
            case 'c':
                color = true; break;
            case 'l':
                for(int i = 1; i < 21; i++)
                    if(strcmp(optarg, languages[i]) == 0)
                        pivot = i;                    
                break; 
            default : break;
        }
    }
    if(strcmp(src, languages[pivot]) == 0) pivot = 0;
    FILE *src_code = NULL;
    if((src_code = fopen(src, "r")) == NULL)
    {
        printf("Fail to open file.\n");
        return 0;
    }
    int max_line = 0; char line[500];
    while(fgets(line, 500, src_code)) max_line++;
    rewind(src_code);
    
    if(color)
    {
        char **t = calloc(table[pivot], sizeof(char*));
        char *str = malloc(500);
        for(int i = 0; i < pivot; i++)
            for(int j = 0; j < table[i]; j++)
                fscanf(fp, "%s", str);
        for(int i = 0; i < table[pivot]; i++)
        {
            fscanf(fp, "%s", str);
            *(t+i) = deal(str);  
        }
    
        char line[500]; bool find = false;
        int count = 0, count_label = 1;
        while(fgets(line, 500, src_code))
        {
            if(label) print_label(count_label, max_line);
            int offset = 0;
            while(line[offset] == ' ') offset++;
            for(int i = 0; i < offset; i++)
            printf(" ");
            char *add_space = malloc(1500);
            add_space = change_line(line);
            char *token = strtok(add_space, " ");
            while(token)
            {         
                token = strtok(NULL, " ");
                count++;
            } 
            int quotation[count];            
            char **s = calloc(count, sizeof(char*));
            count = 0;
            add_space = malloc(1500);
            add_space = change_line(line);
            token = strtok(add_space, " ");
            while(token)
            {
                *(s+count) = calloc(strlen(token)+1, sizeof(char)); 
                *(s+count) = token;
                quotation[count] = quotation_count(*(s+count));
                token = strtok(NULL, " ");
                count++;
            }
            
            for(int i = 1; i < count; i++)
                if(quotation[i] == 0 && quotation[i-1] == 1)
                    quotation[i] = 1;
            for(int i = 1; i < count; i++)
                if(quotation[i] == 2) quotation[i] = 1;    
            bool annotation = false;
            for(int i = 0; i < count; i++)
            {    
                if(quotation[i] == 0 && strstr(*(s+i), "//")) annotation = true;
                for(int j = 0; j < table[pivot]; j++)
                {            
                    if(strcmp(*(s+i), *(t+j)) == 0 && !annotation && quotation[i] == 0)
                    {
                        printf(RED"%s ", *(s+i));
                        find = true; break;
                    }
                }                
                if(!find) printf(NONE"%s ", *(s+i));    
                find = false;
            } printf(NONE"\n");
            count = 0;  count_label++;
        }
    }
    else
    {
        char line[500];
        int count_label = 1;
        while(fgets(line, 500, src_code))
        {
            if(label) print_label(count_label, max_line);
            printf("%s", line);
            count_label++;
        }
    }
    fclose(fp); fclose(src_code);
    return 0;
}