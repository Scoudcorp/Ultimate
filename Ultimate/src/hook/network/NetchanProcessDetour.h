#pragma once
#include "hook/Detour.h"
#include "iw4/network.h"

using NetchanProcessFunction = int(*)(netchan_t *chan, msg_t *msg);

class NetchanProcessDetour: public Detour
{
public:
	static NetchanProcessFunction m_originalNetchanProcess;

	long applyDetour() override;
	long restoreDetour() override;

	static int hookNetchanProcess(netchan_t *chan, msg_t *msg);
};
