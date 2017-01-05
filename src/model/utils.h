#ifndef UTILS_H
#define UTILS_H

#include <gource.h>

char *rgba_to_hex(double red, double green, double blue);

void copy_string(_string *destination, const char *source);

void append_string(_string *destination, const char *source);

#endif
