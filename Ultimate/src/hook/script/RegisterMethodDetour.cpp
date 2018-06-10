#include "RegisterMethodDetour.h"
#include "detours/detours.h"
#include "hook/DetourManager.h"
#include "ultimate/Ultimate.h"

RegisterMethodFunction RegisterMethodDetour::m_originalRegisterMethod;

long RegisterMethodDetour::applyDetour()
{
    m_originalRegisterMethod = reinterpret_cast<RegisterMethodFunction>(0x577520);

    const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalRegisterMethod), hookRegisterMethod);

    std::printf("Hooked Script_RegisterMethod\n");

    return result;
}

long RegisterMethodDetour::restoreDetour()
{
    const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalRegisterMethod), hookRegisterMethod);

    std::printf("Restored Script_RegisterMethod\n");

    return result;
}

void RegisterMethodDetour::hookRegisterMethod(void (*method)(scr_entref_t))
{
    const auto index = *Script::g_allMethodCount;

    m_originalRegisterMethod(method);

    g_detours.m_scriptManager.installHook(index);
}
