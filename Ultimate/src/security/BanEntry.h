#pragma once

#include <array>
#include <cstdint>

class BanEntry {
public:
    const std::array<uint8_t, 4> m_ip;
    const uint64_t m_steamId;

    BanEntry(std::array<uint8_t, 4> ip, uint64_t steamId);

    bool matches(const BanEntry& other) const;
    bool matches(std::array<uint8_t, 4> ip) const;
    bool matches(uint64_t steamId) const;
};
