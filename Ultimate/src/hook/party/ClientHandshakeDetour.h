#pragma once
#include "../Detour.h"
#include "iw4/network.h"
#include "iw4/party.h"

using ClientHandshakeFunction = void (*)(PartyData_s* party, int localControllerIndex, netadr_t from, msg_t* msg);

class ClientHandshakeDetour : public Detour {
public:
    static ClientHandshakeFunction m_originalClientHandshake;

    long applyDetour() override;
    long restoreDetour() override;

    static void hookClientHandshake(PartyData_s* party, int localControllerIndex, netadr_t from, msg_t* msg);
};
