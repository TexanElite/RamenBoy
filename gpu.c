#include "gpu.h"

const unsigned short LINE_ADDR = 0xFF44;
const unsigned short STATUS_ADDR = 0xFF41;

gpu_t *gpu_new(cpu_t *cpu) {
    gpu_t *gpu = (gpu_t*)malloc(sizeof(gpu_t));
    gpu->cpu = cpu;
    gpu->memory = cpu->memory;
    gpu->display = display_new();
    memset(gpu->pixels, 0, sizeof(gpu->pixels));
}

void gpu_free(gpu_t *gpu) {
    if (gpu != NULL) {
        display_destroy(gpu->display);
        free(gpu);
    }
}

void gpu_draw_screen(gpu_t *gpu) {
    for (int row = 0; row < WINDOW_HEIGHT; row++) {
        for (int col = 0; col < WINDOW_WIDTH; col++) {
            int r = gpu->pixels[row][col][0];
            int g = gpu->pixels[row][col][1];
            int b = gpu->pixels[row][col][2];
            display_draw_point(gpu->display, row, col, r, g, b);
        }
    }
    display_render(gpu->display);
}

void gpu_renderscan(gpu_t *gpu) {
    cpu_t *cpu = gpu->cpu;
    mmu_t *memory = gpu->memory;
    unsigned char scx = mmu_read(memory, 0xff43);
    unsigned char scy = mmu_read(memory, 0xff42);
    uint8_t control = mmu_read(memory, 0xff40);
}

void gpu_step(gpu_t *gpu) {
    gpu->clock += gpu->cpu->t;

    switch (gpu->mode) {
        case 0:
            if (gpu->clock >= 204) {
                gpu->clock = 0;
                gpu->line++;
                if (gpu->line == 143) {
                    gpu->mode = 1;
                    gpu_draw_screen(gpu);
                }
                else {
                    gpu->mode = 2;
                }
            }
            break;
        case 1:
            if (gpu->clock >= 456) {
                gpu->clock = 0;
                gpu->line++;

                if (gpu->line > 153) {
                    gpu->mode = 2;
                    gpu->line = 0;
                }
            }
            break;
        case 2:
            if (gpu->clock >= 80) {
                gpu->clock = 0;
                gpu->mode = 3;
            }
            break;
        case 3:
            if (gpu->clock >= 172) {
                gpu->clock = 0;
                gpu->mode = 0;
            }
            break;
    }
}