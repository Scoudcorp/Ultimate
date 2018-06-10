#pragma once
#include "Patch.h"
#include "iw4/command.h"
#include "iw4/dvar.h"
#include <vector>

class PatchManager {
public:
    PatchManager();

    void registerPatch(const Patch& patch);

    void applyPatches();
    void restorePatches();

    void registerCommands();
    void removeCommands();

private:
    std::vector<Patch> m_patches;
};

static inline cmd_function_s g_mapRestart {};
