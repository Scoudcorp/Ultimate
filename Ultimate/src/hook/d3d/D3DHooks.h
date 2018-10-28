#pragma once
#include "hook/VirtualHook.h"
#include "imgui/impl/imgui_impl_dx9.h"
#include "iw4/render.h"

HRESULT WINAPI HookReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params);
HRESULT WINAPI HookEndScene(IDirect3DDevice9* device);

inline auto g_deviceFunctionMap = PLH::VFuncMap {
    { 16, reinterpret_cast<uint64_t>(&HookReset) },
    { 42, reinterpret_cast<uint64_t>(&HookEndScene) }
};

inline auto g_deviceHooks = VirtualHook(
    g_device, g_deviceFunctionMap
);

class D3DHooks {
public:
    void hook() const;
    void unhook() const;
};
