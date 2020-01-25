#pragma once
#include <iostream>

namespace anticheat {
    int Init(void(*killer)(void));
    void DeInit(void);
}