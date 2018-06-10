#pragma once
#include "VmInstruction.h"
#include "vm/value/VmStack.h"

namespace Vm {

struct Context {
    Instruction *m_currentInstruction{};
    uint32_t m_stackBaseIndex {0};
    Stack m_stack {};

    void draw();
};

}
