#ifndef REG_H
#define REG_H

#include <stdlib.h>

typedef struct registers_t
{
    unsigned char A;
    unsigned char F;

    unsigned char B;
    unsigned char C;

    unsigned char D;
    unsigned char E;

    unsigned char H;
    unsigned char L;

    unsigned short SP;
    unsigned short PC;

} registers_t;

// registers_t *registers_new();

// unsigned char get_A(registers_t* regs);
// unsigned char get_F(registers_t* regs);
// unsigned char get_B(registers_t* regs);
// unsigned char get_C(registers_t* regs);
// unsigned char get_D(registers_t* regs);
// unsigned char get_E(registers_t* regs);
// unsigned short get_SP(registers_t* regs);
// unsigned short get_PC(registers_t* regs);
unsigned short get_AF(registers_t* regs);
unsigned short get_BC(registers_t* regs);
unsigned short get_DE(registers_t* regs);
unsigned short get_HL(registers_t* regs);
unsigned char get_PC_upper(registers_t* regs);
unsigned char get_PC_lower(registers_t* regs);


// void set_A(registers_t* regs, unsigned char val);
// void set_F(registers_t* regs, unsigned char val);
// void set_B(registers_t* regs, unsigned char val);
// void set_C(registers_t* regs, unsigned char val);
// void set_D(registers_t* regs, unsigned char val);
// void set_E(registers_t* regs, unsigned char val);
// void set_SP(registers_t* regs, unsigned short val);
// void set_PC(registers_t* regs, unsigned short val);
void set_AF(registers_t* regs, unsigned short val);
void set_BC(registers_t* regs, unsigned short val);
void set_DE(registers_t* regs, unsigned short val);
void set_HL(registers_t* regs, unsigned short val);

unsigned char get_flag_zero(registers_t *regs);
unsigned char get_flag_neg(registers_t *regs);
unsigned char get_flag_half(registers_t *regs);
unsigned char get_flag_carry(registers_t *regs);

void set_flag_zero(registers_t* regs, unsigned char val);
void set_flag_neg(registers_t* regs, unsigned char val);
void set_flag_half(registers_t* regs, unsigned char val);
void set_flag_carry(registers_t* regs, unsigned char val);

#endif