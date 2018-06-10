#include "FindConfigstringIndexDetour.h"
#include "ClientDisconnectDetour.h"
#include "detours/detours.h"

FindConfigstringIndexFunction FindConfigstringIndexDetour::m_originalFindConfigstringIndex;

long FindConfigstringIndexDetour::applyDetour()
{
    m_originalFindConfigstringIndex = reinterpret_cast<FindConfigstringIndexFunction>(0x54D530);

    const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalFindConfigstringIndex), &hookFindConfigstringIndex);

    std::printf("Hooked G_FindConfigstringIndex\n");

    return result;
}

long FindConfigstringIndexDetour::restoreDetour()
{
    const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalFindConfigstringIndex), &hookFindConfigstringIndex);

    std::printf("Restored G_FindConfigstringIndex\n");

    return result;
}

int FindConfigstringIndexDetour::hookFindConfigstringIndex(const char* name, const int start, const int max, const int create, const char* errormsg)
{
    const auto result = m_originalFindConfigstringIndex(name, start, max, create, errormsg);

    if (create) {
        std::printf("G_FindConfigstringIndex -> searching for: %s - start: %d - max: %d - create: %d - found: %d\n", name, start, max, create, result);
    }

    return result;
}
