#include "UltimateConsole.h"
#include <Windows.h>

UltimateConsole::UltimateConsole()
{
    AllocConsole();
    freopen_s(&m_fileOut, "CONOUT$", "w", stdout);
}

UltimateConsole::~UltimateConsole()
{
    fclose(m_fileOut);
    FreeConsole();
}
