#include "interrupt.h"

void interrupt() {
    printf(CSI "?25h");         // Make the cursor visible
    free(z_buffer);
    free(pixel_buffer);
    exit(EXIT_SUCCESS);
}