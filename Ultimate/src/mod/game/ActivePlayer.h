 #pragma once
#include "hook/party/ClientHandshakeDetour.h"
#include "iw4/gclient.h"
#include "iw4/hudelem.h"
#include <array>
#include <cstdint>

class ActivePlayer {

public:
    ActivePlayer()
        : m_index(0)
        , m_active(false)
        , m_kills(0)
        , m_deaths(0)
        , m_killstreak(0)
        , m_nextRandomWeapons{ nullptr, nullptr }
        , m_currentRandomWeaponIndex(0)
        , m_nextRandomEquipment{ nullptr, nullptr }
        , m_currentRandomEquipmentIndex(0)
        , m_hudKillStreak(nullptr)
    {
    }

    uint32_t m_index;

    bool m_active;

    uint32_t m_kills;
    uint32_t m_deaths;
    uint32_t m_killstreak;

    std::array<const char*, 2> m_nextRandomWeapons;
    uint32_t m_currentRandomWeaponIndex;

    std::array<const char*, 2> m_nextRandomEquipment;
    uint32_t m_currentRandomEquipmentIndex;

    game_hudelem_s* m_hudKillStreak;

    void reset();
    void addDeath();
    void addKill();

    PartyClient* getPartyClient() const;

    void initHud();
    void updateKillStreakHud();

    void draw();
};
