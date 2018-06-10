#pragma once
#include "hook/Detour.h"
#include "iw4/script.h"

using NotifyFunction = void(*)(unsigned int notifyListOwnerId, unsigned int stringValue, VariableValue *top);

class NotifyDetour: public Detour
{
public:
	static NotifyFunction m_originalNotify;

	long applyDetour() override;
	long restoreDetour() override;

	static void hookNotify(unsigned int notifyListOwnerId, unsigned int stringValue, VariableValue *top);
};
