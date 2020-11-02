#include <stdint.h>

void format(int8_t val, char format_string[]){
    char buffer[sizeof(format_string)*2];
    sprintf(buffer, format_string, val);
    return buffer;
}