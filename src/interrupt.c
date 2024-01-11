#include "interrupt.h"

void interrupt() {
    printf(CSI "?25h");         // Make the cursor visible
    exit(EXIT_SUCCESS);
}