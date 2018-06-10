#pragma once
#include "entity.h"
#include "objective.h"

struct level_locals_t
{
    gclient_s *clients;
    gentity_s *gentities;
    int num_entities;
    void *firstFreeEnt;
    void *lastFreeEnt;
    void *turrets;
    void *logFile;
    int initializing;
    int clientSpawning;
    objective_t objectives[32];
    int maxclients;
    int framenum;
    int time;
    int previousTime;
    int frameTime;
    int startTime;
};

const inline auto g_level = reinterpret_cast<level_locals_t*>(0x1B4B558);
