#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.14159

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 22
#define SCREEN_X_CENTER (SCREEN_WIDTH / 2)
#define SCREEN_Y_CENTER (SCREEN_HEIGHT / 2)
#define X_SCALE (SCREEN_WIDTH / 2 - 10)
#define Y_SCALE (X_SCALE / 2)
#define VIEW_DISTANCE 5

#define R1 1
#define R2 2

#define DONUT_STEP 0.07
#define ROTATION_STEP 0.02
#define LUMINANCE 8

#define X_AXIS_ROTATION 0.00004
#define Z_AXIS_ROTATION 0.00002

int main(int argc, char const *argv[]) {
    float A = 0, B = 0;     // Angles
    float i, j;             // Iterators (To create the donut)
    int k;                  // Iterator (To render the donut)

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

        for(j = 0; j < (2 * PI); j += DONUT_STEP) {                 // Build the donut
            for (i = 0; i < (2 * PI); i += ROTATION_STEP) {        // Rotate the donut
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
        printf("\x1b[H");   // Put cursor at home
        for(k = 0; k < SCREEN_HEIGHT * SCREEN_WIDTH + 1; k++) {
            putchar(k % SCREEN_WIDTH ? b[k] : 10);
            A += X_AXIS_ROTATION;
            B += Z_AXIS_ROTATION;
        }

        usleep(30000);
    }
    return 0; 
}



