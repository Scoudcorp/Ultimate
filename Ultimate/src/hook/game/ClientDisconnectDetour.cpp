#include "ClientDisconnectDetour.h"
#include "ultimate/Ultimate.h"
#include <detours/detours.h>

ClientDisconnectFunction ClientDisconnectDetour::m_originalClientDisconnect;

long ClientDisconnectDetour::applyDetour()
{
	m_originalClientDisconnect = reinterpret_cast<ClientDisconnectFunction>(0x51F830);

	const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalClientDisconnect), &hookClientDisconnect);

	std::printf("Hooked ClientDisconnect\n");

	return result;
}

long ClientDisconnectDetour::restoreDetour()
{
	const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalClientDisconnect), &hookClientDisconnect);

	std::printf("Restored ClientDisconnect\n");

	return result;
}

void ClientDisconnectDetour::hookClientDisconnect(const int clientNum)
{
	Ultimate::m_ultimate->m_activeGame.playerDisconnected(clientNum);

	return m_originalClientDisconnect(clientNum);
}
