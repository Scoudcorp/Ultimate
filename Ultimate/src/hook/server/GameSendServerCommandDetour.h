#pragma once
#include "hook/Detour.h"
#include "iw4/server.h"

using GameSendServerCommandFunction = void(*)(int, svscmd_type, const char*);

class GameSendServerCommandDetour : public Detour {
public:

	static GameSendServerCommandFunction m_originalGameSendServerCommand;

	long applyDetour() override;

	long restoreDetour() override;

	static void hookGameSendServerCommand(int clientNum, svscmd_type type, const char *fmt);
};
