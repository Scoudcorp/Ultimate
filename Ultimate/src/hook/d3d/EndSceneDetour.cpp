#include "EndSceneDetour.h"
#include "iw4/render.h"
#include <ultimate/Ultimate.h>
#include <util/VTable.h>

EndSceneFunction EndSceneDetour::m_originalEndScene = nullptr;

long EndSceneDetour::applyDetour()
{
    m_originalEndScene = reinterpret_cast<EndSceneFunction>(VTable::Hook(g_device, hookEndScene, 42));

    std::printf("Hooked IDirect3DDevice9::EndScene\n");

    return NO_ERROR;
}

long EndSceneDetour::restoreDetour()
{
    VTable::Hook(g_device, m_originalEndScene, 42);

    std::printf("Restored IDirect3DDevice9::EndScene\n");

    return NO_ERROR;
}

HRESULT EndSceneDetour::hookEndScene(IDirect3DDevice9* device)
{
    Ultimate::m_ultimate->onEndScene();

    return m_originalEndScene(device);
}
