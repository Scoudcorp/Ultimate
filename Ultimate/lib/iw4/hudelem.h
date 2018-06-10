#pragma once
#include "iw_string.h"
#include "util.h"

enum he_type_t : __int32 {
    HE_TYPE_FREE = 0x0,
    HE_TYPE_TEXT = 0x1,
    HE_TYPE_VALUE = 0x2,
    HE_TYPE_PLAYERNAME = 0x3,
    HE_TYPE_MATERIAL = 0x4,
    HE_TYPE_TIMER_DOWN = 0x5,
    HE_TYPE_TIMER_UP = 0x6,
    HE_TYPE_TIMER_STATIC = 0x7,
    HE_TYPE_TENTHS_TIMER_DOWN = 0x8,
    HE_TYPE_TENTHS_TIMER_UP = 0x9,
    HE_TYPE_TENTHS_TIMER_STATIC = 0xA,
    HE_TYPE_CLOCK_DOWN = 0xB,
    HE_TYPE_CLOCK_UP = 0xC,
    HE_TYPE_WAYPOINT = 0xD,
    HE_TYPE_MAPNAME = 0xE,
    HE_TYPE_GAMETYPE = 0xF,
    HE_TYPE_COUNT = 0x10,
};

struct color_t {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

union hudelem_color_t {
    color_t color;
    uint32_t rgba;
};

struct hudelem_s {
    he_type_t type;
    float x;
    float y;
    float z;
    int targetEntNum;
    float fontScale;
    float fromFontScale;
    float fontScaleStartTime;
    float fontScaleTime;
    int font;
    int alignOrg;
    int alignScreen;
    hudelem_color_t color;
    hudelem_color_t fromColor;
    int fadeStartTime;
    int fadeTime;
    int label;
    int width;
    int height;
    int materialIndex;
    int fromWidth;
    int fromHeight;
    int scaleStartTime;
    int scaleTime;
    float fromX;
    float fromY;
    int fromAlignOrg;
    int fromAlignScreen;
    int moveStartTime;
    int moveTime;
    int time;
    int duration;
    float value;
    int text;
    float sort;
    hudelem_color_t glowColor;
    int fxBirthTime;
    int fxLetterTime;
    int fxDecayStartTime;
    int fxDecayDuration;
    int soundID;
    int flags;

    void setText(const char *format, ...);
};

struct game_hudelem_s {
    hudelem_s hud;
    int clientNum;
    int team;
    int archived;
};

namespace Hud {

    IW4_FUNCTION(Alloc, game_hudelem_s *, (int clientNum, int teamNum), 0x529550);
    IW4_FUNCTION(Free, void, (game_hudelem_s *hud), 0x54ADD0);

}
