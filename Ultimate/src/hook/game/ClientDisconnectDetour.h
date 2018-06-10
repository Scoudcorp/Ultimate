#pragma once
#include "hook/Detour.h"

using ClientDisconnectFunction = void(*)(int);

class ClientDisconnectDetour : public Detour {
public:

	static ClientDisconnectFunction m_originalClientDisconnect;

	long applyDetour() override;

	long restoreDetour() override;

	static void hookClientDisconnect(int clientNum);
};
