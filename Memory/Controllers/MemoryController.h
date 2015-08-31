//
// Created by Daniel Marchese on 8/29/15.
//

#ifndef EMULATORCORE_MEMORYCONTROLLER_H
#define EMULATORCORE_MEMORYCONTROLLER_H

#include "../../Common.h"

class MemoryMap;

class MemoryController {
protected:
    MemoryMap *_mmap;
public:
    MemoryController(MemoryMap *map) { _mmap = map; }
    virtual ~MemoryController() { }
    virtual uint8_t read(uint16_t addr) = 0;
    virtual void write(uint16_t addr, uint8_t value) = 0;
    virtual void reset() = 0;
};

#endif //EMULATORCORE_MEMORYCONTROLLER_H
