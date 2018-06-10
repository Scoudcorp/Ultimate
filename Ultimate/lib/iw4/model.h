#pragma once
#include "material.h"
#include "phys.h"
#include "surface.h"

struct DObjAnimMat
{
	float quat[4];
	float trans[3];
	float transWeight;
};

struct XModelCollSurf
{
	float unknown1;
	int unknown2;
	ModelSurface *collSurf;
	char unknownData[28];
};

typedef char XModelHighMipBounds[36];

struct XBoneInfo
{
	float bounds[2][3];
	float radiusSquared;
};

struct XModel
{
	char *name;
	char numBones;
	char numRootBones;
	char numsurfs;
	char undefined;
	char unknownData1[28];
	unsigned __int16 *boneNames;
	unsigned __int8 *parentList;
	unsigned __int16 *quats;
	float *trans;
	unsigned __int8 *partClassification;
	DObjAnimMat *baseMat;
	Material **materialArray;
	XModelCollSurf collSurfs[4];
	int unknown3;
	XModelHighMipBounds *highMipBounds;
	int unknownDataCount1;
	int unknownInt1;
	XBoneInfo *boneInfo;
	char unknownData3[28];
	__int16 *unknownDataPointer3;
	int unknownInt2;
	PhysPreset *physPreset;
	PhysCollMap *physGeoms;
};
