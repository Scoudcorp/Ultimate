#pragma once

union GFxDrawSurfFields {
    unsigned __int64 unused;
    unsigned __int64 primarySortKey;
    unsigned __int64 surfType;
    unsigned __int64 primaryLightIndex;
    unsigned __int64 prepass;
    unsigned __int64 materialSortedIndex;
    unsigned __int64 customIndex;
    unsigned __int64 reflectionProbeIndex;
    unsigned __int64 objectId;
};

union GfxDrawSurf {
    GFxDrawSurfFields fields;
    unsigned __int64 packed;
};

struct XSurfaceVertexInfo {
    __int16 vertCount[4];
    unsigned __int16* vertsBlend;
};

struct XSurface {
    short pad;
    short numVertices;
    short numPrimitives;
    unsigned char streamHandle;
    char pad2;
    int pad3;
    void* indexBuffer;
    char pad4[12];
    void* vertexBuffer;
    char pad5[32];
};

struct ModelSurface {
    char* name;
    XSurface* xSurficies;
    __int16 xSurficiesCount;
    __int16 _pad;
    char unknown[24];
};
