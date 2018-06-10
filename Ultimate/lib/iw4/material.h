#pragma once
#include "image.h"
#include "surface.h"
#include "water.h"

struct __declspec(align(8)) MaterialInfo {
    const char* name;
    char gameFlags;
    char sortKey;
    char textureAtlasRowCount;
    char textureAtlasColumnCount;
    GfxDrawSurf drawSurf;
    int surfaceTypeBits;
};

enum MaterialWorldVertexFormat : __int8 {
    MTL_WORLDVERT_TEX_1_NRM_1 = 0x0,
    MTL_WORLDVERT_TEX_2_NRM_1 = 0x1,
    MTL_WORLDVERT_TEX_2_NRM_2 = 0x2,
    MTL_WORLDVERT_TEX_3_NRM_1 = 0x3,
    MTL_WORLDVERT_TEX_3_NRM_2 = 0x4,
    MTL_WORLDVERT_TEX_3_NRM_3 = 0x5,
    MTL_WORLDVERT_TEX_4_NRM_1 = 0x6,
    MTL_WORLDVERT_TEX_4_NRM_2 = 0x7,
    MTL_WORLDVERT_TEX_4_NRM_3 = 0x8,
    MTL_WORLDVERT_TEX_5_NRM_1 = 0x9,
    MTL_WORLDVERT_TEX_5_NRM_2 = 0xA,
    MTL_WORLDVERT_TEX_5_NRM_3 = 0xB,
};

struct MaterialVertexDeclaration {
    char unknown[28];
};

struct MaterialVertexShaderProgram {
    void* CgBinaryProgram_vs;
    int size;
};

struct MaterialVertexShader {
    const char* name;
    MaterialVertexShaderProgram prog;
};

struct MaterialPixelShaderProgram {
    void* CgBinaryProgram_ps;
    int size;
    char unknown[12];
};

struct MaterialPixelShader {
    const char* name;
    MaterialPixelShaderProgram prog;
};

struct MaterialArgumentCodeConst {
    unsigned __int16 index;
    char firstRow;
    char rowCount;
};

union MaterialArgumentDef {
    const float* literalConst;
    MaterialArgumentCodeConst codeConst;
    unsigned int codeSampler;
    unsigned int nameHash;
};

struct MaterialShaderArgument {
    unsigned __int16 type;
    unsigned __int16 dest;
    MaterialArgumentDef u;
};

struct MaterialPass {
    MaterialVertexDeclaration* vertexDecl;
    MaterialVertexShader* vertexShader;
    MaterialPixelShader* pixelShader;
    char perPrimArgCount;
    char perObjArgCount;
    char stableArgCount;
    char customSamplerFlags;
    char precompiledIndex;
    MaterialShaderArgument* args;
};

struct MaterialTechnique {
    const char* name;
    unsigned __int16 flags;
    unsigned __int16 passCount;
    MaterialPass passArray[1];
};

struct MaterialTechniqueSet {
    char* name;
    MaterialWorldVertexFormat worldVertFormat;
    MaterialTechnique* techniques[48];
};

union MaterialTextureDefInfo {
    GfxImage* image;
    water_t* water;
};

struct MaterialTextureDef {
    unsigned int nameHash;
    char nameStart;
    char nameEnd;
    char sampleState;
    char semantic;
    unsigned __int8 isMatureContent;
    unsigned __int8 pad[3];
    MaterialTextureDefInfo u;
};

struct MaterialConstantDef {
    int nameHash;
    char name[12];
    float literal[4];
};

struct GfxStateBits {
    int unknown;
};

struct Material {
    MaterialInfo info;
    char stateBitsEntry[28];
    char textureCount;
    char constantCount;
    char stateBitsCount;
    char stateFlags;
    char cameraRegion;
    MaterialTechniqueSet* techniqueSet;
    MaterialTextureDef* textureTable;
    MaterialConstantDef* constantTable;
    GfxStateBits* stateBitTable;
    const char** unknownXStringArray;
};
