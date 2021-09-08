#include "cpu.h"

unsigned short rst_param(unsigned char opcode) {
    if (opcode < 0xC7) return 0;
    unsigned char index = (opcode - 0xC7) / 8;
    unsigned short param = index * 8;
    if (index > 0) param += (index - 1) * 2;
    return param;
}

void nop(cpu_t *cpu, registers_t *regs) {
    cpu->m = 1;
    cpu->t = 4;
}

void ld_bc_uu(cpu_t *cpu, registers_t *regs) {
    set_BC(regs, mmu_read_short(cpu->memory, regs->PC));
    regs->PC += 2;
    cpu->m = 3;
    cpu->t = 12;
}

void ld_pbc_a(cpu_t *cpu, registers_t *regs) {
    mmu_write(cpu->memory, get_BC(regs), regs->A);
    cpu->m = 2;
    cpu->t = 8;
}

void inc_bc(cpu_t *cpu, registers_t *regs) {
    set_BC(regs, get_BC(regs) + 1);
    cpu->m = 2;
    cpu->t = 8;
}

void inc_b(cpu_t *cpu, registers_t *regs) {
    set_flag_half(regs, (regs->B & 0x0F) == 0x0F);
    regs->B++;
    set_flag_zero(regs, regs->B == 0);
    set_flag_neg(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void dec_b(cpu_t *cpu, registers_t *regs) {
    set_flag_half(regs, !(regs->L & 0x0F));
    regs->B--;
    set_flag_zero(regs, regs->B == 0);
    set_flag_neg(regs, 1);
    cpu->m = 1;
    cpu->t = 4;
}

void ld_b_u(cpu_t *cpu, registers_t *regs) {
    regs->B = mmu_read(cpu->memory, regs->PC++);
    cpu->m = 2;
    cpu->t = 8;
}

void rlca(cpu_t *cpu, registers_t *regs) {
    set_flag_carry(regs, regs->A & 0x80);
    regs->A = (regs->A << 1) | (regs->A >> 7);
    cpu->m = 1;
    cpu->t = 4;
}

void ld_pnn_sp(cpu_t *cpu, registers_t *regs) {
    mmu_write_short(cpu->memory, mmu_read_short(cpu->memory, regs->PC), regs->SP);
    regs->PC += 2;
    cpu->m = 5;
    cpu->t = 20;
}

void add_hl_bc(cpu_t *cpu, registers_t *regs) {
    unsigned short result = get_HL(regs) + get_BC(regs);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (get_HL(regs) & 0x0F) + (get_BC(regs) & 0x0F) > 0x0F);
    set_flag_carry(regs, result < get_HL(regs));
    set_HL(regs, result);
    cpu->m = 2;
    cpu->t = 8;
}

void ld_a_pbc(cpu_t *cpu, registers_t *regs) {
    regs->A = mmu_read(cpu->memory, get_BC(regs));
    cpu->m = 2;
    cpu->t = 8;
}

void dec_bc(cpu_t *cpu, registers_t *regs) {
    set_BC(regs, get_BC(regs) - 1);
    cpu->m = 2;
    cpu->t = 8;
}

void inc_c(cpu_t *cpu, registers_t *regs) {
    set_flag_half(regs, (regs->C & 0x0F) == 0x0F);
    regs->C++;
    set_flag_zero(regs, regs->C == 0);
    set_flag_neg(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void dec_c(cpu_t *cpu, registers_t *regs) {
    set_flag_half(regs, !(regs->C & 0x0F));
    regs->C--;
    set_flag_zero(regs, regs->C == 0);
    set_flag_neg(regs, 1);
    cpu->m = 1;
    cpu->t = 4;
}

void ld_c_u(cpu_t *cpu, registers_t *regs) {
    regs->C = mmu_read(cpu->memory, regs->PC++);
    cpu->m = 2;
    cpu->t = 8;
}

void rrca(cpu_t *cpu, registers_t *regs) {
    set_flag_carry(regs, regs->A & 0x01);
    regs->A = (regs->A >> 1) | ((regs->A & 0x01) << 7);
    cpu->m = 1;
    cpu->t = 4;
}

void stop(cpu_t *cpu, registers_t *regs) {
    // TODO: Implement the stop function
}

void ld_de_uu(cpu_t *cpu, registers_t *regs) {
    set_DE(regs, mmu_read_short(cpu->memory, regs->PC));
    regs->PC += 2;
    cpu->m = 3;
    cpu->t = 12;
}

void ld_pde_a(cpu_t *cpu, registers_t *regs) {
    regs->A = mmu_read(cpu->memory, regs->PC++);
    cpu->m = 2;
    cpu->t = 8;
}

void inc_de(cpu_t *cpu, registers_t *regs) {
    set_DE(regs, get_DE(regs) + 1);
    cpu->m = 2;
    cpu->t = 8;
}

void inc_d(cpu_t *cpu, registers_t *regs) {
    set_flag_half(regs, (regs->D & 0x0F) == 0x0F);
    regs->D++;
    set_flag_zero(regs, regs->D == 0);
    set_flag_neg(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void dec_d(cpu_t *cpu, registers_t *regs) {
    set_flag_half(regs, !(regs->D & 0x0F));
    regs->D--;
    set_flag_zero(regs, regs->D == 0);
    set_flag_neg(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void ld_d_u(cpu_t *cpu, registers_t *regs) {
    regs->D = mmu_read(cpu->memory, regs->PC++);
    cpu->m = 2;
    cpu->t = 8;
}

void rla(cpu_t *cpu, registers_t *regs) {
    unsigned char carry = get_flag_carry(regs);
    set_flag_carry(regs, regs->A & 0x80);
    regs->A <<= 7;
    regs->A |= carry;
    cpu->m = 1;
    cpu->t = 4;
}

void jr_i(cpu_t *cpu, registers_t *regs) {
    char signed_offset = mmu_read(cpu->memory, regs->PC++);
    regs->PC += signed_offset;
    cpu->m = 3;
    cpu->t = 12;
}

void add_hl_de(cpu_t *cpu, registers_t *regs) {
    unsigned short result = get_HL(regs) + get_DE(regs);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (get_HL(regs) & 0x0F) + (get_DE(regs) & 0x0F) > 0x0F);
    set_flag_carry(regs, result < get_HL(regs));
    set_HL(regs, result);
    cpu->m = 2;
    cpu->t = 8;
}

void ld_a_pde(cpu_t *cpu, registers_t *regs) {
    regs->A = mmu_read(cpu->memory, get_DE(regs));
    cpu->m = 2;
    cpu->t = 8;
}

void dec_de(cpu_t *cpu, registers_t *regs) {
    set_DE(regs, get_DE(regs) - 1);
    cpu->m = 1;
    cpu->t = 4;
}

void inc_e(cpu_t *cpu, registers_t *regs) {
    set_flag_half(regs, (regs->E & 0x0F) == 0x0F);
    regs->E++;
    set_flag_zero(regs, regs->E == 0);
    set_flag_neg(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void dec_e(cpu_t *cpu, registers_t *regs) {
    set_flag_half(regs, !(regs->E & 0x0F));
    regs->E--;
    set_flag_zero(regs, regs->E == 0);
    set_flag_neg(regs, 1);
    cpu->m = 1;
    cpu->t = 4;
}

void ld_e_u(cpu_t *cpu, registers_t *regs) {
    regs->E = mmu_read(cpu->memory, regs->PC++);
    cpu->m = 2;
    cpu->t = 8;
}

void rra(cpu_t *cpu, registers_t *regs) {
    unsigned char carry = get_flag_carry(regs);
    set_flag_carry(regs, regs->A & 0x01);
    regs->A = (regs->A >> 1) | (carry << 7);
    cpu->m = 1;
    cpu->t = 4;
}

void jr_nz_i(cpu_t *cpu, registers_t *regs) {
    char signed_offset = mmu_read(cpu->memory, regs->PC++);
    if (!get_flag_zero(regs)) {
        regs->PC += signed_offset;
        cpu->m = 3;
        cpu->t = 12;
    }
    else {
        cpu->m = 2;
        cpu->t = 8;
    }
}

void ld_hl_uu(cpu_t *cpu, registers_t *regs) {
    set_HL(regs, mmu_read_short(cpu->memory, regs->PC));
    regs->PC += 2;
    cpu->m = 3;
    cpu->t = 12;
}

void ld_phlp_a(cpu_t *cpu, registers_t *regs) {
    mmu_write(cpu->memory, get_HL(regs), regs->A);
    set_HL(regs, get_HL(regs) + 1);
    cpu->m = 2;
    cpu->t = 8;
}

void inc_hl(cpu_t *cpu, registers_t *regs) {
    set_HL(regs, get_HL(regs) + 1);
    cpu->m = 2;
    cpu->t = 8;
}

void inc_h(cpu_t *cpu, registers_t *regs) {
    set_flag_half(regs, (regs->H & 0x0F) == 0x0F);
    regs->H++;
    set_flag_zero(regs, regs->H == 0);
    set_flag_neg(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void dec_h(cpu_t *cpu, registers_t *regs) {
    set_flag_half(regs, !(regs->H & 0x0F));
    regs->H--;
    set_flag_zero(regs, regs->H == 0);
    set_flag_neg(regs, 1);
    cpu->m = 1;
    cpu->t = 4;
}

void ld_h_u(cpu_t *cpu, registers_t *regs) {
    regs->H = mmu_read(cpu->memory, regs->PC++);
    cpu->m = 2;
    cpu->t = 8;
}

void daa(cpu_t *cpu, registers_t *regs) {
    unsigned char change = 0;
    if (get_flag_half(regs) || (!get_flag_neg(regs) && (regs->A & 0x0F) > 0x09)) {
        change |= 0x06;
    }
    if (get_flag_carry(regs) || (!get_flag_neg(regs) && regs->A > 0x99)) {
        change |= 0x60;
        set_flag_carry(regs, 1);
    }
    if (get_flag_neg(regs)) {
        regs->A -= change;
    }
    else {
        regs->A += change;
    }
    set_flag_zero(regs, regs->A == 0);
    set_flag_half(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void jr_z_i(cpu_t *cpu, registers_t *regs) {
    char signed_offset = mmu_read(cpu->memory, regs->PC++);
    if (get_flag_zero(regs)) {
        regs->PC += signed_offset;
        cpu->m = 3;
        cpu->t = 12;
    }
    else {
        cpu->m = 2;
        cpu->t = 8;
    }
}

void add_hl_hl(cpu_t *cpu, registers_t *regs)  {
    unsigned short result = get_HL(regs) + get_HL(regs);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (get_HL(regs) & 0x0F) + (get_HL(regs) & 0x0F) > 0x0F);
    set_flag_carry(regs, result < get_HL(regs));
    set_HL(regs, result);
    cpu->m = 2;
    cpu->t = 8;
}

void ld_a_phlp(cpu_t *cpu, registers_t *regs) {
    regs->A = mmu_read(cpu->memory, get_HL(regs));
    set_HL(regs, get_HL(regs) + 1);
    cpu->m = 2;
    cpu->t = 8;
}

void dec_hl(cpu_t *cpu, registers_t *regs) {
    set_HL(regs, get_HL(regs) - 1);
    cpu->m = 2;
    cpu->t = 8;
}

void inc_l(cpu_t *cpu, registers_t *regs) {
    set_flag_half(regs, (regs->L & 0x0F) == 0x0F);
    regs->L++;
    set_flag_zero(regs, regs->L == 0);
    set_flag_neg(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void dec_l(cpu_t *cpu, registers_t *regs) {
    set_flag_half(regs, !(regs->L & 0x0F));
    regs->L--;
    set_flag_zero(regs, regs->L == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, regs->L > 0x0F);
    cpu->m = 1;
    cpu->t = 4;
}

void ld_l_u(cpu_t *cpu, registers_t *regs) {
    regs->L = mmu_read(cpu->memory, regs->PC++);
    cpu->m = 2;
    cpu->t = 8;
}

void cpl(cpu_t *cpu, registers_t *regs) {
    regs->A = ~(regs->A);
    set_flag_neg(regs, 1);
    set_flag_half(regs, 1);
    cpu->m = 1;
    cpu->t = 4;
}

void jr_nc_i8(cpu_t *cpu, registers_t *regs) {
    char signed_offset = mmu_read(cpu->memory, regs->PC++);
    if (!get_flag_carry(regs)) {
        regs->PC += signed_offset;
        cpu->m = 3;
        cpu->t = 12;
    }
    else {
        cpu->m = 2;
        cpu->t = 8;
    }
}

void ld_sp_uu(cpu_t *cpu, registers_t *regs) {
    regs->SP = mmu_read_short(cpu->memory, regs->PC);
    regs->PC += 2;
    cpu->m = 3;
    cpu->t = 12;
}

void ld_phlm_a(cpu_t *cpu, registers_t *regs) {
    regs->A = mmu_read(cpu->memory, get_HL(regs));
    set_HL(regs, get_HL(regs) - 1);
    cpu->m = 2;
    cpu->t = 8;
}

void inc_sp(cpu_t *cpu, registers_t *regs) {
    regs->SP++;
    cpu->m = 2;
    cpu->t = 8;
}

void inc_phl(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, get_HL(regs)) + 1;
    mmu_write(cpu->memory, get_HL(regs), val);
    set_flag_zero(regs, val);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (val - 1) & 0x0F == 0x0F);
    cpu->m = 3;
    cpu->t = 12;
}

void dec_phl(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, get_HL(regs)) - 1;
    mmu_write(cpu->memory, get_HL(regs), val);
    set_flag_zero(regs, val);
    set_flag_neg(regs, 1);
    set_flag_half(regs, !((val + 1) & 0x0F));
    cpu->m = 3;
    cpu->t = 12;
}

void ld_phl_u(cpu_t *cpu, registers_t *regs) {
    mmu_write(cpu->memory, get_HL(regs), mmu_read(cpu->memory, regs->PC++));
    cpu->m = 3;
    cpu->t = 12;
}

void scf(cpu_t *cpu, registers_t *regs) {
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 1);
    cpu->m = 1;
    cpu->t = 4;
}

void jr_c_i(cpu_t *cpu, registers_t *regs) {
    char signed_offset = mmu_read(cpu->memory, regs->PC++);
    if (get_flag_carry(regs)) {
        regs->PC += signed_offset;
        cpu->m = 3;
        cpu->t = 12;
    }
    else {
        cpu->m = 2;
        cpu->t = 8;
    }
}

void add_hl_sp(cpu_t *cpu, registers_t *regs) {
    unsigned short result = get_HL(regs) + regs->SP;
    set_flag_neg(regs, 0);
    set_flag_half(regs, (get_HL(regs) & 0x0F) + (regs->SP & 0x0F) > 0x0F);
    set_flag_carry(regs, result < get_HL(regs));
    set_HL(regs, result);
    cpu->m = 2;
    cpu->t = 8;
}

void ld_a_phlm(cpu_t *cpu, registers_t *regs) {
    regs->A = mmu_read(cpu->memory, get_HL(regs));
    cpu->m = 2;
    cpu->t = 8;
}

void dec_sp(cpu_t *cpu, registers_t *regs) {
    regs->SP--;
    cpu->m = 2;
    cpu->t = 8;
}

void inc_a(cpu_t *cpu, registers_t *regs) {
    set_flag_half(regs, (regs->A & 0x0F) == 0x0F);
    regs->A++;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void dec_a(cpu_t *cpu, registers_t *regs) {
    set_flag_half(regs, !(regs->A & 0x0F));
    regs->A--;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 1);
    cpu->m = 1;
    cpu->t = 4;
}

void ld_a_u(cpu_t *cpu, registers_t *regs) {
    regs->A = mmu_read(cpu->memory, regs->PC++);
    cpu->m = 2;
    cpu->t = 8;
}

void ccf(cpu_t *cpu, registers_t *regs) {
    set_flag_carry(regs, !get_flag_carry(regs));
    cpu->m = 1;
    cpu->t = 4;
}

void ld_b_b(cpu_t *cpu, registers_t *regs) {
    regs->B = regs->B;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_b_c(cpu_t *cpu, registers_t *regs) {
    regs->B = regs->C;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_b_d(cpu_t *cpu, registers_t *regs) {
    regs->B = regs->D;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_b_e(cpu_t *cpu, registers_t *regs) {
    regs->B = regs->E;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_b_h(cpu_t *cpu, registers_t *regs) {
    regs->B = regs->H;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_b_l(cpu_t *cpu, registers_t *regs) {
    regs->B = regs->L;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_b_phl(cpu_t *cpu, registers_t *regs) {
    regs->B = mmu_read(cpu->memory, get_HL(regs));
    cpu->m = 2;
    cpu->t = 8;
}

void ld_b_a(cpu_t *cpu, registers_t *regs) {
    regs->B = regs->A;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_c_b(cpu_t *cpu, registers_t *regs) {
    regs->C = regs->B;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_c_c(cpu_t *cpu, registers_t *regs) {
    regs->C = regs->C;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_c_d(cpu_t *cpu, registers_t *regs) {
    regs->C = regs->D;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_c_e(cpu_t *cpu, registers_t *regs) {
    regs->C = regs->E;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_c_h(cpu_t *cpu, registers_t *regs) {
    regs->C = regs->H;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_c_l(cpu_t *cpu, registers_t *regs) {
    regs->C = regs->L;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_c_phl(cpu_t *cpu, registers_t *regs) {
    regs->C = mmu_read(cpu->memory, get_HL(regs));
    cpu->m = 2;
    cpu->t = 8;
}

void ld_c_a(cpu_t *cpu, registers_t *regs) {
    regs->C = regs->A;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_d_b(cpu_t *cpu, registers_t *regs) {
    regs->D = regs->B;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_d_c(cpu_t *cpu, registers_t *regs) {
    regs->D = regs->C;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_d_d(cpu_t *cpu, registers_t *regs) {
    regs->D = regs->D;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_d_e(cpu_t *cpu, registers_t *regs) {
    regs->D = regs->E;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_d_h(cpu_t *cpu, registers_t *regs) {
    regs->D = regs->H;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_d_l(cpu_t *cpu, registers_t *regs) {
    regs->D = regs->L;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_d_phl(cpu_t *cpu, registers_t *regs) {
    regs->D = mmu_read(cpu->memory, get_HL(regs));
    cpu->m = 2;
    cpu->t = 8;
}

void ld_d_a(cpu_t *cpu, registers_t *regs) {
    regs->D = regs->A;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_e_b(cpu_t *cpu, registers_t *regs) {
    regs->E = regs->B;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_e_c(cpu_t *cpu, registers_t *regs) {
    regs->E = regs->C;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_e_d(cpu_t *cpu, registers_t *regs) {
    regs->E = regs->D;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_e_e(cpu_t *cpu, registers_t *regs) {
    regs->E = regs->E;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_e_h(cpu_t *cpu, registers_t *regs) {
    regs->E = regs->H;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_e_l(cpu_t *cpu, registers_t *regs) {
    regs->E = regs->L;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_e_phl(cpu_t *cpu, registers_t *regs) {
    regs->E = mmu_read(cpu->memory, get_HL(regs));
    cpu->m = 2;
    cpu->t = 8;
}

void ld_e_a(cpu_t *cpu, registers_t *regs) {
    regs->E = regs->A;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_h_b(cpu_t *cpu, registers_t *regs) {
    regs->H = regs->B;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_h_c(cpu_t *cpu, registers_t *regs) {
    regs->H = regs->C;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_h_d(cpu_t *cpu, registers_t *regs) {
    regs->H = regs->D;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_h_e(cpu_t *cpu, registers_t *regs) {
    regs->H = regs->E;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_h_h(cpu_t *cpu, registers_t *regs) {
    regs->H = regs->H;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_h_l(cpu_t *cpu, registers_t *regs) {
    regs->H = regs->L;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_h_phl(cpu_t *cpu, registers_t *regs) {
    regs->H = mmu_read(cpu->memory, get_HL(regs));
    cpu->m = 2;
    cpu->t = 8;
}

void ld_h_a(cpu_t *cpu, registers_t *regs) {
    regs->H = regs->A;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_l_b(cpu_t *cpu, registers_t *regs) {
    regs->L = regs->B;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_l_c(cpu_t *cpu, registers_t *regs) {
    regs->L = regs->C;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_l_d(cpu_t *cpu, registers_t *regs) {
    regs->L = regs->D;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_l_e(cpu_t *cpu, registers_t *regs) {
    regs->L = regs->E;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_l_h(cpu_t *cpu, registers_t *regs) {
    regs->L = regs->H;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_l_l(cpu_t *cpu, registers_t *regs) {
    regs->L = regs->L;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_l_phl(cpu_t *cpu, registers_t *regs) {
    regs->L = mmu_read(cpu->memory, get_HL(regs));
    cpu->m = 2;
    cpu->t = 8;
}

void ld_l_a(cpu_t *cpu, registers_t *regs) {
    regs->L = regs->A;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_phl_b(cpu_t *cpu, registers_t *regs) {
    mmu_write(cpu->memory, get_HL(regs), regs->B);
    cpu->m = 2;
    cpu->t = 8;
}

void ld_phl_c(cpu_t *cpu, registers_t *regs) {
    mmu_write(cpu->memory, get_HL(regs), regs->C);
    cpu->m = 2;
    cpu->t = 8;
}

void ld_phl_d(cpu_t *cpu, registers_t *regs) {
    mmu_write(cpu->memory, get_HL(regs), regs->D);
    cpu->m = 2;
    cpu->t = 8;
}

void ld_phl_e(cpu_t *cpu, registers_t *regs) {
    mmu_write(cpu->memory, get_HL(regs), regs->E);
    cpu->m = 2;
    cpu->t = 8;
}

void ld_phl_h(cpu_t *cpu, registers_t *regs) {
    mmu_write(cpu->memory, get_HL(regs), regs->H);
    cpu->m = 2;
    cpu->t = 8;
}

void ld_phl_l(cpu_t *cpu, registers_t *regs) {
    mmu_write(cpu->memory, get_HL(regs), regs->L);
    cpu->m = 2;
    cpu->t = 8;
}

void halt(cpu_t *cpu, registers_t *regs) {
    // TODO: Implement Halt
}

void ld_phl_a(cpu_t *cpu, registers_t *regs) {
    mmu_write(cpu->memory, get_HL(regs), regs->A);
    cpu->m = 2;
    cpu->t = 8;
}

void ld_a_b(cpu_t *cpu, registers_t *regs) {
    regs->A = regs->B;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_a_c(cpu_t *cpu, registers_t *regs) {
    regs->A = regs->C;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_a_d(cpu_t *cpu, registers_t *regs) {
    regs->A = regs->D;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_a_e(cpu_t *cpu, registers_t *regs) {
    regs->A = regs->E;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_a_h(cpu_t *cpu, registers_t *regs) {
    regs->A = regs->H;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_a_l(cpu_t *cpu, registers_t *regs) {
    regs->A = regs->L;
    cpu->m = 1;
    cpu->t = 4;
}

void ld_a_phl(cpu_t *cpu, registers_t *regs) {
    regs->A = mmu_read(cpu->memory, get_HL(regs));
    cpu->m = 2;
    cpu->t = 8;
}

void ld_a_a(cpu_t *cpu, registers_t *regs) {
    regs->A = regs->A;
    cpu->m = 1;
    cpu->t = 4;
}

// 0xC3
void jp_uu(cpu_t *cpu, registers_t *regs) {
    unsigned short addr = mmu_read_short(cpu->memory, regs->PC);
    regs->PC = addr;
    cpu->m = 4;
    cpu->t = 16;
}

void add_a_b(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A + regs->B;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (regs->B & 0x0F) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void add_a_c(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A + regs->B;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (regs->B & 0x0F) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void add_a_d(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A + regs->B;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (regs->B & 0x0F) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void add_a_e(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A + regs->B;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (regs->B & 0x0F) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void add_a_h(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A + regs->B;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (regs->B & 0x0F) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void add_a_l(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A + regs->B;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (regs->B & 0x0F) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void add_a_phl(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, get_HL(regs));
    unsigned char result = regs->A + val;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (val & 0x0F) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = result;
    cpu->m = 2;
    cpu->t = 8;
}

void add_a_a(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A + regs->A;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (regs->A & 0x0F) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}


void adc_a_b(cpu_t *cpu, registers_t *regs) {
    unsigned short result = regs->A + regs->B + get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (regs->B & 0x0F) + get_flag_carry(regs) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = (unsigned char) result;
    cpu->m = 1;
    cpu->t = 4;
}

void adc_a_c(cpu_t *cpu, registers_t *regs) {
    unsigned short result = regs->A + regs->C + get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (regs->C & 0x0F) + get_flag_carry(regs) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = (unsigned char) result;
    cpu->m = 1;
    cpu->t = 4;
}

void adc_a_d(cpu_t *cpu, registers_t *regs) {
    unsigned short result = regs->A + regs->D + get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (regs->D & 0x0F) + get_flag_carry(regs) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = (unsigned char) result;
    cpu->m = 1;
    cpu->t = 4;
}

void adc_a_e(cpu_t *cpu, registers_t *regs) {
    unsigned short result = regs->A + regs->E + get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (regs->E & 0x0F) + get_flag_carry(regs) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = (unsigned char) result;
    cpu->m = 1;
    cpu->t = 4;
}

void adc_a_h(cpu_t *cpu, registers_t *regs) {
    unsigned short result = regs->A + regs->H + get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (regs->H & 0x0F) + get_flag_carry(regs) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = (unsigned char) result;
    cpu->m = 1;
    cpu->t = 4;
}

void adc_a_l(cpu_t *cpu, registers_t *regs) {
    unsigned short result = regs->A + regs->L + get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (regs->L & 0x0F) + get_flag_carry(regs) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = (unsigned char) result;
    cpu->m = 1;
    cpu->t = 4;
}

void adc_a_phl(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, get_HL(regs));
    unsigned short result = regs->A + val + get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + val + get_flag_carry(regs) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = (unsigned char) result;
    cpu->m = 2;
    cpu->t = 8;
}

void adc_a_a(cpu_t *cpu, registers_t *regs) {
    unsigned short result = regs->A + regs->A + get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (regs->A & 0x0F) + get_flag_carry(regs) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = (unsigned char) result;
    cpu->m = 1;
    cpu->t = 4;
}

void sub_a_b(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A - regs->B;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (regs->B & 0x0F));
    set_flag_carry(regs, regs->A < result);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void sub_a_c(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A - regs->C;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (regs->C & 0x0F));
    set_flag_carry(regs, regs->A < result);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void sub_a_d(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A - regs->D;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (regs->D & 0x0F));
    set_flag_carry(regs, regs->A < result);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void sub_a_e(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A - regs->E;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (regs->E & 0x0F));
    set_flag_carry(regs, regs->A < result);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void sub_a_h(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A - regs->H;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (regs->H & 0x0F));
    set_flag_carry(regs, regs->A < result);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void sub_a_l(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A - regs->L;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (regs->L & 0x0F));
    set_flag_carry(regs, regs->A < result);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void sub_a_phl(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, get_HL(regs));
    unsigned char result = regs->A - val;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (val & 0x0F));
    set_flag_carry(regs, regs->A < result);
    regs->A = result;
    cpu->m = 2;
    cpu->t = 8;
}

void sub_a_a(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A - regs->A;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (regs->A & 0x0F));
    set_flag_carry(regs, regs->A < result);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void sbc_a_b(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A - regs->B - get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < ((regs->B & 0x0F) + get_flag_carry(regs)));
    set_flag_carry(regs, regs->A - regs->B - get_flag_carry(regs) < 0);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void sbc_a_c(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A - regs->C - get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < ((regs->C & 0x0F) + get_flag_carry(regs)));
    set_flag_carry(regs, regs->A - regs->C - get_flag_carry(regs) < 0);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void sbc_a_d(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A - regs->D - get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < ((regs->D & 0x0F) + get_flag_carry(regs)));
    set_flag_carry(regs, regs->A - regs->D - get_flag_carry(regs) < 0);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void sbc_a_e(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A - regs->E - get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < ((regs->E & 0x0F) + get_flag_carry(regs)));
    set_flag_carry(regs, regs->A - regs->E - get_flag_carry(regs) < 0);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void sbc_a_h(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A - regs->H - get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < ((regs->H & 0x0F) + get_flag_carry(regs)));
    set_flag_carry(regs, regs->A - regs->H - get_flag_carry(regs) < 0);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void sbc_a_l(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A - regs->L - get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < ((regs->L & 0x0F) + get_flag_carry(regs)));
    set_flag_carry(regs, regs->A - regs->L - get_flag_carry(regs) < 0);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void sbc_a_phl(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, get_HL(regs));
    unsigned char result = regs->A - val;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < ((val & 0x0F) + get_flag_carry(regs)));
    set_flag_carry(regs, regs->A - val - get_flag_carry(regs) < 0);
    regs->A = result;
    cpu->m = 2;
    cpu->t = 8;
}

void sbc_a_a(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A - regs->A - get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < ((regs->A & 0x0F) + get_flag_carry(regs)));
    set_flag_carry(regs, regs->A - regs->A - get_flag_carry(regs) < 0);
    regs->A = result;
    cpu->m = 1;
    cpu->t = 4;
}

void and_a_b(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A & regs->B;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 1);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void and_a_c(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A & regs->C;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 1);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void and_a_d(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A & regs->D;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 1);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void and_a_e(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A & regs->E;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 1);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void and_a_h(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A & regs->H;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 1);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void and_a_l(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A & regs->L;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 1);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void and_a_phl(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, get_HL(regs));
    unsigned char result = regs->A & val;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 1);
    set_flag_carry(regs, 0);
    cpu->m = 2;
    cpu->t = 8;
}

void and_a_a(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A & regs->A;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 1);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void xor_a_b(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A ^ regs->B;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void xor_a_c(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A ^ regs->C;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void xor_a_d(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A ^ regs->D;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void xor_a_e(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A ^ regs->E;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void xor_a_h(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A ^ regs->H;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void xor_a_l(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A ^ regs->L;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void xor_a_phl(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, get_HL(regs));
    unsigned char result = regs->A ^ val;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 2;
    cpu->t = 8;
}

void xor_a_a(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A ^ regs->A;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void or_a_b(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A | regs->B;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void or_a_c(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A | regs->C;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void or_a_d(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A | regs->D;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void or_a_e(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A | regs->E;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void or_a_h(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A | regs->H;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void or_a_l(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A | regs->L;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void or_a_phl(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, get_HL(regs));
    unsigned char result = regs->A | val;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 2;
    cpu->t = 8;
}

void or_a_a(cpu_t *cpu, registers_t *regs) {
    unsigned char result = regs->A | regs->A;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 0);
    set_flag_carry(regs, 0);
    cpu->m = 1;
    cpu->t = 4;
}

void cp_a_b(cpu_t *cpu, registers_t *regs) {
    set_flag_zero(regs, regs->A == regs->B);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (regs->B & 0x0F));
    set_flag_carry(regs, regs->A < regs->B);
    cpu->m = 1;
    cpu->t = 4;
}

void cp_a_c(cpu_t *cpu, registers_t *regs) {
    set_flag_zero(regs, regs->A == regs->C);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (regs->C & 0x0F));
    set_flag_carry(regs, regs->A < regs->C);
    cpu->m = 1;
    cpu->t = 4;
}

void cp_a_d(cpu_t *cpu, registers_t *regs) {
    set_flag_zero(regs, regs->A == regs->D);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (regs->D & 0x0F));
    set_flag_carry(regs, regs->A < regs->D);
    cpu->m = 1;
    cpu->t = 4;
}

void cp_a_e(cpu_t *cpu, registers_t *regs) {
    set_flag_zero(regs, regs->A == regs->E);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (regs->E & 0x0F));
    set_flag_carry(regs, regs->A < regs->E);
    cpu->m = 1;
    cpu->t = 4;
}

void cp_a_h(cpu_t *cpu, registers_t *regs) {
    set_flag_zero(regs, regs->A == regs->H);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (regs->H & 0x0F));
    set_flag_carry(regs, regs->A < regs->H);
    cpu->m = 1;
    cpu->t = 4;
}

void cp_a_l(cpu_t *cpu, registers_t *regs) {
    set_flag_zero(regs, regs->A == regs->L);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (regs->L & 0x0F));
    set_flag_carry(regs, regs->A < regs->L);
    cpu->m = 1;
    cpu->t = 4;
}

void cp_a_phl(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, get_HL(regs));
    set_flag_zero(regs, regs->A == val);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (val & 0x0F));
    set_flag_carry(regs, regs->A < val);
    cpu->m = 2;
    cpu->t = 8;
}

void cp_a_a(cpu_t *cpu, registers_t *regs) {
    set_flag_zero(regs, regs->A == regs->A);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (regs->A & 0x0F));
    set_flag_carry(regs, regs->A < regs->A);
    cpu->m = 1;
    cpu->t = 4;
}

void ret_nz(cpu_t *cpu, registers_t *regs) {
    if (get_flag_zero(regs) == 0) {
        unsigned short addr = mmu_read_short(cpu->memory, regs->SP);
        regs->SP += 2;
        regs->PC = addr;
        cpu->m = 5;
        cpu->t = 20;
    }
    else {
        cpu->m = 2;
        cpu->t = 8;
    }
}

void pop_bc(cpu_t *cpu, registers_t *regs) {
    set_BC(regs, mmu_read_short(cpu->memory, regs->SP));
    regs->SP += 2;
    cpu->m = 3;
    cpu->t = 12;
}

void jp_nz_uu(cpu_t *cpu, registers_t *regs) {
    unsigned short addr = mmu_read_short(cpu->memory, regs->PC);
    regs->PC += 2;
    if (get_flag_zero(regs) == 0) {
        regs->PC = addr;
        cpu->m = 4;
        cpu->t = 16;
    }
    else {
        cpu->m = 3;
        cpu->t = 12;
    }
}

void call_nz_uu(cpu_t *cpu, registers_t *regs) {
    unsigned short addr = mmu_read_short(cpu->memory, regs->PC);
    regs->PC += 2;
    if (get_flag_zero(regs) == 0) {
        mmu_write_short(cpu->memory, regs->SP - 2, regs->PC);
        regs->SP -= 2;
        regs->PC = addr;
        cpu->m = 6;
        cpu->t = 24;
    }
    else {
        cpu->m = 3;
        cpu->t = 12;
    }
}

void push_bc(cpu_t *cpu, registers_t *regs) {
    mmu_write_short(cpu->memory, regs->SP - 2, get_BC(regs));
    cpu->m = 4;
    cpu->t = 16;
}

void add_a_u(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, regs->PC++);
    unsigned char result = regs->A + val;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + (val & 0x0F) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = result;
    cpu->m = 2;
    cpu->t = 8;
}

void rst_00(cpu_t *cpu, registers_t *regs) {
    mmu_write_short(cpu->memory, regs->SP - 2, regs->PC);
    regs->PC = 0x00;
    cpu->m = 4;
    cpu->t = 16;
}

void ret_z(cpu_t *cpu, registers_t *regs) {
    if (get_flag_zero(regs) != 0) {
        unsigned short addr = mmu_read_short(cpu->memory, regs->SP);
        regs->SP += 2;
        regs->PC = addr;
        cpu->m = 5;
        cpu->t = 20;
    }
    else {
        cpu->m = 2;
        cpu->t = 8;
    }
}

void ret(cpu_t *cpu, registers_t *regs) {
    unsigned short addr = mmu_read_short(cpu->memory, regs->SP);
    regs->SP += 2;
    regs->PC = addr;
    cpu->m = 4;
    cpu->t = 16;
}

void jp_z_uu(cpu_t *cpu, registers_t *regs) {
    unsigned short addr = mmu_read_short(cpu->memory, regs->PC);
    regs->PC += 2;
    if (get_flag_zero(regs) != 0) {
        regs->PC = addr;
        cpu->m = 4;
        cpu->t = 16;
    }
    else {
        cpu->m = 3;
        cpu->t = 12;
    }
}

void prefix_cb(cpu_t *cpu, registers_t *regs) {
    //TODO: Implement prefixes
}

void call_z_uu(cpu_t *cpu, registers_t *regs) {
    unsigned short addr = mmu_read_short(cpu->memory, regs->PC);
    regs->PC += 2;
    if (get_flag_zero(regs) != 0) {
        mmu_write_short(cpu->memory, regs->SP - 2, regs->PC);
        regs->SP -= 2;
        regs->PC = addr;
        cpu->m = 6;
        cpu->t = 24;
    }
    else {
        cpu->m = 3;
        cpu->t = 12;
    }
}

void call_uu(cpu_t *cpu, registers_t *regs) {
    unsigned short addr = mmu_read_short(cpu->memory, regs->PC);
    regs->PC += 2;
    mmu_write_short(cpu->memory, regs->SP - 2, regs->PC);
    regs->SP -= 2;
    regs->PC = addr;
    cpu->m = 6;
    cpu->t = 24;
}

void adc_a_u(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, regs->PC++);
    unsigned short result = regs->A + val + get_flag_carry(regs);
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, (regs->A & 0x0F) + val + get_flag_carry(regs) > 0x0F);
    set_flag_carry(regs, regs->A > result);
    regs->A = (unsigned char) result;
    cpu->m = 2;
    cpu->t = 8;
}

void rst_08(cpu_t *cpu, registers_t *regs) {
    mmu_write_short(cpu->memory, regs->SP - 2, regs->PC);
    regs->PC = 0x08;
    cpu->m = 4;
    cpu->t = 16;
}

void ret_nc(cpu_t *cpu, registers_t *regs) {
    if (get_flag_carry(regs) == 0) {
        unsigned short addr = mmu_read_short(cpu->memory, regs->SP);
        regs->SP += 2;
        regs->PC = addr;
        cpu->m = 5;
        cpu->t = 20;
    }
    else {
        cpu->m = 2;
        cpu->t = 8;
    }
}

void pop_de(cpu_t *cpu, registers_t *regs) {
    set_DE(regs, mmu_read_short(cpu->memory, regs->SP));
    regs->SP += 2;
    cpu->m = 3;
    cpu->t = 12;
}

void jp_nc_uu(cpu_t *cpu, registers_t *regs) {
    unsigned short addr = mmu_read_short(cpu->memory, regs->PC);
    regs->PC += 2;
    if (get_flag_carry(regs) == 0) {
        regs->PC = addr;
        cpu->m = 4;
        cpu->t = 16;
    }
    else {
        cpu->m = 3;
        cpu->t = 12;
    }
}

void call_nc_uu(cpu_t *cpu, registers_t *regs) {
    unsigned short addr = mmu_read_short(cpu->memory, regs->PC);
    regs->PC += 2;
    if (get_flag_carry(regs) == 0) {
        mmu_write_short(cpu->memory, regs->SP - 2, regs->PC);
        regs->SP -= 2;
        regs->PC = addr;
        cpu->m = 6;
        cpu->t = 24;
    }
    else {
        cpu->m = 3;
        cpu->t = 12;
    }
}

void push_de(cpu_t *cpu, registers_t *regs) {
    mmu_write_short(cpu->memory, regs->SP - 2, get_DE(regs));
    cpu->m = 4;
    cpu->t = 16;
}

void sub_a_u(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, regs->PC++);
    unsigned char result = regs->A - val;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (val & 0x0F));
    set_flag_carry(regs, regs->A < result);
    regs->A = result;
    cpu->m = 2;
    cpu->t = 8;
}

void rst_10(cpu_t *cpu, registers_t *regs) {
    mmu_write_short(cpu->memory, regs->SP - 2, regs->PC);
    regs->PC = 0x10;
    cpu->m = 4;
    cpu->t = 16;
}

// 0xf5
void cp_a_u(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, regs->PC++);
    set_flag_zero(regs, regs->A == val);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < (val & 0x0F));
    set_flag_carry(regs, regs->A < val);
    cpu->m = 2;
    cpu->t = 8;
}

void ret_c(cpu_t *cpu, registers_t *regs) {
    if (get_flag_carry(regs) != 0) {
        unsigned short addr = mmu_read_short(cpu->memory, regs->SP);
        regs->SP += 2;
        regs->PC = addr;
        cpu->m = 5;
        cpu->t = 20;
    }
    else {
        cpu->m = 2;
        cpu->t = 8;
    }
}

void reti(cpu_t *cpu, registers_t *regs) {
    unsigned short addr = mmu_read_short(cpu->memory, regs->SP);
    regs->SP += 2;
    regs->PC = addr;

    // TODO: Enable interrupts

    cpu->m = 4;
    cpu->t = 16;
}

void jp_c_uu(cpu_t *cpu, registers_t *regs) {
    unsigned short addr = mmu_read_short(cpu->memory, regs->PC);
    regs->PC += 2;
    if (get_flag_carry(regs) != 0) {
        regs->PC = addr;
        cpu->m = 4;
        cpu->t = 16;
    }
    else {
        cpu->m = 3;
        cpu->t = 12;
    }
}

void call_c_uu(cpu_t *cpu, registers_t *regs) {
    unsigned short addr = mmu_read_short(cpu->memory, regs->PC);
    regs->PC += 2;
    if (get_flag_carry(regs) != 0) {
        mmu_write_short(cpu->memory, regs->SP - 2, regs->PC);
        regs->SP -= 2;
        regs->PC = addr;
        cpu->m = 6;
        cpu->t = 24;
    }
    else {
        cpu->m = 3;
        cpu->t = 12;
    }
}

void sbc_a_u(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, regs->PC++);
    unsigned char result = regs->A - val;
    set_flag_zero(regs, result == 0);
    set_flag_neg(regs, 1);
    set_flag_half(regs, (regs->A & 0x0F) < ((val & 0x0F) + get_flag_carry(regs)));
    set_flag_carry(regs, regs->A - val - get_flag_carry(regs) < 0);
    regs->A = result;
    cpu->m = 2;
    cpu->t = 8;
}

void rst_18(cpu_t *cpu, registers_t *regs) {
    mmu_write_short(cpu->memory, regs->SP - 2, regs->PC);
    regs->PC = 0x18;
    cpu->m = 4;
    cpu->t = 16;
}

void ld_ffpu_a(cpu_t *cpu, registers_t *regs) {
    unsigned short addr = 0xff00 + mmu_read(cpu->memory, regs->PC++);
    mmu_write(cpu->memory, addr, regs->A);
    cpu->m = 3;
    cpu->t = 12;
}

void pop_hl(cpu_t *cpu, registers_t *regs) {
    set_HL(regs, mmu_read_short(cpu->memory, regs->SP));
    regs->SP += 2;
    cpu->m = 3;
    cpu->t = 12;
}

void ld_ffpc_a(cpu_t *cpu, registers_t *regs) {
    unsigned short addr = 0xff00 + regs->C;
    mmu_write(cpu->memory, addr, regs->A);
    cpu->m = 2;
    cpu->t = 8;
}

void push_hl(cpu_t *cpu, registers_t *regs) {
    mmu_write_short(cpu->memory, regs->SP - 2, get_HL(regs));
    cpu->m = 4;
    cpu->t = 16;
}

void and_a_u(cpu_t *cpu, registers_t *regs) {
    unsigned char val = mmu_read(cpu->memory, regs->PC++);
    unsigned char result = regs->A & val;
    regs->A = result;
    set_flag_zero(regs, regs->A == 0);
    set_flag_neg(regs, 0);
    set_flag_half(regs, 1);
    set_flag_carry(regs, 0);
    cpu->m = 2;
    cpu->t = 8;
}

void rst_20(cpu_t *cpu, registers_t *regs) {
    mmu_write_short(cpu->memory, regs->SP - 2, regs->PC);
    regs->PC = 0x20;
    cpu->m = 4;
    cpu->t = 16;
}

void add_sp_i(cpu_t *cpu, registers_t *regs) {
    char val = mmu_read(cpu->memory, regs->PC++);
    regs->SP += val;
    
}

void (*opcode_table[256])(cpu_t *cpu, registers_t *regs) = {
    // 0x0_
    nop,
    ld_bc_uu,
    ld_pbc_a,
    inc_bc,
    inc_b,
    dec_b,
    ld_b_u,
    rlca,
    ld_pnn_sp,
    add_hl_bc,
    ld_a_pbc,
    dec_bc,
    inc_c,
    dec_c,
    ld_c_u,
    rrca,
    // 0x1_
    stop,
    ld_de_uu,
    ld_pde_a,
    inc_de,
    inc_d,
    dec_d,
    ld_d_u,
    rla,
    jr_i,
    add_hl_de,
    ld_a_pde,
    dec_de,
    inc_e,
    dec_e,
    ld_e_u,
    rra,
    // 0x2_
    jr_nz_i,
    ld_hl_uu,
    ld_phlp_a,
    inc_hl,
    inc_h,
    dec_h,
    ld_h_u,
    daa,
    jr_z_i,
    add_hl_hl,
    ld_a_phlp,
    dec_hl,
    inc_l,
    dec_l,
    ld_l_u,
    cpl,
    // 0x3_
    jr_nc_i8,
    ld_sp_uu,
    ld_phlm_a,
    inc_sp,
    inc_phl,
    dec_phl,
    ld_phl_u,
    scf,
    jr_c_i,
    add_hl_sp,
    ld_a_phlm,
    dec_sp,
    inc_a,
    dec_a,
    ld_a_u,
    ccf,
    // 0x4_
    ld_b_b,
    ld_b_c,
    ld_b_d,
    ld_b_e,
    ld_b_h,
    ld_b_l,
    ld_b_phl,
    ld_b_a,
    ld_c_b,
    ld_c_c,
    ld_c_d,
    ld_c_e,
    ld_c_h,
    ld_c_l,
    ld_c_phl,
    ld_c_a,
    // 0x5_
    ld_d_b,
    ld_d_c,
    ld_d_d,
    ld_d_e,
    ld_d_h,
    ld_d_l,
    ld_d_phl,
    ld_d_a,
    ld_e_b,
    ld_e_c,
    ld_e_d,
    ld_e_e,
    ld_e_h,
    ld_e_l,
    ld_e_phl,
    ld_e_a,
    // 0x6_
    ld_h_b,
    ld_h_c,
    ld_h_d,
    ld_h_e,
    ld_h_h,
    ld_h_l,
    ld_h_phl,
    ld_h_a,
    ld_l_b,
    ld_l_c,
    ld_l_d,
    ld_l_e,
    ld_l_h,
    ld_l_l,
    ld_l_phl,
    ld_l_a,
    // 0x7_
    ld_phl_b,
    ld_phl_c,
    ld_phl_d,
    ld_phl_e,
    ld_phl_h,
    ld_phl_l,
    halt,
    ld_phl_a,
    ld_a_b,
    ld_a_c,
    ld_a_d,
    ld_a_e,
    ld_a_h,
    ld_a_l,
    ld_a_phl,
    ld_a_a,
    // 0x8_
    add_a_b,
    add_a_c,
    add_a_d,
    add_a_e,
    add_a_h,
    add_a_l,
    add_a_phl,
    add_a_a,
    adc_a_b,
    adc_a_c,
    adc_a_d,
    adc_a_e,
    adc_a_h,
    adc_a_l,
    adc_a_phl,
    adc_a_a,
    // 0x9_
    sub_a_b,
    sub_a_c,
    sub_a_d,
    sub_a_e,
    sub_a_h,
    sub_a_l,
    sub_a_phl,
    sub_a_a,
    sbc_a_b,
    sbc_a_c,
    sbc_a_d,
    sbc_a_e,
    sbc_a_h,
    sbc_a_l,
    sbc_a_phl,
    sbc_a_a,
    // 0xA_
    and_a_b,
    and_a_c,
    and_a_d,
    and_a_e,
    and_a_h,
    and_a_l,
    and_a_phl,
    and_a_a,
    xor_a_b,
    xor_a_c,
    xor_a_d,
    xor_a_e,
    xor_a_h,
    xor_a_l,
    xor_a_phl,
    xor_a_a,
    // 0xB_
    or_a_b,
    or_a_c,
    or_a_d,
    or_a_e,
    or_a_h,
    or_a_l,
    or_a_phl,
    or_a_a,
    cp_a_b,
    cp_a_c,
    cp_a_d,
    cp_a_e,
    cp_a_h,
    cp_a_l,
    cp_a_phl,
    cp_a_a,
    // 0xC_
    ret_nz,
    pop_bc,
    jp_nz_uu,
    jp_uu,
    call_nz_uu,
    push_bc,
    add_a_u,
    rst_00,
    ret_z,
    ret,
    jp_z_uu,
    prefix_cb,
    call_z_uu,
    call_uu,
    adc_a_u,
    rst_08,
    // 0xD_
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    // 0xE_
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    // 0xF_
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    cp_a_e,
    NULL,
};

int execute_cycle(cpu_t *cpu) {
    mmu_t *memory = cpu->memory;
    registers_t *regs = &cpu->regs;
    unsigned char instruction = mmu_read(memory, regs->PC++);
    void (*operation)(cpu_t *cpu, registers_t *regs) = opcode_table[instruction];
    if (operation == NULL) {
        printf("Operation not implemented: %x\n", instruction);
        return 1;
    }
    operation(cpu, regs);
    return 0;
}

cpu_t *cpu_new() {
    cpu_t *cpu = (cpu_t *)malloc(sizeof(cpu_t));
    return cpu;
}

void cpu_free(cpu_t *cpu) {
    mmu_free(cpu->memory);
    free(cpu);
}

// Purely for testing purposes, don't look here

int main() {
    int count = 0;
    cpu_t *cpu = cpu_new();
    cpu->memory = mmu_new("/home/sidh/Downloads/Tetris (World) (Rev A).gb");
    for (;; count++) {
        int status = execute_cycle(cpu);
        if (status != 0) break;
    }
    cpu_free(cpu);
    printf("%d\n", count);
}