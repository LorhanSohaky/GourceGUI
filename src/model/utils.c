#include <utils.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *rgba_to_hex(double red, double green, double blue){
    static char hex[8];
    sprintf(hex, "#%02X%02X%02X", (int)(red*255), (int)(green*255), (int)(blue*255));//%02X it's a lower-case hexadecimal
    return hex;
}

void copy_string(_string *destination, const char *source){
    if(strlen(source)<destination->size){
        strcpy(destination->value,source);
    }else{
        char *tmp=(char *)realloc(destination->value,strlen(source)+1);
        if(tmp!=NULL){
            destination->size=strlen(source)+1;
            destination->value=tmp;
            strcpy(destination->value,source);
        }else{
            destination->size=0;
        }
    }
}

void append_string(_string *destination, const char *source){
    if(strlen(source)+strlen(destination->value)+1<destination->size){
        strcat(destination->value,source);
    }else{
        char *tmp=(char *)realloc(destination->value,strlen(source)+destination->size+1);
        if(tmp!=NULL){
            destination->size=strlen(source)+destination->size+1;
            destination->value=tmp;
            strcat(destination->value,source);
        }else{
            destination->size=0;
        }
    }
}

int length_of_int(int value){
    int length=1;
    while(value/10!=0){
        value=value/10;
        length++;
    }
    return length;
}
