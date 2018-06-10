#include "ResetDetour.h"
#include "imgui/dx9/imgui_impl_dx9.h"
#include "iw4/render.h"
#include "ultimate/Ultimate.h"
#include <util/VTable.h>

ResetFunction ResetDetour::m_originalReset;

long ResetDetour::applyDetour()
{
    m_originalReset = reinterpret_cast<ResetFunction>(VTable::Hook(g_device, hookReset, 16));

    std::printf("Hooked IDirect3DDevice9::Reset\n");

    return NO_ERROR;
}

long ResetDetour::restoreDetour()
{
    VTable::Hook(g_device, m_originalReset, 16);

    std::printf("Restored IDirect3DDevice9::Reset\n");

    return NO_ERROR;
}

HRESULT WINAPI ResetDetour::hookReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params)
{
    std::printf("IDirect3DDevice9::Reset -> invalidating ImGui\n");

    ImGui_ImplDX9_InvalidateDeviceObjects();

    const auto result = m_originalReset(device, params);

    ImGui_ImplDX9_CreateDeviceObjects();

    std::printf("IDirect3DDevice9::Reset -> done!\n");

    return result;
}
