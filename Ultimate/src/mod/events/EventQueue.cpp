#include "EventQueue.h"

void EventQueue::pushEvent(const std::shared_ptr<Event>& event)
{
	std::lock_guard<std::mutex> lock(m_lock);

    std::printf("EventQueue -> Lock push\n");

	m_events.push_back(event);

    std::printf("EventQueue -> pushed 1 event\n");
}

void EventQueue::runEvents()
{
	std::lock_guard<std::mutex> lock(m_lock);

	for (auto event = std::begin(m_events); event != std::end(m_events);) {
		(*event)->execute();
		event = m_events.erase(event);
	}
}
