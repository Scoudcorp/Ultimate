#pragma once
#include "hook/Detour.h"
#include <iw4/entity.h>

using RegisterMethodFunction = void (*)(void (*)(scr_entref_t));

class RegisterMethodDetour : public Detour {
public:

    static RegisterMethodFunction m_originalRegisterMethod;

    long applyDetour() override;

    long restoreDetour() override;

    static void hookRegisterMethod(void (*method)(scr_entref_t));
};
