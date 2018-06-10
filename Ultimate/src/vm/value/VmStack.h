#pragma once
#include "VMValue.h"
#include <array>

namespace Vm {

#define MAX_STACK_SIZE 8192

struct Stack {
    int32_t m_topIndex{ -1 };
    std::array<Value, MAX_STACK_SIZE> m_stack{};

    void push(Value value);
    Value pop();
    void set(Value value, int32_t offset);
    Value get(int32_t offset);

    void draw();
    void printAll() const;
};
}
