#pragma once
#include "disasembler/Disassembler.h"
#include <d3d9.h>

class MenuManager {
public:
    MenuManager();

    HWND m_window;
    bool m_open;

	Disassembler m_dissasembler{ *reinterpret_cast<Opcode::Instruction**>(0x1FB77D0) };

    void initializeImGui() const;
	static void shutdownImGui();

    void onEndScene();
    bool onMessage(MSG* message) const;
    bool isMenuOpen() const;
};
