#include "VmContext.h"
#include "imgui/imgui.h"

void Vm::Context::draw()
{
    ImGui::Text("Frame offset: %d", m_stackBaseIndex);
    m_stack.draw();
}
