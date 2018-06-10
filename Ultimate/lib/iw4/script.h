#pragma once
#include "entity.h"
#include "util.h"
#include <cstdint>
#include <gsl/span.h>
#include <vector>

struct scr_const_t {
    uint16_t _;
    uint16_t active;
    uint16_t j_spine4;
    uint16_t j_helmet;
    uint16_t j_head;
    uint16_t all;
    uint16_t allies;
    uint16_t angles;
    uint16_t auto_ai;
    uint16_t auto_nonai;
    uint16_t axis;
    uint16_t back;
    uint16_t bad_guys;
    uint16_t bad_path;
    uint16_t begin_firing;
    uint16_t begin_firing_left;
    uint16_t cancel_location;
    uint16_t chest;
    uint16_t confirm_location;
    uint16_t crouch;
    uint16_t current;
    uint16_t damage;
    uint16_t dead;
    uint16_t death;
    uint16_t deathshield;
    uint16_t detonate;
    uint16_t direct;
    uint16_t dlight;
    uint16_t done;
    uint16_t empty;
    uint16_t empty_offhand;
    uint16_t offhand_end;
    uint16_t end_firing;
    uint16_t end_firing_left;
    uint16_t entity;
    uint16_t explode;
    uint16_t failed;
    uint16_t first_person;
    uint16_t forward;
    uint16_t fraction;
    uint16_t free;
    uint16_t goal;
    uint16_t goal_changed;
    uint16_t goal_yaw;
    uint16_t grenade;
    uint16_t grenade_danger;
    uint16_t grenade_fire;
    uint16_t glass_destroyed;
    uint16_t missile_fire;
    uint16_t grenade_pullback;
    uint16_t missile_stuck;
    uint16_t info_notnull;
    uint16_t invisible;
    uint16_t key1;
    uint16_t key2;
    uint16_t killanimscript;
    uint16_t left;
    uint16_t light;
    uint16_t manual;
    uint16_t manual_ai;
    uint16_t movedone;
    uint16_t none;
    uint16_t normal;
    uint16_t origin;
    uint16_t other;
    uint16_t player;
    uint16_t physics_finished;
    uint16_t position;
    uint16_t projectile_impact;
    uint16_t prone;
    uint16_t right;
    uint16_t reload;
    uint16_t reload_start;
    uint16_t result;
    uint16_t reverse;
    uint16_t rocket;
    uint16_t rotatedone;
    uint16_t script_brushmodel;
    uint16_t script_model;
    uint16_t script_origin;
    uint16_t sentry;
    uint16_t sentry_offline;
    uint16_t snd_enveffectsprio_level;
    uint16_t snd_enveffectsprio_shellshock;
    uint16_t snd_channelvolprio_holdbreath;
    uint16_t snd_channelvolprio_pain;
    uint16_t snd_channelvolprio_shellshock;
    uint16_t spawned;
    uint16_t stand;
    uint16_t suppression;
    uint16_t suppression_end;
    uint16_t surfacetype;
    uint16_t tag_aim;
    uint16_t tag_aim_animated;
    uint16_t tag_aim_pivot;
    uint16_t tag_brass;
    uint16_t tag_butt;
    uint16_t tag_clip;
    uint16_t tag_eye;
    uint16_t tag_flash;
    uint16_t tag_flash_silenced;
    uint16_t tag_flash_11;
    uint16_t tag_flash_2;
    uint16_t tag_flash_22;
    uint16_t tag_flash_3;
    uint16_t tag_fx;
    uint16_t tag_inhand;
    uint16_t tag_knife_fx;
    uint16_t tag_laser;
    uint16_t tag_origin;
    uint16_t tag_weapon;
    uint16_t tag_player;
    uint16_t tag_camera;
    uint16_t tag_weapon_left;
    uint16_t tag_weapon_right;
    uint16_t tag_weapon_chest;
    uint16_t tag_stowed_back;
    uint16_t tag_gasmask;
    uint16_t tag_gasmask2;
    uint16_t tag_sync;
    uint16_t tag_screen_tl;
    uint16_t tag_screen_bl;
    uint16_t tag_screen_br;
    uint16_t tag_motion_tracker_fx;
    uint16_t tag_reticle_acog;
    uint16_t tag_reticle_red_dot;
    uint16_t tag_reticle_tavor_scope;
    uint16_t tag_reticle_thermal_scope;
    uint16_t tag_eotech_reticle;
    uint16_t target_script_trigger;
    uint16_t third_person;
    uint16_t top;
    uint16_t touch;
    uint16_t trigger;
    uint16_t trigger_use;
    uint16_t trigger_use_touch;
    uint16_t trigger_damage;
    uint16_t truck_cam;
    uint16_t weapon_change;
    uint16_t weapon_fired;
    uint16_t weapon_switch_started;
    uint16_t weapon_taken;
    uint16_t weapon_dropped;
    uint16_t worldspawn;
    uint16_t flashbang;
    uint16_t flash;
    uint16_t smoke;
    uint16_t frag;
    uint16_t throwingknife;
    uint16_t night_vision_on;
    uint16_t night_vision_off;
    uint16_t MOD_UNKNOWN;
    uint16_t MOD_PISTOL_BULLET;
    uint16_t MOD_RIFLE_BULLET;
    uint16_t MOD_EXPLOSIVE_BULLET;
    uint16_t MOD_GRENADE;
    uint16_t MOD_GRENADE_SPLASH;
    uint16_t MOD_PROJECTILE;
    uint16_t MOD_PROJECTILE_SPLASH;
    uint16_t MOD_MELEE;
    uint16_t MOD_HEAD_SHOT;
    uint16_t MOD_CRUSH;
    uint16_t MOD_FALLING;
    uint16_t MOD_SUICIDE;
    uint16_t MOD_TRIGGER_HURT;
    uint16_t MOD_EXPLOSIVE;
    uint16_t MOD_IMPACT;
    uint16_t script_vehicle;
    uint16_t script_vehicle_collision;
    uint16_t script_vehicle_collmap;
    uint16_t script_vehicle_corpse;
    uint16_t turret_deactivate;
    uint16_t turret_fire;
    uint16_t turret_no_vis;
    uint16_t turret_not_on_target;
    uint16_t turret_on_target;
    uint16_t turret_on_vistarget;
    uint16_t turret_pitch_clamped;
    uint16_t turret_rotate_stopped;
    uint16_t turret_yaw_clamped;
    uint16_t turretstatechange;
    uint16_t turretownerchange;
    uint16_t reached_end_node;
    uint16_t reached_wait_node;
    uint16_t reached_wait_speed;
    uint16_t near_goal;
    uint16_t tag_wheel_front_left;
    uint16_t tag_wheel_front_right;
    uint16_t tag_wheel_back_left;
    uint16_t tag_wheel_back_right;
    uint16_t tag_wheel_middle_left;
    uint16_t tag_wheel_middle_right;
    uint16_t tag_detach;
    uint16_t tag_popout;
    uint16_t tag_body;
    uint16_t tag_turret;
    uint16_t tag_turret_base;
    uint16_t tag_barrel;
    uint16_t front_left;
    uint16_t front_right;
    uint16_t back_left;
    uint16_t back_right;
    uint16_t middle_left;
    uint16_t middle_right;
    uint16_t veh_boatbounce;
    uint16_t veh_collision;
    uint16_t veh_predictedcollision;
    uint16_t veh_leftground;
    uint16_t veh_landed;
    uint16_t veh_jolt;
    uint16_t vehicle_mount;
    uint16_t vehicle_dismount;
    uint16_t constrained;
    uint16_t follow;
    uint16_t j_head_2;
    uint16_t j_neck;
    uint16_t thermal;
    uint16_t primary;
    uint16_t offhand;
    uint16_t item;
    uint16_t altmode;
    uint16_t exclusive;
    uint16_t scavenger;
    uint16_t primaryoffhand;
    uint16_t secondaryoffhand;
    uint16_t actionslot1;
    uint16_t actionslot2;
    uint16_t actionslot3;
    uint16_t actionslot4;
    uint16_t back_low;
    uint16_t back_mid;
    uint16_t back_up;
    uint16_t pelvis;
    uint16_t auto_change;
    uint16_t begin;
    uint16_t call_vote;
    uint16_t freelook;
    uint16_t intermission;
    uint16_t j_mainroot;
    uint16_t manual_change;
    uint16_t menuresponse;
    uint16_t pistol;
    uint16_t plane_waypoint;
    uint16_t playing;
    uint16_t spectator;
    uint16_t spectating_cycle;
    uint16_t vote;
    uint16_t sprint_begin;
    uint16_t sprint_end;
    uint16_t normal_radar;
    uint16_t fast_radar;
    uint16_t tag_engine_left;
    uint16_t tag_engine_right;
    uint16_t slowmo_active;
    uint16_t slowmo_passive;
};

struct VariableStackBuffer {
    const char* pos;
    uint16_t size;
    uint16_t bufLen;
    uint16_t localId;
    char time;
    char buf[1];
};

union VariableUnion {
    int intValue;
    float floatValue;
    unsigned int stringValue;
    const float* vectorValue;
    const char* codePosValue;
    unsigned int pointerValue;
    VariableStackBuffer* stackValue;
    unsigned int entityOffset;
};

enum VariableValueType {
    VARIABLE_VALUE_ENTITY = 0x1,
    VARIABLE_VALUE_STRING = 3,
    VARIABLE_VALUE_INT = 0x6,
};

struct VariableValue {
    VariableUnion u;
    VariableValueType type;
};

struct function_stack_t {
    const char* pos;
    unsigned int localId;
    unsigned int localVarCount;
    VariableValue* top;
    VariableValue* startTop;
};

struct function_frame_t {
    function_stack_t fs;
    int topType;
};

struct scrVmPub_t {
    unsigned int* localVars;
    VariableValue* maxstack;
    int function_count;
    function_frame_t* function_frame;
    VariableValue* top;
    unsigned int inparamcount;
    unsigned int outparamcount;
    function_frame_t function_frame_start[32];
    VariableValue stack[2048];
};

namespace Script {

IW4_FUNCTION(GetNumParam, uint32_t, (), 0x580F30);

IW4_FUNCTION(ClearOutParams, void, (), 0x57F480);

IW4_FUNCTION(GetOffset, VariableUnion, (unsigned int classnum, const char* name), 0x57B920);

IW4_FUNCTION(GetConstString, unsigned int, (unsigned int index), 0x580730);

IW4_FUNCTION(GetString, const char*, (unsigned int index), 0x5808E0);

IW4_FUNCTION(GetInt, int, (unsigned int index), 0x580540);

IW4_FUNCTION(GetEntity, gentity_s*, (unsigned int index), 0x54ADA0);

IW4_FUNCTION(GetEntityIdRef, scr_entref_t, (unsigned int entId), 0x57BC20);

IW4_FUNCTION(GetSelf, unsigned int, (unsigned int threadId), 0x57B630);

IW4_FUNCTION(AddString, void, (const char* value), 0x581100);

IW4_FUNCTION(AddInt, void, (int value), 0x580F40);

IW4_FUNCTION(GetObjectType, unsigned int, (unsigned int id), 0x57B890);

IW4_FUNCTION(CreateCanonicalFilename, unsigned int, (const char* filename), 0x57A980);

IW4_FUNCTION(FindVariable, unsigned int, (unsigned int parentId, unsigned int unsignedValue), 0x57B3D0);

IW4_FUNCTION(GetNewVariable, unsigned int, (unsigned int parentId, unsigned int unsignedValue), 0x57CCB0);

IW4_FUNCTION(RemoveVariable, void, (unsigned int parentId, unsigned int unsignedValue), 0x57CE10);

IW4_FUNCTION(GetVariable, unsigned int, (unsigned int parentId, unsigned int unsignedValue), 0x57CC80);

IW4_FUNCTION(FindObject, unsigned int, (unsigned int id), 0x57B830);

IW4_FUNCTION(GetObject, unsigned int, (unsigned int parentId, unsigned int unsignedValue), 0x57B770);

std::vector<gentity_s*> GetEntArray(const char* key, const char* value);

const inline auto g_scrVmPub = reinterpret_cast<scrVmPub_t*>(0x1FDE0E0);

const inline gsl::span<void (*)(scr_entref_t)> g_interalFunctions = { reinterpret_cast<void (**)(scr_entref_t)>(0x1D96718), 1024 };

const inline auto g_allMethodCount = reinterpret_cast<int32_t*>(0x1D96714);

const inline auto g_scriptStringConstants = reinterpret_cast<scr_const_t*>(0x1B6A980);
}
