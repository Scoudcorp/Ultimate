#pragma once
#include "network.h"
#include "util.h"

namespace Message
{
	IW4_FUNCTION(Init, void, (msg_t *buf, char *data, int length), 0x56FA70);
	IW4_FUNCTION(BeginReading, void, (msg_t *msg), 0x56FB50);
	IW4_FUNCTION(ReadLong, int, (msg_t *msg), 0x5702C0);
	IW4_FUNCTION(ReadShort, int, (msg_t *msg), 0x570260);
	IW4_FUNCTION(WriteLong, void, (msg_t *msg, int c), 0x56FEC0);
	IW4_FUNCTION(WriteData, void, (msg_t *buf, const void *data, int length), 0x56FE30);
}
