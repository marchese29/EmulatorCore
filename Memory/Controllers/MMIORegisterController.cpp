//
// Created by Daniel Marchese on 9/1/15.
//

#include "MMIORegisterController.h"

MMIORegisterController::MMIORegisterController(MemoryMap *map) : MemoryController(map) {
    // TODO: Maybe call reset?
}

void MMIORegisterController::reset() { }

uint8_t MMIORegisterController::read(uint16_t addr) {
    if (addr < 0xFF00) {
        Log("Attempted read at 0x%04x with incorrect controller (MMIORegisterController).", addr);
        return 0x0;
    } else if (addr > 0xFF4B) {
        Log("Attempted read at 0x%04x with incorrect controller (MMIORegisterController).", addr);
        return 0x0;
    }
    switch (addr & 0xFF) {
        case 0x00:
            // TODO: Read the inputs.
            return 0xFF;
        case 0x01: case 0x02:
            Log("Gameboy connections are not supported.  Attempted read of serial transfer flags.");
            return 0xFF;
        case 0x03:
            // Undocumented
            return 0xFF;
        case 0x04:
            // DIV Register
            // TODO: Read this register.
            return 0xFF;
        case 0x05:
            // TIMA Register
            // TODO: Read this register.
            return 0xFF;
        case 0x06:
            // TMA Register
            // TODO: Read this register.
            return 0xFF;
        case 0x07:
            // TAC Register
            // TODO: Read this register.
            return 0xFF;
        case 0x08: case 0x09: case 0x0A: case 0x0B:
        case 0x0C: case 0x0D: case 0x0E:
            // Undocumented
            return 0xFF;
        case 0x0F:
            // Interrupt Flag Register
            return _interruptRegister;
        case 0x10: case 0x11: case 0x12: case 0x13:
        case 0x14: case 0x15: case 0x16: case 0x17:
        case 0x18: case 0x19: case 0x1A: case 0x1B:
        case 0x1C: case 0x1D: case 0x1E: case 0x1F:
        case 0x20: case 0x21: case 0x22: case 0x23:
        case 0x24: case 0x25: case 0x26: case 0x27:
        case 0x28: case 0x29: case 0x2A: case 0x2B:
        case 0x2C: case 0x2D: case 0x2E: case 0x2F:
        case 0x30: case 0x31: case 0x32: case 0x33:
        case 0x34: case 0x35: case 0x36: case 0x37:
        case 0x38: case 0x39: case 0x3A: case 0x3B:
        case 0x3C: case 0x3D: case 0x3E: case 0x3F:
            // Various sound registers, will be handed to the sound controller.
            // TODO: Hand this to the sound controller.
            return 0xFF;
        case 0x40:
            // LCDC Register
            // TODO: Hand this to the LCD Controller
            return 0xFF;
        case 0x41:
            // LCD STAT Register
            // TODO: Hand this to the LCD Controller
            return 0xFF;
        case 0x42:
            // SCY Register
            // TODO: Hand this to the LCD Controller
            return 0xFF;
        case 0x43:
            // SCX Register
            // TODO: Hand this to the LCD Controller
            return 0xFF;
        case 0x44:
            // LY Register
            // TODO: Hand this to the LCD Controller
            return 0xFF;
        case 0x45:
            // LYC Register
            // TODO: Hand this to the LCD Controller
            return 0xFF;
        case 0x46:
            // DMA Register
            Log("Attempted read from write-only DMA register.");
            return 0xFF;
        case 0x47:
            // BGP Register
            // TODO: Hand this to the LCD Controller
            return 0xFF;
        case 0x48:
            // OBP0 Register
            // TODO: Hand this to the LCD Controller
            return 0xFF;
        case 0x49:
            // OBP1 Register
            // TODO: Hand this to the LCD Controller
            return 0xFF;
        case 0x4A:
            // WY Register
            // TODO: Hand this to the LCD Controller
            return 0xFF;
        case 0x4B:
            // WX Register
            // TODO: Hand this to the LCD Controller
            return 0xFF;
        case 0xFF:
            // IE Register
            return _interruptEnableRegister;
        default:
            Log("Attmpted read from unexpected address 0x%04x", addr);
            return 0xFF;
    }
}
