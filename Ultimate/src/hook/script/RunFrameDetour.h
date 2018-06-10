#pragma once
#include "hook/Detour.h"
#include "iw4/entity.h"
#include <cstdint>

using RunFrameFunction = void(*)(int32_t);

class RunFrameDetour : public Detour
{
public:
	static RunFrameFunction m_originalRunFrame;

	long applyDetour() override;
	long restoreDetour() override;

    static void hookRunFrame(int32_t levelTime);
};

inline gentity_s *currentLookAt = nullptr;
