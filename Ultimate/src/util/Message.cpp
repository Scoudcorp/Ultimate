#include "Message.h"
#include "iw4/iw_string.h"
#include "iw4/party.h"
#include "iw4/server.h"

void Message::SendHostChat(const char* message)
{
	SendHostChat(-1, message);
}

void Message::SendHostChat(const int32_t playerNum, const char* message)
{
	const auto name = String::Format("^2MW2LT ^7(%s^7)", Party::g_partyData->partyMembers[*g_hostId].name);
	SendChat(playerNum, name, message);
}

void Message::SendChat(const int32_t playerNum, const char* name, const char* message)
{
	const auto command = String::Format("U \"%c%c%s: ^7\x15%s\"", '\x15', '\x15', name, message);

	if (playerNum == -1) {
		for (auto i = 0; i < 18; i++) {
			SV_GameSendServerCommand(i, svscmd_type::SV_CMD_RELIABLE, command);
		}
	}
	else {
		SV_GameSendServerCommand(playerNum, svscmd_type::SV_CMD_RELIABLE, command);
	}
}

void Message::SendChatAnnouncement(const int32_t playerNum, const char* message)
{
	SendChat(playerNum, "^2MW2LT^7", message);
}

void Message::SendHostAnnouncement(const int32_t playerNum, const char* message)
{
    const auto command = String::Format("c \"%\"",  message);
    SV_GameSendServerCommand(playerNum, svscmd_type::SV_CMD_RELIABLE, command);
}
