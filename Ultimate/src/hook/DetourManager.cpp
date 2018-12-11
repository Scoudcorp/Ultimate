#include "DetourManager.h"
#include "asset/FindXAssetHeaderDetour.h"
#include "d3d/EndSceneDetour.h"
#include "detours/detours.h"
#include "game/ClientDisconnectDetour.h"
#include "game/MenuResponseDetour.h"
#include "game/PlayerDieDetour.h"
#include "game/SayDetour.h"
#include "input/MouseEventDetour.h"
#include "party/CanHostServerDetour.h"
#include "party/ClientHandshakeDetour.h"
#include "script/NotifyDetour.h"
#include "script/RegisterMethodDetour.h"
#include "script/RunFrameDetour.h"
#include "script/Scripts.h"
#include "user32/DispatchMessageDetour.h"

DetourManager::DetourManager()
{
//    registerDetour(std::make_shared<EndSceneDetour>());
//    registerDetour(std::make_shared<ResetDetour>());
    registerDetour(std::make_shared<DispatchMessageDetour>());
    registerDetour(std::make_shared<MouseEventDetour>());
    registerDetour(std::make_shared<ClientHandshakeDetour>());
    registerDetour(std::make_shared<SayDetour>());
    registerDetour(std::make_shared<PlayerDieDetour>());
    registerDetour(std::make_shared<CanHostServerDetour>());
    registerDetour(std::make_shared<RegisterMethodDetour>());
    registerDetour(std::make_shared<ClientDisconnectDetour>());
    //registerDetour(std::make_shared<FindXAssetHeaderDetour>());
    registerDetour(std::make_shared<MenuResponseDetour>());
    //registerDetour(std::make_shared<GameSendServerCommandDetour>());
    //registerDetour(std::make_shared<NetchanProcessDetour>());
    registerDetour(std::make_shared<NotifyDetour>());
    registerDetour(std::make_shared<RunFrameDetour>());
    //registerDetour(std::make_shared<ShellExecuteDetour>());
    //registerDetour(std::make_shared<FindConfigstringIndexDetour>());

    m_scriptManager.registerHook(230, Proxies::ExitLevel);
    m_scriptManager.registerHook(430, Proxies::SetSpawnWeaponControl);
    m_scriptManager.registerHook(438, Proxies::Spawn);
    m_scriptManager.registerHook(467, Proxies::GiveWeaponControl);
    m_scriptManager.registerHook(527, Proxies::SetClientDvar);
    m_scriptManager.registerHook(563, Proxies::SetPerk);
    m_scriptManager.registerHook(185, Proxies::GetEntArray);

    //m_scriptManager.registerHook(589, Proxies::CloneBrushmodelToScriptmodel);
}

void DetourManager::hook()
{
    m_d3dHooks.hook();

    beginTransaction();

    std::printf("Applying %Iu detours...\n", m_detours.size());

    for (const auto& detour : m_detours) {
        const auto error = applyDetour(detour);
        if (error != NO_ERROR) {
            std::printf("ApplyDetour failed: %ld\n", error);
        }
    }

    commitTransaction();
}

void DetourManager::unhook()
{
    m_d3dHooks.unhook();

    beginTransaction();

    std::printf("Restoring %Iu detours...\n", m_detours.size());

    for (auto detour = m_detours.rbegin(); detour != m_detours.rend(); ++detour) {
        const auto error = restoreDetour(*detour);
        if (error != NO_ERROR) {
            std::printf("RestoreDetour failed: %ld\n", error);
        }
    }

    m_scriptManager.resetHooks();

    commitTransaction();
}

void DetourManager::registerDetour(const std::shared_ptr<Detour>& detour)
{
    m_detours.push_back(detour);
}

long DetourManager::beginTransaction()
{
    auto error = DetourTransactionBegin();
    if (error != NO_ERROR) {
        std::printf("DetourTransactionBegin failed: %ld\n", error);
        return error;
    }

    error = DetourUpdateThread(GetCurrentThread());
    if (error != NO_ERROR) {
        std::printf("DetourUpdateThread failed: %ld\n", error);
        return error;
    }

    return error;
}

long DetourManager::applyDetour(const std::shared_ptr<Detour>& detour)
{
    return detour->applyDetour();
}

long DetourManager::restoreDetour(const std::shared_ptr<Detour>& detour)
{
    return detour->restoreDetour();
}

long DetourManager::commitTransaction()
{
    const auto error = DetourTransactionCommit();
    if (error != NO_ERROR) {
        std::printf("DetourTransactionCommit failed: %ld\n", error);
    }

    return error;
}
