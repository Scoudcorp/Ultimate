#pragma once
#include "util.h"

namespace PlayerCmd {

    IW4_FUNCTION(GiveWeapon, void, (int entref), 0x520000);
    IW4_FUNCTION(SwitchToWeapon, void, (int entref), 0x5207D0);

}
