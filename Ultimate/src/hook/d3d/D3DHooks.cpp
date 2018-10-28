#include "D3DHooks.h"
#include "ultimate/Ultimate.h"

HRESULT __stdcall HookReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params)
{
    std::printf("IDirect3DDevice9::Reset -> invalidating ImGui\n");

    ImGui_ImplDX9_InvalidateDeviceObjects();

    auto original = reinterpret_cast<decltype(&HookReset)>(g_deviceHooks.m_originalMapping.at(16));
    const auto result = original(device, params);

    ImGui_ImplDX9_CreateDeviceObjects();

    std::printf("IDirect3DDevice9::Reset -> done!\n");

    return result;
}

HRESULT __stdcall HookEndScene(IDirect3DDevice9* device)
{
    Ultimate::m_ultimate->onEndScene();

    auto original = reinterpret_cast<decltype(&HookEndScene)>(g_deviceHooks.m_originalMapping.at(42));
    return original(device);
}

void D3DHooks::hook() const
{
    g_deviceHooks.hook();
}

void D3DHooks::unhook() const
{
    g_deviceHooks.unhook();
}
