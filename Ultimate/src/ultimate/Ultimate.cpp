#include "Ultimate.h"
#include "hook/DetourManager.h"

std::shared_ptr<Ultimate> Ultimate::m_ultimate = nullptr;

Ultimate::Ultimate()
    : m_hooked{ false }
{
    static_assert(sizeof(gentity_s) == 0x274);
}

void Ultimate::hook()
{
    m_patchManager.applyPatches();
    m_menuManager.initializeImGui();
    g_detours.hook();
    m_hooked = true;
}

void Ultimate::unhook()
{
    g_detours.unhook();
    MenuManager::shutdownImGui();
	m_patchManager.restorePatches();
    m_hooked = false;
}

void Ultimate::onEndScene()
{
	m_runningThreads.runThreads();
    m_menuManager.onEndScene();
}

bool Ultimate::onMessage(MSG* message) const
{
    return m_menuManager.onMessage(message);
}
