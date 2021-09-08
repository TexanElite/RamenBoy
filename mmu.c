#include "mmu.h"

#define ROM_OFFSET_ROM_SIZE 0x148
mmu_t *mmu_new(char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error loading ROM: Could not locate file %s\n", filename);
        exit(1);
    }

    // Find length of file
    fseek(file, 0, SEEK_END);
    size_t filesize = ftell(file);
    if (filesize != 0x8000) {
        printf("Error loading ROM: Invalid ROM\n");
        exit(1);
    }
    fseek(file, 0, SEEK_SET);
    mmu_t *memory = (mmu_t*)malloc(sizeof(mmu_t));
    assert(memory->rom != 0);
    if (fread(memory->rom, 1, filesize, file) != filesize) {
        printf("Error loading ROM: File reading Error\n");
    }
    fclose(file);
    return memory;
}

unsigned char mmu_read(mmu_t *memory, unsigned short addr) {
    if (addr >= HRAM_START) {
        return memory->hram[addr - HRAM_START];
    }
    else if (addr >= IO_START) {
        return memory->io[addr - IO_START];
    }
    else if (addr >= OAM_START) {
        return memory->oam[addr - OAM_START];
    }
    else if (addr >= WRAM_START) {
        return memory->wram[addr - WRAM_START];
    }
    else if (addr >= ERAM_START) {
        return memory->eram[addr - ERAM_START];
    }
    else if (addr >= VRAM_START) {
        return memory->vram[addr - VRAM_START];
    }
    else if (addr >= ROM_START) {
        return memory->rom[addr - ROM_START];
    }
    return 0;
}

unsigned short mmu_read_short(mmu_t *memory, unsigned short addr) {
    return (mmu_read(memory, addr) << 8) | (mmu_read(memory, addr + 1));
}

void mmu_write(mmu_t *memory, unsigned short addr, unsigned char val) {
    if (addr >= HRAM_START) {
        memory->hram[addr - HRAM_START] = val;
    }
    else if (addr >= IO_START) {
        memory->io[addr - IO_START] = val;
    }
    else if (addr >= OAM_START) {
        memory->oam[addr - OAM_START] = val;
    }
    else if (addr >= WRAM_START) {
        memory->wram[addr - WRAM_START] = val;
    }
    else if (addr >= ERAM_START) {
        memory->eram[addr - ERAM_START] = val;
    }
    else if (addr >= VRAM_START) {
        memory->vram[addr - VRAM_START] = val;
    }
    else if (addr >= ROM_START) {
        memory->rom[addr - ROM_START] = val;
    }
}

void mmu_write_short(mmu_t *memory, unsigned short addr, unsigned short val) {
    mmu_write(memory, addr, val >> 8);
    mmu_write(memory, addr + 1, val & 0xFF);
}

void mmu_free(mmu_t* memory) {
    if (memory != NULL) {
        free(memory->title);
        free(memory);
    }
}

// int main() {
//     mmu_t *memory = mmu_new("/home/sidh/Downloads/Tetris (World) (Rev A).gb");
//     mmu_free(memory);
// }