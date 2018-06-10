#pragma once
#include "vm/context/VmContext.h"
#include "vm/value/VMValue.h"

#define INVALID_TRIGGER 0

namespace Vm {

struct Thread {
    bool m_free{ true };
    uint32_t m_index{ 0 };
    uint32_t m_waitFrames{ 0 };
    uint32_t m_stopTrigger{ INVALID_TRIGGER };
    uint32_t m_waitTrigger{ INVALID_TRIGGER };
    Context m_context{};

    void draw();
};
}
