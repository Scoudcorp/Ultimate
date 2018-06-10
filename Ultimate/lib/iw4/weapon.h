#pragma once
#include "gsl/span.h"
#include "material.h"
#include "model.h"
#include "sound.h"
#include <string>
#include <string_view>

enum playerAnimType_t {
    none = 0x0,
    other = 0x1,
    pistol = 0x2,
    smg = 0x3,
    autorifle = 0x4,
    mg = 0x5,
    sniper = 0x6,
    rocketlauncher = 0x7,
    plosive = 0x8,
    grenade = 0x9,
    turret = 0xA,
    c4 = 0xB,
    m203 = 0xC,
    hold = 0xD,
    briefcase = 0xE,
    laptop = 0x10,
    throwingknife = 0x11,
};

enum weapType_t {
    WEAPTYPE_BULLET = 0x0,
    WEAPTYPE_GRENADE = 0x1,
    WEAPTYPE_PROJECTILE = 0x2,
    WEAPTYPE_RIOTSHIELD = 0x3,
    WEAPTYPE_MAX = 0x4,
};

enum weapClass_t {
    WEAPCLASS_RIFLE = 0x0,
    WEAPCLASS_SNIPER = 0x1,
    WEAPCLASS_MG = 0x2,
    WEAPCLASS_SMG = 0x3,
    WEAPCLASS_SPREAD = 0x4,
    WEAPCLASS_PISTOL = 0x5,
    WEAPCLASS_GRENADE = 0x6,
    WEAPCLASS_ROCKETLAUNCHER = 0x7,
    WEAPCLASS_TURRET = 0x8,
    WEAPCLASS_THROWINGKNIFE = 0x9,
    WEAPCLASS_NON_PLAYER = 0xA,
    WEAPCLASS_ITEM = 0xB,
    WEAPCLASS_MAX = 0xC,
};

enum PenetrateType {
    PENETRATE_TYPE_NONE = 0x0,
    PENETRATE_TYPE_SMALL = 0x1,
    PENETRATE_TYPE_MEDIUM = 0x2,
    PENETRATE_TYPE_LARGE = 0x3,
    PENETRATE_TYPE_COUNT = 0x4,
};

enum weapInventoryType_t {
    WEAPINVENTORY_PRIMARY = 0x0,
    WEAPINVENTORY_OFFHAND = 0x1,
    WEAPINVENTORY_ITEM = 0x2,
    WEAPINVENTORY_ALTMODE = 0x3,
    WEAPINVENTORY_EXCLUSIVE = 0x4,
    WEAPINVENTORY_SCAVENGER = 0x5,
    WEAPINVENTORY_MAX = 0x6,
};

enum weapFireType_t {
    WEAPON_FIRETYPE_FULLAUTO = 0x0,
    WEAPON_FIRETYPE_SINGLESHOT = 0x1,
    WEAPON_FIRETYPE_BURSTFIRE2 = 0x2,
    WEAPON_FIRETYPE_BURSTFIRE3 = 0x3,
    WEAPON_FIRETYPE_BURSTFIRE4 = 0x4,
    WEAPON_FIRETYPE_DOUBLE_BARREL = 0x5,
    WEAPON_FIRETYPE_MAX = 0x6,
};

enum OffhandClass {
    OFFHAND_CLASS_NONE = 0x0,
    OFFHAND_CLASS_FRAG_GRENADE = 0x1,
    OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
    OFFHAND_CLASS_FLASH_GRENADE = 0x3,
    OFFHAND_CLASS_MAX = 0x4,
};

enum weapStance_t {
    WEAPSTANCE_STAND = 0x0,
    WEAPSTANCE_DUCK = 0x1,
    WEAPSTANCE_PRONE = 0x2,
    WEAPSTANCE_NUM = 0x3,
};

struct FxEffectDef {
    const char* name;
    int flags;
    int totalSize;
    int msecLoopingLife;
    int elemDefCountLooping;
    int elemDefCountOneShot;
    int elemDefCountEmission;
    /*FxElemDef*/ void* elemDefs;
};

struct FxImpactEntry {
    FxEffectDef* nonflesh[31];
    FxEffectDef* flesh[4];
};

struct FxImpactTable {
    const char* name;
    FxImpactEntry* table;
};

union snd_alias_list_name {
    char* name;
    snd_alias_list_t* asset;
};

enum activeReticleType_t {
    VEH_ACTIVE_RETICLE_NONE = 0x0,
    VEH_ACTIVE_RETICLE_PIP_ON_A_STICK = 0x1,
    VEH_ACTIVE_RETICLE_BOUNCING_DIAMOND = 0x2,
    VEH_ACTIVE_RETICLE_MAX = 0x3,
};

enum weaponIconRatioType_t {
    WEAPON_ICON_RATIO_1TO1 = 0x0,
    WEAPON_ICON_RATIO_2TO1 = 0x1,
    WEAPON_ICON_RATIO_4TO1 = 0x2,
    WEAPON_ICON_RATIO_COUNT = 0x3,
};

enum ammoCounterClipType_t {
    AMMO_COUNTER_CLIP_NONE = 0x0,
    AMMO_COUNTER_CLIP_MAGAZINE = 0x1,
    AMMO_COUNTER_CLIP_SHORTMAGAZINE = 0x2,
    AMMO_COUNTER_CLIP_SHOTGUN = 0x3,
    AMMO_COUNTER_CLIP_ROCKET = 0x4,
    AMMO_COUNTER_CLIP_BELTFED = 0x5,
    AMMO_COUNTER_CLIP_ALTWEAPON = 0x6,
    AMMO_COUNTER_CLIP_COUNT = 0x7,
};

enum weapOverlayReticle_t {
    WEAPOVERLAYRETICLE_NONE = 0x0,
    WEAPOVERLAYRETICLE_CROSSHAIR = 0x1,
    WEAPOVERLAYRETICLE_NUM = 0x2,
};

enum weapOverlayInterface_t {
    WEAPOVERLAYINTERFACE_NONE = 0x0,
    WEAPOVERLAYINTERFACE_JAVELIN = 0x1,
    WEAPOVERLAYINTERFACE_TURRETSCOPE = 0x2,
    WEAPOVERLAYINTERFACECOUNT = 0x3,
};

enum weapProjExplosion_t {
    WEAPPROJEXP_GRENADE = 0x0,
    WEAPPROJEXP_ROCKET = 0x1,
    WEAPPROJEXP_FLASHBANG = 0x2,
    WEAPPROJEXP_NONE = 0x3,
    WEAPPROJEXP_DUD = 0x4,
    WEAPPROJEXP_SMOKE = 0x5,
    WEAPPROJEXP_HEAVY = 0x6,
    WEAPPROJEXP_NUM = 0x7,
};

enum WeapStickinessType {
    WEAPSTICKINESS_NONE = 0x0,
    WEAPSTICKINESS_ALL = 0x1,
    WEAPSTICKINESS_ALL_ORIENT = 0x2,
    WEAPSTICKINESS_GROUND = 0x3,
    WEAPSTICKINESS_GROUND_WITH_YAW = 0x4,
    WEAPSTICKINESS_KNIFE = 0x5,
    WEAPSTICKINESS_COUNT = 0x6,
};

enum guidedMissileType_t {
    MISSILE_GUIDANCE_NONE = 0x0,
    MISSILE_GUIDANCE_SIDEWINDER = 0x1,
    MISSILE_GUIDANCE_HELLFIRE = 0x2,
    MISSILE_GUIDANCE_JAVELIN = 0x3,
    MISSILE_GUIDANCE_MAX = 0x4,
};

struct Tracer {
    const char* name;
    Material* material;
    unsigned int drawInterval;
    float speed;
    float beamLength;
    float beamWidth;
    float screwRadius;
    float screwDist;
    float colors[5][4];
};

struct WeaponDef {
    char* szInternalName;
    XModel* gunXModel;
    XModel* handXModel;
    const char** szXAnimsR;
    const char** szXAnimsL;
    char* szModeName;
    uint16_t (*noteTrackSoundMap[2])[16];
    uint16_t (*noteTrackRumbleMap[2])[16];
    playerAnimType_t playerAnimType;
    weapType_t weaponType;
    weapClass_t weaponClass;
    PenetrateType penetrateType;
    weapInventoryType_t inventoryType;
    weapFireType_t fireType;
    OffhandClass offhandClass;
    weapStance_t stance;
    FxEffectDef* viewFlashEffect;
    FxEffectDef* worldFlashEffect;
    snd_alias_list_name pickUpSound;
    snd_alias_list_name pickUpSoundPlayer;
    snd_alias_list_name ammoPickupSound;
    snd_alias_list_name ammoPickupSoundPlayer;
    snd_alias_list_name projectileSound;
    snd_alias_list_name pullbackSound;
    snd_alias_list_name pullbackSoundPlayer;
    snd_alias_list_name fireSound;
    snd_alias_list_name fireSoundPlayer;
    snd_alias_list_name fireSoundPlayerAkimbo;
    snd_alias_list_name loopFireSound;
    snd_alias_list_name loopFireSoundPlayer;
    snd_alias_list_name stopFireSound;
    snd_alias_list_name stopFireSoundPlayer;
    snd_alias_list_name lastShotSound;
    snd_alias_list_name lastShotSoundPlayer;
    snd_alias_list_name emptyFireSound;
    snd_alias_list_name emptyFireSoundPlayer;
    snd_alias_list_name meleeSwipeSound;
    snd_alias_list_name meleeSwipeSoundPlayer;
    snd_alias_list_name meleeHitSound;
    snd_alias_list_name meleeMissSound;
    snd_alias_list_name rechamberSound;
    snd_alias_list_name rechamberSoundPlayer;
    snd_alias_list_name reloadSound;
    snd_alias_list_name reloadSoundPlayer;
    snd_alias_list_name reloadEmptySound;
    snd_alias_list_name reloadEmptySoundPlayer;
    snd_alias_list_name reloadStartSound;
    snd_alias_list_name reloadStartSoundPlayer;
    snd_alias_list_name reloadEndSound;
    snd_alias_list_name reloadEndSoundPlayer;
    snd_alias_list_name detonateSound;
    snd_alias_list_name detonateSoundPlayer;
    snd_alias_list_name nightVisionWearSound;
    snd_alias_list_name nightVisionWearSoundPlayer;
    snd_alias_list_name nightVisionRemoveSound;
    snd_alias_list_name nightVisionRemoveSoundPlayer;
    snd_alias_list_name altSwitchSound;
    snd_alias_list_name altSwitchSoundPlayer;
    snd_alias_list_name raiseSound;
    snd_alias_list_name raiseSoundPlayer;
    snd_alias_list_name firstRaiseSound;
    snd_alias_list_name firstRaiseSoundPlayer;
    snd_alias_list_name putawaySound;
    snd_alias_list_name putawaySoundPlayer;
    snd_alias_list_name scanSound;
    snd_alias_list_name* bounceSound;
    FxEffectDef* viewShellEjectEffect;
    FxEffectDef* worldShellEjectEffect;
    FxEffectDef* viewLastShotEjectEffect;
    FxEffectDef* worldLastShotEjectEffect;
    Material* reticleCenter;
    Material* reticleSide;
    int iReticleCenterSize;
    int iReticleSideSize;
    int iReticleMinOfs;
    activeReticleType_t activeReticleType;
    float vStandMove[3];
    float vStandRot[3];
    float vStrafeMove[3];
    float vStrafeRot[3];
    float vDuckedOfs[3];
    float vDuckedMove[3];
    float vDuckedRot[3];
    float vProneOfs[3];
    float vProneMove[3];
    float vProneRot[3];
    float fPosMoveRate;
    float fPosProneMoveRate;
    float fStandMoveMinSpeed;
    float fDuckedMoveMinSpeed;
    float fProneMoveMinSpeed;
    float fPosRotRate;
    float fPosProneRotRate;
    float fStandRotMinSpeed;
    float fDuckedRotMinSpeed;
    float fProneRotMinSpeed;
    XModel* worldModel;
    XModel* worldClipModel;
    XModel* rocketModel;
    XModel* knifeModel;
    XModel* worldKnifeModel;
    Material* hudIcon;
    weaponIconRatioType_t hudIconRatio;
    Material* pickupIcon;
    weaponIconRatioType_t pickupIconRatio;
    Material** ammoCounterIcon;
    weaponIconRatioType_t ammoCounterIconRatio;
    ammoCounterClipType_t ammoCounterClip;
    int iStartAmmo;
    const char* szAmmoName;
    int iAmmoIndex;
    const char* szClipName;
    int iClipIndex;
    int iMaxAmmo;
    int shotCount;
    const char* szSharedAmmoCapName;
    int iSharedAmmoCapIndex;
    int iSharedAmmoCap;
    int damage;
    int playerDamage;
    int iMeleeDamage;
    int iDamageType;
    int iFireDelay;
    int iMeleeDelay;
    int meleeChargeDelay;
    int iDetonateDelay;
    int iRechamberTime;
    int iRechamberOneHanded;
    int iRechamberBoltTime;
    int iHoldFireTime;
    int iDetonateTime;
    int iMeleeTime;
    int meleeChargeTime;
    int iReloadTime;
    int reloadShowRocketTime;
    int iReloadEmptyTime;
    int iReloadAddTime;
    int iReloadStartTime;
    int iReloadStartAddTime;
    int iReloadEndTime;
    int iDropTime;
    int iRaiseTime;
    int iAltDropTime;
    int quickDropTime;
    int quickRaiseTime;
    int iFirstRaiseTime;
    int iEmptyRaiseTime;
    int iEmptyDropTime;
    int sprintInTime;
    int sprintLoopTime;
    int sprintOutTime;
    int stunnedTimeBegin;
    int stunnedTimeLoop;
    int stunnedTimeEnd;
    int nightVisionWearTime;
    int nightVisionWearTimeFadeOutEnd;
    int nightVisionWearTimePowerUp;
    int nightVisionRemoveTime;
    int nightVisionRemoveTimePowerDown;
    int nightVisionRemoveTimeFadeInStart;
    int fuseTime;
    int aifuseTime;
    float autoAimRange;
    float aimAssistRange;
    float aimAssistRangeAds;
    float aimPadding;
    float enemyCrosshairRange;
    float moveSpeedScale;
    float adsMoveSpeedScale;
    float sprintDurationScale;
    float adsZoomInFrac;
    float adsZoomOutFrac;
    Material* AdsOverlayShader;
    Material* AdsOverlayShaderLowRes;
    Material* AdsOverlayShaderEMP;
    Material* AdsOverlayShaderEMPLowRes;
    weapOverlayReticle_t adsOverlayReticle;
    weapOverlayInterface_t adsOverlayInterface;
    float adsOverlayWidth;
    float adsOverlayHeight;
    float adsOverlayWidthSplitscreen;
    float adsOverlayHeightSplitscreen;
    float fAdsBobFactor;
    float fAdsViewBobMult;
    float fHipSpreadStandMin;
    float fHipSpreadDuckedMin;
    float fHipSpreadProneMin;
    float hipSpreadStandMax;
    float hipSpreadDuckedMax;
    float hipSpreadProneMax;
    float fHipSpreadDecayRate;
    float fHipSpreadFireAdd;
    float fHipSpreadTurnAdd;
    float fHipSpreadMoveAdd;
    float fHipSpreadDuckedDecay;
    float fHipSpreadProneDecay;
    float fHipReticleSidePos;
    float fAdsIdleAmount;
    float fHipIdleAmount;
    float adsIdleSpeed;
    float hipIdleSpeed;
    float fIdleCrouchFactor;
    float fIdleProneFactor;
    float fGunMaxPitch;
    float fGunMaxYaw;
    float swayMaxAngle;
    float swayLerpSpeed;
    float swayPitchScale;
    float swayYawScale;
    float swayHorizScale;
    float swayVertScale;
    float swayShellShockScale;
    float adsSwayMaxAngle;
    float adsSwayLerpSpeed;
    float adsSwayPitchScale;
    float adsSwayYawScale;
    float adsSwayHorizScale;
    float adsSwayVertScale;
    float adsViewErrorMin;
    float adsViewErrorMax;
    PhysCollMap* collisions;
    float dualWieldViewModelOffset;
    weaponIconRatioType_t killIconRatio;
    int iReloadAmmoAdd;
    int iReloadStartAdd;
    int iDropAmmoMin;
    int ammoDropClipPercentMin;
    int ammoDropClipPercentMax;
    int iExplosionRadius;
    int iExplosionRadiusMin;
    int iExplosionInnerDamage;
    int iExplosionOuterDamage;
    float damageConeAngle;
    float bulletExplDmgMult;
    float bulletExplRadiusMult;
    int iProjectileSpeed;
    int iProjectileSpeedUp;
    int iProjectileSpeedForward;
    int iProjectileActivateDist;
    float projLifetime;
    float timeToAccelerate;
    float projectileCurvature;
    XModel* projectileModel;
    weapProjExplosion_t projExplosiveType;
    FxEffectDef* projExplosionEffect;
    FxEffectDef* projDudEffect;
    snd_alias_list_name projExplosionSound;
    snd_alias_list_name projDudSound;
    WeapStickinessType stickiness;
    float lowAmmoWarningThreshold;
    float ricochetChance;
    float* parallelBounce;
    float* perpendicularBounce;
    FxEffectDef* projTrailEffect;
    FxEffectDef* projBeaconEffect;
    float vProjectileColor[3];
    guidedMissileType_t guidedMissileType;
    float maxSteeringAccel;
    float projIgnitionDelay;
    FxEffectDef* projIgnitionEffect;
    snd_alias_list_name projIgnitionSound;
    float fAdsAimPitch;
    float fAdsCrosshairInFrac;
    float fAdsCrosshairOutFrac;
    int adsGunKickReducedKickBullets;
    float adsGunKickReducedKickPercent;
    float fAdsGunKickPitchMin;
    float fAdsGunKickPitchMax;
    float fAdsGunKickYawMin;
    float fAdsGunKickYawMax;
    float fAdsGunKickAccel;
    float fAdsGunKickSpeedMax;
    float fAdsGunKickSpeedDecay;
    float fAdsGunKickStaticDecay;
    float fAdsViewKickPitchMin;
    float fAdsViewKickPitchMax;
    float fAdsViewKickYawMin;
    float fAdsViewKickYawMax;
    float fAdsViewScatterMin;
    float fAdsViewScatterMax;
    float fAdsSpread;
    int hipGunKickReducedKickBullets;
    float hipGunKickReducedKickPercent;
    float fHipGunKickPitchMin;
    float fHipGunKickPitchMax;
    float fHipGunKickYawMin;
    float fHipGunKickYawMax;
    float fHipGunKickAccel;
    float fHipGunKickSpeedMax;
    float fHipGunKickSpeedDecay;
    float fHipGunKickStaticDecay;
    float fHipViewKickPitchMin;
    float fHipViewKickPitchMax;
    float fHipViewKickYawMin;
    float fHipViewKickYawMax;
    float fHipViewScatterMin;
    float fHipViewScatterMax;
    float fightDist;
    float maxDist;
    const char* accuracyGraphName[2];
    float* accuracyGraphKnots[2];
    float* originalAccuracyGraphKnots[2];
    __int16 accuracyGraphKnotCount;
    __int16 originalAccuracyGraphKnotCount;
    int iPositionReloadTransTime;
    float leftArc;
    float rightArc;
    float topArc;
    float bottomArc;
    float accuracy;
    float aiSpread;
    float playerSpread;
    float minVertTurnSpeed;
    float minHorTurnSpeed;
    float maxVertTurnSpeed;
    float maxHorTurnSpeed;
    float pitchConvergenceTime;
    float yawConvergenceTime;
    float suppressTime;
    float maxRange;
    float fAnimHorRotateInc;
    float fPlayerPositionDist;
    const char* szUseHintString;
    const char* dropHintString;
    int iUseHintStringIndex;
    int dropHintStringIndex;
    float horizViewJitter;
    float vertViewJitter;
    float scanSpeed;
    float scanAccel;
    int scanPauseTime;
    const char* szScript;
    float fOOPosAnimLength[2];
    int minDamage;
    int minPlayerDamage;
    float maxDamageRange;
    float minDamageRange;
    float destabilizationRateTime;
    float destabilizationCurvatureMax;
    int destabilizeDistance;
    float* locationDamageMultipliers;
    const char* fireRumble;
    const char* meleeImpactRumble;
    Tracer* tracer;
    int turretScopeZoomRate;
    int turretScopeZoomMin;
    int turretScopeZoomMax;
    int turretOverheatUpRate;
    int turretOverheatDownRate;
    int turretOverheatPenalty;
    snd_alias_list_name turretOverheatSound;
    FxEffectDef* turretOverheatEffect;
    char* turretBarrelSpinRumble;
    int turretBarrelSpinUpTime;
    int turretBarrelSpinDownTime;
    int turretBarrelSpinSpeed;
    snd_alias_list_name turretBarrelSpinMaxSnd;
    snd_alias_list_name turretBarrelSpinUpSnds[4];
    snd_alias_list_name turretBarrelSpinDownSnds[4];
    snd_alias_list_name missileConeSoundAlias;
    snd_alias_list_name missileConeSoundAliasAtBase;
    float missileConeSoundRadiusAtTop;
    float missileConeSoundRadiusAtBase;
    float missileConeSoundHeight;
    float missileConeSoundOriginOffset;
    float missileConeSoundVolumescaleAtCore;
    float missileConeSoundVolumescaleAtEdge;
    float missileConeSoundVolumescaleCoreSize;
    float missileConeSoundPitchAtTop;
    float missileConeSoundPitchAtBottom;
    float missileConeSoundPitchTopSize;
    float missileConeSoundPitchBottomSize;
    float missileConeSoundCrossfadeTopSize;
    float missileConeSoundCrossfadeBottomSize;
    bool shareAmmo;
    bool lockonSupported;
    bool requireLockonToFire;
    bool bigExplosion;
    bool noAdsWhenMagEmpty;
    bool avoidDropCleanup;
    bool inheritsPerks;
    bool crosshairColorChange;
    bool rifleBullet;
    bool armorPiercing;
    bool boltAction;
    bool aimDownSight;
    bool rechamberWhileAds;
    bool bBulletExplosiveDamage;
    bool cookOffHold;
    bool clipOnly;
    bool noAmmoPickup;
    bool adsFire;
    bool cancelAutoHolsterWhenEmpty;
    bool disableSwitchToWhenEmpty;
    bool suppressAmmoReserveDisplay;
    bool laserSightDuringNightvision;
    bool markableViewmodel;
    bool noDualWield;
    bool flipKillIcon;
    bool noPartialReload;
    bool segmentedReload;
    bool blocksProne;
    bool silenced;
    bool isRollingGrenade;
    bool projExplosionEffectForceNormalUp;
    bool projImpactExplode;
    bool stickToPlayers;
    bool hasDetonator;
    bool disableFiring;
    bool timedDetonation;
    bool rotate;
    bool holdButtonToThrow;
    bool freezeMovementWhenFiring;
    bool thermalScope;
    bool altModeSameWeapon;
    bool turretBarrelSpinEnabled;
    bool missileConeSoundEnabled;
    bool missileConeSoundPitchshiftEnabled;
    bool missileConeSoundCrossfadeEnabled;
    bool offhandHoldIsCancelable;
};

enum ImpactType {
    IMPACT_TYPE_NONE = 0x0,
    IMPACT_TYPE_BULLET_SMALL = 0x1,
    IMPACT_TYPE_BULLET_LARGE = 0x2,
    IMPACT_TYPE_BULLET_AP = 0x3,
    IMPACT_TYPE_SHOTGUN_FMJ = 0x4,
    IMPACT_TYPE_SHOTGUN = 0x5,
    IMPACT_TYPE_GRENADE_BOUNCE = 0x7,
    IMPACT_TYPE_GRENADE_EXPLODE = 0x8,
    IMPACT_TYPE_ROCKET_EXPLODE = 0x9,
    IMPACT_TYPE_PROJECTILE_DUD = 0xA,
    IMPACT_TYPE_MAX = 0xB,
};

struct WeaponVariantDef {
    char* szInternalName;
    WeaponDef* WeaponDef;
    char* szDisplayName;
    __int16 (*hideTags)[32];
    const char** szXAnims;
    float fAdsZoomFov;
    int iAdsTransInTime;
    int iAdsTransOutTime;
    int iClipSize;
    ImpactType impactType;
    int iFireTime;
    weaponIconRatioType_t dpadIconRatio;
    float fPenetrateMultiplier;
    float fAdsViewKickCenterSpeed;
    float fHipViewKickCenterSpeed;
    const char* szAltWeaponName;
    unsigned int altWeaponIndex;
    int iAltRaiseTime;
    Material* killIcon;
    Material* dpadIcon;
    int unknown8;
    int iFirstRaiseTime;
    int iDropAmmoMax;
    float adsDofStart;
    float adsDofEnd;
    __int16 accuracyGraphKnotCount;
    __int16 originalAccuracyGraphKnotCount;
    float* accuracyGraphKnots[2];
    float* originalAccuracyGraphKnots[2];
    bool motionTracker;
    bool enhanced;
    bool dpadIconShowsAmmo;
};

using BG_WeaponName_f = const char* (*)(int weapon);
const inline auto BG_WeaponName = reinterpret_cast<BG_WeaponName_f>(0x479530);

using BG_FindWeaponIndexForName_f = int (*)(const char* name);
const inline auto BG_FindWeaponIndexForName = reinterpret_cast<BG_FindWeaponIndexForName_f>(0x479540);

std::string TranslateWeaponBase(const std::string_view& weapon);
std::string TranslateWeaponAttachment(const std::string_view& attachment);
std::string TranslatePerk(const std::string_view& perk);

bool IsWeapon(int weaponIndex);
bool IsEquipment(int weaponIndex);
bool IsAkimbo(int weaponIndex);

const inline gsl::span<WeaponDef*> g_weaponDefs = { reinterpret_cast<WeaponDef**>(0x86CE20), 1191 };
