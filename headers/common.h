#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <math.h>

// Control Sequencer Introducer
#define CSI "\x1b["

// Distance of the viewer to the screen
#define VIEW_DISTANCE 5

// Radius of the circle & the donut
#define R1 1
#define R2 2

// Light vector (Normalised to have the values b/w -1 and 1)
#define Lx 0
#define Ly 1
#define Lz -1

// Brightness of the light source
#define LUMINANCE 8

// Steps (Determine the quality of the donut)
#define CIRCLE_STEP ((2 * M_PI) / 100)
#define DONUT_STEP ((2 * M_PI) / 100)

// Steps of rotation (Determine the speed/smoothness of the animation)
#define X_AXIS_ROTATION 0.00004
#define Z_AXIS_ROTATION 0.00002

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 22
#define SCREEN_X_CENTER (SCREEN_WIDTH / 2)
#define SCREEN_Y_CENTER (SCREEN_HEIGHT / 2)
#define X_SCALE (SCREEN_WIDTH / 2 - 10)
#define Y_SCALE (X_SCALE / 2)

// Global Variables
extern float *z_buffer;
extern char *pixel_buffer;
