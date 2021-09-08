#ifndef MMU_H
#define MMU_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

static const int ROM_START  = 0x0000;
static const int VRAM_START = 0x8000;
static const int ERAM_START = 0xA000;
static const int WRAM_START = 0xC000;
static const int SHAD_START = 0xE000;
static const int OAM_START  = 0xFE00;
static const int IO_START   = 0xFF00;
static const int HRAM_START = 0xFF80;

typedef struct mmu_t {
    unsigned char *title;
    unsigned char rom[0x8000];
    unsigned char vram[0x2000];
    unsigned char eram[0x2000];
    unsigned char wram[0x2000];
    unsigned char oam[0x100];
    unsigned char io[0x80];
    unsigned char hram[0x80];
} mmu_t;

mmu_t *mmu_new(char *filename);
void mmu_free(mmu_t* memory);
unsigned char mmu_read(mmu_t *memory, unsigned short addr);
unsigned short mmu_read_short(mmu_t *memory, unsigned short addr);
void mmu_write(mmu_t *memory, unsigned short addr, unsigned char val);
void mmu_write_short(mmu_t *memory, unsigned short addr, unsigned short val);

#endif