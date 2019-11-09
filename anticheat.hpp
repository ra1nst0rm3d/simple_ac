#pragma once
#include <iostream>

namespace anticheat {
    int Init(uint16_t pid, void(*killer)(void));
    void DeInit(void);
}