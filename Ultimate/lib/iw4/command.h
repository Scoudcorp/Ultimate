#pragma once
#include "util.h"

struct cmd_function_s
{
    cmd_function_s *next;
    const char *name;
    const char *autoCompleteDir;
    const char *autoCompleteExt;
    void(__cdecl *function)();
};

namespace Cmd {

	IW4_FUNCTION(ExecuteSingleCommand, void, (int localClientNum, int argc, const char* text), 0x5648D0);
	IW4_FUNCTION(AddCommandToBuffer, void, (int localClientNum, const char* text), 0x563D10);
    IW4_FUNCTION(AddCommandInternal, void, (const char *cmdName, void(__cdecl *function)(), cmd_function_s *allocedCmd), 0x564460);
    IW4_FUNCTION(RemoveCommand, void, (const char *cmdName), 0x564490);
}
