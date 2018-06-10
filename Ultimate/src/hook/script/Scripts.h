#pragma once
#include <iw4/script.h>

using ScriptInternalFunction = bool (*)(scr_entref_t);

namespace Proxies {

	bool GiveWeaponControl(scr_entref_t entref);
	bool SetSpawnWeaponControl(scr_entref_t entref);
	bool SetClientDvar(scr_entref_t entref);
	bool SetPerk(scr_entref_t entref);
	bool Spawn(scr_entref_t entref);
	bool ExitLevel(scr_entref_t entref);
    bool GetEntArray(scr_entref_t entref);
    bool CloneBrushmodelToScriptmodel(scr_entref_t entref);
}
