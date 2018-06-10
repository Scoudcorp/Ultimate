#include "network.h"

std::array<uint8_t, 4> netadr_t::getIp()
{
    std::array<uint8_t, 4> out{};

    std::copy(ip, ip + 4, out.begin());

    return out;
}

namespace Network {
std::string_view UPNP_NatTypeToString(const UPNP_NatType natType)
{
    switch (natType) {
    case NAT_OPEN:
        return "Open";
    case NAT_MODERATE:
        return "Moderate";
    case NAT_STRICT:
        return "Strict";
    default:
        return "Unknown";
    }
}
}
