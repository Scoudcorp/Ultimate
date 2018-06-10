#include "NotifyDetour.h"
#include "detours/detours.h"
#include "iw4/iw_string.h"
#include "ultimate/Ultimate.h"

NotifyFunction NotifyDetour::m_originalNotify;

long NotifyDetour::applyDetour()
{
    m_originalNotify = reinterpret_cast<NotifyFunction>(0x57FBB0);

    const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalNotify), &hookNotify);

    std::printf("Hooked VM_Notify\n");

    return result;
}

long NotifyDetour::restoreDetour()
{
    const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalNotify), &hookNotify);

    std::printf("Restored VM_Notify\n");

    return result;
}

void NotifyDetour::hookNotify(const unsigned int notifyListOwnerId, const unsigned int stringValue, VariableValue * top)
{
    if (stringValue == 14532) {
        const auto killStreak = top->u.intValue;
        const auto self = Script::GetSelf(notifyListOwnerId);

        Ultimate::m_ultimate->m_activeGame.setKillStreak(self, killStreak);
    }

    return m_originalNotify(notifyListOwnerId, stringValue, top);
}
