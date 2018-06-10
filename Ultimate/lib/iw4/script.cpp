#include "script.h"
#include "iw_string.h"
#include "level.h"

std::vector<gentity_s*> Script::GetEntArray(const char* key, const char* value)
{
    std::vector<gentity_s*> results{};

    if (!key || !value) {
        return results;
    }

    const auto valueIndex = String::GetString(value, 0);

    const auto field = *reinterpret_cast<int32_t*>(20 * Script::GetOffset(0, key).intValue + 0x69B9B8 + 0x04);

    for (auto i = 0; i < g_level->num_entities; ++i) {

        const auto entity = &g_entities[i];

        if (!entity->shared.inuse) {
            continue;
        }

        const auto valueAtOffset = *reinterpret_cast<unsigned int*>((reinterpret_cast<char*>(entity) + field));

        if (valueAtOffset == valueIndex) {
            results.push_back(&g_entities[entity->state.number]);
        }
    }

    return results;
}
