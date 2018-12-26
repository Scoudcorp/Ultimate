#include "EndSceneDetour.h"
#include "iw4/render.h"
#include <polyhook/CapstoneDisassembler.hpp>
#include <polyhook/Virtuals/VFuncSwapHook.hpp>
#include <ultimate/Ultimate.h>


EndSceneFunction EndSceneDetour::m_originalEndScene = nullptr;

static PLH::VFuncMap original_map;
static PLH::VFuncSwapHook *hook;

long EndSceneDetour::applyDetour()
{
//    m_originalEndScene = reinterpret_cast<EndSceneFunction>(VTable::Hook(g_device, hookEndScene, 42));
   
    PLH::VFuncMap new_map{{ 42, reinterpret_cast<uint64_t>(&hookEndScene) }};
    hook = new PLH::VFuncSwapHook{ reinterpret_cast<char*>(g_device), new_map, &original_map };

    hook->hook();

    std::printf("Hooked IDirect3DDevice9::EndScene\n");

    return NO_ERROR;
}

long EndSceneDetour::restoreDetour()
{
//    VTable::Hook(g_device, m_originalEndScene, 42);

    hook->unHook();
    delete hook;

    std::printf("Restored IDirect3DDevice9::EndScene\n");

    return NO_ERROR;
}

HRESULT EndSceneDetour::hookEndScene(IDirect3DDevice9* device)
{
    Ultimate::m_ultimate->onEndScene();

//    return m_originalEndScene(device);
    return reinterpret_cast<EndSceneFunction>(original_map.at(42))(device);
}
