#include "party.h"

std::array<uint8_t, 4> PartyClient::getRemoteIp() const
{
    std::array<uint8_t, 4> out{};

    std::copy(remoteIp, remoteIp + 4, out.begin());

    return out;
}
