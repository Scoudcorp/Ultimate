#pragma once
#include "util.h"

struct enumEntry {
    char* name;
    __int16 index;
    __int16 _pad;

	void draw();
};

struct definedEnum {
    int entryCount;
    int unknown4;
    enumEntry* entries;

	void draw();
};

enum structuredDataType_t {
    STRUCTURED_DATA_INT = 0x0,
    STRUCTURED_DATA_BYTE = 0x1,
    STRUCTURED_DATA_BOOL = 0x2,
    STRUCTURED_DATA_STRING = 0x3,
    STRUCTURED_DATA_ENUM = 0x4,
    STRUCTURED_DATA_STRUCT = 0x5,
    STRUCTURED_DATA_INDEXEDARR = 0x6,
    STRUCTURED_DATA_ENUMARR = 0x7,
    STRUCTURED_DATA_FLOAT = 0x8,
    STRUCTURED_DATA_SHORT = 0x9,
};

struct structuredDataItem_t {
    structuredDataType_t type;

    union {
        int index;
    };
    int offset;

	void draw();
};

struct structureEntry {
    char* name;
    structuredDataItem_t item;

	void draw();
};

struct definedStructure {
    int entryCount;
    structureEntry* entries;
    int size;
    int unknown7;

	void draw();
};

struct structuredDataIndexedArray_t {
    int numItems;
    structuredDataItem_t item;

	void draw();
};

struct structuredDataEnumArray_t {
    int enumIndex;
    structuredDataItem_t item;

	void draw();
};

struct StructuredData {
    int version;
    unsigned int hash;
    int enumCount;
    definedEnum* enums;
    int structureCount;
    definedStructure* structures;
    int indexedArrayCount;
    structuredDataIndexedArray_t* indexedArrays;
    int enumArrayCount;
    structuredDataEnumArray_t* enumArrays;
    structuredDataItem_t rootItem;

	void draw();
};

struct StructuredDataDef {
    char* name;
    int structureCount;
    StructuredData* internalStructure;
};

namespace Structure
{
	IW4_FUNCTION(FindStructuredDataOfSize, StructuredData*, (const char *name, unsigned int availableBytes), 0x5BAA90);
}
