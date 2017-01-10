/*
The MIT License (MIT)
Copyright (c) 2016 Lorhan Sohaky
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
