#pragma once
#include <hook/Detour.h>

using DispatchMessageFunction = LRESULT(WINAPI*)(MSG*);

class DispatchMessageDetour : public Detour {
public:
    static DispatchMessageFunction m_originalDispatchMessage;

    long applyDetour() override;
    long restoreDetour() override;

    static LRESULT WINAPI hookDispatchMessage(MSG* message);
};
