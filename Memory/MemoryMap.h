//
// Created by Daniel Marchese on 8/29/15.
//

#ifndef EMULATORCORE_MEMORYMAP_H
#define EMULATORCORE_MEMORYMAP_H

#include "../Common.h"

class MemoryController;
class InternalMemoryController;
class MMIORegisterController;

class MemoryMap {
private:
    MemoryController *_cartridgeController;
    InternalMemoryController *_internalController;
    MMIORegisterController *_mmioRegisterController;
public:
    MemoryMap();

    // Configuration
    void setCartridgeController(MemoryController *controller);
    void reset();

    // Memory Operations
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};

const static uint8_t BIOS[0x100] = {
    0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
    0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
    0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
    0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
    0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
    0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
    0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
    0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
    0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xE2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
    0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
    0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9,
    // Start of scrolling NINTENDO graphic
                                                    0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
    0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
    0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
    0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E,
    // End of scrolling NINTENDO graphic
                                                    0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C,
    0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x00, 0x00, 0x23, 0x7D, 0xFE, 0x34, 0x20,
    0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x00, 0x00, 0x3E, 0x01, 0xE0, 0x50
};

#include "Controllers/MemoryController.h"
#include "Controllers/InternalMemoryController.h"
#include "Controllers/MMIORegisterController.h"

inline uint8_t MemoryMap::read(uint16_t addr) {
    switch (addr & 0xE000) {
        case 0x0000:
            // If we are booting, this memory is internal to the GameBoy (it's the BIOS).
            // TODO: Check if we are still in the middle of boot
            if (addr < 0x100)
                return BIOS[addr];
            // Otherwise, this memory belongs to the cartridge.
        case 0x2000: case 0x4000: case 0x6000:
            // This memory belongs to the cartridge.
            return _cartridgeController->read(addr);
        case 0x8000:
            // This memory belongs to the graphics controller.
            // TODO: Do whatever we need to with video memory.
            return 0x0;
        case 0xA000:
            // This is the switchable ROM bank in the cartridge.
            return _cartridgeController->read(addr);
        case 0xC000:
            // This is the gameboy's internal working RAM.
            return _internalController->read(addr);
        case 0xE000:
            // There are a couple things that can happen in this memory space
            if (addr < 0xFE00) {
                // This is a shadow of working RAM
            } else if (addr < 0xFF00) {
                // This area contains information about the sprites
            } else if (addr < 0xFF80) {
                // This area is used for Memory-Mapped IO
                return _mmioRegisterController->read(addr);
            } else {
                // This area is HRAM.
                return _internalController->read(addr);
            }
            return 0x0;
        default:
            Log("Read from an unexpected memory address: 0x%04x", addr);
            return 0x0;
    }
}

inline void MemoryMap::write(uint16_t addr, uint8_t value) {
    switch (addr & 0xE000) {
        case 0x0000: case 0x2000: case 0x4000: case 0x6000:
            // This area belongs to the cartridge.
            _cartridgeController->write(addr, value);
            break;
        case 0x8000:
            // This memory belongs to the graphics controller.
            break;
        case 0xA000:
            // This is the switchable RAM bank
            _cartridgeController->write(addr, value);
            break;
        case 0xC000:
            // This is the gameboy's internal working RAM.
            _internalController->write(addr, value);
            break;
        case 0xE000:
            // There are a couple things that can happen in this memory space
            if (addr < 0xFE00) {
                // This is a shadow of working RAM
            } else if (addr < 0xFF00) {
                // This area is the sprite attribute memory
            } else if (addr < 0xFF80) {
                // This area is used for Memory-Mapped IO
                _mmioRegisterController->write(addr, value);
            } else {
                // This area is HRAM
                _internalController->write(addr, value);
            }
            break;
        default:
            Log("Write to an unexpected memory address: 0x%04x", addr);
            break;
    }
}

#endif //EMULATORCORE_MEMORYMAP_H
