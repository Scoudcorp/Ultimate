#pragma once

#include "Detour.h"
#include "script/ScriptManager.h"
#include <memory>
#include <vector>

class DetourManager {
public:
    DetourManager();

    void hook();
    void unhook();

    void registerDetour(const std::shared_ptr<Detour>& detour);

    ScriptManager m_scriptManager;

private:
    std::vector<std::shared_ptr<Detour>> m_detours;

    static long beginTransaction();
    static long applyDetour(const std::shared_ptr<Detour>&);
    static long restoreDetour(const std::shared_ptr<Detour>&);
    static long commitTransaction();
};

inline DetourManager g_detours{};
