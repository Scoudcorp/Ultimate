#pragma once

#include "image.h"
#include "material.h"
#include "model.h"
#include "phys.h"

struct unknownGfxWorldStruct2 {
    int unknownCount;
    int* unknownArray;
    GfxImage* unknownImage;
    int unknown;
};

struct GfxWorldDpvsPlanes {
    int cellCount;
    cplane_s* planes;
    unsigned __int16* nodes;
    unsigned int* sceneEntCellBits;
};

struct GfxAabbTree {
    float mins[3];
    float maxs[3];
    unsigned __int16 childCount;
    unsigned __int16 surfaceCount;
    unsigned __int16 startSurfIndex;
    unsigned __int16 smodelIndexCount;
    unsigned __int16* smodelIndexes;
    int childrenOffset;
};

struct GfxPortalWritable {
    bool isQueued;
    bool isAncestor;
    char recursionDepth;
    char hullPointCount;
    float (*hullPoints)[2];
};

struct DpvsPlane {
    float coeffs[4];
    char side[3];
};

struct GfxPortal {
    GfxPortalWritable writable;
    DpvsPlane plane;
    float (*vertices)[3];
    char unknown[2];
    char vertexCount;
    float hullAxis[2][3];
};

struct GfxCell {
    float mins[3];
    float maxs[3];
    int portalCount;
    GfxPortal* portals;
    char reflectionProbeCount;
    char* reflectionProbes;
};

struct GfxReflectionProbe {
    float offset[3];
};

struct GfxLightmapArray {
    GfxImage* primary;
    GfxImage* secondary;
};

union GfxColor {
    unsigned int packed;
    char array[4];
};

union PackedUnitVec {
    unsigned int packed;
};

struct GfxWorldVertex {
    float xyz[3];
    float binormalSign;
    GfxColor color;
    float texCoord[2];
    float lmapCoord[2];
    PackedUnitVec normal;
    PackedUnitVec tangent;
};

struct D3DResource {
    unsigned int Common;
    unsigned int ReferenceCount;
    unsigned int Fence;
    unsigned int ReadFence;
    unsigned int Identifier;
    unsigned int BaseFlush;
};

union GPUVERTEX_FETCH_CONSTANT {
    unsigned int dword[2];
    union {
        char gap0[4];
        int _bf4;
    } _s1;
};

struct D3DVertexBuffer {
    D3DResource baseclass_0;
    GPUVERTEX_FETCH_CONSTANT Format;
};

struct GfxWorldVertexData {
    GfxWorldVertex* vertices;
    D3DVertexBuffer worldVb;
};

struct GfxWorldVertexLayerData {
    char* data;
    D3DVertexBuffer layerVb;
};

struct D3DIndexBuffer {
    D3DResource baseclass_0;
    unsigned int Address;
    unsigned int Size;
};

struct GfxWorldDraw {
    unsigned int reflectionProbeCount;
    GfxImage** reflectionImages;
    GfxReflectionProbe* reflectionProbes;
    GfxTexture* reflectionProbeTextures;
    int lightmapCount;
    GfxLightmapArray* lightmaps;
    GfxTexture* lightmapPrimaryTextures;
    GfxTexture* lightmapSecondaryTextures;
    GfxImage* skyImage;
    GfxImage* outdoorImage;
    unsigned int vertexCount;
    GfxWorldVertexData vd;
    unsigned int vertexLayerDataSize;
    GfxWorldVertexLayerData vld;
    int indexCount;
    unsigned __int16* indices;
    D3DIndexBuffer indexBuffer;
};

struct GfxLightGridEntry {
    unsigned __int16 colorsIndex;
    char primaryLightIndex;
    char needsTrace;
};

struct GfxLightGridColors {
    char rgb[56][3];
};

struct GfxLightGrid {
    bool hasLightRegions;
    unsigned int sunPrimaryLightIndex;
    unsigned __int16 mins[3];
    unsigned __int16 maxs[3];
    unsigned int rowAxis;
    unsigned int colAxis;
    unsigned __int16* rowDataStart;
    unsigned int rawRowDataSize;
    char* rawRowData;
    unsigned int entryCount;
    GfxLightGridEntry* entries;
    unsigned int colorCount;
    GfxLightGridColors* colors;
};

struct GfxBrushModelWritable {
    float mins[3];
    float maxs[3];
};

struct GfxBrushModel {
    GfxBrushModelWritable writable;
    float bounds[2][3];
    unsigned int surfaceCount;
    unsigned int startSurfIndex;
};

struct MaterialMemory {
    Material* material;
    int memory;
};

struct sunflare_t {
    bool hasValidData;
    Material* spriteMaterial;
    Material* flareMaterial;
    float spriteSize;
    float flareMinSize;
    float flareMinDot;
    float flareMaxSize;
    float flareMaxDot;
    float flareMaxAlpha;
    int flareFadeInTime;
    int flareFadeOutTime;
    float blindMinDot;
    float blindMaxDot;
    float blindMaxDarken;
    int blindFadeInTime;
    int blindFadeOutTime;
    float glareMinDot;
    float glareMaxDot;
    float glareMaxLighten;
    int glareFadeInTime;
    int glareFadeOutTime;
    float sunFxPosition[3];
};

struct XModelDrawInfo {
    unsigned __int16 lod;
    unsigned __int16 surfId;
};

struct GfxSceneDynModel {
    XModelDrawInfo info;
    unsigned __int16 dynEntId;
};

struct BModelDrawInfo {
    unsigned __int16 surfId;
};

struct GfxSceneDynBrush {
    BModelDrawInfo info;
    unsigned __int16 dynEntId;
};

struct GfxShadowGeometry {
    unsigned __int16 surfaceCount;
    unsigned __int16 smodelCount;
    unsigned __int16* sortedSurfIndex;
    unsigned __int16* smodelIndex;
};

struct GfxLightRegionAxis {
    float dir[3];
    float midPoint;
    float halfSize;
};

struct GfxLightRegionHull {
    float kdopMidPoint[9];
    float kdopHalfSize[9];
    unsigned int axisCount;
    GfxLightRegionAxis* axis;
};

struct GfxLightRegion {
    unsigned int hullCount;
    GfxLightRegionHull* hulls;
};

struct GfxStaticModelInst {
    float mins[3];
    float maxs[3];
    GfxColor groundLighting;
};

struct srfTriangles_t {
    int vertexLayerData;
    int firstVertex;
    unsigned __int16 vertexCount;
    unsigned __int16 triCount;
    int baseIndex;
};

struct GfxSurface {
    srfTriangles_t tris;
    Material* material;
    char lightmapIndex;
    char reflectionProbeIndex;
    char primaryLightIndex;
    bool castsSunShadow;
};

struct GfxCullGroup {
    float mins[3];
    float maxs[3];
    int surfaceCount;
    int startSurfIndex;
};

struct GfxPackedPlacement {
    float origin[3];
    PackedUnitVec axis[3];
    float scale;
};

struct GfxStaticModelDrawInst {
    GfxPackedPlacement placement;
    XModel* model;
    float cullDist;
    char reflectionProbeIndex;
    char primaryLightIndex;
    unsigned __int16 lightingHandle;
    char flags;
};

struct GfxWorldDpvsStatic {
    unsigned int smodelCount;
    unsigned int staticSurfaceCount;
    unsigned int litSurfsBegin;
    unsigned int litSurfsEnd;
    char unknown1[32];
    char* smodelVisData[3];
    char* surfaceVisData[3];
    unsigned __int16* sortedSurfIndex;
    GfxStaticModelInst* smodelInsts;
    GfxSurface* surfaces;
    GfxCullGroup* cullGroups;
    GfxStaticModelDrawInst* smodelDrawInsts;
    GfxDrawSurf* surfaceMaterials;
    unsigned int* surfaceCastsSunShadow;
    volatile int usageCount;
};

struct GfxWorldDpvsDynamic {
    unsigned int dynEntClientWordCount[2];
    unsigned int dynEntClientCount[2];
    unsigned int* dynEntCellBits[2];
    char* dynEntVisData[2][3];
};

struct GfxWorld {
    const char* name;
    const char* baseName;
    int planeCount;
    int nodeCount;
    int unknown1;
    unsigned int unknownCount1;
    unknownGfxWorldStruct2* unknownStructs1;
    char unknown2[24];
    GfxWorldDpvsPlanes dpvsPlanes;
    char* unknown3;
    GfxAabbTree* aabbTree;
    GfxCell* cells;
    GfxWorldDraw worldDraw;
    GfxLightGrid lightGrid;
    int modelCount;
    GfxBrushModel* models;
    float mins[3];
    float maxs[3];
    unsigned int checksum;
    int materialMemoryCount;
    MaterialMemory* materialMemory;
    sunflare_t sun;
    unsigned int* cellCasterBits[2];
    GfxSceneDynModel* sceneDynModel;
    GfxSceneDynBrush* sceneDynBrush;
    unsigned int* primaryLightEntityShadowVis;
    unsigned int* primaryLightDynEntShadowVis[2];
    char* primaryLightForModelDynEnt;
    GfxShadowGeometry* shadowGeom;
    GfxLightRegion* lightRegion;
    GfxWorldDpvsStatic dpvs;
    GfxWorldDpvsDynamic dpvsDyn;
    unsigned int unknownCount2;
    char* unknown4;
    int unknown5;
};
