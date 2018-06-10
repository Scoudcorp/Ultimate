#include "ScriptManager.h"

void ScriptManager::installHook(const uint32_t index)
{
    m_proxies[index].installHook(index);
}

void ScriptManager::registerHook(const uint32_t index, const ScriptInternalFunction hook)
{
    m_proxies[index].registerHook(hook);

    if (*Script::g_allMethodCount >= 742) {
        installHook(index);
    }
}

void ScriptManager::resetHooks()
{
    for (auto& proxy : m_proxies) {
        proxy.reset();
    }
}

uint32_t ScriptManager::findIndex(uint32_t address)
{
    const auto result = std::find_if(m_proxies.begin(), m_proxies.end(), [address](ScriptProxy& proxy) {
        return proxy.doesOriginalAddressMatch(address);
    });

    if (result == m_proxies.end()) {
        return 1025;
    }

    return (*result).getOriginalAddress();
}

void ScriptManager::runHooks(const uint32_t index, const scr_entref_t entref)
{
    m_proxies[index].runHooks(entref);
}
