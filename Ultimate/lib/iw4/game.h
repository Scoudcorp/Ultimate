#pragma once
#include "entity.h"
#include "util.h"

enum MeansOfDeath
{
	MOD_UNKNOWN,
	MOD_PISTOL_BULLET,
	MOD_RIFLE_BULLET,
	MOD_EXPLOSIVE_BULLET,
	MOD_GRENADE,
	MOD_GRENADE_SPLASH,
	MOD_PROJECTILE,
	MOD_PROJECTILE_SPLASH,
	MOD_MELEE,
    MOD_HEADSHOT,
	MOD_CRUSH,
    MOD_FALLING,
	MOD_SUICIDE,
	MOD_TRIGGER_HURT,
	MOD_EXPLOSIVE,
	MOD_IMPACT
};

namespace Game {

	IW4_FUNCTION(G_Say, void, (gentity_s* ent, gentity_s* target, int mode, const char* chatText), 0x5260E0);
	IW4_FUNCTION(player_die, void, (gentity_s *self, gentity_s *inflictor, gentity_s *attacker, int damage, MeansOfDeath meansOfDeath, int iWeapon, const float *vDir, hitLocation_t hitLoc, int psTimeOffset), 0x526A00);
    IW4_FUNCTION(GetPlayerViewOrigin, void, (playerState_s *ps, float *origin), 0x51EFB0);
    IW4_FUNCTION(LocationalTrace, void, (trace_t *results, const float *start, const float *end, int passEntityNum, int contentmask, char *priorityMap), 0x52FDF0);

    IW4_FUNCTION(Spawn, gentity_s*, (), 0x54E600);
    IW4_FUNCTION(CallSpawnEntity, int, (gentity_s*), 0x54ABD0);
    IW4_FUNCTION(FreeEntity, void, (gentity_s*), 0x54E870);
    IW4_FUNCTION(SetModel, void, (gentity_s *ent, const char *modelName), 0x54DDB0);

	void Suicide(int32_t index);
}
