#include "common.h"
#include "interrupt.h"
#include "draw.h"

int main() {
    signal(SIGINT, interrupt);
    // printf(CSI "?25l");  // Make Cursor Invisible

    struct winsize size;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);     // Get terminal size

    // const int rows = size.ws_row;            // Number of rows on terminal
    // const int cols = size.ws_col;            // Number of columns on terminal
    
    // const int x_center = rows / 2;
    // const int y_center = cols / 2;

    float A = 0, B = 0;     // Angles
    float i, j;             // Iterators (To create the donut)

    // z-buffer and character buffer
    float z[SCREEN_HEIGHT * SCREEN_WIDTH];
    char b[SCREEN_HEIGHT * SCREEN_WIDTH];

    printf("\x1b[2J"); // Clear screen

    while(true) {
        memset(z, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(float)); // Fill with 0
        memset(b, 32, SCREEN_HEIGHT * SCREEN_WIDTH);                // Fill with " "

        float sin_A = sin(A);
        float sin_B = sin(B);
        float cos_A = cos(A);
        float cos_B = cos(B);

        for(j = 0; j < (2 * M_PI); j += CIRCLE_STEP) {                 // Build the donut
            for (i = 0; i < (2 * M_PI); i += DONUT_STEP) {        // Rotate the donut
                float sin_phi = sin(i);
                float cos_phi = cos(i);
                float sin_theta = sin(j);
                float cos_theta = cos(j);

                float R2_R1_cos_theta = R2 + R1 * cos_theta;

                float z_div = 1 / (R2_R1_cos_theta * sin_A * sin_phi + R1 * cos_A * sin_theta + VIEW_DISTANCE);
                float num_common = R2_R1_cos_theta * cos_A * sin_phi - R1 * sin_theta * sin_A;

                int x = SCREEN_X_CENTER + X_SCALE * z_div * (R2_R1_cos_theta * cos_phi * cos_B - num_common * sin_B);
                int y = SCREEN_Y_CENTER + Y_SCALE * z_div * (R2_R1_cos_theta * cos_phi * sin_B + num_common * cos_B);
                int o = x + SCREEN_WIDTH * y;

                int normal = LUMINANCE * (cos_B * (sin_A * sin_theta - cos_theta * cos_A * sin_phi) - (cos_phi * cos_theta * sin_B) - (sin_A * cos_theta * sin_phi) - (cos_A * sin_theta));

                if(y > 0 && y < SCREEN_HEIGHT && x > 0 && x < SCREEN_WIDTH && z_div > z[o]) {
                    z[o] = z_div;
                    b[o] = ".,-~:;=!*#$@"[normal > 0 ? normal : 0];
                }
            }
        }
        
        draw(b, sizeof(b), &A, &B);

        usleep(30000);
    }
    return 0; 
}
