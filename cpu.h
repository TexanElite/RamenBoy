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

