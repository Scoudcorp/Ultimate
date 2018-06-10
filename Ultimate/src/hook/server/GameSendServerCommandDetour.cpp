#include "GameSendServerCommandDetour.h"
#include "settings/Settings.h"
#include "ultimate/Ultimate.h"
#include <detours/detours.h>

GameSendServerCommandFunction GameSendServerCommandDetour::m_originalGameSendServerCommand;

long GameSendServerCommandDetour::applyDetour()
{
	m_originalGameSendServerCommand = reinterpret_cast<GameSendServerCommandFunction>(0x588480);

	const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalGameSendServerCommand), &hookGameSendServerCommand);

	std::printf("Hooked SV_GameSendServerCommand\n");

	return result;
}

long GameSendServerCommandDetour::restoreDetour()
{
	const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalGameSendServerCommand), &hookGameSendServerCommand);

	std::printf("Restored SV_GameSendServerCommand\n");

	return result;
}

void GameSendServerCommandDetour::hookGameSendServerCommand(const int clientNum, const svscmd_type type, const char* fmt)
{
	if (g_settings.m_logSettings.m_logServerCommands) {
		std::printf("SV_GameSendServerCommand: %d (%10s) -> %s\n", clientNum, type == svscmd_type::SV_CMD_CAN_IGNORE ? "unreliable" : "reliable", fmt);
	}

	return m_originalGameSendServerCommand(clientNum, type, fmt);
}
