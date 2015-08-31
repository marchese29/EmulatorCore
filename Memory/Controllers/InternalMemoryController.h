//
// Created by Daniel Marchese on 8/31/15.
//

#ifndef EMULATORCORE_INTERNALMEMORYCONTROLLER_H
#define EMULATORCORE_INTERNALMEMORYCONTROLLER_H

#include "MemoryController.h"

/**
 * This controller handles all memory that is internal to the GameBoy.
 */
class InternalMemoryController : public MemoryController {
private:
    uint8_t _workingRAM[0x2000] = { 0x0 };
    uint8_t _hRAM[0x80] = { 0x0 };
public:
    InternalMemoryController(MemoryMap *map) : MemoryController(map) { }
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
    void reset();
};

#endif //EMULATORCORE_INTERNALMEMORYCONTROLLER_H
