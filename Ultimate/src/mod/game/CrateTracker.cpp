#include "CrateTracker.h"
#include "iw4/game.h"

void CrateTracker::frame()
{
    std::lock_guard<std::mutex> lock(m_lock);

    for (auto item = std::begin(m_timedEntities); item != std::end(m_timedEntities);) {
        if (item->m_time <= 0) {
            if (item->m_entity && item->m_entity->state.number > 0) {
                Game::FreeEntity(item->m_entity);
                item->m_entity = nullptr;
            }

            item = m_timedEntities.erase(item);
        } else {
            --item->m_time;
            ++item;
        }
    }
}

void CrateTracker::spawnCarePackage(float* position, float* angle, const int32_t time)
{
    std::lock_guard<std::mutex> lock(m_lock);

    TimedEntity entity{};
    entity.m_entity = Entity::SpawnCarePackage(position, angle);
    entity.m_time = time;

    m_timedEntities.push_back(entity);
}
