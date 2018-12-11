#pragma once

#include "UltimateConsole.h"
#include "mod/LoadoutControl.h"
#include "mod/events/EventQueue.h"
#include "mod/game/ActiveGame.h"
#include "mod/game/CrateTracker.h"
#include "mod/thread/RunningThreads.h"
#include "security/AccessControl.h"
#include "vm/VirtualMachine.h"
#include <memory>
#include <menu/MenuManager.h>
#include <patch/PatchManager.h>

class Ultimate {

public:
    static std::shared_ptr<Ultimate> m_ultimate;

    Ultimate();

    void hook();
    void unhook();

    void onEndScene();
    bool onMessage(MSG* message) const;

    UltimateConsole m_console;
    PatchManager m_patchManager;
    MenuManager m_menuManager;
    AccessControl m_accessControl;
    LoadoutControl m_loadoutControl;
	ActiveGame m_activeGame;
	RunningThreads m_runningThreads;
	EventQueue m_eventQueue;
    Vm::VirtualMachine m_virtualMachine;
    CrateTracker m_crateTracker;

    bool m_hooked;
};
