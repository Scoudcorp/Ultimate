#pragma once
#include "math.h"
#include <cstdint>

struct trace_t
{
    float fraction;
    float normal[3];
    int surfaceFlags;
    int contents;
    const char *material;
    int hitType;
    uint16_t hitId;
    uint16_t modelIndex;
    uint16_t partName;
    uint16_t partGroup;
    bool allsolid;
    bool startsolid;
    bool walkable;
    char __padding;
};

struct TraceResult
{
    trace_t m_trace;
    float m_start[3];
    float m_end[3];

    void getHitLocation(float* location);
};

struct IgnoreEntParams
{
    int baseEntity;
    int parentEntity;
    bool ignoreSelf;
    bool ignoreParent;
    bool ignoreSiblings;
    bool ignoreChildren;
};

struct sprintState_t {
    int sprintButtonUpRequired;
    int sprintDelay;
    int lastSprintStart;
    int lastSprintEnd;
    int sprintStartMaxLength;
};

struct mantleState_t {
    float yaw;
    int timer;
    int transIndex;
    int flags;
};

enum weaponstate_t : __int32 {
    WEAPON_READY = 0x0,
    WEAPON_RAISING = 0x1,
    WEAPON_RAISING_ALTSWITCH = 0x2,
    WEAPON_DROPPING = 0x3,
    WEAPON_DROPPING_QUICK = 0x4,
    WEAPON_DROPPING_ALTSWITCH = 0x5,
    WEAPON_FIRING = 0x6,
    WEAPON_RECHAMBERING = 0x7,
    WEAPON_RELOADING = 0x8,
    WEAPON_RELOADING_INTERUPT = 0x9,
    WEAPON_RELOAD_START = 0xA,
    WEAPON_RELOAD_START_INTERUPT = 0xB,
    WEAPON_RELOAD_END = 0xC,
    WEAPON_MELEE_INIT = 0xD,
    WEAPON_MELEE_FIRE = 0xE,
    WEAPON_MELEE_END = 0xF,
    WEAPON_OFFHAND_INIT = 0x10,
    WEAPON_OFFHAND_PREPARE = 0x11,
    WEAPON_OFFHAND_HOLD = 0x12,
    WEAPON_OFFHAND_START = 0x13,
    WEAPON_OFFHAND = 0x14,
    WEAPON_OFFHAND_END = 0x15,
    WEAPON_DETONATING = 0x16,
    WEAPON_SPRINT_RAISE = 0x17,
    WEAPON_SPRINT_LOOP = 0x18,
    WEAPON_SPRINT_DROP = 0x19,
    WEAPON_NIGHTVISION_WEAR = 0x1A,
    WEAPON_NIGHTVISION_REMOVE = 0x1B,
};

struct WeaponState {
    int weapAnim;
    int weaponTime;
    int weaponDelay;
    int weaponRestrictKickTime;
    weaponstate_t weaponstate;
    int weapHandFlags;
    int weaponShotCount;
};

struct AmmoReserve {
    int weapon;
    int reserveAmmo;
};

struct AmmoCurrent {
    int weapon;
    int ammo;
    int akimboAmmo;
};

#pragma pack(1)
struct playerState_s {
    int commandTime;
    int pm_type;
    int bobCycle;
    int pm_flags;
    int otherFlags;
    int linkFlags;
    int pm_time;
    float origin[3];
    float velocity[3];
    int weaponTime;
    int weaponDelay;
    int grenadeTimeLeft;
    int throwBackGrenadeOwner;
    int remoteEyesEnt;
    int remoteEyesTagName;
    int remoteControlEnt;
    int foliageSoundTime;
    int gravity;
    float leanf;
    int speed;
    float delta_angles[3];
    int groundEntityNum;
    float vLadderVec[3];
    int jumpTime;
    float jumpoOriginZ;
    int legsTimer;
    int legsAnim;
    int torsoTimer;
    int torsoAnim;
    int legsAnimDuration;
    int torsoAnimDuration;
    int damageTimer;
    int damageDuration;
    int flinchYawAnim;
    int corspeIndex;
    int movementDir;
    int eFlags;
    int eventSequence;
    int events[4];
    int eventParms[4];
    int oldEventSequence;
    int unpredictableEventSequence;
    int unpredictableEventSequenceOld;
    int unpredictableEvents[4];
    int unpredictableEventParms[4];
    int clientNum;
    int viewModelIndex;
    float viewAngles[3];
    int viewHeightTarget;
    float viewHeightCurrent;
    int viewHeightLerpTime;
    int viewHeightLerpTarget;
    int viewHeightLerpDown;
    float viewAngleClampBase[2];
    float viewAngleClampRange[2];
    int damageEvent;
    int damageYaw;
    int damagePitch;
    int damageCount;
    int kills;
    int health;
    int assists;
    int maxHealth;
    int deaths;
    float proneDirection;
    float proneDirectionPitch;
    float proneTorsoPitch;
    int viewlocked;
    int viewlocked_entNum;
    char pad_0x0174[68];
    sprintState_t sprintState;
    float holdBreathScale;
    int holdBreathTimer;
    float moveSpeedScaleMultiplier;
    mantleState_t mantleState;
    WeaponState weaponState;
    char pad_0x0204[28];
    int weapons[15];
    char pad_0x025C[76];
    int offHandIndex;
    int offhandPrimaryClass;
    int offHandSecondaryClass;
    int weapon;
    int primaryWeaponForAltMode;
    int weapFlags;
    float fWeaponPosFrac;
    float aimSpreadScale;
    int adsDelayTime;
    int spreadOverride;
    int spreadOverrideState;
    int isDualWielding;
    AmmoReserve ammoReserve[15];
    AmmoCurrent ammoCurrent[15];
    char pad_0x0404[20];

    TraceResult getViewTrace(float maxDistance = 900000);
    Direction getViewDirection() const;
};
#pragma pack()
