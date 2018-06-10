#pragma once
#include "material.h"

struct glyphs_s {
    unsigned __int16 character;
    unsigned __int8 padLeft;
    unsigned __int8 padTop;
    unsigned __int8 padRight;
    unsigned __int8 width;
    unsigned __int8 height;
    unsigned __int8 const0;
    float uvLeft;
    float uvTop;
    float uvRight;
    float uvBottom;
};

struct Font_s {
    char* fontName;
    int pixelHeight;
    int glyphCount;
    Material* material;
    Material* glowMaterial;
    glyphs_s* glyphs;
};
