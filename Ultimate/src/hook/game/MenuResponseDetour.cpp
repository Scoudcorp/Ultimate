#include "MenuResponseDetour.h"
#include "detours/detours.h"
#include "iw4/arg.h"
#include "iw4/server.h"
#include "settings/Settings.h"
#include "ultimate/Ultimate.h"

MenuResponseFunction MenuResponseDetour::m_originalMenuResponse = nullptr;

long MenuResponseDetour::applyDetour()
{
    m_originalMenuResponse = reinterpret_cast<MenuResponseFunction>(0x525860);

    const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalMenuResponse), &hookMenuResponse);

    std::printf("Hooked Cmd_MenuResponse_f\n");

    return result;
}

long MenuResponseDetour::restoreDetour()
{
    const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalMenuResponse), &hookMenuResponse);

    std::printf("Restored Cmd_MenuResponse_f\n");

    return result;
}

void MenuResponseDetour::hookMenuResponse(gentity_s* entity)
{
    constexpr auto bufferSize = 1024;

    char serverIdBuffer[bufferSize];
    char menuNameBuffer[bufferSize];
    char responseBuffer[bufferSize];

    if (g_serverCmdArgs->argc[g_serverCmdArgs->nesting] == 4) {
        Server::ArgvBuffer(1, serverIdBuffer, bufferSize);
        const auto serverId = std::atoi(serverIdBuffer);
        if (serverId != *g_serverId) {
            return;
        }

        Server::ArgvBuffer(2, menuNameBuffer, bufferSize);
        const auto menuId = std::atoi(menuNameBuffer);
        if (menuId <= 0x1F) {
            Server::GetConfigString(menuId + 2453, menuNameBuffer, bufferSize);
        }

        Server::ArgvBuffer(3, responseBuffer, bufferSize);

        const auto clientNum = entity->client->playerState.clientNum;

        if (g_settings.m_logSettings.m_logMenuResponses) {
            std::printf("Cmd_MenuRespone_f: received menu response from %d: %d - %s (%d) - %s\n", clientNum, serverId, menuNameBuffer, menuId, responseBuffer);
        }

        if (std::strcmp(responseBuffer, "endround") == 0) {
            if (clientNum == *g_hostId) {
				if (g_settings.m_logSettings.m_logAccessViolations) {
					std::printf("Cmd_MenuRespone_f: allowing endround call for host\n");
				}
				return m_originalMenuResponse(entity);
            }

	        if (g_settings.m_logSettings.m_logAccessViolations) {
		        std::printf("Cmd_MenuRespone_f: endround response from client %d\n", clientNum);
	        }

	        Ultimate::m_ultimate->m_accessControl.banClient(clientNum, "it seems like you ended your own game...");
        }
    }

    return m_originalMenuResponse(entity);
}
