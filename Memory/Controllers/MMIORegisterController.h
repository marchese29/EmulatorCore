//
// Created by Daniel Marchese on 9/1/15.
//

#ifndef EMULATORCORE_MMIOREGISTERCONTROLLER_H
#define EMULATORCORE_MMIOREGISTERCONTROLLER_H

#include "../../Common.h"
#include "MemoryController.h"

class MMIORegisterController : public MemoryController {
private:
    uint8_t _interruptRegister;
    uint8_t _interruptEnableRegister;
public:
    MMIORegisterController(MemoryMap *map);
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
    void reset();
};

#endif //EMULATORCORE_MMIOREGISTERCONTROLLER_H
