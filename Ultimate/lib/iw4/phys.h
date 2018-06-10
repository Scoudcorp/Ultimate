#pragma once

typedef unsigned __int8 cbrushedge_t;

#pragma pack(push, 4)
struct cplane_s {
    float normal[3];
    float dist;
    char type;
    char signbits;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct cbrushside_t {
    cplane_s* plane;
    unsigned int materialNum;
};
#pragma pack(pop)

struct PhysPreset {
    const char* name;
    int type;
    float mass;
    float bounce;
    float friction;
    float bulletForceScale;
    float explosiveForceScale;
    const char* sndAliasPrefix;
    float piecesSpreadFraction;
    float piecesUpwardVelocity;
    bool tempDefaultToCylinder;
};

#pragma pack(push, 4)
struct BrushWrapper {
    float mins[3];
    float maxs[3];
    __int16 cBrushSideCount;
    __int16 unknown1;
    cbrushside_t* brushSideArray;
    cbrushedge_t* brushEdgeArray;
    char unknownData2[24];
    int cBrushEdgeCount;
    cplane_s* cPlane;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct PhysGeomInfo {
    BrushWrapper* wrapper;
    int type;
    float orientation[3][3];
    float offset[3];
    float halfLengths[3];
};
#pragma pack(pop)

#pragma pack(push, 4)
struct PhysCollMap {
    char* name;
    int PhysGeomInfoCount;
    PhysGeomInfo* geomInfo;
    char unknownData1[60];
};
#pragma pack(pop)
