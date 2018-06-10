#include "ultimate/Ultimate.h"
#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE /*module*/, const DWORD reason, LPVOID /*reserved*/)
{
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        Ultimate::m_ultimate = std::make_shared<Ultimate>();
        Ultimate::m_ultimate->hook();
        break;
    case DLL_PROCESS_DETACH:
        Ultimate::m_ultimate->unhook();
        Ultimate::m_ultimate.reset();
        break;
    default:
        break;
    }

    return TRUE;
}
