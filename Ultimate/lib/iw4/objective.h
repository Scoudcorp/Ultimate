#pragma once

enum objectiveState_t
{
    OBJST_EMPTY = 0x0,
    OBJST_ACTIVE = 0x1,
    OBJST_INVISIBLE = 0x2,
    OBJST_DONE = 0x3,
    OBJST_CURRENT = 0x4,
    OBJST_FAILED = 0x5,
    OBJST_NUMSTATES = 0x6,
};


struct objective_t
{
    objectiveState_t state;
    float origin[3];
    int entNum;
    int teamNum;
    int icon;
};
