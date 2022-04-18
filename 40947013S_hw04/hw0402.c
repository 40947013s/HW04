#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strtrim(char *s) 
{
    char *p = s, *q = s;
    while (*p == ' ' || *p == '\t') p++;
    while ((p != NULL)&&(q != NULL)&&(*p != '\0')&&(*p != '\0'))
        *q++ = *p++;
    q -= 2;
    while(*q == ' ' || *q == '\t') q--;
    *(q+1) ='\0';
    return s;
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
                printf("%s\n", token);
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

void store_item(char *filename, char *store[100])
{
    FILE *input = fopen(filename, "r"); 
    char line[600];
    int item = 0, max = (strlen(line)-1)/2;
    fgets(line, 600, input);
    fgets(line, 600, input);
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
                strcpy(store[item++], strtrim(token));
                printf("%d %s\n", count, store[item-1]);
                token = strtok(NULL, "|");
            }           
        }
    }
}

int main(int argc, char *argv[])
{
    char **store = NULL;
    int size = count_item("ip.txt");
    printf("%d", size);
    //store_item("ip.txt", store) ;
}