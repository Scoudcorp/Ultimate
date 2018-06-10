#include "RunningThreads.h"

void RunningThreads::runThreads()
{
    std::lock_guard<std::mutex> lock(m_lock);

	for (auto thread = std::begin(m_threads); thread != std::end(m_threads);) {
		if ((*thread)->onFrame()) {
			thread = m_threads.erase(thread);
		}
		else {
			++thread;
		}
    }
}

void RunningThreads::registerThread(const std::shared_ptr<ThreadAction>& thread)
{
    std::lock_guard<std::mutex> lock(m_lock);

    m_threads.push_back(thread);
}
