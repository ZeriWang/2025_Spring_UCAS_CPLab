#include <stdio.h>

void print_int(int value) {
    printf("%d", value);
}

void print_float(float value) {
    printf("%f", value);
}

void print_char(char value) {
    printf("%c", value);
}

int get_int() {
    int value;
    scanf("%d", &value);
    return value;
}

float get_float() {
    float value;
    scanf("%f", &value);
    return value;
}

char get_char() {
    char value;
    scanf("%c", &value);
    return value;
}
