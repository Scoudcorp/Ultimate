#pragma once
#include "iw4/dvar.h"
#include "iw4/network.h"
#include "iw4/party.h"

struct PartySettings {

    PartySettings()
        : m_minLobbyTime{ Dvar::FindDvar("party_minLobbyTime") }
        , m_connectTimeOut{ Dvar::FindDvar("party_connectTimeout") }
        , m_bandwithTestEnabled{ Dvar::FindDvar("bandwidthtest_enable") }
        , m_autoTeams{ Dvar::FindDvar("party_autoTeams") }
        , m_maxTeamDifference{ Dvar::FindDvar("party_maxTeamDiff") }
        , m_requireOpenNat{ Dvar::FindDvar("requireOpenNat") }
        , m_migrateTimoutMax{ Dvar::FindDvar("partymigrate_timeoutmax") }
        , m_doWeSuckAsHost{ reinterpret_cast<bool*>(0x6427E66) }
        , m_natType{ reinterpret_cast<UPNP_NatType*>(0x85CCC0) }
        , m_maxClients{ &Party::g_partyData->gameSession->publicSlots }
        , m_forceHost{ false }
    {
    }

    dvar_s* m_minLobbyTime;
    dvar_s* m_connectTimeOut;
    dvar_s* m_bandwithTestEnabled;
    dvar_s* m_autoTeams;
    dvar_s* m_maxTeamDifference;
    dvar_s* m_requireOpenNat;
    dvar_s* m_migrateTimoutMax;
    bool* m_doWeSuckAsHost;
    UPNP_NatType* m_natType;
    int32_t* m_maxClients;
    bool m_forceHost;

    void drawPartySettings();
};

struct LogSettings {

    LogSettings()
        : m_logDeaths{ false }
        , m_logChat{ true }
        , m_logAllowedHandshakes{ false }
        , m_logDeniedHandshakes{ true }
        , m_logWeapons{ false }
        , m_logClientDvars{ false }
        , m_logPerks{ false }
        , m_logSpawnWeapons{ false }
        , m_logSpawn{ false }
        , m_logLoadoutControl{ false }
        , m_logXAssetLookups{ false }
        , m_logXAssetFilter{ -1 }
        , m_logMenuResponses{ false }
        , m_logAccessViolations{ true }
        , m_logServerCommands{ false }
    {
    }

    bool m_logDeaths;
    bool m_logChat;
    bool m_logAllowedHandshakes;
    bool m_logDeniedHandshakes;
    bool m_logWeapons;
    bool m_logClientDvars;
    bool m_logPerks;
    bool m_logSpawnWeapons;
    bool m_logSpawn;
    bool m_logLoadoutControl;
    bool m_logXAssetLookups;
    int m_logXAssetFilter;
    bool m_logMenuResponses;
    bool m_logAccessViolations;
    bool m_logServerCommands;

    void drawLogSettings();
};

struct ModSettings {
    ModSettings()
        : m_randomWeaponModEnabled{ false }
    {
    }

    bool m_randomWeaponModEnabled;

    void drawModSettings();
};

struct GameSettings {
    GameSettings()
        : m_forcedFov{ 80 }
    {
    }

    int m_forcedFov;

    void drawGameSettings();
};

struct Settings {

    PartySettings m_partySettings;
    LogSettings m_logSettings;
    ModSettings m_modSettings;
    GameSettings m_gameSettings;

    void drawSettings();
};

inline Settings g_settings{};
