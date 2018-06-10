#pragma once
#include "Event.h"
#include "iw4/script.h"

class EntityEvent: public Event
{
	using EntityCallback = void(*)(int32_t);

	int32_t m_entNum;
	EntityCallback m_callback;

public:

	EntityEvent(const int32_t entref, const EntityCallback callback)
		: m_entNum(entref)
		, m_callback(callback)
	{
	}

	void execute() override;
};
