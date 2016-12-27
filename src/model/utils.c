#include <utils.h>
#include <stdio.h>

char *rgba_to_hex(double red, double green, double blue){
    static char hex[8];
    sprintf(hex, "#%02X%02X%02X", (int)(red*255), (int)(green*255), (int)(blue*255));//%02X it's a lower-case hexadecimal
    return hex;
}
