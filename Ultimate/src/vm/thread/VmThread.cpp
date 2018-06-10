#include "VmThread.h"
#include "imgui/imgui.h"

void Vm::Thread::draw()
{
    ImGui::Text("Thread %d", m_index);
    ImGui::Text("Wait Trigger %d", m_waitTrigger);
    ImGui::Text("Stop Trigger %d", m_stopTrigger);
    ImGui::Text("Wait frames %d", m_waitFrames);

    m_context.draw();
}
