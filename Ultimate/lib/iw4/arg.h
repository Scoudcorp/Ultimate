#pragma once
#include "util.h"

struct CmdArgs
{
	int nesting;
	int localClientNum[8];
	int argshift[8];
	int argc[8];
	const char **argv[8];
	char textPool[8192];
	const char *argvPool[512];
	int usedTextPool[8];
	int totalUsedArgvPool;
	int totalUsedTextPool;
};

const inline auto g_serverCmdArgs = reinterpret_cast<CmdArgs*>(0x1B87254);

namespace Server
{
	IW4_FUNCTION(ArgvBuffer, void, (int arg, char *buffer, int bufferLength), 0x564030);
}
