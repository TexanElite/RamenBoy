#include "registers.h"

// registers_t *registers_new() {
//     return (registers_t *)malloc(sizeof(registers_t));
// }

// unsigned char get_A(registers_t *regs) {
//     return regs->A;
// }

// unsigned char get_F(registers_t *regs) {
//     return regs->F;
// }

// unsigned char get_B(registers_t *regs) {
//     return regs->B;
// }

// unsigned char get_C(registers_t *regs) {
//     return regs->C;
// }

// unsigned char get_D(registers_t *regs) {
//     return regs->D;
// }

// unsigned char get_E(registers_t *regs) {
//     return regs->E;
// }

// unsigned short get_SP(registers_t *regs) {
//     return regs->PC;
// }

// unsigned short get_PC(registers_t *regs) {
//     return regs->PC;
// }

unsigned short get_AF(registers_t *regs) {
    return (regs->A << 8) | regs->F;
}

unsigned short get_BC(registers_t *regs) {
    return (regs->B << 8) | regs->C;
}

unsigned short get_DE(registers_t *regs) {
    return (regs->D << 8) | regs->E;
}

unsigned short get_HL(registers_t *regs) {
    return (regs->H << 8) | regs->L;
}

unsigned char get_PC_upper(registers_t *regs) {
    return regs->PC >> 8;
}

unsigned char get_PC_lower(registers_t *regs) {
    return regs->PC & 0xFF;
}

// void set_A(registers_t *regs, unsigned char val) {
//     regs->A = val;
// }

// void set_F(registers_t *regs, unsigned char val) {
//     regs->F = val;
// }

// void set_B(registers_t *regs, unsigned char val) {
//     regs->B = val;
// }

// void set_C(registers_t *regs, unsigned char val) {
//     regs->C = val;
// }

// void set_D(registers_t *regs, unsigned char val) {
//     regs->D = val;
// }

// void set_E(registers_t *regs, unsigned char val) {
//     regs->E = val;
// }

// void set_SP(registers_t *regs, unsigned short val) {
//     regs->SP = val;
// }

// void set_PC(registers_t *regs, unsigned short val) {
//     regs->PC = val;
// }

void set_AF(registers_t *regs, unsigned short val) {
    regs->A = val >> 8;
    regs->F = val & 0xFF;
}

void set_BC(registers_t *regs, unsigned short val) {
    regs->B = val >> 8;
    regs->C = val & 0xFF;
}

void set_DE(registers_t *regs, unsigned short val) {
    regs->D = val >> 8;
    regs->E = val & 0xFF;
}

void set_HL(registers_t *regs, unsigned short val) {
    regs->H = val >> 8;
    regs->L = val & 0xFF;
}

unsigned char get_flag_zero(registers_t *regs) {
    return (regs->F & 0x80) > 0;
}

unsigned char get_flag_neg(registers_t *regs) {
    return (regs->F & 0x40) > 0;
}

unsigned char get_flag_half(registers_t *regs) {
    return (regs->F & 0x20) > 0;
}

unsigned char get_flag_carry(registers_t *regs) {
    return (regs->F & 0x10) > 0;
}

void set_flag_zero(registers_t *regs, unsigned char val) {
    val = val > 0;
    if (((regs->F >> 7) & 1) != val) {
        regs->F ^= (1 << 7);
    }
}

void set_flag_neg(registers_t *regs, unsigned char val) {
    val = val > 0;
    if (((regs->F >> 6) & 1) != val) {
        regs->F ^= (1 << 6);
    }
}

void set_flag_half(registers_t *regs, unsigned char val) {
    val = val > 0;
    if (((regs->F >> 5) & 1) != val) {
        regs->F ^= (1 << 5);
    }
}

void set_flag_carry(registers_t *regs, unsigned char val) {
    val = val > 0;
    if (((regs->F >> 4) & 1) != val) {
        regs->F ^= (1 << 4);
    }
}