#pragma once
#include "hook/Detour.h"
#include "iw4/entity.h"

using SayFunction = void (*)(gentity_s* ent, gentity_s* target, int mode, const char* chatText);

class SayDetour : public Detour {
public:
    static SayFunction m_originalSay;

    long applyDetour() override;

    long restoreDetour() override;

    static void hookSay(gentity_s* ent, gentity_s* target, int mode, const char* chatText);
};
