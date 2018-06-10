#pragma once
#include "gclient.h"

struct scr_entref_t {
    uint16_t entnum;
    uint16_t classnum;
};

enum hitLocation_t {
    HITLOC_NONE = 0x0,
    HITLOC_HELMET = 0x1,
    HITLOC_HEAD = 0x2,
    HITLOC_NECK = 0x3,
    HITLOC_TORSO_UPR = 0x4,
    HITLOC_TORSO_LWR = 0x5,
    HITLOC_R_ARM_UPR = 0x6,
    HITLOC_L_ARM_UPR = 0x7,
    HITLOC_R_ARM_LWR = 0x8,
    HITLOC_L_ARM_LWR = 0x9,
    HITLOC_R_HAND = 0xA,
    HITLOC_L_HAND = 0xB,
    HITLOC_R_LEG_UPR = 0xC,
    HITLOC_L_LEG_UPR = 0xD,
    HITLOC_R_LEG_LWR = 0xE,
    HITLOC_L_LEG_LWR = 0xF,
    HITLOC_R_FOOT = 0x10,
    HITLOC_L_FOOT = 0x11,
    HITLOC_GUN = 0x12,
    HITLOC_NUM = 0x13,
};

enum trType_t {
    TR_STATIONARY = 0x0,
    TR_INTERPOLATE = 0x1,
    TR_LINEAR = 0x2,
    TR_LINEAR_STOP = 0x3,
    TR_SINE = 0x4,
    TR_GRAVITY = 0x5,
    TR_ACCELERATE = 0x6,
    TR_DECELERATE = 0x7,
    TR_PHYSICS = 0x8,
    TR_RAGDOLL = 0x9,
};

struct trajectory_t {
    trType_t trType;
    int trTime;
    int trDuration;
    float trBase[3];
    float trDelta[3];
};

struct LerpEntityStateAnonymous {
    int data[9];
};

struct LerpEntityStateMissile {
    int launchTime;
    int flightMode;
};

struct LerpEntityStateScriptMover {
    int entToTakeMarksFrom;
    int xModelIndex;
    int animIndex;
    int animTime;
};

struct LerpEntityStateSoundBlend {
    int lerp;
};

struct LerpEntityStateLoopFx {
    int cullDist;
    int period;
};

struct LerpEntityStateTurret {
    float gunAngles[3];
    int lastBarrelRotChangeTime;
    int lastBarrelRotChangeRate;
    int lastHeatChangeTime;
    int lastHeatChangeLevel;
};

struct LerpEntityStateVehicle {
    int indices;
    int flags;
    int bodyPitch;
    int bodyRoll;
    int steerYaw;
    int gunPitch;
    int gunYaw;
    int playerIndex;
    int pad;
};

struct LerpEntityStatePlane {
    int ownerNum;
    int enemyIcon;
    int friendIcon;
};

struct LerpEntityStatePlayer {
    int leanf;
    int movementDir;
    int torsoPitch;
    int waistPitch;
    int offhandWeapon;
    int lastSpawnTime;
};

union LerpEntityStateTypeUnion {
    LerpEntityStateTurret turret;
    LerpEntityStateLoopFx loopFx;
    LerpEntityStatePlayer player;
    LerpEntityStateScriptMover scriptMover;
    LerpEntityStateVehicle vehicle;
    LerpEntityStatePlane plane;
    LerpEntityStateMissile missile;
    LerpEntityStateSoundBlend soundBlend;
    LerpEntityStateAnonymous anonymous;
};

struct LerpEntityState {
    int eFlags;
    trajectory_t pos;
    trajectory_t apos;
    LerpEntityStateTypeUnion u;
};

struct entityState_s {
    int number; // 0x0
    int eType; // 0x4
    LerpEntityState lerp; // 0x8
    int time2; // 0x78
    int otherEntityNum; // 0x7C
    int attackerEntityNum; // 0x80
    int groundEntityNum; // 0x84
    int loopSound; // 0x88
    int surfType; // 0x8C
    union {
        int brushmodel;
        int item;
        int xmodel;
        int primaryLight;
    } index;
    int clientNum;
    int iHeadIcon;
    int iHeadIconTeam;
    int solid;
    int eventParm;
    int eventSequence; 
    int events[4];
    int eventParms[4];
    int wes;
    int legsAnim;
    int torsoAnim;
    union {
        int scale;
        int eventParm2;
        int helicopterStage;
    } un1;
    union {
        int hintString;
        int grenadeInPickupRange;
        int vehicleXModel;
    } un2; // 0xDC
    int clientLinkInfo;
    int partBits[6];
};

struct EntHandle {
    uint16_t number;
    uint16_t infoIndex;
};

struct entityShared_t {
    int clientMask;
    char linked;
    char bmodel;
    char svFlags;
    char inuse;
    float mins[3]; // 0x8
    float maxs[3]; // 0x14
    int contents; // 0x20
    float absmin[3]; // 0x24
    float absmax[3]; // 0x30
    float currentOrigin[3]; // 0x3C
    float currentAngles[3]; // 0x48
    EntHandle ownerNum; // 0x54
    int eventTime; // 0x58
};

struct gentity_s {
    entityState_s state;
    entityShared_t shared;
    gclient_s* client;
    char unknown_data2[0xC];
    uint16_t model;
    char physicsObject;
    char takedamage;
    char active;
    char handler;
    char team;
    char freeAfterEvent;
    uint16_t code_classname;
    uint16_t classname;
    uint16_t script_linkname;
    uint16_t target;
    uint16_t targetname;
    int attachIgnoreCollision;
    int spawnFlags;
    int flags;
    int unlinkAfterEvent; // 0x188
    int clipMask;  // 0x18C
    int processedFrame; // 0x190
    EntHandle parent; // 0x194
    int nextthink; // 0x198
    int health; // 0x19C
    int maxhealth; // 0x1A0
    int damage; // 0x1A4
    int count; // 0x1A8
    char __pad[0xC8];

    void cloneBrushModelToScriptModel(gentity_s* brushEntity);
    void draw();
};

const inline gsl::span<gentity_s> g_entities = { reinterpret_cast<gentity_s*>(0x194B9D0), 2048 };

inline gentity_s *g_airdropCollisionBrush = nullptr;

namespace Entity {

    gentity_s * Spawn(const char* modelName, const float* origin, const float* angles);

    gentity_s * SpawnCarePackage(const float* origin, const float* angles);

    void DrawEntityList();
}
