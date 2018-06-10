#pragma once

#include <Windows.h>
#include <cstdio>

class Detour {
public:
    virtual ~Detour() = default;

    virtual long applyDetour();
    virtual long restoreDetour();
};
