#pragma once
#include "Event.h"
#include <memory>
#include <mutex> 
#include <vector>

class EventQueue
{
	std::vector<std::shared_ptr<Event>> m_events;
	std::mutex m_lock;

public:
	void pushEvent(const std::shared_ptr<Event>& event);
	void runEvents();
	
};
