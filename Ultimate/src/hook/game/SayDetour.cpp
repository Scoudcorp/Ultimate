#include "SayDetour.h"
#include "iw4/party.h"
#include "iw4/server.h"
#include "settings/Settings.h"
#include "ultimate/Ultimate.h"
#include "util/Message.h"
#include <detours/detours.h>

SayFunction SayDetour::m_originalSay;

long SayDetour::applyDetour()
{
    m_originalSay = reinterpret_cast<SayFunction>(0x5260E0);

    const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalSay), hookSay);

    std::printf("Hooked G_Say\n");

    return result;
}

long SayDetour::restoreDetour()
{
    const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalSay), hookSay);

    std::printf("Restored G_Say\n");

    return result;
}

void SayDetour::hookSay(gentity_s* from, gentity_s* to, const int mode, const char* chatText)
{
	const auto text = &chatText[1];

    if (g_settings.m_logSettings.m_logChat) {
        const auto name = Party::g_partyData->partyMembers[from->state.number].name;

        std::printf("G_Say: %2d - %s: %s\n", from->state.number, name, text);
    }

	if (from->state.number == *g_hostId)
	{
		if (text[0] == '!')
		{
			return Message::SendHostChat(-1, text + 1);
		}
	}

	return m_originalSay(from, to, mode, chatText);
}
