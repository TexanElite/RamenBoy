#ifndef CPU_H
#define CPU_H

#include <string.h>
#include <stdlib.h>

#include "mmu.h"
#include "registers.h"

typedef struct cpu_t {
    mmu_t *memory;
    registers_t regs;
    int cycles;

    unsigned char m;
    unsigned char t;
} cpu_t;

cpu_t *cpu_new();
void cpu_free(cpu_t *cpu);
int cpu_step(cpu_t *cpu);

#endif