#include "FindXAssetHeaderDetour.h"
#include "detours/detours.h"
#include "settings/Settings.h"
#include "ultimate/Ultimate.h"

FindXAssetHeaderFunction FindXAssetHeaderDetour::m_originalFindXAssetHeader;

long FindXAssetHeaderDetour::applyDetour()
{
    m_originalFindXAssetHeader = reinterpret_cast<FindXAssetHeaderFunction>(0x4F4800);

    const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalFindXAssetHeader), &hookFindXAssetHeader);

    std::printf("Hooked DB_FindXAssetHeader\n");

    return result;
}

long FindXAssetHeaderDetour::restoreDetour()
{
    const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalFindXAssetHeader), &hookFindXAssetHeader);

    std::printf("Restored DB_FindXAssetHeader\n");

    return result;
}

XAssetHeader FindXAssetHeaderDetour::hookFindXAssetHeader(const XAssetType type, const char* name)
{
    if (g_settings.m_logSettings.m_logXAssetLookups) {
        if (g_settings.m_logSettings.m_logXAssetFilter < 0 || g_settings.m_logSettings.m_logXAssetFilter == type) {
            std::printf("DB_FindXAssetHeader -> [%2d] - %s\n", type, name);
        }
    }

    return m_originalFindXAssetHeader(type, name);
}
