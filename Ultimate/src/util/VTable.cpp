#include "VTable.h"
#include <Windows.h>

int VTable::Unprotect(void* region)
{
    MEMORY_BASIC_INFORMATION mbi;
    VirtualQuery(static_cast<LPCVOID>(region), &mbi, sizeof(mbi));
    VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &mbi.Protect);
    return mbi.Protect;
}

void VTable::Protect(void* region, const int protection)
{
    MEMORY_BASIC_INFORMATION mbi;
    VirtualQuery(static_cast<LPCVOID>(region), &mbi, sizeof(mbi));
    VirtualProtect(mbi.BaseAddress, mbi.RegionSize, protection, &mbi.Protect);
}

void* VTable::Hook(void* instance, void* hook, const int offset)
{
    const auto vtable = *static_cast<intptr_t*>(instance);
    const intptr_t entry = vtable + sizeof(intptr_t) * offset;
    const auto original = *reinterpret_cast<intptr_t*>(entry);

    const auto originalProtection = Unprotect(reinterpret_cast<void*>(entry));
    *reinterpret_cast<intptr_t*>(entry) = reinterpret_cast<intptr_t>(hook);
    Protect(reinterpret_cast<void*>(entry), originalProtection);

    return reinterpret_cast<void*>(original);
}
