#pragma once
#include "hook/Detour.h"
#include "iw4/entity.h"

using PlayerDieFunction = void (*)(gentity_s* self, gentity_s* inflictor, gentity_s* attacker, int damage, int meansOfDeath, int iWeapon, const float* vDir, hitLocation_t hitLoc, int psTimeOffset);

class PlayerDieDetour : public Detour {
public:
    static PlayerDieFunction m_originalPlayerDie;

    long applyDetour() override;

    long restoreDetour() override;

    static void hookPlayerDie(gentity_s* self, gentity_s* inflictor, gentity_s* attacker, int damage, int meansOfDeath, int iWeapon, const float* vDir, hitLocation_t hitLoc, int psTimeOffset);
};
