#pragma once
#include "../Detour.h"

using CanHostServerFunction = bool (*)(int numplayers);

class CanHostServerDetour : public Detour {
public:
    static CanHostServerFunction m_originalCanHostServer;

    long applyDetour() override;

    long restoreDetour() override;

    static bool hookCanHostServer(int numplayers);
};
