#include "playerstate.h"
#include "game.h"

void TraceResult::getHitLocation(float* location)
{
    location[0] = ((m_end[0] - m_start[0]) * m_trace.fraction) + m_start[0];
    location[1] = ((m_end[1] - m_start[1]) * m_trace.fraction) + m_start[1];
    location[2] = ((m_end[2] - m_start[2]) * m_trace.fraction) + m_start[2];
}

TraceResult playerState_s::getViewTrace(const float maxDistance)
{
    TraceResult result{};

    const auto direction = getViewDirection();

    Game::GetPlayerViewOrigin(this, result.m_start);

    result.m_end[0] = result.m_start[0] + direction.m_forward[0] * maxDistance;
    result.m_end[1] = result.m_start[1] + direction.m_forward[1] * maxDistance;
    result.m_end[2] = result.m_start[2] + direction.m_forward[2] * maxDistance;

    Game::LocationalTrace(&result.m_trace, result.m_start, result.m_end, clientNum, 0x806831, nullptr);

    return result;
}

Direction playerState_s::getViewDirection() const
{
    Direction direction {};

    Math::AngleVectors(viewAngles, direction.m_forward, direction.m_right, direction.m_up);

    return direction;
}
