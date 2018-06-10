#pragma once
#include "anim.h"
#include "clip.h"
#include "font.h"
#include "iw_string.h"
#include "leaderboard.h"
#include "light.h"
#include "loc.h"
#include "menu.h"
#include "model.h"
#include "phys.h"
#include "sound.h"
#include "structure.h"
#include "surface.h"
#include "vehicle.h"
#include "weapon.h"
#include "world.h"

enum XAssetType : int
{
	ASSET_TYPE_XMODELPIECES = 0x0,
	ASSET_TYPE_PHYSPRESET = 0x1,
	ASSET_TYPE_PHYSCONSTRAINTS = 0x2,
	ASSET_TYPE_DESTRUCTIBLEDEF = 0x3,
	ASSET_TYPE_XANIMPARTS = 0x4,
	ASSET_TYPE_XMODEL = 0x5,
	ASSET_TYPE_MATERIAL = 0x6,
	ASSET_TYPE_TECHNIQUE_SET = 0x7,
	ASSET_TYPE_IMAGE = 0x8,
	ASSET_TYPE_SOUND = 0x9,
	ASSET_TYPE_SOUND_PATCH = 0xA,
	ASSET_TYPE_CLIPMAP = 0xB,
	ASSET_TYPE_CLIPMAP_PVS = 0xC,
	ASSET_TYPE_COMWORLD = 0xD,
	ASSET_TYPE_GAMEWORLD_SP = 0xE,
	ASSET_TYPE_GAMEWORLD_MP = 0xF,
	ASSET_TYPE_MAP_ENTS = 0x10,
	ASSET_TYPE_GFXWORLD = 0x11,
	ASSET_TYPE_LIGHT_DEF = 0x12,
	ASSET_TYPE_LOCALIZE_ENTRY = 0x17,
	ASSET_TYPE_WEAPON = 0x14,
	ASSET_TYPE_WEAPONDEF = 0x15,
	ASSET_TYPE_WEAPON_VARIANT = 0x16,
	ASSET_TYPE_UI_MAP = 0x13,
	ASSET_TYPE_FONT = 0x18,
	ASSET_TYPE_MENULIST = 0x19,
	ASSET_TYPE_MENU = 0x1A,
	ASSET_TYPE_SNDDRIVER_GLOBALS = 0x1B,
	ASSET_TYPE_FX = 0x1C,
	ASSET_TYPE_IMPACT_FX = 0x1D,
	ASSET_TYPE_AITYPE = 0x1E,
	ASSET_TYPE_MPTYPE = 0x1F,
	ASSET_TYPE_MPBODY = 0x20,
	ASSET_TYPE_MPHEAD = 0x21,
	ASSET_TYPE_CHARACTER = 0x22,
	ASSET_TYPE_XMODELALIAS = 0x23,
	ASSET_TYPE_RAWFILE = 0x24,
	ASSET_TYPE_STRINGTABLE = 0x25,
	ASSET_TYPE_PACK_INDEX = 0x26,
	ASSET_TYPE_XGLOBALS = 0x27,
	ASSET_TYPE_DDL = 0x28,
	ASSET_TYPE_GLASSES = 0x29,
	ASSET_TYPE_EMBLEMSET = 0x2A,
	ASSET_TYPE_COUNT = 0x2B,
	ASSET_TYPE_STRING = 0x2B,
	ASSET_TYPE_ASSETLIST = 0x2C,
};

struct Rawfile {
    char* name;
    int compressedSize;
    int decompressedSize;
    char* data;
};

union XAssetHeader {
    PhysPreset* physpreset;
    PhysCollMap* phys_collmap;
    XAnimParts* xanim;
    ModelSurface* modelsurfs;
    XModel* xmodel;
    Material* material;
    MaterialPixelShader* pixelshader;
    MaterialTechniqueSet* techset;
    GfxImage* image;
    snd_alias_list_t* sound;
    LoadedSound* loadedSound;
    SndCurve* sndCurve;
    clipMap_t* clipMap;
    MapEnts* mapEnts;
    GfxWorld* gfxWorld;
    GfxLightDef* lightDef;
    Font_s* font;
    MenuList* menuList;
    MenuDefinition* menu;
    LocalizeEntry* localize;
    WeaponVariantDef* weapon;
    SndDriverGlobals* sndDriverGlobals;
    FxEffectDef* fx;
    FxImpactTable* impactFx;
    Rawfile* rawfile;
    StringTable* stringTable;
    LeaderboardDef* leaderboard;
    StructuredDataDef* structuredData;
    Tracer* tracer;
    VehicleDef* vehicle;
    AddonMapEnts* addonEnts;
    void* data;
};
