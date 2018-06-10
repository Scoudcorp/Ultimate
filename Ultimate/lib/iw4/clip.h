#pragma once
#include "model.h"
#include "phys.h"
#include "weapon.h"

struct cStaticModel_t {
    XModel* xmodel;
    float origin[3];
    float invScaledAxis[3][3];
    float absmin[3];
    float absmax[3];
};

struct dmaterial_t {
    char* material;
    int surfaceFlags;
    int contentFlags;
};

struct cNode_t {
    cplane_s* plane;
    __int16 children[2];
};

struct cLeaf_t {
    unsigned __int16 firstCollAabbIndex;
    unsigned __int16 collAabbCount;
    int brushContents;
    int terrainContents;
    float mins[3];
    float maxs[3];
    int leafBrushNode;
};

struct cLeafBrushNodeLeaf_t {
    unsigned __int16* brushes;
};

struct cLeafBrushNodeChildren_t {
    float dist;
    float range;
    unsigned __int16 childOffset[2];
};

union cLeafBrushNodeData_t {
    cLeafBrushNodeLeaf_t leaf;
    cLeafBrushNodeChildren_t children;
};

struct cLeafBrushNode_s {
    char axis;
    __int16 leafBrushCount;
    int contents;
    cLeafBrushNodeData_t data;
};

struct CollisionBorder {
    float distEq[3];
    float zBase;
    float zSlope;
    float start;
    float length;
};

struct CollisionPartition {
    char triCount;
    char borderCount;
    int firstTri;
    CollisionBorder* borders;
};

union CollisionAabbTreeIndex {
    int firstChildIndex;
    int partitionIndex;
};

struct CollisionAabbTree {
    float origin[3];
    float halfSize[3];
    unsigned __int16 materialIndex;
    unsigned __int16 childCount;
    CollisionAabbTreeIndex u;
};

struct cmodel_t {
    float mins[3];
    float maxs[3];
    float radius;
    cLeaf_t leaf;
};

struct cbrush_t {
    int contents;
    cbrushside_t* sides;
    cbrushedge_t* edge;
    char unknownData[24];
};

struct unknownInternalMapEnts1 {
    int unknownCount1;
    char* unknownData1;
    int unknownCount2;
    char* unknownData2;
    int unknownCount3;
    char* unknownData3;
};

struct AddonMapEnts
{
	char *name;
	char *entityString;
	int numEntityChars;
	unknownInternalMapEnts1 unknownStruct1;
};

struct Stage {
    char* stageName;
    float offset[3];
    int flags;
};

struct MapEnts {
    char* name;
    char* entityString;
    int numEntityChars;
    unknownInternalMapEnts1 unknownStruct1;
    Stage* stages;
    char unknownCount;
    char _padding[3];
};

struct PhysMass {
    float centerOfMass[3];
    float momentsOfInertia[3];
    float productsOfInertia[3];
};

enum DynEntityType : __int32 {
    DYNENT_TYPE_INVALID = 0x0,
    DYNENT_TYPE_CLUTTER = 0x1,
    DYNENT_TYPE_DESTRUCT = 0x2,
    DYNENT_TYPE_COUNT = 0x3,
};

struct GfxPlacement {
    float quat[4];
    float origin[3];
};

struct DynEntityDef {
    DynEntityType type;
    GfxPlacement pose;
    XModel* xModel;
    unsigned __int16 brushModel;
    unsigned __int16 physicsBrushModel;
    FxEffectDef* destroyFx;
    PhysPreset* physPreset;
    int health;
    PhysMass mass;
    int contents;
};

struct DynEntityPose {
    GfxPlacement pose;
    float radius;
};

struct DynEntityClient {
    int physObjId;
    unsigned __int16 flags;
    unsigned __int16 lightingHandle;
    int health;
};

struct DynEntityColl {
    unsigned __int16 sector;
    unsigned __int16 nextEntInSector;
    float linkMins[2];
    float linkMaxs[2];
};

struct clipMap_t {
    char* name;
    int unknown1;
    int planeCount;
    cplane_s* planes;
    unsigned int numStaticModels;
    cStaticModel_t* staticModelList;
    unsigned int numMaterials;
    dmaterial_t* materials;
    unsigned int numBrushSides;
    cbrushside_t* brushsides;
    unsigned int numBrushEdges;
    cbrushedge_t* brushEdges;
    unsigned int numNodes;
    cNode_t* nodes;
    unsigned int numLeafs;
    cLeaf_t* leafs;
    unsigned int leafbrushNodesCount;
    cLeafBrushNode_s* leafbrushNodes;
    unsigned int numLeafBrushes;
    unsigned __int16* leafbrushes;
    unsigned int numLeafSurfaces;
    unsigned int* leafsurfaces;
    unsigned int vertCount;
    float (*verts)[3];
    int triCount;
    unsigned __int16 (*triIndices)[3];
    char* triEdgeIsWalkable;
    int borderCount;
    CollisionBorder* borders;
    int partitionCount;
    CollisionPartition* partitions;
    int aabbTreeCount;
    CollisionAabbTree* aabbTrees;
    unsigned int numSubModels;
    cmodel_t* cmodels;
    unsigned __int16 numBrushes;
    __int16 unknownCount;
    cbrush_t* brushes;
    char* unknownData2;
    char* unknownData3;
    MapEnts* mapEnts;
    __int16 unknownCount3;
    __int16 unknownCount4;
    char* unknownData4;
    unsigned __int16 dynEntCount[2];
    DynEntityDef* dynEntDefList[2];
    DynEntityPose* dynEntPoseList[2];
    DynEntityClient* dynEntClientList[2];
    DynEntityColl* dynEntCollList[2];
    char unknownData5[52];
};
