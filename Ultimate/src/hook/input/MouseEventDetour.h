#pragma once
#include "../Detour.h"

using MouseEventFunction = int (*)(int x, int y, int dx, int dy);

class MouseEventDetour : public Detour {
public:
    static MouseEventFunction m_originalMouseEvent;

    long applyDetour() override;

    long restoreDetour() override;

    static int hookMouseEvent(int x, int y, int dx, int dy);
};
