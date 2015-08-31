//
// Created by Daniel Marchese on 8/31/15.
//

#include "../../Common.h"
#include "InternalMemoryController.h"

uint8_t InternalMemoryController::read(uint16_t addr) {
    if ((addr & 0xE000) == 0xC000) {
        // This is the internal working RAM
        return _workingRAM[addr - 0xC000];
    } else if ((addr & 0xE000) == 0xE000 && addr < 0xFE00) {
        // This is the shadow of working RAM
        return _workingRAM[addr - 0xE000];
    } else if (addr >= 0xFF80) {
        // This is the zero-page RAM
        return _hRAM[addr - 0xFF80];
    } else {
        // We shouldn't be accessing this memory through this controller.
        Log("Attempted read at 0x%04x with the wrong controller (InternalMemoryController).", addr);
        return 0x0;
    }
}

void InternalMemoryController::write(uint16_t addr, uint8_t value) {
    if ((addr & 0xE000) == 0xC000) {
        // This is the internal working RAM
        _workingRAM[addr - 0xC000] = value;
    } else if ((addr & 0xE000) == 0xE000 && addr < 0xFE00) {
        // This is the shadow of working RAM
        _workingRAM[addr - 0xE000] = value;
    } else if (addr >= 0xFF80) {
        // This is the zero-page RAM
        _hRAM[addr - 0xFF80] = value;
    } else {
        // We shouldn't be writing here from this controller.
        Log("Attempted write at 0x%04x with the wrong controller (InternalMemoryController).", addr);
    }
}

void InternalMemoryController::reset() {
    // TODO: Bring these memory sections back to their original state.
}
