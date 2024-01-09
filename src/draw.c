#include "draw.h"

void draw(char *pixel_buffer, size_t size) {
    printf(CSI "2J");       // Clear the screen
    printf(CSI "[H");     // Place the cursor at home

    for(size_t k = 0; k < size + 1; k++) {
        putchar(k % SCREEN_WIDTH ? pixel_buffer[k] : 10);
    }
}