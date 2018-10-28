#pragma once
#include "Hook.h"
#include <headers/Virtuals/VFuncSwapHook.hpp>
#include <utility>

class VirtualHook : public Hook {
public:
    PLH::VFuncMap m_originalMapping;

    VirtualHook(void* instance, PLH::VFuncMap hookMapping)
        : m_hookMapping(std::move(hookMapping))
        , m_hook(reinterpret_cast<char*>(instance), m_hookMapping, &m_originalMapping)
    {
    }

    void hook() override
    {
        m_hook.hook();
    }

    void unhook() override
    {
        m_hook.unHook();
    }

private:
    PLH::VFuncMap m_hookMapping;
    PLH::VFuncSwapHook m_hook;
};
