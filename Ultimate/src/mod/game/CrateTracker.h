#pragma once
#include "iw4/entity.h"
#include <mutex>
#include <vector>

struct TimedEntity {
    gentity_s* m_entity;
    int32_t m_time;
};

class CrateTracker {
    std::mutex m_lock;
    std::vector<TimedEntity> m_timedEntities;

public:
    void frame();
    void spawnCarePackage(float *position, float *angle, int32_t time);

};
