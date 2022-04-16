#include "hw0401.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Wrong file numbers input.\n");
        return 0;
    }

    char l1_name[128], l2_name[128], o_name[128];
    name(argv[1], l1_name, l2_name, o_name);
    twice(argv[1], "enlarge.bmp");    
    gray("enlarge.bmp", "gray.bmp");    
    remove("enlarge.bmp");
    generate("gray.bmp", l1_name, l2_name);
    remove("gray.bmp");
    overlap(l1_name, l2_name, o_name);
    
    return 0; 
}