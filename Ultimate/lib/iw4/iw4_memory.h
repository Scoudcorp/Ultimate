#pragma once
#include "util.h"

namespace Memory {

    IW4_FUNCTION(HunkUserAlloc, int, (void *user, int size, int alignment), 0x5B83F0);

}
