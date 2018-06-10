#include "ClientHandshakeDetour.h"
#include "detours/detours.h"
#include "settings/Settings.h"
#include "ultimate/Ultimate.h"

ClientHandshakeFunction ClientHandshakeDetour::m_originalClientHandshake;

long ClientHandshakeDetour::applyDetour()
{
    m_originalClientHandshake = reinterpret_cast<ClientHandshakeFunction>(0x4DB0C0);

    const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalClientHandshake), hookClientHandshake);

    std::printf("Hooked PartyHost_HandleClientHandshake\n");

    return result;
}

long ClientHandshakeDetour::restoreDetour()
{
    const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalClientHandshake), hookClientHandshake);

    std::printf("Restored PartyHost_HandleClientHandshake\n");

    return result;
}

void ClientHandshakeDetour::hookClientHandshake(PartyData_s* party, const int localControllerIndex, netadr_t from, msg_t* msg)
{
    const auto ip = from.getIp();
    const auto accessRights = Ultimate::m_ultimate->m_accessControl.getAccessRights(ip);

    switch (accessRights) {
    case AccessRights::FullAccess:
        if (g_settings.m_logSettings.m_logAllowedHandshakes) {
            std::printf("Allowing %03u.%03u.%03u.%03u to enter the server\n", from.ip[0], from.ip[1], from.ip[2], from.ip[3]);
        }
        return m_originalClientHandshake(party, localControllerIndex, from, msg);
    default:
        if (g_settings.m_logSettings.m_logDeniedHandshakes) {
            std::printf("Blocking %03u.%03u.%03u.%03u from entering the server\n", from.ip[0], from.ip[1], from.ip[2], from.ip[3]);
        }
        break;
    }
}
