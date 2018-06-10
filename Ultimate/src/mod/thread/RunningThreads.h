#pragma once
#include "ThreadAction.h"
#include <memory>
#include <mutex>
#include <vector>

class RunningThreads
{
    std::mutex m_lock;
	std::vector<std::shared_ptr<ThreadAction>> m_threads;

public:
	void runThreads();

	void registerThread(const std::shared_ptr<ThreadAction>& thread);

};
