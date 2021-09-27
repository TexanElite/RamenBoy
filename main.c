#include "cpu.h"
#include "mmu.h"
#include "gpu.h"
#include "gui.h"

int main() {
    cpu_t *cpu = cpu_new();
    mmu_t *memory = mmu_new("/home/sidh/Downloads/Tetris (World) (Rev A).gb");
    cpu->memory = memory;
    gpu_t *gpu = gpu_new(cpu);
    // Completely broken gui and memory leaks? Let's gooooooooooooooooooooooooooooooo
    for (;;) {
        cpu_step(cpu);
        gpu_step(gpu);
    }
    mmu_free(memory);
    gpu_free(gpu);
    cpu_free(cpu);
}