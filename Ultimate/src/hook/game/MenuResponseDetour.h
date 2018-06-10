#pragma once
#include "hook/Detour.h"
#include "iw4/entity.h"

using MenuResponseFunction = void(*)(gentity_s*);

class MenuResponseDetour : public Detour
{
public:
	static MenuResponseFunction m_originalMenuResponse;

	long applyDetour() override;
	long restoreDetour() override;

	static void hookMenuResponse(gentity_s *entity);
};
