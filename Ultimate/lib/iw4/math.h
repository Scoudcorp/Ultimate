#pragma once
#include "util.h"

struct Direction
{
    float m_forward[3];
    float m_right[3];
    float m_up[3];
};

namespace Math {

    IW4_FUNCTION(AngleVectors, void, (const float *angles, float *forward, float *right, float *up), 0x5B74E0);

}
