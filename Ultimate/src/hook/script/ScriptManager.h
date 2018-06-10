#pragma once
#include "ScriptProxy.h"
#include <array>
#include <cstdint>

class ScriptManager {
    std::array<ScriptProxy, 1024> m_proxies;

public:

    void runHooks(uint32_t index, scr_entref_t entref);

    void installHook(uint32_t index);
    void registerHook(uint32_t index, ScriptInternalFunction hook);

    void resetHooks();

    uint32_t findIndex(uint32_t address);
};
