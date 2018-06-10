#include "CanHostServerDetour.h"
#include <detours/detours.h>

CanHostServerFunction CanHostServerDetour::m_originalCanHostServer;

long CanHostServerDetour::applyDetour()
{
	m_originalCanHostServer = reinterpret_cast<CanHostServerFunction>(0x5C7430);

	const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalCanHostServer), hookCanHostServer);

	std::printf("Hooked Live_CanHostServer\n");

	return result;
}

long CanHostServerDetour::restoreDetour()
{
	const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalCanHostServer), &hookCanHostServer);

	std::printf("Restored Live_CanHostServer\n");

	return result;
}

bool CanHostServerDetour::hookCanHostServer(int numplayers)
{
	return true;
}
