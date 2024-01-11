#include "draw.h"

void draw(char *pixel_buffer, size_t size, float *A, float *B) {
    printf("\x1b[H"); // Put cursor at home
    for (size_t k = 0; k < size + 1; k++) {
        putchar(k % SCREEN_WIDTH ? pixel_buffer[k] : 10);
        *A += X_AXIS_ROTATION;
        *B += Z_AXIS_ROTATION;
    }
}