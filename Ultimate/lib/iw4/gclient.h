#pragma once

#include "playerstate.h"
#include <gsl/span.h>

enum clientConnected_t : int
{
	CON_DISCONNECTED = 0x0,
	CON_CONNECTING = 0x1,
	CON_CONNECTED = 0x2,
};

enum sessionState_t : int
{
	SESS_STATE_PLAYING = 0x0,
	SESS_STATE_DEAD = 0x1,
	SESS_STATE_SPECTATOR = 0x2,
	SESS_STATE_INTERMISSION = 0x3,
};

struct usercmd_s
{
	char data[44];
};

struct playerTeamState_t
{
	int location;
};

enum team_t
{
	TEAM_FREE = 0x0,
	TEAM_AXIS = 0x1,
	TEAM_ALLIES = 0x2,
	TEAM_SPECTATOR = 0x3,
};

struct clientState_s
{
	int clientIndex;
	team_t team;
	int modelindex;
	int dualWielding;
	int riotShieldNext;
	int attachModelIndex[6];
	int attachTagIndex[6];
	char name[0x20];
	float maxSprintTimeMultiplier;
	int rank;
	int prestige;
	int perks[2];
	int diveState;
	int voiceConnectivityBits;
	char clanAbb[4];
};

#pragma pack(1)
struct clientSession_t {
	sessionState_t sessionState;
	int clientNum;
	int score;
	int deaths;
	int kills;
	int assists;
	__int16 scriptPersID;
	__int16 undefined;
	clientConnected_t connected;
	usercmd_s cmd;
	usercmd_s oldcmd;
	int localClient;
	int predictItemPickup;
	char name[32];
	int maxHealth;							//0x3228
	int enterTime;							//0x322C
	playerTeamState_t teamState;			//0x3230
	int voteCount;							//0x3234
	int teamVoteCount;						//0x3238
	float moveSpeedScaleMultiplier;			//0x323C
	int viewmodelIndex;						//0x3240
	int noSpectate;							//0x3244
	int teamInfo;							//0x3248
	clientState_s _cs;						//0x324C
	char unknown_data6[0x10];				//0x32D0
	int psOffsetTime;
	int hasRadar;							//0x32E4
	int isRadarBlocked;
	char unknown_data5[0x130];				//0x32D0
}; //Size=0x3664
#pragma pack()

struct gclient_s {
    playerState_s playerState;
    clientSession_t clientSession;
    char pad_0x33C4[0x2A8]; //0x33C4
};

const inline gsl::span<gclient_s> g_clients = { reinterpret_cast<gclient_s*>(0x1B0E1C0), 18 };
