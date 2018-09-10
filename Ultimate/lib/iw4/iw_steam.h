#pragma once
#include "steam_api.h"
#include "steamclientpublic.h"

struct IWSteamClient
{
    CCallResult<IWSteamClient, LobbyCreated_t> lobbyCreated;
    CCallResult<IWSteamClient, LobbyEnter_t> lobbyEnter;
    CCallResult<IWSteamClient, GameLobbyJoinRequested_t> gameLobbyJoinRequested;
    CCallResult<IWSteamClient, GameOverlayActivated_t> gameOverlayActivated;
    char __unknown[10];
    CSteamID lobbyId; // or, 'const inline steam_lobby_id = reinterpret_cast<uint64_t*>(0x66547B8 + 0x90);'
};

const inline auto g_IWSteamClient = reinterpret_cast<IWSteamClient*>(0x66547B8);
