#pragma once
#include "image.h"

struct GfxLightImage {
    GfxImage* image;
    char samplerState;
};

struct GfxLightDef {
    const char* name;
    GfxLightImage attenuation;
    int lmapLookupStart;
};
