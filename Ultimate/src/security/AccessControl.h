#pragma once
#include "BanEntry.h"
#include <array>
#include <vector>

enum class AccessRights {
    FullAccess,
    Banned
};

class AccessControl {
public:
    void ban(std::array<uint8_t, 4> ip, uint64_t steamId);

	void kickClient(int32_t clientNum, const char* message);
	void banClient(int32_t clientNum, const char* message);

    AccessRights getAccessRights(std::array<uint8_t, 4> ip);

private:
    std::vector<BanEntry> m_bans;
};
