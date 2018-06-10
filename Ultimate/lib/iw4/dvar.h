#pragma once
#include "util.h"

struct DvarLimitsEnumeration {
    int stringCount;
    const char** strings;

	int findIndexForString(const char* input);

    void draw();
};

struct DvarLimitsInteger {
    int min;
    int max;

    void draw();
};

struct DvarLimitsValue {
    float min;
    float max;

    void draw();
};

union DvarLimits {
    DvarLimitsEnumeration enumeration;
    DvarLimitsInteger integer;
    DvarLimitsValue value;
    DvarLimitsValue vector;

    void draw();
};

struct DvarValueStringBuf {
    const char* pad;
    char string[12];

    void draw();
};

enum DvarType_t : char {
    DVAR_TYPE_BOOL,
    DVAR_TYPE_FLOAT,
    DVAR_TYPE_FLOAT_2,
    DVAR_TYPE_FLOAT_3,
    DVAR_TYPE_FLOAT_4,
    DVAR_TYPE_INT,
    DVAR_TYPE_ENUM,
    DVAR_TYPE_STRING,
    DVAR_TYPE_FLOAT_3_COLOR,
    DVAR_TYPE_COUNT,
};

union DvarValue {
    bool enabled;
    int integer;
    unsigned int unsignedInt;
    float value;
    float vec2[2];
    float vec3[3];
    float vec4[4];
    const char* string;
    char color[4];

    void draw(DvarType_t type, struct dvar_s* dvar, DvarLimitsEnumeration* enumeration);
};

enum DvarFlags_t : short {
    DVAR_ARCHIVE = 0x1,
    DVAR_LATCH = 0x2,
    DVAR_CHEAT = 0x4,
    DVAR_USER_CREATED = 0x100,
    DVAR_SAVED = 0x200,
    DVAR_SERVERINFO = 0x400,
    DVAR_INIT = 0x800,
    DVAR_CHANGEABLE_RESET = 0x1000,
    DVAR_ROM = 0x2000,
    DVAR_EXTERNAL = 0x4000,
    //DVAR_AUTOEXEC = 0x8000
};


#pragma pack(1)
struct dvar_s {
    const char* name;
    const char* description;
    DvarType_t type;
    DvarFlags_t flags;
    bool modified;
    DvarValue current;
    DvarValue latched;
    DvarValue reset;
    DvarLimits domain;
    dvar_s* next;
    int hashNext;

    void draw();
};
#pragma pack()

enum DvarSetSource {
    DVAR_SOURCE_INTERNAL = 0x0,
    DVAR_SOURCE_EXTERNAL = 0x1,
    DVAR_SOURCE_SCRIPT = 0x2,
};

namespace Dvar {

IW4_FUNCTION(FindDvar, dvar_s*, (const char* dvarName), 0x5BCF30);

IW4_FUNCTION(SetString, void, (dvar_s * dvar, const char* value), 0x5BE5E0);

const inline auto g_dvars = reinterpret_cast<dvar_s**>(0x637C470);
const inline auto g_numDvars = reinterpret_cast<int*>(0x637C448);

inline dvar_s* g_matchedDvars[4096] { nullptr };
inline auto g_numMatchedDvars = 0;

void QueryDvars(const char *text);

void Draw();
}
