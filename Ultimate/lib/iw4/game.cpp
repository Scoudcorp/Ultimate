#include "game.h"
#include "script.h"
#include "server.h"

void Game::Suicide(const int32_t index)
{
    const auto entity = &g_entities[index];

    if (!entity->client) {
        std::printf("Suicide -> entity %d is not a client\n", index);
        return;
    }

    const auto hostEntity = &g_entities[*g_hostId];

    player_die(entity, nullptr, hostEntity, 100, MOD_SUICIDE, entity->health, nullptr, HITLOC_NONE, 0);
}
