#include "PlayerDieDetour.h"
#include "iw4/party.h"
#include "iw4/weapon.h"
#include "settings/Settings.h"
#include "ultimate/Ultimate.h"
#include <detours/detours.h>

PlayerDieFunction PlayerDieDetour::m_originalPlayerDie;

long PlayerDieDetour::applyDetour()
{
    m_originalPlayerDie = reinterpret_cast<PlayerDieFunction>(0x526A00);

    const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalPlayerDie), hookPlayerDie);

    std::printf("Hooked player_die\n");

    return result;
}

long PlayerDieDetour::restoreDetour()
{
    const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalPlayerDie), hookPlayerDie);

    std::printf("Restored player_die\n");

    return result;
}

void PlayerDieDetour::hookPlayerDie(
    gentity_s* self, gentity_s* inflictor, gentity_s* attacker,
    const int damage, const int meansOfDeath, const int iWeapon,
    const float* vDir, const hitLocation_t hitLoc, const int psTimeOffset)
{
    if (!self) {
        return;
    }

    if (!attacker) {
        Ultimate::m_ultimate->m_activeGame.playerSuicide(self->state.number);
    }

    const auto weaponName = BG_WeaponName(iWeapon);
    const auto attackerName = attacker->client ? Party::g_partyData->partyMembers[attacker->state.number].name : "undefined";
    const auto selfName = self->client ? Party::g_partyData->partyMembers[self->state.number].name : "undefined";

    if (g_settings.m_logSettings.m_logDeaths) {
        std::printf("player_die -> %s killed %s with %s\n", attackerName, selfName, weaponName);
    }

    Ultimate::m_ultimate->m_activeGame.playerSuicide(self->state.number);

    return m_originalPlayerDie(self, inflictor, attacker, damage, meansOfDeath, iWeapon, vDir, hitLoc, psTimeOffset);
}
