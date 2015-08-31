//
// Created by Daniel Marchese on 8/29/15.
//

#include "MemoryMap.h"

void MemoryMap::setCartridgeController(MemoryController *controller) {
    _cartridgeController = controller;
}

void MemoryMap::reset() {
    // TODO: Reset to the beginning state.
}

MemoryMap::MemoryMap() {
    // TODO: Store the processor state.
}
