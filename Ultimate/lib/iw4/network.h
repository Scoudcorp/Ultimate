#pragma once

#include <array>
#include <cstdint>

enum netadrtype_t {
    NA_BOT = 0x0,
    NA_BAD = 0x1,
    NA_LOOPBACK = 0x2,
    NA_BROADCAST = 0x3,
    NA_IP = 0x4,
};

struct netadr_t {
    netadrtype_t type;
    union {
        uint8_t ip[4];
        uint8_t ipx[8];
    };
    uint16_t port;
    int32_t addrHandleIndex;

    std::array<uint8_t, 4> getIp();
};

struct msg_t {
    int overflowed;
    int readOnly;
    char* data;
    char* splitData;
    int maxsize;
    int cursize;
    int splitSize;
    int readcount;
    int bit;
    int lastEntityRef;
};

enum netsrc_t {
    NS_CLIENT = 0x0,
    NS_SERVER = 0x1,
};

struct netProfilePacket_t {
    int iTime;
    int iSize;
    int bFragment;
};

struct netProfileStream_t {
    netProfilePacket_t packets[60];
    int iCurrPacket;
    int iBytesPerSecond;
    int iLastBPSCalcTime;
    int iCountedPackets;
    int iCountedFragments;
    int iFragmentPercentage;
    int iLargestPacket;
    int iSmallestPacket;
};

struct netProfileInfo_t {
    netProfileStream_t send;
    netProfileStream_t recieve;
};

struct netchan_t {
    int outgoingSequence;
    netsrc_t sock;
    int dropped;
    int incomingSequence;
    netadr_t remoteAddress;
    int fragmentSequence;
    int fragmentLength;
    char* fragmentBuffer;
    int fragmentBufferSize;
    int unsentFragments;
    int unsentFragmentStart;
    int unsentLength;
    char* unsentBuffer;
    int unsentBufferSize;
    netProfileInfo_t prof;
};

enum UPNP_NatType {
    NAT_UNKNOWN = 0x0,
    NAT_OPEN = 0x1,
    NAT_MODERATE = 0x2,
    NAT_STRICT = 0x3,
};

namespace Network {
std::string_view UPNP_NatTypeToString(UPNP_NatType natType);
}
