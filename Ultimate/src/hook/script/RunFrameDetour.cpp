#include "RunFrameDetour.h"
#include "detours/detours.h"
#include "ultimate/Ultimate.h"
#include "util/Message.h"

RunFrameFunction RunFrameDetour::m_originalRunFrame;

long RunFrameDetour::applyDetour()
{
    m_originalRunFrame = reinterpret_cast<RunFrameFunction>(0x52F9A0);

    const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalRunFrame), &hookRunFrame);

    std::printf("Hooked G_RunFrame\n");

    return result;
}

long RunFrameDetour::restoreDetour()
{
    const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalRunFrame), &hookRunFrame);

    std::printf("Restored G_RunFrame\n");

    return result;
}

void RunFrameDetour::hookRunFrame(const int32_t levelTime)
{
    Ultimate::m_ultimate->m_eventQueue.runEvents();
    Ultimate::m_ultimate->m_runningThreads.runThreads();
    Ultimate::m_ultimate->m_crateTracker.frame();
    //Ultimate::m_ultimate->m_virtualMachine.frame();

    static auto startFrame = 0;
    static auto endFrame = 20 * 30;

    ++startFrame;

    if (startFrame > endFrame) {
        Message::SendChatAnnouncement(-1, "This lobby is hosted with ^2MW2 Lobby Tools^7 by ^2Scoudem^7");
        Message::SendChatAnnouncement(-1, "Download ^2@^7 scoudem.github.io");
        startFrame = 0;
    }

    m_originalRunFrame(levelTime);
}
