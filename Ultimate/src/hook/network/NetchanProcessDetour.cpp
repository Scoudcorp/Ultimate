#include "NetchanProcessDetour.h"
#include "detours/detours.h"
#include "iw4/message.h"

NetchanProcessFunction NetchanProcessDetour::m_originalNetchanProcess;

long NetchanProcessDetour::applyDetour()
{
    m_originalNetchanProcess = reinterpret_cast<NetchanProcessFunction>(0x572BA0);

    const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalNetchanProcess), &hookNetchanProcess);

    std::printf("Hooked Netchan_Process\n");

    return result;
}

long NetchanProcessDetour::restoreDetour()
{
    const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalNetchanProcess), &hookNetchanProcess);

    std::printf("Restored Netchan_Process\n");

    return result;
}

int NetchanProcessDetour::hookNetchanProcess(netchan_t* chan, msg_t* msg)
{
    Message::BeginReading(msg);

    auto sequence = Message::ReadLong(msg);

    int fragmented;
    if (sequence >= 0) {
        fragmented = 0;
    } else {
        sequence &= 0x7FFFFFFF;
        fragmented = 1;
    }

    if (chan->sock == 1) {
        Message::ReadShort(msg);
    }

    auto chana = 0;
    auto v5 = 0;
    if (fragmented) {
        chana = Message::ReadLong(msg);
        v5 = Message::ReadShort(msg);
    }

    const auto v8 = chan->incomingSequence;

    if (sequence <= v8) {
        return 0;
    }

    chan->dropped = sequence - v8 - 1;

    if (fragmented) {
        if (sequence != chan->fragmentLength) {
            chan->fragmentLength = sequence;
            chan->fragmentBuffer = 0;
        }

        const auto fragmentBuffer = chan->fragmentBuffer;

        if (reinterpret_cast<char*>(chana) != fragmentBuffer) {
            return 0;
        }

        if (v5 < 0) {
            return 0;
        }

        const auto v11 = msg->readcount;
        if (v11 + v5 > msg->cursize) {
            return 0;
        }

        if (reinterpret_cast<signed int>(&fragmentBuffer[v5]) > chan->unsentFragments) {
            return 0;
        }

        if (v5 > msg->maxsize) {
			//std::printf("Netchan_Process -> message claims size is %d but max size is %d\n", v5, msg->maxsize);
			return 0;
        }

        memcpy(&fragmentBuffer[chan->fragmentBufferSize], &msg->data[v11], v5);

        const auto v12 = chan->remoteAddress.type;
        chan->fragmentBuffer += v5;

        if (v5 == (v12 != 2 ? 1300 : 1386) || reinterpret_cast<int>(chan->fragmentBuffer) > msg->maxsize) {
            return 0;
        }

        Message::Init(msg, msg->data, msg->maxsize);
        Message::WriteLong(msg, sequence);
        Message::WriteData(msg, reinterpret_cast<const void*>(chan->fragmentBufferSize), reinterpret_cast<int>(chan->fragmentBuffer));

        chan->fragmentBuffer = 0;

        Message::BeginReading(msg);
        Message::ReadLong(msg);
    }

    chan->incomingSequence = sequence;
    return 1;
}
