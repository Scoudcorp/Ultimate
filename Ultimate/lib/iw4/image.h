#pragma once

struct CardMemory {
    int platform[1];
};

typedef char GfxTexture[52];

struct GfxImage {
    GfxTexture texture;
    char unknown[4];
    char mapType;
    char semantic;
    char category;
    char flags;
    CardMemory cardMemory;
    unsigned __int16 width;
    unsigned __int16 height;
    unsigned __int16 depth;
    char mipmap;
    bool streaming;
    char* pixels;
    char unknownData[32];
    const char* name;
};
