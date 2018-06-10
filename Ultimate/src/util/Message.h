#pragma once
#include <cstdint>

namespace Message
{

	void SendHostChat(const char *message);
	void SendHostChat(int32_t playerNum, const char *message);
	void SendChat(int32_t playerNum, const char* name, const char* message);

	void SendChatAnnouncement(int32_t playerNum, const char *message);
	void SendHostAnnouncement(int32_t playerNum, const char *message);
}
