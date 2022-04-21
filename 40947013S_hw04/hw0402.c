#include "hw0402.h"

struct option long_options[] = 
{  
    {"i", 1, NULL, 'i'},
    {"n", 1, NULL, 'n'},
    {"p", 1, NULL, 'p'},
    {0, 0, 0, 0},  
}; 

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
    write_h(file_name, struct_name, store, value, size);
    write_c(file_name, struct_name, store, value, size);
}