#ifndef GPU_H
#define GPU_H

#include "gui.h"
#include "mmu.h"
#include "cpu.h"
#include <string.h>

#define WINDOW_WIDTH 160
#define WINDOW_HEIGHT 144

typedef struct gpu_t {
    unsigned char pixels[WINDOW_HEIGHT][WINDOW_WIDTH][3];
    display_t *display;
    cpu_t *cpu;
    mmu_t *memory;
    unsigned short clock;
    unsigned short line;
    unsigned char mode;
} gpu_t;


gpu_t *gpu_new(cpu_t *cpu);
void gpu_free(gpu_t *gpu);
void gpu_step(gpu_t *gpu);

#endif