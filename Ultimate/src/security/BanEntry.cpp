#include "BanEntry.h"

BanEntry::BanEntry(const std::array<uint8_t, 4> ip, const uint64_t steamId)
    : m_ip{ ip }
    , m_steamId{ steamId }
{
}

bool BanEntry::matches(const BanEntry& other) const
{
    return matches(other.m_ip) || matches(other.m_steamId);
}

bool BanEntry::matches(const std::array<uint8_t, 4> ip) const
{
    return m_ip == ip;
}

bool BanEntry::matches(const uint64_t steamId) const
{
    return m_steamId == steamId;
}
