#include "VmStack.h"
#include "mod/weapon/WeaponClassRule.h"

void Vm::Stack::push(const Value value)
{
    ++m_topIndex;
    m_stack[m_topIndex] = value;
}

Vm::Value Vm::Stack::pop()
{
    const auto value = m_stack[m_topIndex];
    --m_topIndex;
    return value;
}

void Vm::Stack::set(const Value value, const int32_t offset)
{
    m_stack[offset] = value;
}

Vm::Value Vm::Stack::get(const int32_t offset)
{
    return m_stack[offset];
}

void Vm::Stack::draw()
{
    ImGui::Text("Stack size: %d", m_topIndex + 1);
    for (auto i = 0; i <= m_topIndex; i++) {
        ImGui::Text("---%d---", i);
        m_stack[i].draw();
        ImGui::Separator();
    }
}

void Vm::Stack::printAll() const
{
    for (auto i = 0; i <= m_topIndex; i++) {
        m_stack[i].printAll();
    }
}
