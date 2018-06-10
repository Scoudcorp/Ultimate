#include "AccessControl.h"
#include "hook/server/GameSendServerCommandDetour.h"
#include "iw4/iw_string.h"
#include "iw4/party.h"
#include "util/Message.h"

void AccessControl::ban(const std::array<uint8_t, 4> ip, const uint64_t steamId)
{
    const auto entry = BanEntry(ip, steamId);
    m_bans.push_back(entry);

	std::printf("AccessControl -> banned %d.%d.%d.%d (%llu)\n", ip[0], ip[1], ip[2], ip[3], steamId);
}

void AccessControl::kickClient(const int32_t clientNum, const char* message)
{
	const auto member = &Party::g_partyData->partyMembers[clientNum];

	const auto reason = String::Format("%s^7: %s", member->name, message);

	Message::SendChatAnnouncement(-1, reason);
	SV_GameDropClient(clientNum, reason);
}

void AccessControl::banClient(const int32_t clientNum, const char* message)
{
	const auto member = &Party::g_partyData->partyMembers[clientNum];

	ban(member->getRemoteIp(), member->steamId);

	const auto reason = String::Format("%s^7: %s", member->name, message);

	Message::SendChatAnnouncement(-1, reason);
	SV_GameDropClient(clientNum, reason);
}

AccessRights AccessControl::getAccessRights(std::array<uint8_t, 4> ip)
{
    const auto match = std::find_if(m_bans.begin(), m_bans.end(), [&ip](auto& ban) {
        return ban.matches(ip);
    });

    if (match == m_bans.end()) {
        return AccessRights::FullAccess;
    }

    return AccessRights::Banned;
}
