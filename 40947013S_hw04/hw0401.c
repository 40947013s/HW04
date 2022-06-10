/*! \mainpage HW04
 *  
 * 
 * - \subpage HW0401 "hw0401 : Visual Cryptography"
 *
 * - \subpage HW0402 "hw0402 : Code Generator"
 *
 * - \subpage HW0403 "hw0403 : Source Code Highlighter"
 *
 * - \subpage HW0404 "hw0404 : Game Cheater: Princess Maker 2"
 */ 

/*! \page HW0401 hw0401 : Visual Cryptography
 * Refer to website https://www.101computing.net/visual-cryptography/
 * -# Given a colorful BMP image, make it gray scale only.
 * -# Use 128 as the threshold to make the pixel black or white.
 * -# Resize this image to 2x2 larger than the original image. That is, both width and height are twice than the original. So you can use 4 pixels to represent 1 pixel in the
original image.
 * -# Use the method described in the above site to generate layer1, layer2 and overlap.
 *
 */

/*! \page HW0402 hw0402 : Code Generator
 *
 * Get a txt file and generate a code with .c(excute) and .h(function) \n\n
 * The options are as follows:
 * - -i: Mandatory. The argument is the text file name which contains the structure.
 * - -n: Option. The argument is the structure name. Default: Test.
 * - -p: Option. The argument is the output file name. Default: test.\n\n
 * 
 * - Use suitable type for each member. If the size is less than 8-bits, use uint8_t directly.
 * -  If the member is not 8-bits, 16-bits, 32-bits and 64-bits, use minimum required bytes number and represent it as an array.
 * - init() is to allocate enough memory.
 * - free() is to free allocated memory.
 * - encode() is to encode a structure to a memory buffer. 
 * - decode() is to decode a memory buffer to a structure. 
 */
 
 /*! \page HW0403 hw0403 : Source Code Highlighter
 *
 * Get a code in (C, C++, Java, JS, Rust) and stdout code with keyword being highted.\n
 * The options are as follows:
 * - -n --linenum: Display the line number before each line.
 * - -c --color: Display the code and make each keyword colorful.
 * - -l --language: The given programming language. Default is C.
 */
 
  /*! \page HW0404 hw0404 : Game Cheater: Princess Maker 2
 * Game website download : https://dos.zczc.cz/games/%E7%BE%8E%E5%B0%91%E5%A5%B3%E6%A2%A6%E5%B7%A5%E5%8E%822/download\n
 * Design the interface is to modify the daughter¡¦s attributes, health status, money, items stored in the save file.
 */
 
 
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
