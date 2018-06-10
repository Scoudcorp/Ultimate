#include "PatchManager.h"
#include "iw4/command.h"
#include "iw4/server.h"

PatchManager::PatchManager()
{
    registerPatch({ 0x6293C4u, { 0x6A, 0x01 } }); // Steam gameserver vac insecure flag

    registerPatch({ 0x582885u, { 0x8B, 0x0C } }); // VM_Notify store script method in ecx instead of eax
    registerPatch({ 0x582892u, { 0xFF, 0xD1 } }); // VM_Notify change "call eax" to "call ecx" (see previous patch for context)
}

void PatchManager::registerPatch(const Patch& patch)
{
    m_patches.push_back(patch);
}

void PatchManager::applyPatches()
{
    std::printf("Applying %Iu patches...\n", m_patches.size());

    for (auto& patch : m_patches) {
        patch.apply();
    }

    registerCommands();
}

void PatchManager::restorePatches()
{
    std::printf("Restoring %Iu patches...\n", m_patches.size());

    for (auto& patch : m_patches) {
        patch.restore();
    }

    removeCommands();
}

void PatchManager::registerCommands()
{
    Cmd::AddCommandInternal("map_restart", []() {
        Server::MapRestart(0, 0);
    }, &g_mapRestart);
}

void PatchManager::removeCommands()
{
    Cmd::RemoveCommand("map_restart");
}
