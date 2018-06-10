#pragma once
#include "thread/VmThread.h"
#include <array>
#include <atomic>

#define MAX_THREAD_COUNT 1024
#define MAX_NOTIFICATION_COUNT 1024

namespace Vm {

class VirtualMachine {
    bool m_initialized{ false };

    std::array<Thread, MAX_THREAD_COUNT> m_threads{};

    uint32_t m_numTriggers{ 0 };
    std::array<uint32_t, MAX_NOTIFICATION_COUNT> m_triggers{};

    uint32_t m_freeQueuedTriggerSlot{ 0 };
    std::array<uint32_t, MAX_NOTIFICATION_COUNT> m_queuedTriggers{};

    uint32_t firstFreeThread();

    bool isTriggerDefined(uint32_t trigger) const;

public:
    std::atomic<bool> m_interupted{ false };

    void spawnThread(Instruction* entry);
    void notify(uint32_t trigger);
    void frame();
    void run(Thread& thread);
    void draw();
};
}
