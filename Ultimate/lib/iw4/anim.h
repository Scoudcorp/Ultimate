#pragma once

union XAnimIndices {
    char* _1;
    unsigned __int16* _2;
    void* data;
};

struct XAnimNotifyInfo {
    unsigned __int16 name;
    float time;
};

typedef unsigned __int16 UShortVec[3];
typedef unsigned __int8 UCharVec[3];

union XAnimDynamicFrames {
    UShortVec* varUShortVector;
    UCharVec* varCharVector;
};

union XAnimDynamicIndicesTrans {
    __int16* varUnsignedShort;
    char* varByte;
};

struct XAnimPartTransFrames {
    float mins[3];
    float size[3];
    XAnimDynamicFrames frames;
    XAnimDynamicIndicesTrans indices;
};

union XAnimPartTransData {
    XAnimPartTransFrames frames;
    float frame0[3];
};

struct XAnimPartTrans {
    __int16 type;
    __int16 subType;
    XAnimPartTransData data;
};

union XAnimDynamicIndices {
    char _1[1];
    unsigned __int16 _2[1];
};

struct XAnimDeltaPartQuatDataFrames {
    __int16 (*frames)[2];
    XAnimDynamicIndices indices;
};

union XAnimDeltaPartQuatData {
    XAnimDeltaPartQuatDataFrames frames;
    __int16 frame0[2];
};

struct XAnimDeltaPartQuat {
    __int16 type;
    __int16 subType;
    XAnimDeltaPartQuatData u;
};

struct XAnimDeltaPart {
    XAnimPartTrans* trans;
    XAnimDeltaPartQuat* quat;
    void* unknown;
};

struct XAnimParts {
    char* name;
    __int16 dataByteCount;
    __int16 dataShortCount;
    __int16 dataIntCount;
    __int16 randomDataByteCount;
    __int16 randomDataIntCount;
    __int16 numframes;
    bool bLoop;
    bool bDelta;
    char boneCount[12];
    char notifyCount;
    char assetType;
    unsigned int randomDataShortCount;
    unsigned int indexCount;
    float framerate;
    float frequency;
    unsigned __int16* names;
    char* dataByte;
    __int16* dataShort;
    int* dataInt;
    __int16* randomDataShort;
    char* randomDataByte;
    int* randomDataInt;
    XAnimIndices indices;
    XAnimNotifyInfo* notify;
    XAnimDeltaPart* deltaPart;
};
