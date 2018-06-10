#pragma once
#include "Scripts.h"
#include <iw4/script.h>
#include <vector>

class ScriptProxy {
    bool m_initialized;

    uint32_t m_index;

    void (*m_original)(scr_entref_t);

    std::vector<ScriptInternalFunction> m_hooks;

public:
    ScriptProxy();
    ~ScriptProxy();

    void initialize(uint32_t index);
    void reset();

    bool doesOriginalAddressMatch(uint32_t address) const;
    uint32_t getOriginalAddress() const;

    void runHooks(scr_entref_t entref);

    void installHook(uint32_t index);
    void registerHook(ScriptInternalFunction hook);

    static void interceptor(scr_entref_t entref);
};
